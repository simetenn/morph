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

	NrParticles = inArray->get(0);
	Mass = inArray->get(1);
	MeanP.Set(inArray->get(2),inArray->get(3),inArray->get(4)); 
	MeanV.Set(inArray->get(5),inArray->get(6),inArray->get(7));
	SigmaP.Set(inArray->get(8),inArray->get(9),inArray->get(10));
	SigmaV.Set(inArray->get(11),inArray->get(12),inArray->get(13));

	int tmp = NrParticles*ParticleSize;
	CArray* tmpArray = new CArray (tmp);
	for (int i = 0; i < NrParticles*ParticleSize; i++) {
		tmpArray->set(i, inArray->get(i + myConstants::constants.HaloSize));
	}
	
	Halo = CParticles(tmpArray);
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

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->printSubHalo(count);
	}

	//for (int i = 0; i < SubHalos.size(); i++) {
	//	SubHalos[i]->printSubHalo(count);
	//}
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
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->cleanSubHalos();
	}
	//for (int i = 0;i < SubHalos.size(); i++) {
	//	SubHalos[i]->cleanSubHalos();
	//}
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
	CArray tmpArray(Halo.Particles2Array()); // Memory leak
	double* Array = new double [tmpArray.len() + myConstants::constants.HaloSize]; // Memory leak

	Array[0] = NrParticles;
	Array[1] = Mass;
	for (int i = 0; i < MeanP.getDimensions(); i++) {
		Array[2+i] = MeanP[i];
		Array[5+i] = MeanV[i];
		Array[8+i] = SigmaP[i];
		Array[11+i] = SigmaV[i];
	}

	for (int i = 0; i < tmpArray.len(); i++) {
		Array[i + myConstants::constants.HaloSize] = tmpArray[i];
		//cout << Array[i + myConstants::constants.HaloSize] << endl;
	}

	//cout << Array[i + myConstants::constants.HaloSize] << endl;
	
	//tmpArray.print();
	//Delete tmparray here in some way.
	//CArray tmp (tmpArray.len()+myConstants::constants.HaloSize, Array);
	//tmp.print();
	return new CArray(tmpArray.len()+myConstants::constants.HaloSize, Array);
}


CArray* CHalo::SubHalos2Array(){
	
	CArray* Array = new CArray (Halo.Particles2Array());
	CArray* sizeArray = new CArray (); // Memory leak
	SubHalos2ArrayRec(Array,sizeArray);
	
	Array = sizeArray->add(Array);
	Array->front(getTotalNrParticles());
	
	return Array;
}


void CHalo::SubHalos2ArrayRec(CArray* inArray, CArray* sizeArray){
	inArray = inArray->add(Halo.Particles2Array());
	sizeArray->push_back(NrParticles);
	
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SubHalos2ArrayRec(inArray,sizeArray);
	}
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
//int CHalo::getNrSubHalos(){
//	return SubHalos.size();
//}

int CHalo::getTotalNrParticles(){
	int TotalNrParticles = 0;
	getTotalNrParticlesRec(TotalNrParticles);
	return TotalNrParticles;
}


void CHalo::getTotalNrParticlesRec(int& TotalNrParticles){
	TotalNrParticles += NrParticles;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->getTotalNrParticlesRec(TotalNrParticles);
	}
}




list<CHalo*> CHalo::getSubHalos(){
	return SubHalos;
}

list<CHalo*>::iterator CHalo::begin(){
	return SubHalos.begin();
}

list<CHalo*>::iterator CHalo::end(){
	return SubHalos.end();
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
	Halo.addParticles(inHalo->getParticles());
	NrParticles += inHalo->getNrParticles();
	for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
		SubHalos.push_back(*it);
	}
//This might be slow
	CalculateStatistics();
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

//Calculate all the statistics relevant for all subhalos
void CHalo::CalculateAllStatistics(){
	CalculateStatistics();

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->CalculateAllStatistics();
	}
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
	if (NrParticles > myConstants::constants.NrLinking) {
		delta = NrParticles/(double)myConstants::constants.NrLinking;
		tmpNrParticles = myConstants::constants.NrLinking;
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
	//for (int i = 0;i < SubHalos.size(); i++) {
	//	SubHalos[i]->savePRec(fileName,HaloID);
	//}

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->savePRec(fileName,HaloID);
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
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->saveHaloStatX(file,HaloID);
	}

	//for (int i = 0;i < SubHalos.size(); i++) {
	//	SubHalos[i]->saveHaloStatX(file,HaloID);
	//}

	file.close();
}

