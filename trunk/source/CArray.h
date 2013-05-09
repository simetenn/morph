#include "CMPI.h"
#include <iostream>
#include <string.h>
//#include <vector>


class CArray : public CMPI {
 public:

	CArray();

	//Create a CArray with a length and no elements
	CArray(int in_length);

	//Commented out because CArray is supposed to be low level,
	//using pointers and not the vector class. Can be used if wanted/needed
	//CArray( vector<double> in_vector);

	//Create a CArray from an array
	CArray(int in_length, double* in_array);
	//create a CArray from a CArray
	CArray(CArray* inCArray);

	~CArray();

	//Delete all elements in the array and set the length to 0
	void del();
	//Delete all elements in the array
	void delArray();
	
	//Creates an array, [start, end] with in_length elements
	void linspace(double start, double end, int in_length);

	//Print CArray line by line
	void print();
	//Print CArray in one line
	void print_array();

	//Calculate the sum of the array
	double sum();
	//Return the length of the array
	int len();

	//Set a given element of the array,
	void set(int element,double value);
	//Get a given element of the array,
	double get(int element);
	double& operator[](int element);

	//Add a number to each element of a CArray
	CArray operator+(double number);
	//Add two CArrays
	CArray* operator+(CArray* inArray);
	void add(CArray* inArray);

	//Add an element to CArray at the end
	void push_back(double in_value);
	//Add an element to CArray in the front
	void front(double in_value);


	//Send a CArray from the master processor to a slave processor
	void send(int in_processor);
	//Recieve a CArray in the master processor from a slave processor
	void recieve(int in_processor,MPI_Request* Req);

	//Send a CArray from a slave processor to the master process
	void send_slave();
	void send_slave_modified(int inLength);

	//Recieve a CArray from the master in a slave
	void recieve_slave();


	//Return the pointer to the array in CArray
	double* CArray2array();

 protected:
	int length, dataLength;
	double* array;

};
