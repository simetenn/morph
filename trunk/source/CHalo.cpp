#include "CHalo.h"

using namespace std;


struct ParticleAndDistance{
	double r;
	CParticle* Particle;
};

//Sorts Mass and distance from center of halo f after distance from halo
bool ParticleAndDistanceSortFunc(ParticleAndDistance* a, ParticleAndDistance* b){
	return a->r < b->r;
}

bool NrParticlesSortFunc(CHalo* a, CHalo* b){
	return a->getNrParticles() < b->getNrParticles();
}


//Create an empty CHalo
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
	//CArray tmpArray (NrParticles*ParticleSize);
	for (int i = 0; i < NrParticles*ParticleSize; i++) {
		tmpArray->set(i, inArray->get(i + myConstants::constants.HaloSize));
		//tmpArray.set(i, inArray->get(i + myConstants::constants.HaloSize));
	}

	Halo = CParticles(tmpArray);
	if (tmpArray != NULL ) {
		delete tmpArray;
		tmpArray = NULL;
	}
}

//Create a new CHalo from a CHalo
CHalo::CHalo(CHalo* inHalo){
	copy(inHalo);
}


CHalo::~CHalo(){
	/*for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
	  if ((*it) != NULL ) {
	  delete (*it);
	  (*it) = NULL;
	  }
	  }*/
	//clear();
	kill();
}


//Kill all halos and subhalos and delete the particles from memory
void CHalo::kill(){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		if ((*it) != NULL ) {
			delete (*it);
			(*it) = NULL;
		}
	}

	Halo.clear();
	NrParticles = 0;
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
	ParticleSize = myConstants::constants.ParticleSize;

	SubHalos.clear();
	Halo.kill();
}


//Set the values of a CHalo object from an array on the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
void CHalo::set(CArray* inArray){
	clear();
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
	CArray* tmpArray = new CArray (NrParticles*ParticleSize); // <--- kill
	for (int i = 0; i < NrParticles*ParticleSize; i++) {
		tmpArray->set(i, inArray->get(i + myConstants::constants.HaloSize));
	}

	Halo = CParticles(tmpArray);

	if (tmpArray != NULL ){
		delete tmpArray;
		tmpArray = NULL;
	}
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






/*//Clear and remove all information from a CHalo object
  void CHalo::clear() {
  Halo.clear();
  NrParticles = 0;
  Mass = 0;
  MeanP.Set(0,0,0);
  MeanV.Set(0,0,0);
  SigmaP.Set(0,0,0);
  SigmaV.Set(0,0,0);
  ParticleSize = myConstants::constants.ParticleSize;
  }*/

void CHalo::clear(){
	Halo.clear();
	NrParticles = 0;
	Mass = 0;
	MeanP.Set(0,0,0);
	MeanV.Set(0,0,0);
	SigmaP.Set(0,0,0);
	SigmaV.Set(0,0,0);
	ParticleSize = myConstants::constants.ParticleSize;

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->clear();
	}

	SubHalos.clear();
}

//Clear and remove particle information, but keeps halo information, like position and velocity
void CHalo::clean() {
	Halo.clear();
	//NrParticles = 0;
	ParticleSize = myConstants::constants.ParticleSize;
}

void CHalo::eraseSubHalos(){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->eraseSubHalos();
	}
	SubHalos.clear();
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

void CHalo::cleanAll() {
	Halo.clear();
	NrParticles = 0;
	ParticleSize = myConstants::constants.ParticleSize;
}


//Clear and remove particle information, but keeping halo information, like position and velocity
//Does it recursivly for all SubHalos
void CHalo::cleanSubHalosAll(){
	cleanAll();

	//recursivly goes through all subhalos
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->cleanSubHalosAll();
	}
}



//Copy a CHalo object
void CHalo::copy(CHalo* inHalo) {
	Halo.copy(*inHalo->getParticles());
	NrParticles = inHalo->getNrParticles();
	Mass = inHalo->getMass();
	MeanP = *inHalo->getMeanP();
	MeanV = *inHalo->getMeanV();
	SigmaP = *inHalo->getSigmaP();
	SigmaV = *inHalo->getSigmaV();
	ParticleSize = myConstants::constants.ParticleSize;
	r = *inHalo->getR();
	Phi = *inHalo->getPhi();
	Mvir = inHalo->getMvir();
	Rvir = inHalo->getRvir();

	SubHalos = (inHalo->getSubHalos());
}






//Convert from one halo to an CArray. On the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray*	 CHalo::Halo2Array(){
	//CArray tmpArray(Halo.Particles2Array());
	CArray* tmpArray = Halo.Particles2Array();
	double* Array = new double [tmpArray->len() + myConstants::constants.HaloSize];

	Array[0] = NrParticles;
	Array[1] = Mass;
	//Array[1] = Mvir;
	for (int i = 0; i < MeanP.getDimensions(); i++) {
		Array[2+i] = MeanP[i];
		Array[5+i] = MeanV[i];
		Array[8+i] = SigmaP[i];
		Array[11+i] = SigmaV[i];
	}

	for (int i = 0; i < tmpArray->len(); i++) {
		Array[i + myConstants::constants.HaloSize] = tmpArray->get(i);
	}
	CArray* tmpCArray = new CArray(tmpArray->len()+myConstants::constants.HaloSize, Array); //<-- kill
	if (Array != NULL){
		delete [] Array;
		Array = NULL;
	}
	if (tmpArray != NULL){
		delete tmpArray;
		tmpArray = NULL;
	}
	return tmpCArray;
}



