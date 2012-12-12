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
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CHalo::CHalo(CArray* inArray){
	ParticleSize = myConstants::constants.ParticleSize;

	//read NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
	// and standard deviation of velocity
	NrParticles = inArray->get(0);
	Mass = inArray->get(1);
	MeanP.Set(inArray->get(2),inArray->get(3),inArray->get(4));
	MeanV.Set(inArray->get(5),inArray->get(6),inArray->get(7));
	SigmaP.Set(inArray->get(8),inArray->get(9),inArray->get(10));
	SigmaV.Set(inArray->get(11),inArray->get(12),inArray->get(13));

	//Read all the particle information
	CArray* tmpArray = new CArray (NrParticles*ParticleSize);
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


//Print Halo nr, nr particles in halo and position and velocity of halo
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


//Print all halos and subhalos
void CHalo::printSubHalos(){
	int count = 0;
	printSubHalo(count);
}


//Print information for one subhalo. Recursivly goes through the subhalo tree.
//Used by printSubHalos()
void CHalo::printSubHalo(int& count){
	printHalo(count);

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->printSubHalo(count);
	}
}






//Clear and remove all information from a CHalo object
void CHalo::clear() {
	Halo.clear();
	NrParticles = 0;
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
	ParticleSize = myConstants::constants.ParticleSize;
}


//Clear and remove particle information, but keeps halo information, like position and velocity
void CHalo::clean() {
	Halo.clear();
	NrParticles = 0;
	ParticleSize = myConstants::constants.ParticleSize;
}


//Clear and remove particle information, but keeping halo information, like position and velocity
//Does it recursivly for all SubHalos
void CHalo::cleanSubHalos(){
	clean();

	//recursivly goes through all subhalos
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->cleanSubHalos();
	}
}


//Copy a CHalo object
void CHalo::copy(CHalo* inHalo) {
	Halo.copy(*inHalo->getParticles());
	NrParticles = inHalo->getNrParticles();
	Mass = inHalo->getMass();
	MeanP=*inHalo->getMeanP();
	MeanV=*inHalo->getMeanV();
	SigmaP=*inHalo->getSigmaP();
	SigmaV=*inHalo->getSigmaV();
	ParticleSize = myConstants::constants.ParticleSize;
}






//Convert from one halo to an CArray. On the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
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
	}

	return new CArray(tmpArray.len()+myConstants::constants.HaloSize, Array);
}



//Convert all Subahlos to an CArray. On the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray* CHalo::SubHalos2Array(){
	CArray* Array = new CArray ();
	CArray* sizeArray = new CArray (); // Memory leak

	//adds all data from all subhalos
	SubHalos2ArrayRec(Array,sizeArray);
	//Add nr of Halos to the front of SizeArray
	sizeArray->front(sizeArray->len());
	//Add the Array to sizeArray
	sizeArray->add(Array);

	return sizeArray;
}


//Adds the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
//Then recursivly runs for all subhalos
void CHalo::SubHalos2ArrayRec(CArray* inArray, CArray* sizeArray){
	inArray->add(Halo2Array());
	sizeArray->push_back(NrParticles);

	//Recursivly runs through all
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


//Calculate the total nNrParticles in all subhalos
int CHalo::getTotalNrParticles(){
	int TotalNrParticles = 0;
	getTotalNrParticlesRec(TotalNrParticles);
	return TotalNrParticles;
}

//Recursivly run trough all subhalos and add the NrParticles in each halo to TotalNrParticles
void CHalo::getTotalNrParticlesRec(int& TotalNrParticles){
	TotalNrParticles += NrParticles;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->getTotalNrParticlesRec(TotalNrParticles);
	}
}





//Return the list over all subhalos
list<CHalo*> CHalo::getSubHalos(){
	return SubHalos;
}


//Return the iterator pointing at the begining element of the subhalo list
list<CHalo*>::iterator CHalo::begin(){
	return SubHalos.begin();
}


//Return the iterator pointing at the end element of the subhalo list
list<CHalo*>::iterator CHalo::end(){
	return SubHalos.end();
}

//Attach a halo to the subhalo list. At the front position
void CHalo::attachSubHalo(CHalo* inHalo){
	SubHalos.push_front(inHalo);
}

