#include "CHalo.h"


using namespace std;

CHalo::CHalo(){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	nrParticles = 0;
	HaloMass = 0;
}

//Create a CHalo from CParticles
CHalo::CHalo(CParticles* inParticles){
	ParticleSize = inParticles->get(0)->getParticleSize();
	Halo = *inParticles;
	nrParticles = inParticles->getnrParticles();
	HaloMass = 0;
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CHalo::CHalo(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	
	Halo.set(inArray);
	nrParticles = Halo.getnrParticles();
	HaloMass = 0;
}



CHalo::~CHalo(){
}


//Print all particles in halo
void CHalo::print(){
	Halo.print();
}


//Convert from one halo to an CArray
CArray*	 CHalo::Halo2Array(){
	return Halo.Particles2Array();
}



//Return nr of particles
int CHalo::getnrParticles(){
	return nrParticles;
}

//Return the total mass of the halo
double CHalo::getHaloMass(){
	return HaloMass;
}

//Return particle nr #element
CParticle* CHalo::operator[](int element){
	return Halo[element];
}


//Return particle nr #element
CParticle* CHalo::get(int element){
	return Halo[element];
}

/*CParticle* CHalo::getParticle(int element){
	return Halo[element];
	}*/



//Return CParticles
CParticles* CHalo::getParticles(){
	return &Halo;
}




//Add a particle to the array
void CHalo::addParticle(CParticle* inParticle){
	nrParticles += 1;
	Halo.addParticle(inParticle);
}




//Add a halo to the halo
void CHalo::addHalo(CHalo* inHalo){
	HaloMass += inHalo->getHaloMass();
	Halo.addParticles(inHalo->getParticles());
}