//Convert all Subahlos to an CArray. On the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray* CHalo::SubHalos2Array(){
	CArray Array;
	CArray* sizeArray = new CArray (); // <--- kill

	//adds all data from all subhalos
	SubHalos2ArrayRec(&Array,sizeArray);
	//Add nr of Halos to the front of SizeArray
	sizeArray->front(sizeArray->len());
	//Add the Array to sizeArray
	sizeArray->add(&Array);
	//delete [] Array;
	return sizeArray;
}

//Adds the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
//Then recursivly runs for all subhalos
void CHalo::SubHalos2ArrayRec(CArray* inArray, CArray* sizeArray){
	CArray* tmpArray = Halo2Array();
	inArray->add(tmpArray);
	//return;

	if (tmpArray != NULL) {
		delete tmpArray;
		tmpArray = NULL;
	}
	sizeArray->push_back(NrParticles);

	//Recursivly runs through all
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SubHalos2ArrayRec(inArray,sizeArray);
	}
}








//Convert all Subahlos to an CArray that keeps subhalo information. On the form:
//[ID, NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray* CHalo::SubHalosStructure2Array(){
	CArray Array;
	CArray* sizeArray = new CArray (); // <--- kill

	int ID = -1;
	//adds all data from all subhalos
	SubHalosStructure2ArrayRec(&Array, sizeArray, ID);
	//Add nr of Halos to the front of SizeArray
	sizeArray->front(sizeArray->len());
	//Add the Array to sizeArray
	sizeArray->add(&Array);

	return sizeArray;
}

//Adds the ID and the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
//Then recursivly runs for all subhalos
void CHalo::SubHalosStructure2ArrayRec(CArray* inArray, CArray* sizeArray,int& ID){
	ID++;
	inArray->push_back(ID);
	CArray* tmpArray = Halo2Array();
	inArray->add(tmpArray);
	if (tmpArray != NULL) {
		delete tmpArray;
		tmpArray = NULL;
	}
	sizeArray->push_back(NrParticles);

	//Recursivly runs through all subhalos
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SubHalosStructure2ArrayRec(inArray, sizeArray, ID);
		ID--;
	}

}




//Save halos into a text file, as a array
void CHalo::saveStructure(string Filename){
	fstream file;
	CArray* tmpArray = SubHalosStructure2Array();
	file.open((myConstants::constants.inData + Filename).c_str(), ios::out);

	//Saves position data for each particle to file
	file << tmpArray->len() << endl;
	for (int i = 0;i < tmpArray->len(); i++){
		file << tmpArray->get(i) << endl;
	}

	file.close();

	if (tmpArray != NULL) {
		delete tmpArray;
		tmpArray = NULL;
	}
}


//Load halos from a text file
void CHalo::loadStructure(string Filename){
	ifstream file((myConstants::constants.inData + Filename).c_str());
	string line;

	getline(file,line);
	trim(line);

	CArray inArray (atof(line.c_str()));

	int i = 0;
	if (file.is_open()){
		while (true){
			getline(file,line);
			trim(line);
			if (file.eof()) break;
			inArray[i] = atof(line.c_str());
			i++;
		}
		file.close();
	}
	fromStructureArray(&inArray);
}


//Create Halos and subhalos from an array on the form:
//[ID, NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
//This recreates the halo structire from SubHalosStructure2Array()
//If this is used I need to manually kill the halos stored in it.
void CHalo::fromStructureArray(CArray* inArray){
	clear();
	int NrHalos = inArray->get(0);
	ParticleSize = myConstants::constants.ParticleSize;

	int particle_count = 1 + NrHalos;
	//int totalNrParticles = (inArray->len() - 1 - 2*NrHalos - NrHalos*myConstants::constants.HaloSize)/ParticleSize;

	int nrHalo = 0;
	NrParticles = inArray->get(1+nrHalo);

	double* tmpArray = new double [NrParticles*ParticleSize + myConstants::constants.HaloSize];

	int ID = inArray->get(particle_count);
	particle_count++;
	int nextID = inArray->get(particle_count + NrParticles*ParticleSize + myConstants::constants.HaloSize);


	for (int l = 0; l < myConstants::constants.HaloSize; l++){
		tmpArray[l] = inArray->get(particle_count);
		particle_count++;
	}

	for (int j = 0; j < NrParticles;j++){
		for (int k = 0; k < ParticleSize;k++){
			tmpArray[j*ParticleSize+k+myConstants::constants.HaloSize] = inArray->get(particle_count);
			particle_count++;
		}
	}

	CArray tmpCArray((int)(NrParticles*ParticleSize + myConstants::constants.HaloSize), tmpArray);
	set(&tmpCArray); // <--- kill!

	if (tmpArray != NULL) {
		delete [] tmpArray;
		tmpArray = NULL;
	}

	while (ID < nextID){
		fromStructureArrayRec(this, inArray, nrHalo, particle_count,nextID);
	}
}


