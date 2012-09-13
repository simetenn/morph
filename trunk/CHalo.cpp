#include "CHalo.h"


using namespace std;

CHalo::CHalo(){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	CParticles tmpParticles;
	nrParticles = tmpParticles.getnrParticles();
	HaloMass = 0;
}

CHalo::CHalo(CParticles* inParticles){
	ParticleSize = inParticles->get(0)->getParticleSize();
	Halo = *inParticles;
	nrParticles = inParticles->getnrParticles();
	HaloMass = 0;
}

CHalo::CHalo(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	Halo = CParticles(inArray);
	//ParticleSize = Halo[0]->Particle[0].getParticleSize(); //Get this to work!
	nrParticles = Halo.getnrParticles();
	HaloMass = 0;
}


CHalo::~CHalo(){

}

/*CHalo::CHalo(CArray* inArray){
  HaloMass = 0;
  Halo.initialize_CParticles(inArray);
  }*/



CParticle* CHalo::operator[](int element){
	return Halo[element];
}

CParticle* CHalo::get(int element){
	return Halo[element];
}





//Convert from one halo to an array
CArray*	 CHalo::Halo2Array(){//pointer
	return Halo.Particles2Array();
	
	
	//int ParticleSize =
	/*double* Array = new double [ParticleSize*nrParticles]; // Memory leak
	Array[0] = 1;
	Array[1] = nrParticles;

	for (int i = 0; i < nrParticles;i++){
		double* tmpArray = Halo[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j+2] = tmpArray[j];
		}
	}

	return new CArray(ParticleSize*nrParticles+2,Array); //Memory leak*/
}





