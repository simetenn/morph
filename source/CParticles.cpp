#include "CParticles.h"

using namespace std;
using namespace boost;


//Sorts Mass and distance from center of halo f after distance from halo
bool ParticleAndDistanceSortFunc(CParticle a, CParticle b){
	return a.getR() < b.getR();
}



CParticles::CParticles(){
	NrParticles = 0;
	ParticleSize = myConstants::constants.ParticleSize;
	flag = 1;
}

CParticles::~CParticles(){
	/*for (int i = 0; i < NrParticles;i++){
	  if ( Particles[i] != NULL)
	  delete Particles[i]; // <- correct?
	  }*/
	kill();
	//clear();
	//Particles.clear();
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CParticles::CParticles(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;


	if (inArray->len() % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	NrParticles = (inArray->len())/ParticleSize;
	Particles.resize(NrParticles);
	
	for (int i = 0; i<NrParticles;i++){
		CParticle* tmpParticle = &Particles[i];
		tmpParticle->setHalo(inArray->get(ParticleSize*i + 0));
		tmpParticle->setMass(inArray->get(ParticleSize*i + 1));
		tmpParticle->setPosition(inArray->get(ParticleSize*i + 2),
								 inArray->get(ParticleSize*i + 3),
								 inArray->get(ParticleSize*i + 4));
		tmpParticle->setVelocity(inArray->get(ParticleSize*i + 5),
								 inArray->get(ParticleSize*i + 6),
								 inArray->get(ParticleSize*i + 7));
		tmpParticle->setAcceleration(inArray->get(ParticleSize*i + 8),
									 inArray->get(ParticleSize*i + 9),
									 inArray->get(ParticleSize*i + 10));
	}
}



//Sets a already existing CParticles to contain the values from
//a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
//Similar to the constructor
void CParticles::set(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;


	if (inArray->len() % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}
	
	NrParticles = (inArray->len())/ParticleSize;
	Particles.clear();
	Particles.resize(NrParticles);
	
	for (int i = 0; i<NrParticles;i++){
		CParticle* tmpParticle = &Particles[i];
		tmpParticle->setHalo(inArray->get(ParticleSize*i + 0));
		tmpParticle->setMass(inArray->get(ParticleSize*i + 1));
		tmpParticle->setPosition(inArray->get(ParticleSize*i + 2),
								 inArray->get(ParticleSize*i + 3),
								 inArray->get(ParticleSize*i + 4));
		tmpParticle->setVelocity(inArray->get(ParticleSize*i + 5),
								 inArray->get(ParticleSize*i + 6),
								 inArray->get(ParticleSize*i + 7));
		tmpParticle->setAcceleration(inArray->get(ParticleSize*i + 8),
									 inArray->get(ParticleSize*i + 9),
									 inArray->get(ParticleSize*i + 10));
	}
}



//Print all particles
void CParticles::print(){
	for (int i = 0; i < NrParticles;i++){
		Particles[i].print();
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
		return &Particles[NrParticles+element];
	}
	else {
		return &Particles[element];
	}
}


//Return particle nr #element
CParticle* CParticles::get(int element){
	if (element >= NrParticles || element < -NrParticles) {
		throw "Particle out of bounds";
	}
	else if (element < 0){
		return &Particles[NrParticles+element];
	}
	else {
		return &Particles[element];
	}
}


vector<CParticle>* CParticles::getParticles() {
	return &Particles;
}


//Add a particle to CParticles
void CParticles::addParticle(CParticle* inParticle){
	NrParticles += 1;
	Particles.push_back(*inParticle);
}



//Add several particles to CParticles
void CParticles::addParticles(CParticles* inParticles){
	NrParticles += inParticles->getNrParticles();

	for (int i = 0; i < inParticles->getNrParticles();i++){
		Particles.push_back(*inParticles->get(i));
	}
}


//remove particle #element from CParticles
void CParticles::removeParticle(int element){
	Particles.erase(Particles.begin() + element);
	NrParticles--;
}



//Convert CParticles to a CArray on the form
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CArray* CParticles::Particles2Array(){
	CArray* Array = new CArray (ParticleSize*NrParticles); // <--- kill
	double* tmpArray;
	for (int i = 0; i < NrParticles;i++){
		tmpArray = Particles[i].Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array->set(i*ParticleSize+j, tmpArray[j]);
		}
		if (tmpArray != NULL) {
			delete tmpArray;
			tmpArray = NULL;
		}
	}

	return Array;
}



//Set the flag
void CParticles::setFlag(int inFlag){
	flag = inFlag;
	for (int i = 0; i < NrParticles; i++) {
		Particles[i].setFlag(inFlag);
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
		Particles[i].RemoveFromList();
	}
}


//Copy a CParticles to a new CParticles object
void CParticles::copy(CParticles* p) {
	Particles= *p->getParticles();
	NrParticles = p->getNrParticles();
	flag = p->getFlag();
	ParticleSize = myConstants::constants.ParticleSize;
}

//Clear and remove all information from CParticles, it does not delete particles from the memory
void CParticles::clear(){
	//Particles.clear();
	NrParticles = 0;
	flag = 1;
	ParticleSize = myConstants::constants.ParticleSize;
}



//Delete all information from CParticles, also deletes particles from the memory
void CParticles::kill(){
	Particles.clear();
	NrParticles = 0;
	flag = 1;
	ParticleSize = myConstants::constants.ParticleSize;
}



void CParticles::SortParticlesDistance(CVector& inMeanP){
	for (int i = 0; i < NrParticles; i++) {
		Particles[i].setR((inMeanP - Particles[i].getP()).Length());
	}
	sort(Particles.begin(),Particles.end(),&ParticleAndDistanceSortFunc);
	/*cout << "sorted particle distances " << endl;
	for (int i = 0; i < NrParticles; i++) {
		cout << Particles[i].getR() << endl;
		}*/
	//Halo.kill();
	//r.resize(NrParticles);
}