//Recursivly creates subhalos from the array
void CHalo::fromStructureArrayRec(CHalo* prevHalo, CArray* inArray, int& nrHalo,int& particle_count,int& nextID){
	nrHalo++;

	int tmpNrParticles = inArray->get(1+nrHalo);
	double* tmpArray = new double [tmpNrParticles*ParticleSize + myConstants::constants.HaloSize];

	int ID = inArray->get(particle_count);
	particle_count++;

	if (nrHalo >= inArray->get(0)-1) {
		nextID = -1;
	}
	else {
		nextID = inArray->get(particle_count + tmpNrParticles*ParticleSize + myConstants::constants.HaloSize);
	}


	for (int l = 0; l < myConstants::constants.HaloSize; l++){
		tmpArray[l] = inArray->get(particle_count);
		particle_count++;
	}
	for (int j = 0; j < tmpNrParticles;j++){
		for (int k = 0; k < ParticleSize;k++){
			tmpArray[j*ParticleSize+k+myConstants::constants.HaloSize] = inArray->get(particle_count);
			particle_count++;
		}
	}
	CArray tmpCArray (tmpNrParticles*ParticleSize + myConstants::constants.HaloSize, tmpArray);
	if (tmpArray != NULL){
		delete[] tmpArray;
		tmpArray = NULL;
	}
	CHalo* tmpHalo = new CHalo(&tmpCArray); // <---- kill
	prevHalo->attachSubHaloBack(tmpHalo);

	while (ID < nextID){
		fromStructureArrayRec(this, inArray, nrHalo, particle_count, nextID);
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

//Return the virialisation mass
double CHalo::getMvir(){
	return Mvir;
}

//Return the virialisation radius
double CHalo::getRvir(){
	return Rvir;
}

//Return distance from center, sorted
vector<double>* CHalo::getR(){
	return &r;
}

//Retturn gravitational potential, sorted as distance from center
vector<double>* CHalo::getPhi(){
	return &Phi;
}


//Calculate the Virialization mass and radius
void CHalo::calculateVir(){
	Rvir = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),1./3.);
	Mvir = 0;
	//cout << r[0] << " " << Rvir<<endl;
	//cout << NrParticles << endl;
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > Rvir) {
			break;
		}
		Mvir += Halo[i]->getMass();
	}
}

void CHalo::calculateVir2(){
	SortParticlesDistance();
	Rvir = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),1./3.);
	Mvir = 0;
	
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->calculateVir2();
		Mvir += (*it)->getMvir();
	}
	
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > Rvir) {
			break;
		}
		Mvir += Halo[i]->getMass();
	}
}


void CHalo::calculateVirBeta(){
	CalculatePhiSpherical();
	//SortParticlesDistance();
	double maxR = r[NrParticles-1];
	int Shells;
	if (myConstants::constants.NrShells > NrParticles/myConstants::constants.minParticlesShell) {
		Shells = NrParticles/myConstants::constants.minParticlesShell;
	}
	else {
		Shells = myConstants::constants.NrShells;
	}

	//int ParticlesShell = 4;
	//Shells = NrParticles/ParticlesShell;
	int ParticlesShell;
	if (Shells == 0) {
		ParticlesShell = NrParticles;
	}
	else{
		ParticlesShell = NrParticles/Shells;
	}
	CArray BetaR(Shells);
	double R;
	/*for (int i = 0; i < NrParticles/ParticlesShell; i++) {
	  BetaR[i] = Beta(r[i]);
	  }*/
	Rvir = -1;
	int test = -1;
	for (int n = 1; n <= Shells; n++) {
		R = r[n*ParticlesShell];//maxR/(double)Shells*n;//
		//cout << n*ParticlesShell << endl;
		//cout << maxR/(double)Shells*n << " " << endl;//<< r[n*ParticlesShell] << endl;
		BetaR[n-1] = Beta(R);
		if (BetaR[n-1] <= 0) {
			Rvir = R;
			test = 1;
			break;
		}
	}
	//BetaR.save("beta.dat");
	if (test == 1) {
		BetaR.save("beta.dat");
		//exit(1);
	}
	if (Rvir == -1) {
		//Rvir = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),1./3.);
	}
	/*else {
	  cout << "fund new Rvir" << endl;
	  }*/
	//cout << "here"<< endl;
	Mvir = 0;
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > Rvir) {
			break;
		}
		Mvir += Halo[i]->getMass();
	}
}



double CHalo::Beta(double R){
	//cout <<Tr(R) << endl;
	//cout << Es(R)<< endl;
	//cout << Wr(R)<< endl;
	//cout << (2*Tr(R) - Es(R))/Wr(R) + 1 << endl;
	return (2*Tr(R) - Es(R))/Wr(R) + 1;
}

double CHalo::Volume(double R){
	return 16*atan(1)/3.*0.488*R*R*R;
}


double CHalo::Ps(double R){
	double tmpPs = 0;
	int Nr;

	for (Nr = 0; Nr < NrParticles; Nr++) {
		if(r[Nr] > R) break;
	}

	for (int i = (int)(Nr*0.8); i < Nr; i++) {
		tmpPs += Halo[i]->getMass()*Halo[i]->getV().Length2();
	}
	//cout << tmpPs/3./Volume(R) << endl;
	return tmpPs/3./Volume(R);
}

double CHalo::Es(double R){
	return 16*atan(1)*0.729*R*R*R*Ps(R);
}

