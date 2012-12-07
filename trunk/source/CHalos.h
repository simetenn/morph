#pragma once

#include "CHalo.h"
#include "CGrid.h"

//Particle save structure, keeps only P and V.
struct particle_save {
	CVector_bare P, V;
	unsigned int halo;
};



class CHalos{
 public:
	CHalos();
	//Create CHalos from an in array on the form:
	//nr of halos, nr of particles in halo 1, nr of particles in halo 2, ... ,
	//nr of particles of in halo N, particle array 1, particle array 2, ... ,
	//particle array N
	CHalos(CArray* inArray);
	~CHalos();


	//Testing routines, for testing purposes only
	//void initializeHalos();
	//Get data from my own type of input file
	//For testing purposes only
	void getData(string filename);


	//Sort halos by size, not existing yet
	void HaloSort();

	



	//Convert all halos to one array
	CArray* Halos2Array();

	//Add halo to the existing ones
	void addHalo(CHalo* inHalo);
	//Add halos to the existing ones
	void addHalos(CArray* inArray);
	//Remove halo nr element from CHalos
	void removeHalo(int element);




	//Add two CHalos. Not tested, so unsure if correct
	CHalos operator+(CHalos* inCHalo);


	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within the linking length.
	//Before calling itself for each particle found this way	//Return total nr of particles
	int getNrParticles();
	//Return nr of halos
	int getNrHalos();
	//return nr of particles in a halo
	int getNrInHalo(int element);
	//Return a halo
	CHalo* getHalo(int element);
	//Return a halo
	CHalo* operator[](int element);
	//Returns CParticles* for a given halo
	CParticles* getParticles(int element);
	//Returns CParticle* for a given particle
	CParticle* getParticle(int element);


	//Print out all particles one by one
	void print();
	//Print out all halos
	void printHalos();

	//Load a binary file from a N-body simulation into memory
	void loadBin(string Filename);
	//Load a text file, 
	void loadData(string Filename);

	void save(string Filename, int NrParticles2File);
	//save the positions of each particle together with the halo it belongs to to file
	void saveP(string Filename);
	void saveSize(string Filename);

	//Calculate halo statistics for each halo
	void CalculateAllStatistics();

	//Calculating Friend of Friend using recursion, without a grid
	void FriendOfFriendN2();
	//The following 2 methods are used only in the above method
	//Finds the next particle that has no halo assigned and returns it
	CParticle* findParticle();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within the linking length.
	//Before calling itself for each particle found this way
	void findNeighbors(CParticle* inParticle, CHalo* inHalo);


	//Friend of Friend methode that uses a grid to speed up the calculations
	//Scales as something*log(N)
	void FriendOfFriendGrid();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within 26 closest cubes in the grid.
	//Before calling itself for each particle found this way
	void findNeighborsGrid(CParticle* inParticle, CHalo* inHalo);

	//Not used in this class, moved to Halo to be able to sort one halo into subhalos
	//void SplitHalo(int element);
	//void FriendOfFriendPhaseSpace();
	//void findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, CVector* SigmaP,CVector*  SigmaV);
	//double PhaseSpaceDistance(CParticle* p1, CParticle* p2, double SigmaP, double SigmaV);

	void SplitHalos();
	

	CHalos* master();
	void slave();


 protected:
	vector<CParticle> AllParticles;
	int NrHalos,ParticleSize, NrParticles;
	double LinkingLength;
	CParticles allParticles;
	CParticle* searchParticle;
	CGrid Grid;

	vector<int> NrInHalo;
	vector<CHalo*> Halos;
};
