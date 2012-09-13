//#include <iostream>
#include "CHalo.h"
//#include "CArray.h"



class CHalos{

 public:
	CHalos();
	CHalos(CArray* inArray);
	~CHalos();

	void HaloSort();
	void print_Halos();
	void initialize_Halos();


	CArray* Halos2Array();
	CHalos* Array2Halos(CArray* inArray);

	void addHalosArray(CArray* inArray);
	void addHalo(CHalo* inHalo);
	void master();
	void slave();
	int sizeHalos();
	//void operator+(CHalos* inCHalo);
	
	
 protected:
	int nrHalos,ParticleSize, nrParticles;
	vector<int> nrinHalo;
	vector<CHalo*> Halos;


};