double CHalo::Tr(double R){
	double tmpTr = 0;
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > R) break;
		tmpTr += getMass()*Halo[i]->getV().Length2();
	}
	return tmpTr/2.;
}

double CHalo::Wr(double R){
	double tmpWr = 0;
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > R) break;
		tmpWr += getMass()*Phi[i];
	}
	return tmpWr;
}



int CHalo::ParticlesOutsideVir(){
	int i;
	for (i = 0; i < NrParticles; i++) {
		if(r[i] > Rvir) break;
	}
	//cout << "NrParticles " << NrParticles << " Particles inside Rvir " << i <<endl;
	return NrParticles-i-1;
}


//Scale the positions by a number
//mainly used in FOFGrid to scale the halos read in to be between [0,1]
void CHalo::scalePositions(double scale){
	for (int i = 0; i < NrParticles; i++) {
		Halo[i]->setP(Halo[i]->getP()*scale);
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

//Attach a halo to the subhalo list. At the front position
void CHalo::attachSubHaloBack(CHalo* inHalo){
	SubHalos.push_back(inHalo);
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
	NrParticles++;
	Halo.addParticle(inParticle);
	Mass += inParticle->getMass();
}


//Remove particle #element from halo
void CHalo::removeParticle(int element){
	Mass -= Halo[element]->getMass();
	Halo.removeParticle(element);
	r.erase(r.begin()+element);
	Phi.erase(Phi.begin()+element);
	NrParticles--;
}




//Add a halo to the halo
void CHalo::addHalo(CHalo* inHalo){
	Halo.addParticles(inHalo->getParticles());
	NrParticles += inHalo->getNrParticles();
	//Add the subhalos of the inhalo to the current halo
	for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
		SubHalos.push_back(*it);
	}
	//This might be slow, but needed for later use
	//CalculateStatistics();
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

	NrParticles = Halo.getNrParticles();

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

	//calculateVirBeta();

}

//Calculate all the statistics relevant for a halo, such as:
//mean P, mean V, sigma P, sigma V and mass
void CHalo::CalculateStatisticsNoMass(){
	MeanP = 0;
	MeanV = 0;
	SigmaP = 0;
	SigmaV = 0;

	NrParticles = Halo.getNrParticles();

	if(NrParticles != 0){
		for (int i = 0; i < NrParticles; i++) {
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

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->CalculateStatisticsNoMass();
	}
	//calculateVirBeta();

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
	file.open((myConstants::constants.inData + Filename).c_str(), ios::out);

	//Saves data for each particle to file
	for (int i = 0;i<NrParticles;i++){
		tmpArray = Halo[i]->Particle2Array();

		for (int j = 0; j < ParticleSize; j++) {
			file << tmpArray[j] << " ";
		}
		if (tmpArray != NULL) {
			delete tmpArray;
			tmpArray = NULL;
		}
		if (i != NrParticles-1) file << endl;

	}
	file.close();
}

//Save halos into a text file, as a array, as a binary file
void CHalo::saveHaloBin(string Filename){
	fstream file;
	CArray* tmpArray = Halo2Array();

	tmpArray->front(NrParticles);
	tmpArray->front(1);

	file.open((myConstants::constants.inData + Filename).c_str(), ios::out | ios::binary);

	//Saves position data for each particle to file
	file.write((char*)tmpArray->CArray2array(),tmpArray->len()*sizeof(double));
	file.close();
	//Memory leak
	if (tmpArray != NULL) {
		delete tmpArray;
		tmpArray = NULL;
	}
	//tmpArray->del();
}


//Save position data to file for all subhalos
void CHalo::saveP(string Filename){
	fstream file;
	int HaloID = 0;

	file.open((myConstants::constants.outData + Filename).c_str(), ios::out);

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

	file.open((myConstants::constants.inData + Filename).c_str(), ios::out);

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



//save the data for a single halo to file
void CHalo::savePhi(string Filename){
	fstream file;

	file.open((myConstants::constants.outData + Filename).c_str(), ios::out);

	//Saves data for each particle to file
	for (int i = 0;i<NrParticles;i++){
		file << Phi[i] << " " << r[i] << endl;
	}
	file.close();
}


//save the data for a single halo to file
void CHalo::save(string Filename, double value){
	fstream file;
	file.open((myConstants::constants.outData + Filename).c_str(), ios::out | ios::app);
	//Saves value to Filename
	file << value << endl;
	file.close();
}

//empty content of file Filename
void CHalo::del(string Filename){
	fstream file;
	file.open((myConstants::constants.outData + Filename).c_str(), ios::out);
	file.close();
}

//Calculate the Phase-Space distance between a halo and a particle
double CHalo::PhaseSpaceDistanceHalo(CParticle* inParticle){
	double rvir2 = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),2./3.);
	//double rvir2 = Rvir*Rvir;
	//double tmp = sqrt((inParticle->getP() - MeanP).Length2()/rvir2 + (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
	return sqrt((inParticle->getP() - MeanP).Length2()/rvir2 + (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
	//return sqrt((inParticle->getP() - MeanP).Length2()/inSigmaP->Length2() +	(inParticle->getV() - MeanV).Length2()/inSigmaV->Length2());
}


//Calculate the Phase-Space distance between a halo and a particle
double CHalo::PhaseSpaceDistanceHaloHalo(CHalo* inHalo){
	double rvir2 = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),2./3.);
	//double rvir2 = Rvir*Rvir;
	//double tmp = sqrt((inParticle->getP() - MeanP).Length2()/rvir2 + (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
	return sqrt((*inHalo->getMeanP() - MeanP).Length2()/rvir2 + (*inHalo->getMeanV() - MeanV).Length2()/SigmaV.Length2());
	//return sqrt((inParticle->getP() - MeanP).Length2()/inSigmaP->Length2() +	(inParticle->getV() - MeanV).Length2()/inSigmaV->Length2());
}


//Calculate the Linking Length for each halo.mod
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
	if (Halo.getNrParticles() < myConstants::constants.HaloSeed) {
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
	//CParticle* Particle = searchParticle;
	SubHalos.clear();

	//Create a linked list of all particles
	//Particle->prev=NULL;
	for (int i=1; i < NrParticles;i++){
		linkParticles.push_back(Halo[i]);

		/*Particle->setFlag(0);
		  Particle->next = Halo[i];
		  Particle->next->prev = Particle;
		  Particle = Particle->next;*/
	}
	/*Particle->setFlag(0);
	  Particle->next = NULL;*/




	double L = LinkingLength();
	list<CParticle*>::iterator Particle;
	//Using recursion to link all particles belonging to a halo
	while (!linkParticles.empty()){
		Particle = linkParticles.begin();
		linkParticles.erase(Particle);
		tmpHalo.clear();
		//Calls findNeighbors to find the particles within linking distance

		findNeighborsPhaseSpace(*Particle, &tmpHalo, L);
		if (tmpHalo.getNrParticles() > myConstants::constants.HaloSeed && tmpHalo.getNrParticles() != NrParticles){
			SubHalos.push_back(new CHalo(&tmpHalo)); // <-- kill
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
	list<CParticle*>::iterator itKeep;
	for (list<CParticle*>::iterator it = linkParticles.begin(); it != linkParticles.end();) {
		itKeep = it;
		itKeep++;
		double distance = inParticle->PhaseSpaceDistance(*it,&SigmaP,&SigmaV);
		if (distance < L){
			FriendList.addParticle(*it);
			linkParticles.erase(it);
		}
		it = itKeep;
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
	removeEmptySubHalos();
}


//Find the halo a particle is closest too and add the particle to that halo
void CHalo::findHalo(CParticle* inParticle, CHalo* inHalo){
	int flag = 0;
	double distance, prevDistance;
	CHalo* minHalo;

	//The phase distance from a particle to to the main halo
	prevDistance = inHalo->PhaseSpaceDistanceHalo(inParticle);
	//Check if it is closer to a subhalo
	for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
		distance = (*it)->PhaseSpaceDistanceHalo(inParticle);
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









void CHalo::createSeedHalos(){
	SeedHalos.clear();
	cleanSubHalos();
	int count = 0;
	createSeedHalosRec(count, &SeedHalos);
	//cout << this << endl;
	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end(); it++) {
		//cout << (*it) << endl;
		//cout << (*it)->getNrParticles() << endl;
	}
	/*SeedHalos.clear();
	  for (int i = 0; i < test.size(); i++) {
	  SeedHalos.push_back(test[i]);
	  }*/


	//cout << "Number of seedhalos found: " << SeedHalos.size() << endl;

	mergeStatisticalSeed();
}


void CHalo::createSeedHalosRec(int& count, list<CHalo*>* Seeds){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->createSeedHalosRec(count, Seeds);
	}

	if (SubHalos.size() == 0) {
		count++;
		Seeds->push_back(this);
	}
}



void CHalo::mergeStatisticalSeed(){
	int test = 1;
	while (test == 1){
		test = mergeStatisticalSeedRec();
	}
}

int CHalo::mergeStatisticalSeedRec(){
	double tmpX,tmpV,n;
	CVector tmpSigmaP,tmpSigmaV;

	for (list<CHalo*>::iterator it1 = SeedHalos.begin(); it1 != SeedHalos.end(); it1++) {
		for (list<CHalo*>::iterator it2 = SeedHalos.begin(); it2 != SeedHalos.end(); it2++) {
			if ((*it1)->getNrParticles() <= (*it2)->getNrParticles()) {
				tmpX = ((*(*it1)->getMeanP() - *((*it2)->getMeanP()))/ *(*it1)->getSigmaP()).Length2();
				tmpV = ((*(*it1)->getMeanP() - *((*it2)->getMeanP()))/ *(*it1)->getSigmaP()).Length2();
				n = (*it1)->getNrParticles();
			}
			else {
				tmpX = ((*(*it1)->getMeanP() - *((*it2)->getMeanP()))/ *(*it2)->getSigmaP()).Length2();
				tmpV = ((*(*it1)->getMeanP() - *((*it2)->getMeanP()))/ *(*it2)->getSigmaP()).Length2();
				n = (*it2)->getNrParticles();
			}

			//cout << n << endl;
			if ((*it1) != (*it2) && n*(tmpX + tmpV) < 200) {
				//cout << "does this hit" << endl;
				SeedHalos.erase(it2);
				//SubHalos.remove(*it);
				(*it1)->addHalo(*it2);
				return 1;
			}
		}
	}
	//It completes withouth merging any halos
	return 0;
}



//Assign all the particles contained in the subhalos to the correct seed halo
void CHalo::assignParticlesSeed(CParticles* allParticles){
	//Find the halo each particle is closest to and assign the particle to that halo
	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end(); it++) {
		(*it)->cleanSubHalosAll();
	}
	vector<double> distances (SeedHalos.size());
	CParticle* tmpParticle;
	int j;
	for (int i = 0; i < allParticles->getNrParticles(); i++) {
		tmpParticle = allParticles->get(i);
		j = 0;
		for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end(); it++) {
			distances[j] = (*it)->PhaseSpaceDistanceHalo(tmpParticle);
			j++;
		}

		int min_index = min_element(distances.begin(), distances.end()) - distances.begin();
		list<CHalo*>::iterator it = SeedHalos.begin();
		advance(it, min_index);
		(*it)->addParticle(tmpParticle);
	}

	removeEmptySeedHalos();
}


void CHalo::generateSubstructure(){
	//sort(SeedHalos.begin(),SeedHalos.end(),&NrParticlesSortFunc);
	vector<double> distances (SeedHalos.size());
	vector<list<CHalo*>::iterator> iterators (SeedHalos.size());
	int index;
	SeedHalos.sort(&NrParticlesSortFunc);

	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end();it++) {
		(*it)->eraseSubHalos();
	}

	if (SeedHalos.size() == 1) {
		copy(*SeedHalos.begin());
		SeedHalos.clear();
		return;
	}


	int i;
	list<CHalo*>::iterator lastIt;
	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end();it++) {
		i = 0;
		for (list<CHalo*>::iterator it2 = it; it2 != SeedHalos.end(); it2++) {
			if ((*it)->getNrParticles() < (*it2)->getNrParticles() && it2 != it) {
				//cout << (*it)->getNrParticles() << " " << (*it2)->getNrParticles() << endl;
				distances[i] = (*it)->PhaseSpaceDistanceHaloHalo(*it2);
				iterators[i] = it2;
				i++;
			}
		}
		index = min_element(distances.begin(), distances.begin() + i) - distances.begin();

		if ((*iterators[index])->getNrParticles() != (*it)->getNrParticles()) {
			(*iterators[index])->attachSubHaloBack(*it);
		}

		lastIt = it;

	}
	copy(*lastIt);
	SeedHalos.clear();
}


