#include "CHalo.h"

using namespace std;

CHalo::CHalo(){
	HaloMass = 0;
}

CHalo::~CHalo(){
}

CHalo::CHalo(CArray* inArray){
	HaloMass = 0;
	Halo.initialize_CParticles(inArray);
}



CParticle* CHalo::operator[](int element){
	return CParticles[element];
}




//Convert from one halo to an array
CArray*	 CHalo::Halo2Array(){//pointer
	double* Array = new double [ParticleSize*nrParticles]; // Memory leak
	Array[0] = 1;
	Array[1] = nrParticles;

	for (int i = 0; i < nrParticles;i++){
		double* tmpArray = Halo[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j+2] = tmpArray[j];
		}
	}

	return new CArray(ParticleSize*nrParticles+2,Array); //Memory leak
}





