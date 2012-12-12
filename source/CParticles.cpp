#include "CParticles.h"

using namespace std;
//using namespace boost;

CParticles::CParticles(){
	NrParticles = 0;
	ParticleSize = myConstants::constants.ParticleSize;
	flag = 1;
}

CParticles::~CParticles(){
	//for (int i = 0; i < nrParticles;i++){
	//	delete Particles[i];// <- correct?
	//}
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CParticles::CParticles(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;


	if (inArray->len() % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	NrParticles = (inArray->len())/ParticleSize;

	for (int i = 0; i<NrParticles;i++){
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
	ParticleSize = myConstants::constants.ParticleSize;

	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	NrParticles = (inArray->len())/ParticleSize;

	for (int i = 0; i<NrParticles;i++){
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
	for (int i = 0; i < NrParticles;i++){
		Particles[i]->print();
	}
}

//Return nr of Particles
int CParticles::getNrParticles(){
	return NrParticles;
}


//Return particle nr #element
CParticle* CParticles::operator[](int element){
	if (element >= NrParticles || element < -NrParticles) {
		throw "Index out of bounds";
	}
	else if (element < 0){
		return Particles[NrParticles+element];
	}
	else {
		return Particles[element];
	}
}


//Return particle nr #element
CParticle* CParticles::get(int element){
	if (element >= NrParticles || element < -NrParticles) {
		throw "Particle out of bounds";
	}
	else if (element < 0){
		return Particles[NrParticles+element];
	}
	else {
		return Particles[element];
	}
}


vector<CParticle*>* CParticles::getParticles() {
	return &Particles;
}


//Add a particle to CParticles
void CParticles::addParticle(CParticle* inParticle){
	NrParticles += 1;
	Particles.push_back(inParticle);
}


//Add several particles to CParticles
void CParticles::addParticles(CParticles* inParticles){
	NrParticles += inParticles->getNrParticles();

	for (int i = 0; i < inParticles->getNrParticles();i++){
		Particles.push_back(inParticles->get(i));
	}
}



//Convert CParticles to a CArray on the form
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CArray* CParticles::Particles2Array(){
	double* Array = new double [ParticleSize*NrParticles]; // Memory leak

	for (int i = 0; i < NrParticles;i++){
		double* tmpArray = Particles[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j] = tmpArray[j];
		}
	}
	return new CArray(ParticleSize*NrParticles,Array); //Memory leak
}



//Set the flag
void CParticles::setFlag(int inFlag){
	flag = inFlag;
	for (int i = 0; i < NrParticles; i++) {
		Particles[i]->setFlag(inFlag);
	}
}

int CParticles::getFlag(){
	return flag;
	//for (int i = 0; i < NrParticles; i++) {
	//	Particles[i]->setFlag(inFlag);
	//}
}


//Removes all particles in CParticles from a linked list
void CParticles::RemoveFromList(){
	for (int i = 0; i < NrParticles; i++){
		Particles[i]->RemoveFromList();
	}
}


//Copy a CParticles to a new CParticles object
void CParticles::copy(CParticles& p) {
	Particles= *p.getParticles();
	NrParticles = p.getNrParticles();
	flag = p.getFlag();
	ParticleSize = myConstants::constants.ParticleSize;
}

//Clear and remove all information from CParticles
void CParticles::clear(){
	Particles.clear();
	NrParticles = 0;
	flag = 1;
	ParticleSize = myConstants::constants.ParticleSize;
}