void CHalo::calculateMass(){
	Mass = 0;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->calculateMass();
		Mass += (*it)->getMass();

	}
	for (int i = 0; i < NrParticles; i++) {
		Mass += Halo[i]->getMass();
	}
}


void CHalo::removeEmptySeedHalos(){
	//Remove halos that has fewer than HaloLimit particles
	//int count = 0;
	//cout << "1" << endl;
	list<CHalo*>::iterator itKeep;
	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end();) {
		//cout << *it << endl;
		itKeep = it;
		itKeep++;
		//count += (*it)->getNrParticles();
		//cout << (*it)->getNrParticles() << endl;
		if ((*it)->getNrParticles() < myConstants::constants.HaloLimit) {
			SeedHalos.erase(it);
		}
		it = itKeep;
	}
	//cout << "2" << endl;
	//Calculate the new statistics
	/*for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end();it++) {
	  (*it)->CalculateStatistics();
	  //cout << (*it)->getNrParticles() << endl;
	  }*/
	//cout << "3" << endl;
}


//Unbind particles for the halo and all subhalos
void CHalo::UnbindSeed(int& count){
	//count = 0;
	//Halo[0];
	//cout << "Mass: " << Halo[0]->getMass() << endl;
	//cout << "NrParticles: " << NrParticles;
	//Unbind(count);
	//cout << "Percentage off particles unbound: " << (count)/(double)NrParticles*100 << endl;
	//cout << " Nr unbound particles: " <<count << endl;
	//savePhi(myConstants::constants.outPhi);
	//save(myConstants::constants.outBounding, (count-1)/(double)NrParticles);

	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end(); it++) {
		//cout << "Before unbind" << endl;
		cout << "Nr of particles in halo: " << (*it)->getNrParticles() << endl;;
		count = 0;
		(*it)->Unbind(count);
		//cout << (*it)->getNrParticles() << endl;;
		//cout << "after unbind" << endl;
		//(*it)->CalculateStatistics();
		cout << "Nr of Particles unbounded " << count << endl;
	}

}





