#include <iostream>
#include "CMPI.h"

class CArray : public CMPI {
 public:

  CArray();
  CArray(int in_length);
  CArray(int in_length, double* in_array);
  ~CArray();
  
  void linspace(double start, double end, int in_length);
  void print();
  double sum_MPI(int argc,char **argv);
  double sum();
  double len(); 
  double get(int element);
  double& operator[](int element);
  CArray operator+(double number);
  //CArray& operator=(const CArray &other);
  void split_array();
  CArray* gather_sum();
  
 protected:
  
  int length;
  double* array;

};
