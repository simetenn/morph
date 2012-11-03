#include "CHalo.h"

using namespace std;

CHalo::CHalo(){
	ParticleSize = myConstants::constants.ParticleSize;
	NrParticles = 0;
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
}

//Create a CHalo from CParticles
CHalo::CHalo(CParticles* inParticles){
	ParticleSize = myConstants::constants.ParticleSize;
	Halo = *inParticles;
	NrParticles = inParticles->getNrParticles();
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
}


//Creates CParticles from a CArray on the following form:
//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
CHalo::CHalo(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;

	//Halo.set(inArray);
	Halo = CParticles(inArray);
	NrParticles = Halo.getNrParticles();
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
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


//Return the total mass of the halo
double CHalo::getMass(){
	return Mass;
}


//Get the position of the center of the halo
CVector* CHalo::getMeanP(){
	return &MeanP;
}


//Get the velocity of the center of the halo
CVector* CHalo::getMeanV(){
	return &MeanV;
}


//Get the standard deviation of the positions in a halo
CVector* CHalo::getSigmaP(){
	return &SigmaP;
}


//Get the standard deviation of the velocities in a halo
CVector* CHalo::getSigmaV(){
	return &SigmaV;
}


//Return nr of particles
int CHalo::getNrParticles(){
	return NrParticles;
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


void CHalo::setNrParticles(int element){
	NrParticles = element;
}


//Add a particle to the array
void CHalo::addParticle(CParticle* inParticle){
	NrParticles += 1;
	Halo.addParticle(inParticle);
}




//Add a halo to the halo
void CHalo::addHalo(CHalo* inHalo){
	//Mass += inHalo->getMass();
	Halo.addParticles(inHalo->getParticles());
}

//Add several particles to the Halo
void CHalo::addParticles(CParticles* inParticles){
	Halo.addParticles(inParticles);
	NrParticles+=inParticles->getNrParticles();
}

//Calculate all the statistics relevant for a halo, such as:
//mean P, mean V, sigma P, sigma V and mass
void CHalo::CalculateStatistics(){
	MeanP = 0;
	MeanV = 0;
	Mass = 0;
	SigmaP = 0;
	SigmaV = 0;

	for (int i = 0; i < NrParticles; i++) {
		Mass += Halo[i]->getMass();
		MeanP = MeanP + Halo[i]->getP();
		MeanV = MeanV + Halo[i]->getV();
	}
	MeanP = MeanP/NrParticles;
	MeanV = MeanV/NrParticles;

	for (int i = 0; i < NrParticles; i++) {
		SigmaP = SigmaP + (Halo[i]->getP() - MeanP).pow(2);
		SigmaV = SigmaP + (Halo[i]->getV() - MeanV).pow(2);
	}

	SigmaP = SigmaP.sqrt()/(NrParticles-1);
	SigmaV = SigmaV.sqrt()/(NrParticles-1);
}



double CHalo::LinkingLength(){
	int tmpNrParticles = NrParticles;

	if (NrParticles > 10000) tmpNrParticles = 10000;
	vector<double> LinkingLengths (tmpNrParticles);
	int tmpLinkingLength,prevtmpLinkingLength;

	//prevtmpLinkingLength = Halo[0]->PhaseSpaceDistance(Halo[1],tmpSigmaP,tmpSigmaV);
	for (int i = 0; i < tmpNrParticles; i++) {
		if (i!=0) {
			prevtmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[0],&SigmaP,&SigmaV);
		}
		for (int j = 1; j < tmpNrParticles; j++) {
			tmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[j],&SigmaP,&SigmaV);
			if (i!=j &&	 tmpLinkingLength < prevtmpLinkingLength) {
				prevtmpLinkingLength = tmpLinkingLength;
			}
		}
		LinkingLengths[i] = tmpLinkingLength;
	}

	sort(LinkingLengths.begin(),LinkingLengths.end());
	cout << LinkingLengths[3000] << endl;
	cout << LinkingLengths[7000] << endl;
	cout << LinkingLengths[0] << endl;
	return LinkingLengths[(int) LinkingLengths.size()*myConstants::constants.f];
}



//save the data for a single halo to file
void CHalo::saveHalo(){
	fstream file;
	double* tmpArray;
	//string out = myConstants::constants.outFile;
	file.open("Halo.dat", ios::out);

	//Saves data for each particle to file
	for (int i = 0;i<NrParticles;i++){
		tmpArray = Halo[i]->Particle2Array();
		for (int j = 0; j < ParticleSize; j++) {
			file << tmpArray[j] << " ";
		}
		if (i != NrParticles-1) file << endl;
	}
	file.close();
}


