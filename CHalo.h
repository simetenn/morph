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
	//Create a new CHalo from a CHalo
	CHalo(CHalo* inHalo);
	~CHalo();


	//Print all particles in halo
	void print();

	//Print all particles in halo
	void printHalo(int& count);

	//Print all halos and subhalos
	void printSubHalos();
	//Print information for one subhalo
	void printSubHalo(int& count);


	//Convert from one halo to an CArray
	CArray* Halo2Array();

	//Clear and remove all information from a CHalos object
	void clear();
	//Clear and remove particle information, but keeping halo information
	void clean();
	//Clear and remove particle information, but keeping halo information. For all SubHalos
	void cleanSubHalos();

	//Copy a CHalos object
	void copy(CHalo* inHalo);


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
	//return the number of subHalos
	//int getNrSubHalos();

	list<CHalo*> getSubHalos();
	

	void setNrParticles(int element);

	//Return particle nr #element
	CParticle* operator[](int element);
	CParticle* get(int element);

	double PhaseSpaceDistanceHalo(CParticle* inParticle, CVector* inSigmaP, CVector* inSigmaV);


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

	//Save position data to file for all subhalos
	void saveP();
	//Recursivly goes trough all subhalos and write the position data to file
	void savePRec(fstream& fileName, int& HaloID);
	//Saves position data for each particle to file for a single halo
	void saveHaloP(fstream& fileName, int& HaloID);
	
	
	//Save the statistical data in the x direction, for the halo and all subhalos
	void saveStatX();
	//Save the statistical data in the x direction, for a single halo
	void saveHaloStatX(fstream& fileName, int& HaloID);

	
	

	//Calculate the linking length of a halo
	double LinkingLength();

	//Splits the halo into subhalos using the friend of friend methode in phase space.
	//Then calculates the subhalos of the subhalo recursivly untill either the halo limit
	//is reached or no particles are found beeing linked together. the linking length is
	//sett to decrease by f for each iteration.
	void SplitHalo();
	//Calculating Friend of Friend using recursion, in phase space.
	//It must scales as N^2
	void FriendOfFriendPhaseSpace();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within the phase space linking length.
	//Before calling itself for each particle found this way
	void findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, int L);

	//Find the next particle to assign to a Halo
	CParticle* nextParticle();

	
	void assignParticles(CParticles* allParticles);
	void findHalo(CParticle* inParticle,CHalo* inHalo);
	void createSubHalos();
	
	//vector<CHalo*> SubHalos;
 protected:
	CParticles Halo;
	CVector MeanP,MeanV, SigmaP, SigmaV;
	double Mass;
	int ParticleSize, NrParticles;
	CParticle* searchParticle;
	//vector<CHalo*> SubHalos;
	list<CHalo*> SubHalos;
};
