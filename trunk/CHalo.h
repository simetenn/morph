//#include <iostream>
#include "CParticles.h"
//#include "CArray.h"



class CHalo{

 public:
	CHalo();
	CHalo(CParticles* inParticles);
	CHalo(CArray* inArray);
	~CHalo();

	void print_Halo();

	CArray* Halo2Array();

	CParticle* operator[](int element);
	CParticle* get(int element);


 protected:
	CParticles Halo;
	double HaloMass;
	int ParticleSize, nrParticles;


};
