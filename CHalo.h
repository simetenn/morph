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

	CParticles* getCParticles();

	int getnrParticles();
	
	CParticle* operator[](int element);
	CParticle* get(int element);

	void addParticle(CParticle* inParticle);
	CParticle* getParticle(int element);
	void addHalo(CHalo* inHalo);
	double getHaloMass();
	void dummy();

	void print();

	
 protected:
	CParticles Halo;
	double HaloMass;
	int ParticleSize, nrParticles;
	

};
