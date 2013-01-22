//#pragma once

#include "CArray.h"
#include <iostream>
#include <stdlib.h>


using namespace std;


CArray::CArray(){
	length = 0;
	array = NULL;
	CMPI();
}


//Create a CArray with a length and no elements
CArray::CArray(int in_length){
	length = in_length;
	array = new double [length]; //<- memory leak
	CMPI();
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
	length = in_length;
	array = in_array;
	//CMPI();
}

CArray::CArray(CArray* inCArray){
	length = inCArray->len();
	array = inCArray->CArray2array();
	//CMPI();
}


CArray::~CArray(){
	if (array != NULL){
		delete[] array;
	}
	//~CMPI(); <-why not working?
}

void CArray::del(){
	if (array != NULL){
		delete[] array;
	}
}


//Creates an array, [start, end] with in_length elements
void CArray::linspace(double start, double end, int in_length){
	length = in_length;
	if (array != NULL){
		delete[] array;
	}
	array = new double [length]; //<- memory leak
	double step = (end-start)/(length-1);
	for (int i = 0; i < length; i++) {
		array[i] = start + i*step;
	}
}


//Print CArray line by line
void CArray::print(){
	for (int i = 0; i < 200; i++) {
		cout<< array[i] << endl;
	}
}


//Print CArray in one line
void CArray::print_array(){
	for (int i = 0;i<length;i++){
		cout << array[i] << ", ";
	}
	cout << endl;
}

//Calculate the sum of the array
double CArray::sum(){
	double sum = 0;
	for (int i =0; i< length;i++) {
		sum += array[i];
	}
	return sum;
}

//Return the length of the array
int CArray::len(){
	return length;
}


double& CArray::operator[](int element){
	if (array == NULL){
		throw "Array not initialized";
	}
	else if (element >= length || element < -length) {
		throw "Index out of bounds";
	}
	else if (element < 0){
		return array[length+element];
	}
	else {
		return array[element];
	}
}

double CArray::get(int element){
	if (array == NULL){
		cout << "Array not initialized" << endl;
		throw "Array not initialized";
	}
	else if (element >= length || element < -length) {
		cout << "Index out of bounds" << endl;
		throw "Index out of bounds";

	}
	else if (element < 0){
		return array[length+element];
	}
	else {
		return array[element];
	}
}



void CArray::set(int element,double value){
	if (element >= length || element < -length) {
		cout << "Index out of bounds" << endl;
		throw "Index out of bounds";
	}
	else {
		array[element] = value;
	}
}



//Add a number to each element of a CArray
CArray CArray::operator+(double number){
	CArray tmp (length);
	for (int i =0; i< length;i++) {
		tmp.array[i] = array[i] + number;
	}
	return tmp;
}


//Add two CArrays
CArray* CArray::operator+(CArray* inArray){
	double tmp[length+inArray->len()];
	for (int i =0; i< length;i++) {
		tmp[i] = array[i];
	}
	for (int j =0; j< inArray->len();j++) {
		tmp[length + j] = inArray->get(j);
	}
	return new CArray(length+inArray->len(),tmp); //<- memory leak
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
	double oldArray [length];
	int oldlength = length;
	
	for (int i = 0;i<length;i++){
		oldArray[i] = array[i];
	}

	length += inArray->len();
	delete[] array;
	array = new double [length];

	for (int i = 0;i<oldlength;i++){
		array[i] = oldArray[i];
	}
	
	for (int j =0; j< inArray->len();j++) {
		array[oldlength + j] = inArray->get(j);
	}
}


//Add an element to CArray at the end
void CArray::push_back(double in_value){
	double oldArray [length];

	for (int i = 0;i<length;i++){
		oldArray[i] = array[i];
	}

	length += 1;
	delete[] array;
	array = new double [length];

	for (int i = 0;i<length-1;i++){
		array[i] = oldArray[i];
	}
	array[length-1] = in_value;
}



//Add an element to CArray in the front
void CArray::front(double in_value){
	double oldArray [length];
	for (int i = 0;i<length;i++){
		oldArray[i] = array[i];
	}

	length += 1;
	delete[] array;
	array = new double [length];

	array[0] = in_value;
	for (int i = 0;i<length-1;i++){
		array[i+1] = oldArray[i];
	}
}





//Send a CArray from the master processor to a slave processor
void CArray::send(int in_processor){
	CMPI::send_array_master(array, in_processor,length);
}


//Recieve a CArray in the master processor from a slave processor
void CArray::recieve(int in_processor, MPI_Request* Req){
	array = CMPI::receive_array_master(in_processor, length, Req);
}


//Send a CArray from a slave processor to the master process
void CArray::send_slave(){
	CMPI::send_array_slave(array, length);
}

void CArray::send_slave_modified(int inLength){
	inLength = inLength+(1+myConstants::constants.HaloSize)*myConstants::constants.MaxHalos;

	double* tmpArray = new double [inLength];

	for (int i = 0; i < length; i++) {
		tmpArray[i] = array[i];
	}
	CMPI::send_array_slave(tmpArray, inLength);
}

//Recieve a CArray from the master in a slave 
void CArray::recieve_slave(){
	array = CMPI::receive_array_slave(length);
}



//Return the pointer to the array in CArray
double* CArray::CArray2array(){
	return array;
}








//specialized, used for testing purposes only
CArray* CArray::gather_sum(){
	int result_length;
	int size = getSize();
	double **results = CMPI::receive_array_master_all(result_length);
	double* resArray = new double [size-1]; // <-- Memory leak

	for (int i = 0;i<size-1;i++){
		resArray[i] = results[i][0];
	}

	CArray* sumArray = new CArray(size-1, resArray);//<- memory leak
	return sumArray;
}


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




