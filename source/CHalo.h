#pragma once

#include "CParticles.h"



class CHalo{

 public:
	CHalo();
	//Create a CHalo from CParticles
	CHalo(CParticles* inParticles);
	//Creates CHalo from a CArray on the following form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	CHalo(CArray* inArray);
	//Create a new CHalo from a CHalo
	CHalo(CHalo* inHalo);
	~CHalo();


	//Print all particles in halo
	void print();

	//Print Halo nr, nr particles in halo and position and velocity of halo
	void printHalo(int& count);

	//Print all halos and subhalos.
	void printSubHalos();
	//Print information for one subhalo. Recursivly goes through the subhalo tree.
	//Used by printSubHalos()
	void printSubHalo(int& count);


	//Clear and remove all information from a CHalos object
	void clear();
	//Clear and remove particle information, but keeping halo information, like position and velocity
	void clean();

	//Clear and remove particle information, but keeping halo information, like position and velocity
	//Does it recursivly for all SubHalos
	void cleanSubHalos();

	//Copy a CHalos object
	void copy(CHalo* inHalo);


	//Convert from one halo to an CArray. On the form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	CArray* Halo2Array();
	//Convert all Subahlos to an CArray. On the form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	CArray* SubHalos2Array();
	//Adds the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
	//Then recursivly runs for all subhalos
	void SubHalos2ArrayRec(CArray* inArray,CArray* sizeArray);


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
	//Set NrParticles to count
	void setNrParticles(int count);
	//return the number of subHalos
	int getNrSubHalos();
	//Calculate the total nNrParticles in all subhalos
	int getTotalNrParticles();
	//Recursivly run trough all subhalos and add the NrParticles in each halo to TotalNrParticles
	void getTotalNrParticlesRec(int& TotalNrParticles);

	void calculateVir();

	void scalePositions(int scale);

	//Return the list over all subhalos
	list<CHalo*> getSubHalos();
	//Return the iterator pointing at the begining element of the subhalo list
	list<CHalo*>::iterator begin();
	//Return the iterator pointing at the end element of the subhalo list
	list<CHalo*>::iterator end();
	//Attach a halo to the subhalo list. At the front position
	void attachSubHalo(CHalo* inHalo);
	//Remove halo from the subhalo list.
	void removeSubHalo(CHalo* inHalo);
	

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
	//Remove particle #element from halo
	void removeParticle(int element);


	//Calculate all the statistics relevant for a halo, such as:
	//mean P, mean V, sigma P, sigma V and mass
	void CalculateStatistics();
	//Calculate all the statistics relevant for all subhalos
	void CalculateAllStatistics();
	//Printing out the statistics for one halo
	void printStatistics();


	//save the data for a single halo to file
	void saveHalo(string Filename);
	//Save position data to file for all subhalos
	void saveP(string Filename);
	//Recursivly goes trough all subhalos and write the position data to file
	void savePRec(fstream& fileName, int& HaloID);
	//Saves position data for each particle to file for a single halo
	void saveHaloP(fstream& fileName, int& HaloID);


	//Save the statistical data in the x direction, for the halo and all subhalos
	void saveStatX(string Filename);
	//Save the statistical data in the x direction, for a single halo
	void saveHaloStatX(fstream& fileName, int& HaloID);

	void savePhi(string Filename);
	

	//Calculate the Phase-Space distance between a halo and a particle
	double PhaseSpaceDistanceHalo(CParticle* inParticle);
	//Calculate the linking length of a halo

	//Calculate the Linking Length for each halo.
	//The linking length is chosen such that a fraction f of all particles
	//atleast is linked together with one other particle
	//For large groups > NrLinking we only calculate this for NrLinking particles
	//By defult NrLinking = 10000.
	double LinkingLength();

	//Splits the halo into subhalos using the friend of friend methode in phase space.
	//Then calculates the subhalos of the subhalo recursivly untill either the halo limit
	//is reached or no particles are found beeing linked together.
	void SplitHalo();
	//Calculating Friend of Friend using recursion, in phase space.
	//It scales as N^2
	void FriendOfFriendPhaseSpace();
	//Flags the given particle and adds it to the given halo.
	//Then finds the neighboring particles, within the phase space linking length.
	//Before calling itself for each particle found this way
	void findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, int L);

	//Find the next particle to assign to a Halo
	CParticle* nextParticle();


	//Assign all the particles contained in the subhalos to the correct seed halo
	void assignParticles(CParticles* allParticles);
	//Find the halo a particle is closest too and add the particle to that halo
	void findHalo(CParticle* inParticle,CHalo* inHalo);

	void removeEmptySubHalos();
	//Remove halos that has fewer than HaloLimit particles
	void removeEmptyHalos(CHalo* prevHalo);
	

	//Merge halos that are statisticaly the same halo
	void mergeStatistical();
	//Recursivly goes through all subhalos bottom up and merges halos that are statisticaly equal
	void mergeStatisticalRec(CHalo* mergeHalo, int &flag);

	
		
	void SortParticlesDistance();
	void CalculatePhiSpherical();
	//Method for unbinding particles from a halo
	void Unbind();
	void UnbindAll();

	//Do the splitting of halos, assigning particles to all halos, and merge statisticaly equal halos
	void createSubHalos();


 protected:
	CParticles Halo;
	CVector MeanP,MeanV, SigmaP, SigmaV;
	double Mass;
	int ParticleSize, NrParticles;
	CParticle* searchParticle;
	list<CHalo*> SubHalos;
	//New values, needs to be added support for the relevant MPI send/recieve routines
	vector<double> r, Phi;
	double Mvir,Rvir;
};
