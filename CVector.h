#pragma once

#include <vector>
using namespace std;



//A simple CVector class only used for storing data into when
//reading from a binary file. The data must then be transfered
//into the complete CVector class
class CVector_bare{
 public:
	double x,y,z;
};



class CVector{
 public:

	CVector();
	CVector(double in_x, double in_y, double in_z);
	CVector(vector<double> in_Vector);
	CVector(const CVector& in_Vector);

	~CVector();


	//Set the elements of a vector
	void Set(double x,double y,double z);
	//Get a given element of a vector
	double& operator[](int element);

	//Return x,y and z coordinates of the vector
	double x();
	double y();
	double z();


	//Print out a CVector
	void print();
	//Get the nr of dimensions of a vector
	int getDimensions();


	//Add to vectors together
	CVector operator+(const CVector& other) const;
	//Add a number to a vector
	CVector Add(double number) const;

	//Subtract two vectors
	CVector operator-(const CVector& other) const;
	//Subtract a number from a vector
	CVector Subtract(double number) const;

	//Divide a vector by a number
	CVector operator/(double number) const;
	//Divide a vector by another vector
	CVector operator/(CVector& inVector) const;
	//Multiply a vector by a number
	CVector operator*(double number) const;




	//Calculate the length of a vector
	double Length() const;
	//Calculate the length^2 of a vector
	double Length2() const;

	//Returns a normalized vector
	CVector Normalize() const;

	//Calculate the cross product of two vectors
	CVector Cross(const CVector& other) const;
	//Calculate the dot product of two vectors
	double Dot(const CVector& other) const;


	//Calculate the sum of a vector
	double Sum() const;

	//returns the quadrant the vector is in
	double Quadrant();

 protected:
	int Dimensions;
	vector<double> Vector;


};
