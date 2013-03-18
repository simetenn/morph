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
	//nr of particles of in halo N, halo array 1, halo array 2, ... halo array N]
	CHalos(CArray* inArray);
	~CHalos();

	//Sort halos by NrParticles
	void HaloSort();


	//Convert from all halos to one array. On the form:
	//nr of halos, nr of particles in halo 1, nr of particles in halo 2, ... ,
	//nr of particles of in halo N, halo array 1, halo array 2, ... halo array N]
	CArray* Halos2Array();

	//Add halo to the existing ones
	void addHalo(CHalo* inHalo);
	//Add halos to the existing ones
	void addHalos(CArray* inArray);
	//Remove halo nr element from CHalos
	void removeHalo(int element);
	//Remove Halos with fewer particles than HaloLimit
	void removeEmptyHalos();
	
	//Add two CHalos. Not tested, so unsure if correct
	CHalos operator+(CHalos* inCHalo);


	//Return total nr of particles
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

	//Calculate the spherical potential for all halos
	void CalculatePhiSpherical();
	

	//Load a binary file from a N-body simulation into memory. Our format. 
	void loadBin(string Filename);
	//Load a binary file from a N-body simulation into memory.
	//Claudio's format, converted from Ramses files
	void loadClaudio(string Filename);
	//Load a text file, with all information about each particle
	void loadData(string Filename);
	//Load a txt with full halo information
	void loadHalos(string Filename);
	
	//Scale all positions with a number
	void scalePositions(double scale);
	
	
	//Save NrParticles2File evenly distributed particles to file
	//Mainly used to create smaller datasets
	void save(string Filename, int NrParticles2File);
	//save the positions of each particle together with the halo it belongs to to file
	void saveP(string Filename);
	//Save the size of all the halos to a txt fil
	void saveSize(string Filename);
	//Save halos into a text file, as a array
	void saveHalos(string Filename);
	//Calculate halo statistics for all halos
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


	//Friend of Friend methode that uses a grid to sped up the calculations
	//Scales as something*log(N)
	void FriendOfFriendGrid();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within 26 closest cubes in the grid.
	//Before calling itself for each particle found this way
	void findNeighborsGrid(CParticle* inParticle, CHalo* inHalo);


	//Runs the splitting routine for all halos to split each into several subhalos
	void SplitHalos();

	//A routine to be run in the master process to do calulations on each halo in parallel.
	//It sends the data from each halo to all available processors,
	//then sends out new data as soon as a processor finishes its task
	CHalos* master();
	//Slave processor, listening for data from the master processor
	//Then does something with the data before sending it back to the
	//master processor
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