//Remove halo from the subhalo list.
void CHalo::removeSubHalo(CHalo* inHalo){
	SubHalos.remove(inHalo);
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


//Set NrParticles to count
void CHalo::setNrParticles(int count){
	NrParticles = count;
}



//return the number of subHalos
int CHalo::getNrSubHalos(){
	return SubHalos.size();
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
	if(NrParticles != 0){
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
}


//Calculate all the statistics relevant for all subhalos
void CHalo::CalculateAllStatistics(){
	CalculateStatistics();

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->CalculateAllStatistics();
	}
}


//Printing out the statistics for one halo
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





//save the data for a single halo to file
void CHalo::saveHalo(string Filename){
	fstream file;
	double* tmpArray;
	file.open((myConstants::constants.data + Filename).c_str(), ios::out);

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
void CHalo::saveP(string Filename){
	fstream file;
	int HaloID = 0;

	file.open((myConstants::constants.data + Filename).c_str(), ios::out);

	//Saves position data for each particle to file
	cout << "Saving positional data" << endl;
	savePRec(file,HaloID);
	file.close();
}


//Recursivly goes trough all subhalos and write the position data to file
void CHalo::savePRec(fstream& fileName, int& HaloID){
	saveHaloP(fileName,HaloID);

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
void CHalo::saveStatX(string Filename){
	fstream file;
	int HaloID = 0;

	file.open((myConstants::constants.data + Filename).c_str(), ios::out);

	//Saves position data for each particle to file
	cout << "Saving statistical data" << endl;
	saveHaloStatX(file,HaloID);
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->saveHaloStatX(file,HaloID);
	}

	file.close();
}

//Save the statistical data in the x direction, for a single halo
void CHalo::saveHaloStatX(fstream& fileName, int& HaloID){
	CVector tmpP;

	fileName << HaloID << " " << MeanP.x()<< " " << MeanV.x() << " " <<	SigmaP.x() << " " << SigmaV.x() << endl;
	HaloID++;
}


//Calculate the Phase-Space distance between a halo and a particle
double CHalo::PhaseSpaceDistanceHalo(CParticle* inParticle, CVector* inSigmaP, CVector* inSigmaV){
	double rvir2 = pow((Mass/(16./3.*atan(1)*myConstants::constants.rhovir)),2./3.);
	return sqrt((inParticle->getP() - MeanP).Length2()/inSigmaP->Length2() +  (inParticle->getV() - MeanV).Length2()/inSigmaV->Length2());
}


//Calculate the Linking Length for each halo.
//The linking length is chosen such that a fraction f of all particles
//atleast is linked together with one other particle
//For large groups > NrLinking we only calculate this for NrLinking particles
//By defult NrLinking = 10000.
double CHalo::LinkingLength(){
	int tmpNrParticles = NrParticles;
	double delta = 1;

	//If more than NrLinking particles, set NrLinking particles
	//as the maximum amount of particles to use
	if (NrParticles > myConstants::constants.NrLinking) {
		delta = NrParticles/(double)myConstants::constants.NrLinking;
		tmpNrParticles = myConstants::constants.NrLinking;
	}

	vector<double> LinkingLengths (tmpNrParticles);
	int tmpLinkingLength,prevtmpLinkingLength;

	//Calculate the	 phase space distance between the first particle and the particle closest to this
	prevtmpLinkingLength = Halo[0]->PhaseSpaceDistance(Halo[1],&SigmaP,&SigmaV);
	for (double j = delta; j < tmpNrParticles; j+=delta) {
		tmpLinkingLength = Halo[0]->PhaseSpaceDistance(Halo[(int)j],&SigmaP,&SigmaV);
		if (tmpLinkingLength < prevtmpLinkingLength) {
			prevtmpLinkingLength = tmpLinkingLength;
		}
	}

	LinkingLengths[0] = prevtmpLinkingLength;

	//Calculate the minimum phase space distance between all the other particles
	for (int i = 1; i < tmpNrParticles; i++) {
		prevtmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[0],&SigmaP,&SigmaV);
		for (int j = 1; j < tmpNrParticles; j++) {
			tmpLinkingLength = Halo[i]->PhaseSpaceDistance(Halo[j],&SigmaP,&SigmaV);
			if (i!=j &&	 tmpLinkingLength < prevtmpLinkingLength) {
				prevtmpLinkingLength = tmpLinkingLength;
			}
		}
		LinkingLengths[i] = prevtmpLinkingLength;
	}

	//Sort the linking<lengths and return the one where a fraction f of the
	//particles is linked together woth atleast one other aprticle
	sort(LinkingLengths.begin(),LinkingLengths.end());
	return LinkingLengths[(int) LinkingLengths.size()*myConstants::constants.f];
}


//Splits the halo into subhalos using the friend of friend methode in phase space.
//Then calculates the subhalos of the subhalo recursivly until either the halo limit
//is reached or no particles are found being linked together.
void CHalo::SplitHalo(){
	if (Halo.getNrParticles() < myConstants::constants.HaloLimit) {
		return;
	}

	FriendOfFriendPhaseSpace();
	clean();

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SplitHalo();
	}
}




