#include "CVector.h"
#include <iostream>
#include <cmath>

using namespace std;



CVector::CVector(){
	_x=_y=_z=0;
}



CVector::CVector(const double& inx, const double& iny, const double& inz){
	_x = inx;
	_y = iny;
	_z = inz;
}


CVector::CVector(vector<double> inVector){
	_x=inVector[0];
	_y=inVector[1];
	_z=inVector[2];
}



CVector::CVector(const CVector& inVector){
	double d = inVector.x();

	_x= inVector.x();
	_y= inVector.y();
	_z= inVector.z();
}



CVector::~CVector(){
}





//Set the elements of a vector
void CVector::Set(const double& inx, const double& iny,const double& inz){
	_x=inx;
	_y=iny;
	_z=inz;
}


//Get a given element of a vector
double& CVector::operator[](int element){
	if (element == 0) return _x;
	if (element == 1) return _y;
	if (element == 2) return _z; 
}


void CVector::operator=(double other){
	_x = _y = _z = other;
}


//Print out a CVector
void CVector::print(){
	cout << "(" << _x<<","<<_y<<","<<_z<<")";
}


//Get the nr of dimensions of a vector
int CVector::getDimensions(){
	return 3;//Dimensions;
}


//Overloaded operators so the basic math operators does
//the corresponding vector operation

//Add two vectors together
CVector CVector::operator+(const CVector& other)const{
	return CVector(_x+other.x(),_y+other.y(),_z+other.z());
}


//Add a number to a vector
CVector CVector::operator+(double number) const{
	return CVector(_x+number,_y+number,_z+number);
}


//Subtract two vectors
CVector CVector::operator-(const CVector& other) const {
	return CVector(_x-other.x(),_y-other.y(),_z-other.z());
}


//Subtract a number from a vector
CVector CVector::operator-(double number) const{
	return CVector(_x-number,_y-number,_z-number);
}


//Divide a vector by a number
CVector CVector::operator/(double number) const{
	return CVector(_x/number,_y/number,_z/number);
}

//Divide a vector by another
CVector CVector::operator/(const CVector& other) const{
	return CVector(_x/other.x(),_y/other.y(),_z/other.z());
}



//Multiply a vector by a number
CVector CVector::operator*(double number) const{
	return CVector(_x*number,_y*number,_z*number);
}


//Multiply a vector by a vector, returning a new vector
CVector CVector::operator*(const CVector& other) const{
	return CVector(_x*other.x(),_y*other.y(),_z*other.z());
}


CVector CVector::sqrt() const{
	return CVector(std::sqrt(_x),std::sqrt(_y),std::sqrt(_z));
}

		
CVector CVector::pow(double element) const{
	return CVector(std::pow(_x,element),std::pow(_y,element),std::pow(_z,element));
}


//Calculate the length of a vector
double CVector::Length() const{
	return std::sqrt(CVector::Length2());
}


//Calculate the length^2 of a vector
double CVector::Length2() const{
	return _x*_x+_y*_y+_z*_z;//sum;
}




//Normalise a vector
CVector CVector::Normalize() const{
	return *this/CVector::Length();
}


//Calculate the cross product of two vectors
CVector CVector::Cross(CVector& other) const{
	return CVector(_y*other.z() -_z*other.y(),_z*other.x() -_x*other.z(),_x*other.y() -_y*other.x());
}



//Calculate the dot product of two vectors
double CVector::Dot(CVector& other) const{
	return _x*other.x() + _y*other.y() + _z*other.z();
}


//Calculate the sum of a vector
double CVector::Sum() const{
	return _x+_y+_z;
}


//Return x,y and z coordinates of the vector
double CVector::x() const{
	return _x;
}

double CVector::y()  const {
	return _y;
}

double CVector::z() const {
	return _z;
}


/*double CVector::Quadrant(){

	if (Vector[0] > 0 &&  Vector[1] > 0 && Vector[2] < 0) return 1;		  //x+,y+,z-
	else if (Vector[0] > 0 &&  Vector[1] < 0 && Vector[2] < 0) return 2;  //x+,y-,z-
	else if (Vector[0] > 0 &&  Vector[1] < 0 && Vector[2] > 0) return 3;  //x+,y-,z+
	else if (Vector[0] < 0 &&  Vector[1] > 0 && Vector[2] > 0) return 4;  //x-,y+,z+
	else if (Vector[0] < 0 &&  Vector[1] > 0 && Vector[2] < 0) return 5;  //x-,y+,z-
	else if (Vector[0] < 0 &&  Vector[1] < 0 && Vector[2] < 0) return 6;  //x-,y-,z-
	else if (Vector[0] < 0 &&  Vector[1] < 0 && Vector[2] > 0) return 7;  //x-,y-,z+
	else return 0;														  //x+,y+,z+
	//The last else might be dangerous
	}*/
