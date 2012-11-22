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

//Create a new CHalo from a CHalo
CHalo::CHalo(CHalo* inHalo){
	copy(inHalo);
}

CHalo::~CHalo(){
}


//Print all particles in halo
void CHalo::print(){
	Halo.print();
}

void CHalo::printHalo(int& count){
	cout << "__________________________________" << endl;
	cout << "								   " << endl;
	cout << "Halo nr: " << count << endl;
	cout << "Nr of particles in halo: " << NrParticles << endl;
	cout << "Position of halo: ";
	MeanP.print();
	cout << "Velocity of halo: ";
	MeanV.print();
	cout << "__________________________________" << endl;
	count++;

}

void CHalo::printSubHalos(){
	int count = 0;
	printSubHalo(count);
}

void CHalo::printSubHalo(int& count){
	printHalo(count);
	
	for (int i = 0; i < SubHalos.size(); i++) {
		SubHalos[i]->printSubHalo(count);
	}
}

//Clear and remove all information from a CHalos object
void CHalo::clear() {
	Halo.clear();
	NrParticles = 0;
	Mass = 0;
	//NrSubHalos = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
	ParticleSize = myConstants::constants.ParticleSize;
}

//Clear and remove particle information, but keeping halo information
void CHalo::clean() {
	Halo.clear();
	NrParticles = 0;
	//NrSubHalos = 0;
	ParticleSize = myConstants::constants.ParticleSize;
}

//Clear and remove particle information, but keeping halo information. For all SubHalos
void CHalo::cleanSubHalos(){
	clean();
	for (int i = 0;i < SubHalos.size(); i++) {
		SubHalos[i]->cleanSubHalos();
	}
}


//Copy a CHalos object
void CHalo::copy(CHalo* inHalo) {
	Halo.copy(*inHalo->getParticles());
	NrParticles = inHalo->getNrParticles();
	Mass = inHalo->getMass();
	//NrSubHalos = 0;
	MeanP=*inHalo->getMeanP();
	MeanV=*inHalo->getMeanV();
	SigmaP=*inHalo->getSigmaP();
	SigmaV=*inHalo->getSigmaV();
	ParticleSize = myConstants::constants.ParticleSize;
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

//return the number of subHalos
int CHalo::getNrSubHalos(){
	return SubHalos.size();
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



void CHalo::printStatistics(){
	cout << "Mean Position" << endl;
	MeanP.print();
	cout << endl;
	cout << "Standard deviation, Position" << endl;
	MeanV.print();
	cout << endl;
	cout << "Mean Velocity" << endl;
	SigmaP.print();
	cout << endl;
	cout << "Standard deviation, Velocity" << endl;
	SigmaV.print();
	cout << endl;
}


double CHalo::LinkingLength(){
	int tmpNrParticles = NrParticles;
	double delta = 1;
	if (NrParticles > 10000) {
		delta = NrParticles/10000;
		tmpNrParticles = 10000;
	}
	

	vector<double> LinkingLengths (tmpNrParticles);
	int tmpLinkingLength,prevtmpLinkingLength;

	prevtmpLinkingLength = Halo[0]->PhaseSpaceDistance(Halo[1],&SigmaP,&SigmaV);
	for (double j = delta; j < tmpNrParticles; j+=delta) {
		tmpLinkingLength = Halo[0]->PhaseSpaceDistance(Halo[(int)j],&SigmaP,&SigmaV);
		if (tmpLinkingLength < prevtmpLinkingLength) {
			prevtmpLinkingLength = tmpLinkingLength;
		}
	}

	LinkingLengths[0] = prevtmpLinkingLength;

	for (int i = 1; i < tmpNrParticles; i++) {
		prevtmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[0],&SigmaP,&SigmaV);
		for (int j = 1; j < tmpNrParticles; j++) {
			tmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[j],&SigmaP,&SigmaV);
			if (i!=j &&	 tmpLinkingLength < prevtmpLinkingLength) {
				prevtmpLinkingLength = tmpLinkingLength;
			}
		}
		//cout << tmpLinkingLength << endl;
		LinkingLengths[i] = prevtmpLinkingLength;
	}

	sort(LinkingLengths.begin(),LinkingLengths.end());
	//cout << LinkingLengths.size()<<endl;;
	//cout << LinkingLengths[0] << endl;
	//cout << LinkingLengths[LinkingLengths.size()-1] << endl;
	//cout << LinkingLengths[(int) LinkingLengths.size()*myConstants::constants.f] << endl;
	return LinkingLengths[(int) LinkingLengths.size()*myConstants::constants.f];
}



