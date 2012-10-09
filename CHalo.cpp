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

	Halo.set(inArray);
	nrParticles = Halo.getnrParticles();
	HaloMass = 0;
}



CParticles* CHalo::getCParticles(){
	return &Halo;
}

int CHalo::getnrParticles(){
	return nrParticles;//Halo.getnrParticles();
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
CArray*	 CHalo::Halo2Array(){
	return Halo.Particles2Array();
}


void CHalo::addParticle(CParticle* inParticle){
	nrParticles += 1;
	Halo.addParticle(inParticle);
}


CParticle* CHalo::getParticle(int element){
	return Halo[element];
}


void CHalo::print(){
	Halo.print();
}

void CHalo::addHalo(CHalo* inHalo){
	HaloMass += inHalo->getHaloMass();
	Halo.addParticles(inHalo->getCParticles());
}

double CHalo::getHaloMass(){
	return HaloMass;
}
