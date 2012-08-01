#include "CVector.h"
#include <iostream>
#include <cmath>

using namespace std;

CVector::CVector(){
  Dimensions = 3;
  Vector.resize(Dimensions);
  //Vector = new double [Dimensions];
  for (int i = 0;i<Dimensions;i++){
    Vector[i] = 0;
  }
}

CVector::CVector(double in_x, double in_y, double in_z){
  Dimensions = 3;
  Vector.resize(Dimensions);
  
  Vector[0] = in_x;
  Vector[1] = in_y;
  Vector[2] = in_z;
}


//Untested
CVector::CVector(vector<double> in_Vector){
  Vector = in_Vector;
  Dimensions =  Vector.size();
}

CVector::CVector(const CVector& in_Vector){
  Vector = in_Vector.Vector;
}


CVector::~CVector(){
  /*if (Vector != NULL){ 
    delete[] Vector;
    }*/
}

void CVector::Set(double x,double y,double z){
  Vector[0] = x;
  Vector[1] = y;
  Vector[2] = z;
}



void CVector::print(){
  //cout << "(" << x << "," << y << "," << z <<")" << endl;
  cout << "(";
  for(int i = 0; i < Dimensions;i++){
    cout << Vector[i];
    if (i != Dimensions - 1){
      cout << ",";
    }
    
  }    
  cout << ")" << endl;
}


double& CVector::operator[](int element){
  /*if (Vector == NULL){
    throw "tArray not initialized";
  }
  else*/
  if (element >= Dimensions || element < -Dimensions) { 
   throw "Index out of bounds";
  }  
 else if (element < 0){
    return Vector[Dimensions+element];
  }
  else {
    return Vector[element];
  }
}

CVector CVector::operator+(const CVector& other) const{
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i] + other.Vector[i];
  }
  return resVector;
  //return CVector (x + other.x, y + other.y,z + other.z); 
}

/*CVector operator+(int number){
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i] + number;
   }
  return resVector;
  }*/

CVector CVector::Add(double number) const{
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i] + number;
   }
  return resVector;
  }


CVector CVector::operator-(const CVector& other) const {
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i] - other.Vector[i];
  }
  return resVector;
  //return CVector (x - other.x, y - other.y,z - other.z); 
}

CVector CVector::Subtract(double number) const{
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i] - number;
   }
  return resVector;
  }



CVector CVector::operator/(double number) const{ 
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i]/number;
   }
  return resVector;
}


CVector CVector::operator*(double number) const{
  CVector resVector;
  for (int i =0; i< Dimensions;i++) {
    resVector.Vector[i] = Vector[i]*number;
   }
  return resVector;
}


double CVector::Length2() const{
  double sum = 0;
  for (int i = 0;i<Dimensions;i++){
    sum+=Vector[i]*Vector[i];
  }
  return sum;
}


double CVector::Length() const{
  return sqrt(CVector::Length2());
}



CVector CVector::Normalize() const{
  return *this/CVector::Length();
}


CVector CVector::Cross(const CVector& other) const{
  CVector resVector;
  double x1 = Vector[0];
  double x2 = other.Vector[0];

  double y1 = Vector[1];
  double y2 = other.Vector[1];

  double z1 = Vector[2];
  double z2 = other.Vector[2];
  
  resVector.Vector[0] = y1*z2 -z1*y2;
  resVector.Vector[1] = z1*x2 -x1*z2;
  resVector.Vector[2] = x1*y2 -y1*x2;
  
  return resVector;
}



double CVector::Dot(const CVector& other) const{
  double sum = 0;
  for (int i =0; i< Dimensions;i++) {
    sum += Vector[i]*other.Vector[i];
   }
  return sum;
}


double CVector::Sum() const{
  double sum = 0;
  for (int i =0; i< Dimensions;i++) {
    sum += Vector[i];
   }
  return sum;
}

double CVector::x(){
  return Vector[0];
}

double CVector::y(){
  return Vector[1];
}

double CVector::z(){
  return Vector[2];
}


double CVector::Quadrant(){

  if (Vector[0] > 0 &&  Vector[1] > 0 && Vector[2] < 0) return 1;      //x+,y+,z-
  else if (Vector[0] > 0 &&  Vector[1] < 0 && Vector[2] < 0) return 2; //x+,y-,z-
  else if (Vector[0] > 0 &&  Vector[1] < 0 && Vector[2] > 0) return 3; //x+,y-,z+
  else if (Vector[0] < 0 &&  Vector[1] > 0 && Vector[2] > 0) return 4; //x-,y+,z+
  else if (Vector[0] < 0 &&  Vector[1] > 0 && Vector[2] < 0) return 5; //x-,y+,z-
  else if (Vector[0] < 0 &&  Vector[1] < 0 && Vector[2] < 0) return 6; //x-,y-,z-
  else if (Vector[0] < 0 &&  Vector[1] < 0 && Vector[2] > 0) return 7; //x-,y-,z+
  else return 0;                                           //x+,y+,z+
  //The last else might be dangerous
}