//save the data for a single halo to file
void CHalo::saveHalo(){
	fstream file;
	double* tmpArray;// = double[ParticleSize];
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




//Save position data to file for all subhalos
void CHalo::saveP(){
	fstream file;
	int HaloID = 0;
	//string out = myConstants::constants.outFile;
	file.open("positions.dat", ios::out);

	//Saves position data for each particle to file
	cout << "Saving positional data" << endl;
	savePRec(file,HaloID);
	file.close();
}

//Recursivly goes trough all subhalos and write the position data to file
void CHalo::savePRec(fstream& fileName, int& HaloID){
	saveHaloP(fileName,HaloID);
	for (int i = 0;i < SubHalos.size(); i++) {
		SubHalos[i]->savePRec(fileName,HaloID);
	}
}


//Saves position data for each particle to file for a single halo
void CHalo::saveHaloP(fstream& fileName, int& HaloID){
	CVector tmpP;

	for (int i = 0;i < NrParticles; i++){
		tmpP = Halo[i]->getP();
		fileName << tmpP.x() << " " << tmpP.y()<< " " << tmpP.z()<< " " <<	HaloID << endl;
	}
	HaloID++;
}



//Save the statistical data in the x direction, for the halo and all subhalos
void CHalo::saveStatX(){
	fstream file;
	int HaloID = 0;
	//string out = myConstants::constants.outFile;
	file.open("statX.dat", ios::out);

	//Saves position data for each particle to file
	cout << "Saving statistical data" << endl;
	saveHaloStatX(file,HaloID);
	for (int i = 0;i < SubHalos.size(); i++) {
		SubHalos[i]->saveHaloStatX(file,HaloID);
	}

	file.close();
}

//Save the statistical data in the x direction, for a single halo
void CHalo::saveHaloStatX(fstream& fileName, int& HaloID){
	CVector tmpP;

	fileName << HaloID << " " << MeanP.x()<< " " << MeanV.x() << " " <<	SigmaP.x() << " " << SigmaV.x() << endl;
	HaloID++;
}



double CHalo::PhaseSpaceDistanceHalo(CParticle* inParticle, CVector* inSigmaP, CVector* inSigmaV){
	/*MeanV.print();
	MeanP.print();
	cout << inSigmaV->Length2() << endl;
	cout << SigmaV.Length2() << endl;
	
	cout << inSigmaP->Length2() << endl;
	cout << SigmaP.Length2() << endl;
	cout << sqrt((inParticle->getP() - MeanP).Length2()/inSigmaP->Length2() +  (inParticle->getV() - MeanV).Length2()/inSigmaV->Length2()) << endl;
	cout << sqrt((inParticle->getP() - MeanP).Length2()/SigmaP.Length2() +  (inParticle->getV() - MeanV).Length2()/SigmaV.Length2()) << endl;*/
	//return sqrt((inParticle->getP() - MeanP).Length2()/SigmaP.Length2() +  (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
	return sqrt((inParticle->getP() - MeanP).Length2()/inSigmaP->Length2() +  (inParticle->getV() - MeanV).Length2()/inSigmaV->Length2());
}


//Splits the halo into subhalos using the friend of friend methode in phase space.
//Then calculates the subhalos of the subhalo recursivly until either the halo limit
//is reached or no particles are found being linked together. the linking length is
//sett to decrease by f for each iteration.
void CHalo::SplitHalo(){
	if (Halo.getNrParticles() < myConstants::constants.HaloLimit) {
		//cout << "here?" << endl;
		return;
	}
	//cout << "in splithalo" << endl;
	FriendOfFriendPhaseSpace();
	clean();
	//cout << SubHalos.size() << endl;
	for (int i = 0;i < SubHalos.size(); i++) {
		SubHalos[i]->SplitHalo();
	}
}




//Calculating Friend of Friend using recursion, in phase space.
//It must scales as N^2
void CHalo::FriendOfFriendPhaseSpace(){
	CalculateStatistics();

	CHalo tmpHalo;
	vector<CHalo*> tmpHalos;


	searchParticle = Halo[0];
	CParticle* Particle = searchParticle;
	SubHalos.clear();

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
	//double Length = LinkingLength()*myConstants::constants.b;

	double L = LinkingLength();//*myConstants::constants.b;
	//cout << "Linking Length " << Length << endl;
	//Using recursion to link all particles belonging to a halo
	while (true){
		Particle = nextParticle();

		if (Particle == NULL) break;
		else {
			//CHalo* tmpHalo = new CHalo();
			//tmpHalos.push_back(tmpHalo);

			tmpHalo.clear();
			//Calls findNeighbors to find the particles within linking distance
			Particle->setFlag(1);
			Particle->RemoveFromList();
			findNeighborsPhaseSpace(Particle, &tmpHalo, L);
			//cout << tmpHalo.getNrParticles() << endl;
			if (tmpHalo.getNrParticles() > myConstants::constants.HaloLimit){
				cout << "Saving halo with " << tmpHalo.getNrParticles() << endl;
				SubHalos.push_back(new CHalo(&tmpHalo));
			}
		}
	}
}


//Flags the given particle and adds it to the given halo.
//Then finds the neighboring particles, within the phase space linking length.
//Before calling itself for each particle found this way
void CHalo::findNeighborsPhaseSpace(CParticle* inParticle, CHalo* inHalo, int L){
	inHalo->addParticle(inParticle);

	CHalo FriendList;
	//Loops through all particles and finds the ones
	//within the linking length not assigned to a halo. Then adds them to a temporary halo
	for (int i = 0; i<NrParticles;i++){
		if (Halo[i]->getFlag()==0){
			double distance = inParticle->PhaseSpaceDistance(Halo[i],&SigmaP,&SigmaV);
			//cout << distance << " " << L <<endl;
			if (distance < L){
				Halo[i]->setFlag(1);
				FriendList.addParticle(Halo[i]);
				Halo[i]->RemoveFromList();
			}
		}
	}

	//Finds the neighboring particles for each particle found to be within
	//the linking length and adds them to the given halo
	for (int i = 0; i<FriendList.getNrParticles();i++){
		findNeighborsPhaseSpace(FriendList[i],inHalo, L);
	}
}


//Find the next particle to assign to a Halo
CParticle* CHalo::nextParticle(){
	while (true){
		if (searchParticle->getFlag() == 0)
			return searchParticle;

		searchParticle = searchParticle->next;

		if (searchParticle == NULL)
			return NULL;

	}
}


void CHalo::assignParticles(CParticles* allParticles){
	/*searchParticle = allParticles->get(0);
	CParticle* Particle = searchParticle;

	//Create a linked list of all particles
	Particle->prev=NULL;
	for (int i=1; i < allParticles->getNrParticles();i++){
		Particle->setFlag(0);
		Particle->next = allParticles->get(i);;
		Particle->next->prev = Particle;
		Particle = Particle->next;
	}
	Particle->setFlag(0);
	Particle->next = NULL;




	while (true){

		Particle = nextParticle();
		if (Particle == NULL) break;
		else {
			findHalo(Particle,);
		}
		}*/
	for (int i = 0; i < allParticles->getNrParticles(); i++) {
		findHalo(allParticles->get(i),this);
	}
}

void CHalo::findHalo(CParticle* inParticle, CHalo* inHalo){

	//cout << "in Find Halo" << endl;
	
	double DistanceArray[inHalo->getNrSubHalos()];
	int index = 0;
	double distance;
	CVector* tmpSigmaP = inHalo->getSigmaP();
	CVector* tmpSigmaV = inHalo->getSigmaV();
	//inHalo->getMeanP()->print();
	//SubHalos[0]->getMeanP()->print();
	//SubHalos[0]->SubHalos[0]->getMeanP()->print();
	//exit(1);
	distance = inHalo->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
	//cout << "Main Halo " << distance << endl;
	for (int i = 0;i < inHalo->getNrSubHalos(); i++) {
		DistanceArray[i] = inHalo->SubHalos[i]->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
		//cout << "subHalo " << DistanceArray[i] << endl;
	}
	
	for (int i = 0; i < inHalo->getNrSubHalos(); i++) {
		if (DistanceArray[i] < distance) {
			index = i+1;
			distance = DistanceArray[i];
		}
	}

	//cout << index << endl;
	if (index == 0){
		inHalo->addParticle(inParticle);
	}
	else {
		//cout << "In the subhalo" << endl;
		findHalo(inParticle, SubHalos[index-1]);
	}
}

void CHalo::createSubHalos(){

	CParticles allParticles = Halo;

	SplitHalo();
	//saveStatX();
	//printSubHalos();
	assignParticles(&allParticles);
	printSubHalos();
	saveP();

}

