#include <iostream>
//#include <vector>
#include "CMPI.h"

class CArray : public CMPI { 
 public:

  CArray();
  CArray(int in_length);
  //CArray( vector<double> in_vector);
  CArray(int in_length, double* in_array);
  ~CArray();
  
  void linspace(double start, double end, int in_length);
  void print();
  //double sum_MPI(int argc,char **argv);
  double sum();
  int len(); 
  double get(int element);
  void set(int element,double value);
  double& operator[](int element);
  CArray operator+(double number);
  CArray* operator+(CArray* inArray);
  //CArray& operator=(CArray &other);

  void push_back(double in_value);
  
  void send(int in_processor);
  void recieve(int in_processor,MPI_Request* Req);

  void send_slave();
  void recieve_slave();
  void initialize();

  double* CArray2array();

  void print_array();

  CArray* gather_sum();
  
 protected:
  
  int length;
  double* array;

};