void CHalo::saveP(){
	fstream file;
	int HaloID = 0;
	//string out = myConstants::constants.outFile;
	file.open("positions.dat", ios::out);

	//Saves position data for each particle to file
	cout << "Saving positional data" << endl;
	saveHaloP(file,HaloID);
	for (int i = 0;i < NrSubHalos; i++) {
		SubHalos[i]->saveHaloP(file,HaloID);
	}

	file.close();
}

void CHalo::saveHaloP(fstream& fileName, int& HaloID){
	CVector tmpP;

	for (int i = 0;i < NrParticles; i++){
		tmpP = Halo[i]->getP();
		fileName << tmpP.x() << " " << tmpP.y()<< " " << tmpP.z()<< " " <<	HaloID << endl;
	}
	HaloID++;
}



void CHalo::saveStatX(){
	fstream file;
	int HaloID = 0;
	//string out = myConstants::constants.outFile;
	file.open("statX.dat", ios::out);

	//Saves position data for each particle to file
	cout << "Saving statistical data" << endl;
	saveHaloStatX(file,HaloID);
	for (int i = 0;i < NrSubHalos; i++) {
		SubHalos[i]->saveHaloStatX(file,HaloID);
	}

	file.close();
}

void CHalo::saveHaloStatX(fstream& fileName, int& HaloID){
	CVector tmpP;

	fileName << HaloID << " " << MeanP.x()<< " " << MeanV.x() << " " <<	SigmaP.x() << " " << SigmaV.x() << endl;
	HaloID++;
}




void CHalo::SplitHalo(int LinkingLength){
	if (Halo.getNrParticles() < myConstants::constants.HaloLimit) {
		CalculateStatistics();
		return;
	}
	FriendOfFriendPhaseSpace(LinkingLength);
	for (int i = 0;i < NrSubHalos; i++) {
		SubHalos[i]->SplitHalo(LinkingLength*0.7);
	}
}



void CHalo::FriendOfFriendPhaseSpace(int LinkingLength){
	CalculateStatistics();

	vector<CHalo*> tmpHalos;

	//allParticles = Halo;
	searchParticle = Halo[0];//Halos[0]->get(0);
	CParticle* Particle = searchParticle;


	//Create a linked list of all particles
	Particle->prev=NULL;
	for (int i=1; i < NrParticles;i++){
		Particle->setFlag(0);
		Particle->next = Halo[i];
		Particle->next->prev = Particle;
		Particle = Particle->next;
	}
	Particle->setFlag(0);
	Particle->next = NULL;

	//Using recursion to link all particles belonging to a halo
	while (true){
		Particle = nextParticle();

		if (Particle == NULL) break;
		else {
			CHalo* tmpHalo = new CHalo();
			tmpHalos.push_back(tmpHalo);

			//Calls findNeighbors to find the particles within linking distance
			findNeighborsPhaseSpace(Particle, tmpHalo, LinkingLength);
		}
	}


	//Only saving halos that has more than HaloLimit particles, updating NrInHalos
	SubHalos.clear();
	for (int i = 0; i < tmpHalos.size(); i++){
		if (tmpHalos[i]->getNrParticles() > myConstants::constants.HaloLimit){
			SubHalos.push_back(tmpHalos[i]);
			//NrInHalo.push_back(tmpHalos[i]->getNrParticles());
		}
		NrSubHalos = SubHalos.size();
	}
}


//Flags the given particle and adds it to the given halo.
//Then finds the neighboring particles, within the linking length.
//Before calling itself for each particle found this way
void CHalo::findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, int LinkingLength){
	inParticle->setFlag(1);
	inParticle->RemoveFromList();
	inHalo->addParticle(inParticle);

	CHalo FriendList;
	//Loops through all particles and finds the ones
	//within the linking length not assigned to a halo. Then adds them to a temporary halo
	for (int i = 0; i<NrParticles;i++){
		if (Halo[i]->getFlag()==0){
			double distance = inParticle->PhaseSpaceDistance(Halo[i],&SigmaP,&SigmaV);
			//cout << distance << " " << myConstants::constants.PhaseDistance<<endl;
			if (distance < LinkingLength){
				Halo[i]->setFlag(1);
				FriendList.addParticle(Halo[i]);
			}
		}
	}

	//Finds the neighboring particles for each particle found to be within
	//the linking length and adds them to the given halo
	for (int i = 0; i<FriendList.getNrParticles();i++){
		findNeighborsPhaseSpace(FriendList[i],inHalo, LinkingLength);
	}
}


CParticle* CHalo::nextParticle(){
	while (true){
		if (searchParticle->getFlag() == 0)
			return searchParticle;

		searchParticle = searchParticle->next;

		if (searchParticle == NULL)
			return NULL;

	}
}


