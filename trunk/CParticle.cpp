#include "CParticle.h"
#include <iostream>

using namespace std;

int CParticle::ID_Generator = 0;


CParticle::CParticle(){
	ParticleSize = 11;

	CVector P,V,A;
	Mass = 1;
	Charge = 0;
	Generate_ID();
}


CParticle::CParticle(double* in_array){
	//Some way to test if length of the array is 11
	//try {
	Generate_ID();

	//for (int i = 0; i < 11; i++) {
	//	cout << in_array[i] << endl;
	//}
	
	ParticleSize = 11;
	Mass = in_array[0];
	Charge = in_array[1];
	CVector P (in_array[2],in_array[3],in_array[4]);
	CVector V (in_array[5],in_array[6],in_array[7]);
	CVector A (in_array[8],in_array[9],in_array[10]);
	//P.print();
	//V.print();
	//A.print();
	
	/*}
	  catch {
	  CVector P,V,A;
	  Mass = 1;
	  Charge = 0;
	  Generate_ID()
	  }*/

	
}


CParticle::~CParticle(){
}


int CParticle::getParticleSize(){
	return ParticleSize;
}

void CParticle::Set_Mass(double in_M){
	Mass = in_M;
}


double CParticle::get_Mass(){
	return Mass;
}


void CParticle::Set_Charge(double in_C){
	Charge = in_C;
}


void CParticle::Set_Position(double Px, double Py, double Pz){
	P.Set(Px,Py,Pz);
}


void CParticle::Set_Velocity(double Vx, double Vy, double Vz){
	V.Set(Vx,Vy,Vz);
}


void CParticle::Set_Acceleration(double Ax, double Ay, double Az){
	A.Set(Ax,Ay,Az);
}


void CParticle::Set_Data(vector<double> data){
	Set_Mass(data[0]);
	Set_Charge(data[1]);
	Set_Position(data[2],data[3],data[4]);
	Set_Velocity(data[5],data[6],data[7]);
	Set_Acceleration(data[8],data[9],data[10]);
}


//Make these constant in some way or another
CVector& CParticle::get_P(){
	return P;
}


CVector& CParticle::get_V(){
	return V;
}


CVector& CParticle::get_A(){
	return A;
}


void CParticle::Move(double dt){
	for (int i = 0; i < P.getDimensions(); i++) {
		P[i] += V[i]*dt;
		V[i] += A[i]*dt;
	}
}


double CParticle::Ekin(){
	return 0.5*Mass*V.Length2();
}


CVector CParticle::Momentum(){
	return (V*Mass);
}


void CParticle::Generate_ID(){
	ID = ID_Generator++;
}



int CParticle::get_ID(){
	return ID;
}


void CParticle::print(){
	cout << "------------------------------------" << endl;
	cout << "Particle ID: " << ID << endl;
	cout << "Mass: " << Mass << endl;
	cout << "Charge: " << Charge << endl;
	cout << "Position:	   ";
	P.print();
	cout << "Velocity:	   ";
	V.print();
	cout << "Acceleration: ";
	A.print();
	cout << "------------------------------------" << endl;
}


double* CParticle::Particle2Array(){
	double * tmpArray = new double [ParticleSize]; //<- Memory leak
	tmpArray[0] = Mass;
	tmpArray[1] = Charge;

	for (int i = 0;i<P.getDimensions();i++){
		tmpArray[i+2] = P[i];
		tmpArray[i+5] = V[i];
		tmpArray[i+8] = A[i];
	}
	return tmpArray;
}
