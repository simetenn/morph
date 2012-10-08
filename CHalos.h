//#include <iostream>
#include "CHalo.h"
//#include "CArray.h"

struct particle_save {
	CVector_bare P, V;
	unsigned int halo;
};

class CHalos{

 public:
	CHalos();
	CHalos(CArray* inArray);
	~CHalos();

	void HaloSort();
	void printHalos();
	void initialize_Halos();


	CArray* Halos2Array();
	CHalos* Array2Halos(CArray* inArray);

	void addHalosArray(CArray* inArray);
	void addHalo(CHalo* inHalo);
	void master();
	void slave();
	int sizeHalos();
	CHalos operator+(CHalos* inCHalo);
	CHalos operator=(CHalos* inCHalo);
	int getnrParticles();
	int getnrHalos();
	int getnrinHalo(int element);
	CHalo* getHalo(int element);
	void get_Data(string filename);
	CParticles* getCParticles(int element);
	void print();
	void addHalos(CArray* inArray);
	void removeHalo(int element);

	void LoadBin(string Filename);

	// Particle Save structure: Keep only P and V!

	void FriendOfFriendN3();
	
	void FriendOfFriendGrid();

	//Friend of Friend methods
	void FriendOfFriendN2();
	CParticle* findParticle();
	void findNeighbors(CParticle* inParticle, CHalo* inHalo);

	void saveP();
	
 protected:
	int nrHalos,ParticleSize, nrParticles, data_size;
	CParticles allParticles;
	CParticle* searchParticle;
	vector<int> nrinHalo;
	vector<CHalo*> Halos;


};