//Save the statistical data in the x direction, for a single halo
void CHalo::saveHaloStatX(fstream& fileName, int& HaloID){
	CVector tmpP;

	fileName << HaloID << " " << MeanP.x()<< " " << MeanV.x() << " " <<	SigmaP.x() << " " << SigmaV.x() << endl;
	HaloID++;
}



double CHalo::PhaseSpaceDistanceHalo(CParticle* inParticle, CVector* inSigmaP, CVector* inSigmaV){
	double rvir2 = pow((Mass/(16./3.*atan(1)*myConstants::constants.rhovir)),2./3.);
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
	//for (int i = 0;i < SubHalos.size(); i++) {
	//	SubHalos[i]->SplitHalo();
	//}
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SplitHalo();
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
			if (tmpHalo.getNrParticles() > myConstants::constants.HaloLimit && tmpHalo.getNrParticles() != NrParticles){
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
	for (int i = 0; i < allParticles->getNrParticles(); i++) {
		findHalo(allParticles->get(i),this);
	}
	CalculateAllStatistics();
}


void CHalo::findHalo(CParticle* inParticle, CHalo* inHalo){

	//cout << "in Find Halo" << endl;

	//double DistanceArray[inHalo->getNrSubHalos()];
	int flag = 0;
	double distance, prevDistance;
	CHalo* minHalo;
	CVector* tmpSigmaP = inHalo->getSigmaP();
	CVector* tmpSigmaV = inHalo->getSigmaV();
	//inHalo->getMeanP()->print();
	//SubHalos[0]->getMeanP()->print();
	//SubHalos[0]->SubHalos[0]->getMeanP()->print();
	//exit(1);
	prevDistance = inHalo->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
	//for (int i = 0;i < inHalo->getNrSubHalos(); i++) {
	//	DistanceArray[i] = inHalo->SubHalos[i]->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
	//cout << "subHalo " << DistanceArray[i] << endl;
	//}
	for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
		distance = (*it)->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
		if (distance < prevDistance) {
			flag = 1;
			prevDistance = distance;
			minHalo = *it;
		}
	}
	//cout << flag << endl;
	//it++;
	if (flag == 0){
		inHalo->addParticle(inParticle);
	}
	else {
		//cout << "In the subhalo" << endl;
		findHalo(inParticle, minHalo);
	}
}


void CHalo::mergeStatistical(){
	int flag = 0;
	while (flag == 0){
		//cout << flag << endl;
		mergeStatisticalRec(this, flag);
	}
}

void CHalo::mergeStatisticalRec(CHalo* prevHalo, int &flag){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->mergeStatisticalRec(this, flag);
	}
	for (list<CHalo*>::iterator it = prevHalo->begin(); it != prevHalo->end(); it++) {
		double tmp1= ((MeanP - *((*it)->getMeanP()))/SigmaP).Length2();
		double tmp2= ((MeanV - *((*it)->getMeanV()))/SigmaV).Length2();
		//if (this != (*it) && (sqrt(NrParticles*(((MeanP - *((*it)->getMeanP()))/SigmaP).Length2() + (MeanV - *((*it)->getMeanV()))/SigmaV).Length2()) < 10*sqrt(2))){
		//cout << sqrt(NrParticles*(tmp1 + tmp2)) << endl;
		if (this != (*it) && NrParticles*(tmp1 + tmp2) < 200) {
			cout << "in thing"<<endl;
			SubHalos.erase(it);
			addHalo(*it);
			flag = 0;
			return;
		}
	}
	flag = 1;
}

void CHalo::createSubHalos(){

	CParticles allParticles = Halo;


	SplitHalo();
	//saveStatX();
	//printSubHalos();
	assignParticles(&allParticles);
	//printSubHalos();
	mergeStatistical();
	printSubHalos();
	//saveP();

}

