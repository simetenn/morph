//#include <iostream>
#include "CParticles.h"
//#include "CArray.h"



class CHalo : public CParticles{

 public:
	CHalo();
	CHalo(CArray* inArray);
	~CHalo();

	void print_Halo();
	
	CArray* Halo2Array();

	CParticle* operator[](int element);

	
 protected:
	CParticles Halo;
	double HaloMass;
 	
};
