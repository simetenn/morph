//#pragma once

#include "CArray.h"
#include <iostream>
//#include <stdlib.h>


using namespace std;


CArray::CArray(){
	array.clear();
	array.resize(0);
	//CMPI();
}


//Create a CArray with a length and no elements
CArray::CArray(int in_length){
	array.clear();
	array.resize(in_length);
	//CMPI();
}

//Commented out because CArray is supposed to be low level,
//using pointers and not the vector class. Can be used if wanted/needed
/*CArray::CArray(vector<double> in_vector){
  length = in_vector.size();
  array = new double [length];

  for (int i = 0;i<length;i++){
  array[0] = in_vector[0];
  }

  array = new double [length]; //<- memory leak
  CMPI();
  }
*/



//create a CArray from an array
CArray::CArray(int in_length, double* in_array){
	array.clear();
	array.resize(in_length);
	array.assign(in_array, in_array + in_length);
	//CMPI();
}



CArray::CArray(CArray* inCArray){
	array.clear();
	array = inCArray->getVector();
	//CMPI();
}


CArray::~CArray(){
	//~CMPI(); <-why not working?
}

/*void CArray::del(){
	if (array != NULL){
		delete[] array;
	}
	}*/


vector<double> CArray::getVector(){
	return array;
}

//Creates an array, [start, end] with in_length elements
void CArray::linspace(double start, double end, int in_length){
	//length = in_length;
	//if (array != NULL){
	//	delete[] array;
	//}
	
	//array = new double [length]; //<- memory leak
	array.resize(in_length);
	double step = (end-start)/(in_length-1);
	for (int i = 0; i < in_length; i++) {
		array[i] = start + i*step;
	}
}


//Print CArray line by line
void CArray::print(){
	for (int i = 0; i < array.size(); i++) {
		cout<< array[i] << endl;
	}
}


//Print CArray in one line
void CArray::print_array(){
	for (int i = 0; i < array.size(); i++){
		cout << array[i] << ", ";
	}
	cout << endl;
}

//Calculate the sum of the array
double CArray::sum(){
	double sum = 0;
	for (int i =0; i < array.size();i++) {
		sum += array[i];
	}
	return sum;
}

//Return the length of the array
int CArray::len(){
	return array.size();
}


double& CArray::operator[](int element){
	if (element < 0){
		return array[array.size()+element];
	}
	else {
		return array[element];
	}
}

double CArray::get(int element){
	if (element < 0){
		return array[array.size()+element];
	}
	else {
		return array[element];
	}
}



void CArray::set(int element,double value){
	if (element < 0){
		array[array.size()+element] = value;
	}
	else {
		array[element] = value;
	}
}



//Add a number to each element of a CArray
CArray CArray::operator+(double number){
	CArray tmp (array.size());
	for (int i =0; i< array.size();i++) {
		tmp.array[i] = array[i] + number;
	}
	return tmp;
}


//Add two CArrays
CArray* CArray::operator+(CArray* inArray){
	CArray tmparray(array.size() + inArray->len());
	int tmplength = array.size();
	for (int i =0; i< array.size();i++) {
		tmparray[i] = array[i];
	}
	for (int j =0; j< inArray->len();j++) {
		tmparray[tmplength + j] = inArray->get(j);
	}
	return new CArray(tmparray); //<- memory leak
}

//Something is wrong with this method
//Add two CArrays
/*CArray* CArray::add(CArray* inArray){
	double tmp[length+inArray->len()];
	for (int i =0; i< length;i++) {
		tmp[i] = array[i];
	}
	for (int j =0; j< inArray->len();j++) {
		tmp[length + j] = inArray->get(j);
	}
	
	return new CArray(length+inArray->len(),tmp); //<- memory leak
	}*/

void CArray::add(CArray* inArray){
	int tmplen = array.size();
	array.resize(tmplen + inArray->len());
	for (int i = 0; i < inArray->len(); i++) {
		array[tmplen + i] = inArray->get(i);
	}
}


//Add an element to CArray at the end
void CArray::push_back(double in_value){
	array.push_back(in_value);
}



//Add an element to CArray in the front
void CArray::front(double in_value){
	array.insert(array.begin(), in_value);
}





//Send a CArray from the master processor to a slave processor
void CArray::send(int in_processor){
	cout << "huh?" << array[0] << endl;
	cout << array.size() << endl;
	CMPI::send_array_master(array.data(), in_processor,array.size());
}


//Recieve a CArray in the master processor from a slave processor
void CArray::recieve(int in_processor, MPI_Request* Req){
	int length;
	array.clear();
	double* tmparray = CMPI::receive_array_master(in_processor, length, Req);
	array.resize(length);
	array.assign(tmparray,tmparray+length);
}


//Send a CArray from a slave processor to the master process
void CArray::send_slave(){
	CMPI::send_array_slave(array.data(), array.size());
}



void CArray::send_slave_modified(int inLength){
	inLength += (1+myConstants::constants.HaloSize)*myConstants::constants.MaxHalos;

	double* tmpArray = new double [inLength];

	for (int i = 0; i < array.size(); i++) {
		tmpArray[i] = array[i];
	}

	for (int j = array.size(); j < inLength; j++){
		tmpArray[j] = -1;
	}
	
	CMPI::send_array_slave(tmpArray, inLength);
	
	delete [] tmpArray;
}


//Recieve a CArray from the master in a slave 
void CArray::recieve_slave(){
	int length;
	array.clear();
	double* tmparray = CMPI::receive_array_slave(length);
	array.resize(length);
	cout << "matlab: " << tmparray[3] << endl;
	array.assign(tmparray,tmparray+length);
	cout << "matlab: " << array[3] << endl;


}



//Return the pointer to the array in CArray
double* CArray::CArray2array(){
	return array.data();
}








//specialized, used for testing purposes only
/*CArray* CArray::gather_sum(){
	int result_length;
	int size = getSize();
	double **results = CMPI::receive_array_master_all(result_length);
	double* resArray = new double [size-1]; // <-- Memory leak

	for (int i = 0;i<size-1;i++){
		resArray[i] = results[i][0];
	}

	CArray* sumArray = new CArray(size-1, resArray);//<- memory leak
	return sumArray;
	}*/


/*double CArray::sum_MPI(int argc,char **argv){
  CMPI::initialize_CMPI(argc,argv);
  //Master node

  if (rank == 0) {

  split_array();

  CArray* sumArray = gather_sum();

  return sumArray->sum();
  delete[] sumArray;

  }
  else {
  int slave_length;
  double *slave_array = CMPI::receive_array_slave(slave_length);
  double sum = 0;

  for (int i = 0; i<slave_length;i++){
  sum += slave_array[i];
  }
  CMPI::send_array_slave(&sum, 1);
  delete[] slave_array;
  }


  }*/




