//#include <iostream>
#include "CHalo.h"
//#include "CArray.h"

struct particle_save {
	CVector P, V;
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
	

	void LoadBin(string Filename);

	// Particle Save structure: Keep only P and V!

	void FriendOfFriendN2();
		

 protected:
	int nrHalos,ParticleSize, nrParticles, data_size;
	vector<int> nrinHalo;
	vector<CHalo*> Halos;


};
