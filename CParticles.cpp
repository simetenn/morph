#include "CParticles.h"

using namespace std;
using namespace boost;

CParticles::CParticles(){
	nrParticles = 0;
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
}

CParticles::~CParticles(){
	//for (int i = 0; i < nrParticles;i++){
	//	delete Particles[i];// <- correct?
	//}
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CParticles::CParticles(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	if (inArray->len() % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len())/ParticleSize;
	int particle_count = 0;

	for (int i = 0; i<nrParticles;i++){
		double* tmpArray = new double [ParticleSize];

		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(ParticleSize*i+j);
		}

		CParticle * tmpParticle = new CParticle(tmpArray);
		Particles.push_back(tmpParticle);
	}
}



//Sets a already existing CParticles to contain the values from
//a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
//Similar to the constructor
void CParticles::set(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len())/ParticleSize;
	int particle_count = 0;

	for (int i = 0; i<nrParticles;i++){
		double* tmpArray = new double [ParticleSize];

		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(ParticleSize*i+j);
		}

		CParticle * tmpParticle = new CParticle(tmpArray);
		Particles.push_back(tmpParticle);
	}
}



//Print all particles
void CParticles::print(){
	for (int i = 0; i < nrParticles;i++){
		Particles[i]->print();
	}
}

//Return nr of Particles
int CParticles::getnrParticles(){
	return nrParticles;
}


//Return particle nr #element
CParticle* CParticles::operator[](int element){
	if (element >= nrParticles || element < -nrParticles) {
		throw "Index out of bounds";
	}
	else if (element < 0){
		return Particles[nrParticles+element];
	}
	else {
		return Particles[element];
	}
}


//Return particle nr #element
CParticle* CParticles::get(int element){
	if (element >= nrParticles || element < -nrParticles) {
		throw "Index out of bounds";
	}
	else if (element < 0){
		return Particles[nrParticles+element];
	}
	else {
		return Particles[element];
	}
	}


//Return particle nr #element
/*CParticle* CParticles::getParticle(int element){
	if (element >= nrParticles){
		cout << "Particle out of bounds" << endl;
	}
	else {
		return Particles[element];
	}
	}*/


//Add a particle to CParticles
void CParticles::addParticle(CParticle* inParticle){
	nrParticles += 1;
	Particles.push_back(inParticle);
}


//Add several particles to CParticles
void CParticles::addParticles(CParticles* inParticles){
	nrParticles += inParticles->getnrParticles();

	for (int i = 0; i < inParticles->getnrParticles();i++){
		Particles.push_back(inParticles->get(i));
	}
}



//Convert CParticles to a CArray on the form
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CArray* CParticles::Particles2Array(){
	double* Array = new double [ParticleSize*nrParticles]; // Memory leak

	for (int i = 0; i < nrParticles;i++){
		double* tmpArray = Particles[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j] = tmpArray[j];
		}
	}
	return new CArray(ParticleSize*nrParticles,Array); //Memory leak
}
