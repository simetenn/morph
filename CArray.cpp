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

void CArray::initialize(){
  length = 0;
  array = NULL;
  CMPI();
}

CArray::CArray(int in_length){
  length = in_length;
  array = new double [length]; //<- memory leak
  CMPI();
}



CArray::CArray(int in_length, double* in_array){
  length = in_length;
  array = in_array;
  CMPI();
}



//Destrutor
CArray::~CArray(){
  if (array != NULL){
    delete[] array;
  }
  //~CMPI(); <-why not working?
}



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



CArray CArray::operator+(double number){
  CArray tmp (length);
  for (int i =0; i< length;i++) {
    tmp.array[i] = array[i] + number;
  }
  return tmp;
}



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



/*CArray& CArray::operator=(const CArray &other){
  length = other.length;
  double array [other.length];
  for (int i = 0; i <  other.length;i++) {
    array[i] = other.array[i];
  }
  cout << array[1] << endl;
  return *this;
  
  }*/



void CArray::send(int in_processor){
  CMPI::send_array_master(array, in_processor,length);
}



void CArray::recieve(int in_processor, MPI_Request* Req){
  //int master_length;
  cout << "in recieve" << endl;
  cout << "length: "<<length << endl;
  array = CMPI::receive_array_master(in_processor, length, Req);
  //return new ACrray(master_length, resArray);
}



/*void CArray::recieve(int in_processor){
  //int master_length;
  array = CMPI::receive_array_master(in_processor, length, Req);
  //return new CArray(master_length, resArray);
  }*/



void CArray::send_slave(){
  CMPI::send_array_slave(array, length);
}



void CArray::recieve_slave(){
  array = CMPI::receive_array_slave(length);
  //return new CArray(slave_length,resArray);}
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
  //delete[] resArray;  
}
