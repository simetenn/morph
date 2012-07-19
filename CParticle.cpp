#include "CParticle.h"
#include <iostream>

using namespace std;

int CParticle::ID_Generator = 1;


CParticle::CParticle(){
  CVector P,V,A;
  //double Mass = 1;// <- Why do this not work?
  Set_Mass(1);
  //int Charge = 0;
  Set_Charge(0);
  Generate_ID();
  
}

CParticle::~CParticle(){
}




void CParticle::Set_Mass(double in_M){
  Mass = in_M;
}


double CParticle::Get_Mass(){
  return Mass;
}


void CParticle::Set_Charge(int in_C){
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


void CParticle::Move(double dt){
  for (int i = 0; i< Dimensions; i++) {
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


int CParticle::Get_ID(){
  return ID;
}


void CParticle::print_Particle(){
  cout << "------------------------------------" << endl;
  cout << "Particle ID: " << ID << endl;
  cout << "Mass: " << Mass << endl;
  cout << "Charge: " << Charge << endl;
  cout << "Position:     ";
  P.print();
  cout << "Velocity:     ";
  V.print();
  cout << "Acceleration: ";
  A.print();
  cout << "------------------------------------" << endl;
}
