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
	double getMass();
	//Get the position of the center of the halo
	CVector* getMeanP();
	//Get the velocity of the center of the halo
	CVector* getMeanV();
	//Get the standard deviation of the positions in a halo
	CVector* getSigmaP();
	//Get the standard deviation of the velocities in a halo
	CVector* getSigmaV();
	//Return nr of particles
	int getNrParticles();

	void setNrParticles(int element);
	
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

	//Calculate all the statistics relevant for a halo, such as:
	//mean P, mean V, sigma P, sigma V and mass
	void CalculateStatistics();
	
	//Printing out the statistics for one halo
	void printStatistics();
	
	//save the data for a single halo to file
	void saveHalo();
		
	void saveP();
	void saveHaloP(fstream& fileName, int& HaloID);

	void saveStatX();
	void saveHaloStatX(fstream& fileName, int& HaloID);
	

	
	//Calculate the linking length of a halo
	double LinkingLength();



	
	void SplitHalo(int LinkingLength);

	void FriendOfFriendPhaseSpace(int LinkingLength);
	void findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, int LinkingLength);

	CParticle* nextParticle();
	
	
 protected:
	CParticles Halo;
	CVector MeanP,MeanV, SigmaP, SigmaV;
	double Mass;
	int ParticleSize, NrParticles, NrSubHalos;
	CParticle* searchParticle;
	vector<CHalo*> SubHalos;
	
};
