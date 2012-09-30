#include "CArray.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//Default constructor
CArray::CArray(){
	length = 0;
	array = NULL;
	CMPI();
}

//Create a CArray with length and no elements
CArray::CArray(int in_length){
	length = in_length;
	array = new double [length]; //<- memory leak
	CMPI();
}

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
	CMPI();
}


//Destrutro
CArray::~CArray(){
	if (array != NULL){
		delete[] array;
	}
	//~CMPI(); <-why not working?
}


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



void CArray::print(){

	for (int i = 0; i < length; i++) {
		cout<< array[i] << endl;
	}
}


double CArray::sum(){
	double sum = 0;
	for (int i =0; i< length;i++) {
		sum += array[i];
	}
	return sum;
}


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



//Add a number to a CArray
CArray CArray::operator+(double number){
	CArray tmp (length);
	for (int i =0; i< length;i++) {
		tmp.array[i] = array[i] + number;
	}
	return tmp;
}


//Add two CArrays
CArray* CArray::operator+(CArray* inArray){
	double tmp[length+inArray->length];
	for (int i =0; i< length;i++) {
		tmp[i] = array[i];
	}
	for (int j =0; j< length;j++) {
		tmp[length + j] = inArray->get(j);
	}
	return new CArray(length+inArray->length,tmp); //<- memory leak
}


//Send a CArray from the master processor to a slave processor
void CArray::send(int in_processor){
	CMPI::send_array_master(array, in_processor,length);
}



void CArray::recieve(int in_processor, MPI_Request* Req){
	array = CMPI::receive_array_master(in_processor, length, Req);
}


void CArray::send_slave(){
	CMPI::send_array_slave(array, length);
}



void CArray::recieve_slave(){
	array = CMPI::receive_array_slave(length);
}



void CArray::print_array(){
	for (int i = 0;i<length;i++){
		cout << array[i] << ", ";
	}
	cout << endl;
}



//specialized
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


double* CArray::CArray2array(){
	return array;
}


//CArray& operator=(CArray &other){

//}




/*
  CArray::CArray() : CMPI(argc,argv) {
  length = 0;
  array = NULL;
  }

  CArray::CArray(int in_length) : CMPI(argc, argv) {
  length = in_length;
  array = new double [length];
  }CArray(int in_length);
*/



/*void CArray::recieve(int in_processor){
//int master_length;
array = CMPI::receive_array_master(in_processor, length, Req);
//return new CArray(master_length, resArray);
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


/*CArray& CArray::operator=(const CArray &other){
  length = other.length;
  double array [other.length];
  for (int i = 0; i <  other.length;i++) {
  array[i] = other.array[i];
  }
  cout << array[1] << endl;
  return *this;

  }*/




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