//Convert all Subahlos to an CArray. On the form:
//[NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray* CHalo::SeedHalos2Array(){
	CArray Array;
	CArray* sizeArray = new CArray (); // <--- kill


	for (list<CHalo*>::iterator it = SeedHalos.begin(); it != SeedHalos.end();it++) {
		Array.add((*it)->Halo2Array());
		sizeArray->push_back((*it)->getNrParticles());
	}

	//Add nr of Halos to the front of SizeArray
	sizeArray->front(sizeArray->len());
	//Add the Array to sizeArray
	sizeArray->add(&Array);
	//delete [] Array;
	return sizeArray;
}




/*///Find the halo a particle is closest too and add the particle to that halo
  void CHalo::findHalo(CParticle* inParticle, CHalo* inHalo){


  int flag = 0;
  double distance, prevDistance;
  CHalo* prevHalo;

  for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
  prevHalo = *it;
  findHalo(inParticle, prevHalo);
  }

  //The phase distance from a particle to to the main halo
  prevDistance = inHalo->PhaseSpaceDistanceHalo(inParticle);
  //Check if it is closer to a subhalo
  for (list<CHalo*>::iterator it = inHalo->begin(); it != inHalo->end(); it++) {
  distance = (*it)->PhaseSpaceDistanceHalo(inParticle);
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
  }*/


