#pragma once

#include "CVector.h"
#include "Constants.h"


class CParticle{
 public:

	CParticle();
	
	//Create a particle from an array on the following form:
	//[HaloID,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
	CParticle(double* inArray);

	~CParticle();

	//Attatch a particle to the particle list
	void attachParticle(CParticle* p){
		p->nextGrid = nextGrid;
		if (nextGrid != NULL)
			nextGrid->prevGrid = p;
		nextGrid = p;
		p->prevGrid = this;
	};

	
	//Gives the next and previous particle in a linked list
	CParticle* next,*prev,*nextGrid,*prevGrid;
	//Removes the particle from a linked list
	void RemoveFromList();
	//Removes the particle from the grid linked list
	void RemoveFromListGrid();
	
	//LinkedList ListIterator, GridIterator;

	//Set the different values a particle has
	void setPhi(double element);
	void setMass(double in_M);
	void setPosition(double Px, double Py, double Pz);
	void setVelocity(double Vx, double Vy, double Vz);
	void setAcceleration(double Ax, double Ay, double Az);

	//Set all data, given by a vector
	void setData(vector<double> data);
	
	void setP(CVector inP);
	void setV(CVector inV);


	//Get the different values a particle has
	int getHalo();
	double getPhi();
	double getMass();
	CVector& getP();
	CVector& getV();
	CVector& getA();
	int getParticleSize();


	//Get/set flag value.y
	//Used in FoF methods to tell if this particle has been tested yet or not
	void setFlag(int inFlag);
	int getFlag();


	//Convert a particle to an array on the form:
	//[Phi,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
	double* Particle2Array();

	//Calculate the kinetic energy of a particle
	double Ekin();
	//Calculate the momentum of a particle
	CVector Momentum();
	//Move the particle one timestep
	void Move(double dt);
	//CalculatePhaseSpaceDistance between 2 particles
	double PhaseSpaceDistance(CParticle* p2, CVector* inSigmaP, CVector* inSigmaV);
	//CalculatePhaseSpaceDistance between a particle and a Halo
	//double PhaseSpaceDistanceHalo(CHalo* inHalo);

	

	//Print out all the information contained in one particle
	void print();

	//Calculate the gravitational energy of a particle, utilizing the particle acceleration
	void calculatePhi(CVector& MeanP);


	//Test if a particle has been assigned a halo
	int gotHalo();
	//Decreases the Phi by one. Used by my inefficient FoF code
	void decreaseHalo();


 protected:
	CVector P,V,A;
	int ParticleSize,flag;
	double Mass,Phi;
};


