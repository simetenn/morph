#pragma once

#include "CParticles.h"



class CHalo{

 public:
	CHalo();
	//Create a CHalo from CParticles
	CHalo(CParticles* inParticles);
	//Creates CHalo from a CArray on the following form:
	//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
	CHalo(CArray* inArray);
	~CHalo();


	//Print all particles in halo
	void print();
	
	//Convert from one halo to an CArray
	CArray* Halo2Array();

	
	//Return the total mass of the halo
	double getHaloMass();
	//Return nr of particles
	int getNrParticles();

	//Return particle nr #element
	CParticle* operator[](int element);
	CParticle* get(int element);


	//Get CParticles in the Halo
	CParticles* getParticles();

	//Add a particle to the halo
	void addParticle(CParticle* inParticle);
	//Add a halo to the halo
	void addHalo(CHalo* inHalo);
	//Add several particles to the Halo
	void addParticles(CParticles* inParticles);

	//Calculate the standard deviation of the positions in a halo
	double SigmaP();
	//Calculate the standard deviation of the velocities in a halo
	double SigmaV();

	//Calculate the linking length of a halo
	double LinkingLength();

 protected:
	CParticles Halo;
	double HaloMass;//, SigmaP,SigmaV;
	int ParticleSize, NrParticles;
};