//Calculating Friend of Friend using recursion, in phase space.
//It scales as N^2
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

	double L = LinkingLength();
	//Using recursion to link all particles belonging to a halo
	while (true){
		Particle = nextParticle();

		if (Particle == NULL) break;
		else {
			tmpHalo.clear();

			//Calls findNeighbors to find the particles within linking distance
			Particle->setFlag(1);
			Particle->RemoveFromList();
			findNeighborsPhaseSpace(Particle, &tmpHalo, L);

			if (tmpHalo.getNrParticles() > myConstants::constants.HaloLimit && tmpHalo.getNrParticles() != NrParticles){
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







//Assign all the particles contained in the subhalos to the correct seed halo
void CHalo::assignParticles(CParticles* allParticles){
	//Find the halo each particle is closest to and assign the particle to that halo
	for (int i = 0; i < allParticles->getNrParticles(); i++) {
		findHalo(allParticles->get(i),this);
	}

	//curently doesn't do anything if the first halo has fewer than halolimit particles
	//try to copy all below and one step up

	//Remove halos that has fewer than HaloLimit particles
	list<CHalo*>::iterator itKeep;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end();) {
		itKeep = it;
		itKeep++;
		(*it)->removeEmptyHalos(this);
		it = itKeep;
	}
	//Calculate the new statistics
	CalculateAllStatistics();
}


//Find the halo a particle is closest too and add the particle to that halo
void CHalo::findHalo(CParticle* inParticle, CHalo* inHalo){
	int flag = 0;
	double distance, prevDistance;
	CHalo* minHalo;
	CVector* tmpSigmaP = inHalo->getSigmaP();
	CVector* tmpSigmaV = inHalo->getSigmaV();

	//The phase distance from a particle to to the main halo
	prevDistance = inHalo->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
	//Check if it is closer to a subhalo
	for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
		distance = (*it)->PhaseSpaceDistanceHalo(inParticle,tmpSigmaP,tmpSigmaV);
		if (distance < prevDistance) {
			flag = 1;
			prevDistance = distance;
			minHalo = *it;
		}
	}
	//If the main halo is closest, add the particle to that halo
	if (flag == 0){
		inHalo->addParticle(inParticle);
	}
	//If it is closest to a subhalo run findhalo to see if a subhalo of the subhalo is closer
	else {
		findHalo(inParticle, minHalo);
	}
}



//Remove halos that has fewer than HaloLimit particles
void CHalo::removeEmptyHalos(CHalo* prevHalo){
	//recursivly go through the tree, from bottom up
	list<CHalo*>::iterator itKeep;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end();) {
		itKeep = it;
		itKeep++;
		(*it)->removeEmptyHalos(this);
		it = itKeep;
	}

	//If a halo has less than HaloLimit particles, attach the subhalos to the previos subhalo
	//and remove it from the prevois halos subhalo list
	if (NrParticles < myConstants::constants.HaloLimit){
		for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
			prevHalo->attachSubHalo(*it);
		}
		prevHalo->removeSubHalo(this);
	}
}


//Merge halos that are statisticaly the same halo
void CHalo::mergeStatistical(){
	int flag = 0;
	//Stops if it completes withouth merging any halos
	while (flag == 0){
		mergeStatisticalRec(this, flag);
	}
}

//Recursivly goes through all subhalos bottom up and merges halos that are statisticaly equal
void CHalo::mergeStatisticalRec(CHalo* prevHalo, int &flag){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->mergeStatisticalRec(this, flag);
	}

	//For all subhalos of one halo, check if the subhalos are statisticaly equal
	//If they are erase one of the subhalos, and add it to the other
	for (list<CHalo*>::iterator it = prevHalo->begin(); it != prevHalo->end(); it++) {
		double tmp1= ((MeanP - *((*it)->getMeanP()))/SigmaP).Length2();
		double tmp2= ((MeanV - *((*it)->getMeanV()))/SigmaV).Length2();

		if (this != (*it) && NrParticles*(tmp1 + tmp2) < 200) {
			cout << "Merging two halos"<<endl;
			SubHalos.erase(it);
			addHalo(*it);
			flag = 0;
			return;
		}
	}
	//It completes withouth merging any halos
	flag = 1;
}


//Do the splitting of halos, assigning particles to all halos, and merge statisticaly equal halos
void CHalo::createSubHalos(){
	CParticles allParticles = Halo;

	SplitHalo();
	assignParticles(&allParticles);
	mergeStatistical();

}



//TODO:
// - do something if the first halo has fewer than halo limit particles
// - double check the phase distance caluclations in findHalo
