#include "CParticle.h"
#include <iostream>

using namespace std;

int CParticle::ID_Generator = 0;

//Creates an "empty" particle
CParticle::CParticle(){
	ParticleSize = 12;

	CVector P,V,A;
	Mass = 1;
	Charge = 0;
	Generate_ID();
	HaloID = -1;
}


//Create a particle from an array on the following form:
//[HaloID,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
CParticle::CParticle(double* in_array){
	//Some way to test if length of the array is 12
	Generate_ID();

	ParticleSize = 12;
	HaloID = in_array[0];
	Mass = in_array[1];
	Charge = in_array[2];
	P.Set(in_array[3],in_array[4],in_array[5]);
	V.Set(in_array[6],in_array[7],in_array[8]);
	A.Set(in_array[9],in_array[10],in_array[11]);
}


CParticle::~CParticle(){
}




//Removes the particle from a linked list
void CParticle::RemoveFromList(){
	if (next)
		next->prev = prev;

	if (prev)
		prev->next = next;
}




//Set the different values a particle has
void CParticle::setHalo(int element){
	if (element < 0){
		cout << "Warning: This is negative, it should always be a positive number" << endl;
	}
	HaloID = element;
}

void CParticle::Set_Mass(double in_M){
	Mass = in_M;
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
	HaloID = data[0];
	Mass = data[1];
	Charge = data[2];

	for (int i = 0;i<P.getDimensions();i++){
		P[i] = data[i+3];
		V[i] = data[i+6];
		A[i] = data[i+9];
	}
}

void CParticle::setP(CVector inP){
	P = inP;
}

void CParticle::setV(CVector inV){
	V = inV;
}





//Get the different values a particle has
int CParticle::get_ID(){
	return ID;
}

int CParticle::getHalo(){
	return HaloID;
}

double CParticle::get_Mass(){
	return Mass;
}


CVector& CParticle::get_P(){
	return P;
}


CVector& CParticle::get_V(){
	return V;
}


CVector& CParticle::get_A(){
	return A;
}


int CParticle::getParticleSize(){
	return ParticleSize;
}




//Get/set flag value.
//Used in FoF methods to tell if this particle has been tested yet or not
int CParticle::getFlag(){
	return flag;
}

void CParticle::setFlag(int inFlag){
	flag = inFlag;
}




//Convert a particle to an array on the form:
//[HaloID,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
double* CParticle::Particle2Array(){
	double * tmpArray = new double [ParticleSize]; //<- Memory leak
	tmpArray[0] = HaloID;
	tmpArray[1] = Mass;
	tmpArray[2] = Charge;

	for (int i = 0;i<P.getDimensions();i++){
		tmpArray[i+3] = P[i];
		tmpArray[i+6] = V[i];
		tmpArray[i+9] = A[i];
	}
	return tmpArray;
}




//Move the particle one timestep
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





//Print out all the information contained in one particle
void CParticle::print(){
	cout << "------------------------------------" << endl;
	cout << "Particle ID: " << ID << endl;
	cout << "Halo ID: " << HaloID << endl;
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




//Test if a particle has been assigned a halo
int CParticle::gotHalo(){
	if (HaloID != -1 ) {
		return 1;
	}
	else {
		return 0;
	}
}



//Decreases the HaloID by one. Used by my inefficient FoF code
void CParticle::decreaseHalo(){
	HaloID--;
	
	if (HaloID < 0){
		cout << "Warning: HaloID=" << HaloID << "This is negative, it should always be a positive number !" << endl;
	}
}


void CParticle::Generate_ID(){
	ID = ID_Generator++;
}
