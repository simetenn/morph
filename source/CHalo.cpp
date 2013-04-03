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

//Creates CParticles from a CArra yon the following form:
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
	if (tmpArray != NULL ) delete tmpArray;
	tmpArray = NULL;
 }

//Create a new CHalo from a CHalo
CHalo::CHalo(CHalo* inHalo){
	copy(inHalo);
}


CHalo::~CHalo(){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		if ((*it) != NULL ) delete (*it);
		(*it) = NULL;
	}
	clear();
	//kill();
}

void CHalo::kill(){
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->kill();
	}
	Halo.kill();
	clear();
}


void CHalo::set(CArray* inArray){
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
	//delete [] tmpArray;
	if (tmpArray != NULL ) delete tmpArray;
	tmpArray = NULL;
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
	if (Array != NULL) delete [] Array;
	Array = NULL;
	if (tmpArray != NULL) delete tmpArray;
	tmpArray = NULL;
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
	if (tmpArray != NULL) delete tmpArray;
	tmpArray = NULL;
	sizeArray->push_back(NrParticles);

	//Recursivly runs through all
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SubHalos2ArrayRec(inArray,sizeArray);
	}
}








//Convert all Subahlos to an CArray. On the form:
//[ID, NrParticles, Mass, Mean position, Mean velocity, standard deviation of position,
//standard deviation of velocity, ParticleArray 1, ParticleArray 2, ... , ParticleArray N]
CArray* CHalo::SubHalosStructure2Array(){
	CArray Array;
	CArray* sizeArray = new CArray (); // <--- kill

	int ID = -1;
	//Array->front(ID);
	//adds all data from all subhalos
	SubHalosStructure2ArrayRec(&Array, sizeArray,ID);
	//Add nr of Halos to the front of SizeArray
	sizeArray->front(sizeArray->len());

	//Add the Array to sizeArray
	sizeArray->add(&Array);

	return sizeArray;
}

//Adds the subhalo converted to a CArray to the inArray and NrParticles to sizeAray
//Then recursivly runs for all subhalos
void CHalo::SubHalosStructure2ArrayRec(CArray* inArray, CArray* sizeArray,int& ID){
	ID++;
	inArray->push_back(ID);
	CArray* tmpArray = Halo2Array();
	inArray->add(tmpArray);
	if (tmpArray != NULL) delete tmpArray;
	tmpArray = NULL;
	sizeArray->push_back(NrParticles);

	//Recursivly runs through all
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->SubHalosStructure2ArrayRec(inArray, sizeArray, ID);
		ID--;
	}

}




//Save halos into a text file, as a array
void CHalo::saveStructure(string Filename){
	fstream file;
	CArray* tmpArray = SubHalosStructure2Array();
	file.open((myConstants::constants.data + Filename).c_str(), ios::out);

	//Saves position data for each particle to file
	file << tmpArray->len() << endl;
	for (int i = 0;i < tmpArray->len(); i++){
		file << tmpArray->get(i) << endl;
	}
	file.close();
	//Memory leak
	if (tmpArray != NULL) delete tmpArray;
	tmpArray = NULL;
	//tmpArray->del();
}



void CHalo::loadStructure(string Filename){
	ifstream file((myConstants::constants.data + Filename).c_str());
	string line;

	getline(file,line);
	trim(line);

	CArray inArray (atof(line.c_str()));

	int i = 0;
	if (file.is_open()){
		while (true){

			//cout << i << endl;
			getline(file,line);
			trim(line);
			//split(strData, line, is_any_of(" "));
			//cout << i << endl;
			//cout << atof(line.c_str()) << endl;
			if (file.eof()) break;
			inArray[i] = atof(line.c_str());
			i++;
		}
		file.close();
	}
	cout << "before" << endl;
	fromStructureArray(&inArray);
	cout << "after" << endl;
	//cout << inArray[-1] << endl;
	//inArray.del();

}


//If this is used I need to manally kill the halos stored in it.
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

	if (tmpArray != NULL) delete [] tmpArray;
	tmpArray = NULL;
	//delete tmpCArray;
	while (ID < nextID){
		fromStructureArrayRec(this, inArray, nrHalo, particle_count,nextID);
		//cout << nextID << endl;
	}

	
	
}




