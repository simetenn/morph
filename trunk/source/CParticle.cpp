#include "CParticle.h"
#include <iostream>

using namespace std;

//int CParticle::ID_Generator = 0;

//Creates an "empty" particle
CParticle::CParticle(){
	ParticleSize =  myConstants::constants.ParticleSize;
	
	//CVector P,V,A;
	Mass = 1;
	//Charge = 0;
	//Generate_ID();
	P.Set(0,0,0);
	V.Set(0,0,0);
	A.Set(0,0,0);
	Phi = 0;
	next = prev = nextGrid = prevGrid = NULL;
	
}
 

//Create a particle from an array on the following form:
//[Phi,Mass,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
CParticle::CParticle(double* inArray){
	//Some way to test if length of the array is equal to particle size
	//Generate_ID();

	ParticleSize =  myConstants::constants.ParticleSize;

	Phi = inArray[0];
	Mass = inArray[1];
	//Charge = inArray[2];
	P.Set(inArray[2],inArray[3],inArray[4]);
	V.Set(inArray[5],inArray[6],inArray[7]);
	A.Set(inArray[8],inArray[9],inArray[10]);

	next = prev = nextGrid = prevGrid = NULL;
}


CParticle::~CParticle(){
}




//Removes the particle from a linked list
void CParticle::RemoveFromList(){
	if (next != NULL){
		next->prev = prev;
	}
	if (prev != NULL){
		prev->next = next;
		next =  NULL;
	}
	prev =  NULL;
}

void CParticle::RemoveFromListGrid(){
	if (nextGrid != NULL){
		nextGrid->prevGrid = prevGrid;
	}
	if (prevGrid != NULL){
		prevGrid->nextGrid = nextGrid;
		nextGrid =  NULL;
	}
	prevGrid =  NULL;
}

//Somehing weird with this???
//Set the different values a particle has
void CParticle::setPhi(double element){
	/*if (element < 0){
		cout << "Warning: This is negative, it should always be a positive number" << endl;
		}*/
	Phi = element;
}

double CParticle::getPhi(){
	return Phi;
}


void CParticle::setMass(double in_M){
	Mass = in_M;
}


/*void CParticle::setCharge(double in_C){
	Charge = in_C;
	}*/


void CParticle::setPosition(double Px, double Py, double Pz){
	P.Set(Px,Py,Pz);
}


void CParticle::setVelocity(double Vx, double Vy, double Vz){
	V.Set(Vx,Vy,Vz);
}


void CParticle::setAcceleration(double Ax, double Ay, double Az){
	A.Set(Ax,Ay,Az);
}

void CParticle::setData(vector<double> data){
	Phi = data[0];
	Mass = data[1];
	//Charge = data[2];

	for (int i = 0;i<P.getDimensions();i++){
		P[i] = data[i+2];
		V[i] = data[i+5];
		A[i] = data[i+8];
	}
}

void CParticle::setP(CVector inP){
	P = inP;
}

void CParticle::setV(CVector inV){
	V = inV;
}





//Get the different values a particle has
/*int CParticle::getID(){
	return ID;
	}*/

int CParticle::getHalo(){
	return Phi;
}

double CParticle::getMass(){
	return Mass;
}


CVector& CParticle::getP(){
	return P;
}


CVector& CParticle::getV(){
	return V;
}


CVector& CParticle::getA(){
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
//[Phi,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
double* CParticle::Particle2Array(){
	double * tmpArray = new double [ParticleSize]; //<- Memory leak
	tmpArray[0] = Phi;
	tmpArray[1] = Mass;
	//tmpArray[2] = Charge;
	
	for (int i = 0;i<P.getDimensions();i++){
		tmpArray[i+2] = P[i];
		tmpArray[i+5] = V[i];
		tmpArray[i+8] = A[i];
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


double CParticle::PhaseSpaceDistance(CParticle* p2, CVector* inSigmaP, CVector* inSigmaV){
	return sqrt((P - p2->getP()).Length2()/inSigmaP->Length2() +  (V - p2->getV()).Length2()/inSigmaV->Length2());
}




//Print out all the information contained in one particle
void CParticle::print(){
	cout << "------------------------------------" << endl;
	//cout << "Particle ID: " << ID << endl;
	cout << "Halo ID: " << Phi << endl;
	cout << "Mass: " << Mass << endl;
	//cout << "Charge: " << Charge << endl;
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
	if (Phi != -1 ) {
		return 1;
	}
	else {
		return 0;
	}
}



//Decreases the Phi by one. Used by my inefficient FoF code
void CParticle::decreaseHalo(){
	Phi--;
	
	if (Phi < 0){
		cout << "Warning: Phi=" << Phi << "This is negative, it should always be a positive number !" << endl;
	}
}


/*void CParticle::Generate_ID(){
	ID = ID_Generator++;
	}*/