void CHalo::removeEmptySubHalos(){

	//This method completly changes subhalo relationship
	//It might well be that instead of beeing kept as subhalos of each other,
	//I should split it into two different halos.
	//if (NrParticles < myConstants::constants.HaloLimit){
	//	cout << "WARNING: Host halo has to few particles. I need to do stuff!" << endl;


	//Remove halos that has fewer than HaloLimit particles
	list<CHalo*>::iterator itKeep;
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end();) {
		itKeep = it;
		itKeep++;
		(*it)->removeEmptyHalos(this);
		it = itKeep;
	}

	//Calculate the new statistics
	//CalculateAllStatistics();
	calculateMass();
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
			prevHalo->attachSubHaloBack(*it);
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
		double tmp1 = ((MeanP - *((*it)->getMeanP()))/SigmaP).Length2();
		double tmp2 = ((MeanV - *((*it)->getMeanV()))/SigmaV).Length2();

		if (this != (*it) && NrParticles*(tmp1 + tmp2) < 200) {
			SubHalos.erase(it);
			//SubHalos.remove(*it);
			addHalo(*it);
			flag = 0;
			return;
		}
	}
	//It completes withouth merging any halos
	flag = 1;
	return;
}




//Sorts the particles in the halo after distance from the center of the halo,
void CHalo::SortParticlesDistance(){
	vector<ParticleAndDistance*> data;

	for (int i = 0; i < NrParticles; i++) {
		ParticleAndDistance* tmpData = new ParticleAndDistance;
		tmpData->r= (MeanP - Halo[i]->getP()).Length();
		tmpData->Particle = Halo[i];
		data.push_back(tmpData);
	}

	sort(data.begin(),data.end(),&ParticleAndDistanceSortFunc);

	/*cout << "sorted particle distances " << endl;
	  for (int i = 0; i < NrParticles; i++) {
	  cout << data[i]->r << endl;
	  }*/
	Halo.clear();
	r.resize(NrParticles);
	//cout << "sorted particle distances " << endl;
	for (int i = 0; i < NrParticles; i++) {
		//cout << data[i]->r << endl;
		Halo.addParticle(data[i]->Particle);

		r[i] = data[i]->r;
		if (data[i] != NULL) {
			delete data[i];
			data[i] = NULL;
		}
	}

	/*cout << "sorted particle distances " << endl;
	  for (int i = 0; i < NrParticles; i++) {
	  cout << r[i] << endl;
	  }*/
}



//Calculate the gravitational potential using a spherical approximation
void CHalo::CalculatePhiSpherical(){
	//cout << "here" << endl;
	SortParticlesDistance();


	//Move this to the correct place to calulate virialisation stuff. Probably statistics somewhere
	calculateVir();
	//Mvir = Mass;
	//Rvir = r[NrParticles-1];
	double M = 0;
	double resPhi0 = Mvir/Rvir;
	double prevPhi0 = resPhi0;
	double Phi0;// = Mvir/Rvir;

	for (int i = 1; i < NrParticles; i++) {
		if(r[i] > Rvir) break;
		M += Halo[i]->getMass();
		Phi0 = M/(r[i]*r[i]);
		resPhi0 += 0.5*(3*Phi0 - prevPhi0)*(r[i]-r[i-1]);
		//Phi0 += M/(r[i]*r[i])*(r[i]-r[i-1]);
		prevPhi0 = Phi0;
		//Phi0 += Halo[i]->getMass()/(r[i]*r[i]);
	}
	//resPhi0 +=  Mvir/Rvir;
	resPhi0 *= -myConstants::constants.G;
	//Phi0 *= -myConstants::constants.G;
	//cout << Mvir << " " << Rvir <<endl;
	//cout << "Phi0: " << resPhi0 << endl;

	//cout << "--------------------" <<endl;
	//cout << resPhi0 << endl;
	//cout << "--------------------" <<endl;

	M = 0;
	Phi.clear();
	Phi.resize(NrParticles);
	Phi[0] = resPhi0;
	double prevPhi = resPhi0;
	double nowPhi;
	//nowPhi = myConstants::constants.G*M/(r[1]*r[1]);
	//prevPhi = 0.5*(3*nowPhi - prevPhi)*(r[i+1]-r[i]) + Phi[i-1];
	//Phi.push_back(myConstants::constants.G*Halo[1]->getMass()/(r[1]*r[1])*(r[1]-r[0]));
	for (int i = 1; i < NrParticles; i++) {
		//Phi.push_back(myConstants::constants.G*Halo[i]->getMass()/(r[i]*r[i])+Phi[i-1]);
		M += Halo[i]->getMass();
		//Phi[i] = myConstants::constants.G*M/(r[i]*r[i])*(r[i]-r[i-1]) + Phi[i-1];
		nowPhi = myConstants::constants.G*M/(r[i]*r[i]);
		Phi[i] = 0.5*(3*nowPhi - prevPhi)*(r[i]-r[i-1]) + Phi[i-1];
		prevPhi = nowPhi;
	}

	//cout << "PhiTot: " << Phi[NrParticles-1] << endl;
	/*Phi0 = Phi[NrParticles-1];
	  for (int i = 0; i < NrParticles; i++) {
	  Phi[i] -= Phi0;
	  }*/
}