void CHalo::fromStructureArrayRec(CHalo* prevHalo, CArray* inArray, int& nrHalo,int& particle_count,int& nextID){
	nrHalo++;

	int tmpNrParticles = inArray->get(1+nrHalo);
	double* tmpArray = new double [tmpNrParticles*ParticleSize + myConstants::constants.HaloSize];

	int ID = inArray->get(particle_count);
	particle_count++;

	if (nrHalo >= inArray->get(0)-1) {
		nextID = -1;
		//return;
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
	if (tmpArray != NULL)	delete[] tmpArray;
	tmpArray = NULL;
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


//Calculate the Virializati0n mass and radius
void CHalo::calculateVir(){
	Rvir = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),1./3.);
	Mvir = 0;
	//cout << r[0] << " " << Rvir<<endl;
	//cout << NrParticles << endl;
	for (int i = 0; i < NrParticles; i++) {
		if(r[i] > Rvir) {
			//cout << i << endl;
			break;
		}
		Mvir += Halo[i]->getMass();
	}
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
		if (tmpArray != NULL) delete tmpArray;
		tmpArray = NULL;
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



//save the data for a single halo to file
void CHalo::savePhi(string Filename){
	fstream file;
	
	file.open((myConstants::constants.data + Filename).c_str(), ios::out);

	//Saves data for each particle to file
	for (int i = 0;i<NrParticles;i++){
		file << Phi[i] << " " << r[i] << endl;
	}
	file.close();
}


//save the data for a single halo to file
void CHalo::save(string Filename, double value){
	fstream file;
	file.open((myConstants::constants.data + Filename).c_str(), ios::out | ios::app);
	//Saves value to Filename
	file << value << endl;
	file.close();
}

//empty content of file Filename
void CHalo::del(string Filename){
	fstream file;
	file.open((myConstants::constants.data + Filename).c_str(), ios::out);
	file.close();
}

//Calculate the Phase-Space distance between a halo and a particle
double CHalo::PhaseSpaceDistanceHalo(CParticle* inParticle){
	double rvir2 = pow((Mass/(16./3.*atan(1)*myConstants::constants.ScaleDensity*myConstants::constants.RhoC)),2./3.);
	//double tmp = sqrt((inParticle->getP() - MeanP).Length2()/rvir2 + (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
	return sqrt((inParticle->getP() - MeanP).Length2()/rvir2 + (inParticle->getV() - MeanV).Length2()/SigmaV.Length2());
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
			if (tmpHalo.getNrParticles() > myConstants::constants.HaloSeed && tmpHalo.getNrParticles() != NrParticles){
				SubHalos.push_back(new CHalo(&tmpHalo)); // <-- kill
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




void CHalo::removeEmptySubHalos(){

	//This method completly changes subhalo relationship
	//It might well be that instead of beeing kept as subhalos of each other,
	//I should split it into two different halos.
	//if (NrParticles < myConstants::constants.HaloLimit){
	//	cout << "WARNING: Host halo has to few particles. I need to do stuff!" << endl;

	//Find the largest subhalo to use as a new hosthalo
	/*double tmpNrParticles;
	  double SubHaloNrParticles = -1;
	  int count = 0;
	  list<CHalo*>::iterator itKeep;
	  cout << "0" <<endl;
	  for (list<CHalo*>::iterator it = SubHalos.begin()++; it != SubHalos.end();it++) {
	  tmpNrParticles = (*it)->getNrParticles();
	  cout << "sdfsdfsdfsdf: " <<tmpNrParticles << endl;
	  if (tmpNrParticles > SubHaloNrParticles){
	  cout << "Do I ever get here?" << endl;
	  SubHaloNrParticles = tmpNrParticles;
	  itKeep = it;
	  }
	  count++;
	  }
	  if (count > 0){
	  list<CHalo*> otherSubHalos = SubHalos;
	  //otherSubHalos.remove(*itKeep);
	  //Copy over the information from the largest subhalo to this halo
	  cout << "1.3" <<endl;

	  copy(*itKeep);
	  cout << "1.5" <<endl;
	  //Add the other subhalos as subhalos of the same subhalo
	  for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end();it++) {
	  if (it != itKeep){
	  SubHalos.push_back(*it);
	  }
	  }
	  }
	  cout << "2" <<endl;*/
	//}

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
			cout << "Merging two halos"<<endl;
			cout << SubHalos.size()<< endl;
			SubHalos.erase(it);
			//SubHalos.remove(*it);
			addHalo(*it);
			flag = 0;
			return;
		}
	}
	//It completes withouth merging any halos
	flag = 1;
}





void CHalo::SortParticlesDistance(){
	vector<ParticleAndDistance*> data;

	for (int i = 0; i < NrParticles; i++) {
		ParticleAndDistance* tmpData = new ParticleAndDistance;
		tmpData->r= (MeanP - Halo[i]->getP()).Length();
		tmpData->Particle = Halo[i];
		data.push_back(tmpData);
	}

	sort(data.begin(),data.end(),&ParticleAndDistanceSortFunc);

	Halo.clear();

	//free up memory
	for (int i = 0; i < NrParticles; i++) {
		Halo.addParticle(data[i]->Particle);
		r.push_back(data[i]->r);
		if (data[i] != NULL) delete data[i];
		data[i] = NULL;
	}
	//delete ParticleAndDistance;
}




void CHalo::CalculatePhiSpherical(){
	SortParticlesDistance();

	//Move this to the correct place to calulate virialisation stuf. Probably statistics somewhere
	calculateVir();
	double M = 0;
	double Phi0 = Mvir/Rvir;

	for (int i = 1; i < NrParticles; i++) {
		if(r[i] > Rvir) break;
		M+=Halo[i]->getMass();
		Phi0 += M/(r[i]*r[i])*(r[i]-r[i-1]);
		//Phi0 += Halo[i]->getMass()/(r[i]*r[i]);
	}
	Phi0 *= -myConstants::constants.G;

	M = 0;
	Phi.clear();
	Phi.push_back(Phi0);
	//Phi.push_back(myConstants::constants.G*Halo[1]->getMass()/(r[1]*r[1])*(r[1]-r[0]));
	for (int i = 1; i < NrParticles; i++) {
		//Phi.push_back(myConstants::constants.G*Halo[i]->getMass()/(r[i]*r[i])+Phi[i-1]);
		M += Halo[i]->getMass();
		Phi.push_back((myConstants::constants.G*M/(r[i]*r[i]))*(r[i]-r[i-1])+Phi[i-1]);
	}

	/*Phi0 = Phi[NrParticles-1];
	  for (int i = 0; i < NrParticles; i++) {
	  Phi[i] -= Phi0;
	  }*/
}




//Method for unbinding particles from a single halo
void CHalo::Unbind(int& count){
	CalculatePhiSpherical();

	vector<int> RemoveIndex;
	for (int i = 0; i < NrParticles; i++) {
		if (Halo[i]->getV().Length2() > 2*abs(Phi[i])) {
			RemoveIndex.push_back(i);
		}
	}
	count += RemoveIndex.size();

	//Be carefull, this is gona fuck me up royaly(with the RemoveIndex[i]-i)
	for (int i = 0; i < RemoveIndex.size(); i++) {
		removeParticle(RemoveIndex[i]-i);
	}

	if (RemoveIndex.size() > 0 and NrParticles >= myConstants::constants.HaloLimit) Unbind(count);
}


void CHalo::UnbindAll(){
	int count =0;
	Unbind(count);
	//cout << "Percentage off particles unbound: " << (count)/(double)NrParticles*100 << endl;
	//savePhi(myConstants::constants.outPhi);
	//save(myConstants::constants.outBounding, (count-1)/(double)NrParticles);
	for (list<CHalo*>::iterator it = SubHalos.begin(); it != SubHalos.end(); it++) {
		(*it)->UnbindAll();
	}
}



//Do the splitting of halos, assigning particles to all halos, and merge statisticaly equal halos
void CHalo::createSubHalos(){
	//cout << "In createSubHalos in CHalo" << endl;
	CParticles allParticles;
	allParticles.copy(Halo);
	//cout << "In createSubHalos in CHalo, before splithalo" << endl;
	SplitHalo();
	//cout << "In createSubHalos in CHalo, before assigning particles" << endl;
	assignParticles(&allParticles);
	//saveStructure("structureBig.dat");
	//exit(0);
	//cout << "In createSubHalos in CHalo, before merging statistical" << endl;
	mergeStatistical();
	//printSubHalos();
	//del(myConstants::constants.outBoundng);
	//UnbindAll();
	//cout << "In createSubHalos in CHalo, before removing halos" << endl;
	removeEmptySubHalos();
	//cout << "In createSubHalos in CHalo, finished" << endl;
	//Unbind();
}

