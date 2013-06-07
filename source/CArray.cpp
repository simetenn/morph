//#pragma once

#include "CArray.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


CArray::CArray(){
	length = 0;
	dataLength = myConstants::constants.ArrayExtraSize;
	array = new double [dataLength];

	for (int i = 0; i < dataLength; i++) {
		array[i] = -1;
	}

	//CMPI();
}


//Create a CArray with a length and no elements
CArray::CArray(int in_length){
	length = in_length;
	dataLength = in_length + myConstants::constants.ArrayExtraSize;
	array = new double [dataLength]; //<- memory leak

	for (int i = 0; i < dataLength; i++) {
		array[i] = -1;
	}
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
	//del();
	//length=0;
	length = in_length;
	dataLength = in_length + myConstants::constants.ArrayExtraSize;

	array = new double [dataLength];

	memcpy(array,in_array,sizeof(double)*(length));

	for (int i = 0; i < length; i++) {
		array[i] = in_array[i];
	}

	//CMPI();
}

//Create an CArray from CArray
CArray::CArray(CArray* inCArray){
	//del();

	length = inCArray->len();
	dataLength = length + myConstants::constants.ArrayExtraSize;
	array = inCArray->CArray2array();
	//CMPI();
}


CArray::~CArray(){
	del();
	//~CMPI(); <-why not working?
}


//Delete all elements in the array and set the length to 0
void CArray::del(){
	length = 0;
	if (array != NULL){
		delete[] array;
		array = NULL;
	}
}


//Delete all elements in the array
void CArray::delArray(){
	if (array != NULL){
		delete[] array;
		array = NULL;
	}
}



//Creates an array, [start, end] with in_length elements
void CArray::linspace(double start, double end, int in_length){
	del();
	length = in_length;
	dataLength = length + myConstants::constants.ArrayExtraSize;

	array = new double [dataLength]; //<- memory leak

	double step = (end-start)/(length-1);
	for (int i = 0; i < length; i++) {
		array[i] = start + i*step;
	}
}


//Print CArray line by line
void CArray::print(){
	for (int i = 0; i < length; i++) {
		cout << array[i] << endl;
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
	for (int i = 0; i< length;i++) {
		sum += array[i];
	}
	return sum;
}

//Return the length of the array
int CArray::len(){
	return length;
}

//Return a given element of the array, the element can be changed
double& CArray::operator[](int element){
	/*if (array == NULL){
	  throw "Array not initialized";
	  }
	  else if (element >= length || element < -length) {
	  throw "Index out of bounds";
	  }
	  else if (element < 0){
	  return array[length+element];
	  }
	  else {*/
	return array[element];
	//}
}


//Get a given element of the array,
double CArray::get(int element){
	/*if (array == NULL){
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
	  else {*/
	return array[element];
	//}
}



//Set a given element of the array,
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

	memcpy(tmp,array,sizeof(double)*(length));

	for (int j =0; j< inArray->len();j++) {
		tmp[length + j] = inArray->get(j);
	}

	return new CArray(length+inArray->len(),tmp); // <- memory leak
}


//Add two CArrays
void CArray::add(CArray* inArray){
	int oldlength = length;

	if (inArray->len() < dataLength-length){
		for (int i = 0; i < inArray->len(); i++){
			array[length+i] = inArray->get(i);
		}
		length += inArray->len();
		return;
	}

	length += inArray->len();
	dataLength = length + myConstants::constants.ArrayExtraSize;

	double* tmp = new double [dataLength];

	memcpy(tmp,array,sizeof(double)*(oldlength));

	if (array != NULL) {
		delete [] array;
	}
	array = tmp;



	for (int j =0; j< inArray->len();j++) {
		array[oldlength + j] = inArray->get(j);
	}
}


//Add an element to CArray at the end
void CArray::push_back(double in_value){
	if (dataLength-length > 0) {
		array[length] = in_value;
		length++;
		return;
	}

	length++;
	dataLength = length + myConstants::constants.ArrayExtraSize;

	double* tmp = new double [dataLength];

	memcpy(tmp,array,sizeof(double)*(length-1));

	tmp[length-1] = in_value;

	if (array != NULL) {
		delete [] array;
	}
	array = tmp;
}


//Add an element to CArray in the front
void CArray::front(double in_value){
	length++;
	if (dataLength-length > 0) {
		for (int i = length; i > 0; i--) {
			array[i] = array[i-1];
		}
		array[0] = in_value;
		return;
	}

	dataLength = length + myConstants::constants.ArrayExtraSize;

	double* tmp = new double [dataLength];

	for (int i = length; i > 0; i--) {
		tmp[i] = array[i-1];
	}
	
	//	memcpy(&tmp[1],array,sizeof(double)*(length));
	tmp[0] = in_value;

	if (array != NULL) {
		delete[] array;
	}

	array = tmp;
}




//Send a CArray from the master processor to a slave processor
void CArray::send(int in_processor){
	CMPI::send_array_master(array, in_processor,length);
}


//Recieve a CArray in the master processor from a slave processor
void CArray::recieve(int in_processor, MPI_Request* Req){
	delArray();

	array = CMPI::receive_array_master(in_processor, length, Req);
	dataLength = length + myConstants::constants.ArrayExtraSize;
}


//Send a CArray from a slave processor to the master process
void CArray::send_slave(){
	CMPI::send_array_slave(array, length);
}


void CArray::send_slave_modified(int inLength){
	inLength = inLength+(1+myConstants::constants.HaloSize)*myConstants::constants.MaxHalos;

	double* tmpArray = new double [inLength];

	memcpy(tmpArray,array,sizeof(double)*(length));

	for (int i = length; i < inLength; i++) {
		tmpArray[i] = 0;
	}


	CMPI::send_array_slave(tmpArray, inLength);

	if(tmpArray != NULL) {
		delete [] tmpArray;
		tmpArray = NULL;
	}
}


//Recieve a CArray from the master in a slave
void CArray::recieve_slave(){
	del();
	array = CMPI::receive_array_slave(length);
	dataLength = length + myConstants::constants.ArrayExtraSize;
}



//Return the pointer to the array in CArray
double* CArray::CArray2array(){
	return array;
}


void CArray::save(string Filename){
	fstream file;
	file.open((myConstants::constants.inData + Filename).c_str(), ios::out);

	//Saves data to file
	for (int i = 0; i < length;i++){
		file << array[i] << endl;
	}
	file.close();
}