//Unbind particles for the halo and all subhalos
void CHalo::UnbindAll(int& count){
	//count = 0;
	//Halo[0];
	//cout << "Mass: " << Halo[0]->getMass() << endl;
	//cout << "NrParticles: " << NrParticles;
	Unbind(count);
	//cout << "Percentage off particles unbound: " << (count)/(double)NrParticles*100 << endl;
	//cout << " Nr unbound particles: " <<count << endl;
	//savePhi(myConstants::constants.outPhi);
	//save(myConstants::constants.outBounding, (count-1)/(double)NrParticles);
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->UnbindAll(count);
	}
}




//Method for unbinding particles from a single halo
void CHalo::Unbind(int& count){
	CalculatePhiSpherical();
	//cout << " after vCalculatePhiSpherical();" << endl;
	vector<int> RemoveIndex;
	//cout << "------------"<< count << "--------------" << endl;
	for (int i = 0; i < NrParticles; i++) {
		//cout << r[i] << " " << Phi[i] << endl;
		//cout << Halo[i]->getV().Length2() << " " << 2*abs(Halo[i]->getA()[0]*1.045e-12) << endl;
		//cout << (Halo[i]->getV() - MeanV).Length2() << " " << Phi[i] << endl;
		//cout << Phi[i] << " " << (Halo[i]->getA()[0]*1.045e-12) << endl;

		//if (Halo[i]->getV().Length2() > 2*abs(Halo[i]->getA()[0]*1.045e-12)) {
		//cout << Halo[i]->getV().Length() << endl;;
		if ((Halo[i]->getV() - MeanV).Length2() > 2*abs(Phi[i])) {
			RemoveIndex.push_back(i);
		}
	}

	count += RemoveIndex.size();
	//count++;
	//Be carefull, this is gona fuck me up royaly(with the RemoveIndex[i]-i)
	for (int i = 0; i < RemoveIndex.size(); i++) {
		removeParticle(RemoveIndex[i]-i);
	}

	if (RemoveIndex.size() > myConstants::constants.minUnbind and NrParticles >= myConstants::constants.HaloLimit) Unbind(count);
}




//Do the splitting of halos, assigning particles to all halos, and merge statisticaly equal halos
void CHalo::createSubHalos(int& count){
	CParticles allParticles;
	allParticles.copy(Halo);
	SplitHalo();
	cout << "Creating seed halos" << endl;
	createSeedHalos();
	cout << "Assigning particles to seed halos" << endl;
	assignParticlesSeed(&allParticles);
	cout << "Generating substructure" << endl;
	generateSubstructure();
	//cout << "calculating mass" << endl;
	calculateMass();
	//cout << "Calculating statistics, no mass" << endl;
	CalculateStatisticsNoMass();
	//cout << "Unbinding particles" << endl;
	UnbindAll(count);	
	//cout << "Calculating statistics, no mass" << endl;
	CalculateStatisticsNoMass();
	cout << "Finished creating subhalos" << endl;
	//calculateVir2();
	//calculateVirBeta();
	/*assignParticles(&allParticles);
	//saveStructure("structureBig.dat");ha
	mergeStatistical();
	UnbindAll(count);
	removeEmptySubHalos();*/
	//Unbind();
}


//A splitting routine that split the halos into fake halos with equal size.
//Each (sub)halo has #NrSubHalos subhalos each and there are #MaxDepth levels of subhalos
//This is used for debugging purposes
void CHalo::createMockSubHalos(){
	int NrSubHalos = 6;
	int NrParticlesSubHalo = 100;
	int MaxDepth = 6;


	int depth = 0;
	CHalo tmpHalo;


	for (int i = 0; i < NrSubHalos; i++) {
		for (int j = 0; j < NrParticlesSubHalo; j++) {
			if (NrParticles <= 1) break;
			tmpHalo.addParticle(Halo[0]);
			Halo.removeParticle(0);
			NrParticles--;
		}
		if (tmpHalo.getNrParticles() > 0) SubHalos.push_back(new CHalo(&tmpHalo));
		tmpHalo.clear();

	}


	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->createMockSubHalosRec(NrSubHalos,NrParticlesSubHalo, MaxDepth, depth, Halo);
		depth--;
	}

	NrParticles = Halo.getNrParticles();
	CalculateAllStatistics();
}


//A recursive routine that creates the mock subhalos
void CHalo::createMockSubHalosRec(int NrSubHalos, int NrParticlesSubHalo, int MaxDepth, int &depth, CParticles& inHalo){
	depth++;
	if (depth >= MaxDepth) return;
	CHalo tmpHalo;

	for (int i = 0; i < NrSubHalos; i++) {
		for (int j = 0; j < NrParticlesSubHalo; j++) {
			if (inHalo.getNrParticles() <= 1) break;
			tmpHalo.addParticle(inHalo[0]);
			inHalo.removeParticle(0);
		}
		if (tmpHalo.getNrParticles() >0) SubHalos.push_back(new CHalo(&tmpHalo));
		tmpHalo.clear();

	}

	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->createMockSubHalosRec(NrSubHalos,NrParticlesSubHalo, MaxDepth, depth, inHalo);
		depth--;
	}
}
