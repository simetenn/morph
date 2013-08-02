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

	//Kill all halos and subhalos and delete the particles from memory
	void kill();
	//Set the values of a CHalo object from an array on the form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	void set(CArray* inArray);

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

	void eraseSubHalos();


	void cleanAll();
	void cleanSubHalosAll();


	
	//Copy a CHalos object
	void copy(CHalo* inHalo);

	//Convert from one halo to an CArray. On the form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	CArray* Halo2Array();
	//Convert all Subahalos to an CArray. On the form:
	//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , PartileArray N]
	CArray* SubHalos2Array();
	//Adds the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
	//Then recursivly runs for all subhalos
	void SubHalos2ArrayRec(CArray* inArray,CArray* sizeArray);

	//Convert all Subahlos to an CArray. On the form:
	//[ID, NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	CArray* SubHalosStructure2Array();
	//Adds the ID and the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
	//Then recursivly runs for all subhalos
	void SubHalosStructure2ArrayRec(CArray* inArray, CArray* sizeArray, int& ID);

	//Save halos into a text file, as a array
	void saveStructure(string Filename);
	//Load halos from a text file
	void loadStructure(string Filename);

	//Create Halos and subhalos from an array on the form:
	//[ID, NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
	//This recreates the halo structire from SubHalosStructure2Array()
	//If this is used I need to manually kill the halos stored in it.
	void fromStructureArray(CArray* inArray);
	//Recursivly creates subhalos from the array
	void fromStructureArrayRec(CHalo* prevHalo, CArray* inArray, int& nrHalo,int& particle_count,int& nextID);

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
	void setMass(double inMass);
	void setMeanP(double x, double y, double z);
	void setMeanV(double x, double y, double z);
	void setSigmaP(double x, double y, double z);
	void setSigmaV(double x, double y, double z);

	//return the number of subHalos
	int getNrSubHalos();
	//Calculate the total nNrParticles in all subhalos
	int getTotalNrParticles();
	//Recursivly run trough all subhalos and add the NrParticles in each halo to TotalNrParticles
	void getTotalNrParticlesRec(int& TotalNrParticles);
	//Return the virialisation mass
	double getMvir();
	//Return the virialisation radius
	double getRvir();
	//Return distance from center, sorted
	vector<double>* getR();
	//Retturn gravitational potential, sorted as distance from center
	vector<double>* getPhi();

	//Calculate the Virialization mass and radius
	void calculateVir();
	void calculateVir2();
	void calculateVirBeta();
	double Beta(double R);
	double Volume(double R);
	double Ps(double R);
	double Es(double R);
	double Tr(double R);
	double Wr(double R);

	int ParticlesOutsideVir();
	
	//Scale the positions by a number
	//mainly used in FOFGrid to scale the halos read in to be between [0,1]
	void scalePositions(double scale);

	//Return the list over all subhalos
	list<CHalo*> getSubHalos();
	//Return the iterator pointing at the begining element of the subhalo list
	list<CHalo*>::iterator begin();
	//Return the iterator pointing at the end element of the subhalo list
	list<CHalo*>::iterator end();
	//Attach a halo to the subhalo list. At the front position
	void attachSubHalo(CHalo* inHalo);
	void attachSubHaloBack(CHalo* inHalo);

	//Remove halo from the subhalo list.
	void removeSubHalo(CHalo* inHalo);


	//Return particle nr #element
	CParticle* operator[](int element);
	CParticle* get(int element);

	//Get CParticles in the Halo
	CParticles* getParticles();

	//Add a particle to the halo
	void addParticle(CParticle* inParticle);
	void addParticleSimple(CParticle* inParticle);

	//Add a halo to the halo
	void addHalo(CHalo* inHalo);
	//Add several particles to the Halo
	void addParticles(CParticles* inParticles);
	//Remove particle #element from halo
	void removeParticle(int element);


	//Calculate all the statistics relevant for a halo, such as:
	//mean P, mean V, sigma P, sigma V and mass

	void CalculateStatistics();
	void CalculateStatisticsNoMass();
	//Calculate all the statistics relevant for all subhalos
	void CalculateAllStatistics();
	//Printing out the statistics for one halo
	void printStatistics();


	//save the data for a single halo to file
	void saveHalo(string Filename);
	//Save halos into a text file, as a array, as a binary file
	void saveHaloBin(string Filename);

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

	//save the data for a single halo to file
	void savePhi(string Filename);

	//save the data for a single halo to file
	void save(string Filename, double value);
	//empty content of file Filename
	void del(string Filename);


	//Calculate the Phase-Space distance between a halo and a particle
	double PhaseSpaceDistanceHalo(CParticle* inParticle);
	double PhaseSpaceDistanceHaloHalo(CHalo* inHalo);


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

	
	void createSeedHalos();
	void createSeedHalosRec(int& count,list<CHalo*>* Seeds);
	void mergeStatisticalSeed();
	int mergeStatisticalSeedRec();
	void assignParticlesSeed(CParticles* allParticles);
	void calculateMass();
	void removeEmptySeedHalos();
	void generateSubstructure();
	void UnbindSeed(int &count);
	CArray* SeedHalos2Array();
	
	//Assign all the particles contained in the subhalos to the correct seed halo
	void assignParticles(CParticles* allParticles);
	//Find the halo a particle is closest too and add the particle to that halo
	void findHalo(CParticle* inParticle,CHalo* inHalo);

	//Remove Subhalos that has fewer than HaloLimit particles
	void removeEmptySubHalos();
	//Remove halos that has fewer than HaloLimit particles
	void removeEmptyHalos(CHalo* prevHalo);


	//Merge halos that are statisticaly the same halo
	void mergeStatistical();
	//Recursivly goes through all subhalos bottom up and merges halos that are statisticaly equal
	void mergeStatisticalRec(CHalo* mergeHalo, int &flag);


	//Sorts the particles in the halo after distance from the center of the halo,
	void SortParticlesDistance();
	//Calculate the gravitational potential using a spherical approximation
	void CalculatePhiSpherical();

	//Unbind particles for the halo and all subhalos
	void UnbindAll(int& count);
	//Method for unbinding particles from a single halo
	void Unbind(int& count);

	//Do the splitting of halos, assigning particles to all halos, and merge statisticaly equal halos
	void createSubHalos(int& count);

	//A splitting routine that split the halos into fake halos with equal size.
	//Each (sub)halo has #NrSubHalos subhalos each and there are #MaxDepth levels of subhalos
	//This is used for debugging purposes
	void createMockSubHalos();
	//A recursive routine that creates the mock subhalos
	void createMockSubHalosRec(int NrSubHalos, int NrParticlesSubHalo, int MaxDepth, int &depth, CParticles& inHalo);

 protected:
	CParticles Halo;
	CVector MeanP,MeanV, MeanA, SigmaP, SigmaV;
	double Mass;
	int ParticleSize, NrParticles;
	CParticle* searchParticle;
	list<CHalo*> SubHalos, SeedHalos;
	list<CParticle*> linkParticles;
	//New values, needs to be added support for the relevant MPI send/recieve routines
	vector<double> r, Phi;
	double Mvir,Rvir;
};
