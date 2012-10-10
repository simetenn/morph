//#include <iostream>
#include "CHalo.h"
//#include "CArray.h"


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

	//Sort halos by size, not existing yet
	void HaloSort();


	//Testing routines, for testing purposes only
	void initialize_Halos();
	//Get data from my own type of input file
	void get_Data(string filename);



	//Convert all halos to one array
	CArray* Halos2Array();

	//Add halo to the existing ones
	void addHalo(CHalo* inHalo);
	//Add halos to the existing ones
	void addHalosArray(CArray* inArray);
	//Add halos to the existing ones
	void addHalos(CArray* inArray);
	//Remove halo nr element from CHalos
	void removeHalo(int element);

	void master();
	void slave();

	//Add two CHalos. Not tested, so unsure if correct
	CHalos operator+(CHalos* inCHalo);


	//Return total nr of particles
	int getnrParticles();
	//Return nr of halos
	int getnrHalos();
	//Return nr of halos
	int sizeHalos();
	//return nr of particles in a halo
	int getnrinHalo(int element);

	CHalo* getHalo(int element);
	//Returns CParticles* for a given halo
	CParticles* getParticles(int element);

	//Print out all particles one by one
	void print();
	//Print out all halos
	void printHalos();

	//Load a binary file from a N-body simulation into memory
	void LoadBin(string Filename);
	//savesthe positions of each particle together with the halo it belongs to to file
	void saveP();


	//Calculating Friend of Friend using recursion, without a grid
	void FriendOfFriendN2();
	//The following 2 methods are used only in the above method
	//Finds the next particle that has no halo assigned and returns it
	CParticle* findParticle();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within the linking length.
	//Before calling itself for each particle found this way
	void findNeighbors(CParticle* inParticle, CHalo* inHalo);


	void FriendOfFriendGrid();



	//Do not use this. Way to slow method. It is not tested, but seems to run
	void FriendOfFriendN3();



 protected:
	int nrHalos,ParticleSize, nrParticles;

	CParticles allParticles;
	CParticle* searchParticle;

	vector<int> nrinHalo;
	vector<CHalo*> Halos;
};
