#include "CHalo.h"

using namespace std;

CHalo::CHalo(){
	ParticleSize = myConstants::constants.ParticleSize;
	NrParticles = 0;
	HaloMass = 0;
}

//Create a CHalo from CParticles
CHalo::CHalo(CParticles* inParticles){
	ParticleSize = myConstants::constants.ParticleSize;
	Halo = *inParticles;
	NrParticles = inParticles->getNrParticles();
	HaloMass = 0;
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CHalo::CHalo(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;

	Halo.set(inArray);
	NrParticles = Halo.getNrParticles();
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
int CHalo::getNrParticles(){
	return NrParticles;
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

//Return CParticles
CParticles* CHalo::getParticles(){
	return &Halo;
}




//Add a particle to the array
void CHalo::addParticle(CParticle* inParticle){
	NrParticles += 1;
	Halo.addParticle(inParticle);
}




//Add a halo to the halo
void CHalo::addHalo(CHalo* inHalo){
	HaloMass += inHalo->getHaloMass();
	Halo.addParticles(inHalo->getParticles());
}

//Add several particles to the Halo
void CHalo::addParticles(CParticles* inParticles){
	Halo.addParticles(inParticles);
	NrParticles+=inParticles->getNrParticles();
}


double CHalo::SigmaP(){
	double sum = 0;
	for (int i = 0; i < NrParticles; i++) {
		sum += Halo[i]->getP().Length();
	}
	return sum/NrParticles;
}


double CHalo::SigmaV(){
	double sum = 0;
	for (int i = 0; i < NrParticles; i++) {
		sum += Halo[i]->getV().Length();
	}
	return sum/NrParticles;
}
