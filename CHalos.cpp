#include "CHalos.h"

using namespace std;

//Constructor, creates empty CHalos
CHalos::CHalos(){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	nrParticles = 0;
	nrHalos = 0;
}


//Create CHalos from an in array on the form:
//nr of halos, nr of particles in halo 1, nr of particles in halo 2, ... ,
//nr of particles of in halo N, particle array 1, particle array 2, ... ,
//particle array N
CHalos::CHalos(CArray* inArray){
	nrHalos = inArray->get(0);

	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	int particle_count = 1+nrHalos;
	nrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	
	for (int i = 0; i < nrHalos; i++){
		nrinHalo.push_back(inArray->get(1+i));
		double tmpArray[nrinHalo[i]*ParticleSize];

		for (int j = 0; j < nrinHalo[i];j++){
			for (int k = 0; k < ParticleSize;k++){
				tmpArray[j*ParticleSize+k] = inArray->get(particle_count);
				particle_count++;
			}
		}
		
		CArray* tmpCArray = new CArray(nrinHalo[i]*ParticleSize, tmpArray);
		CHalo* tmpHalo = new CHalo(tmpCArray); // <- Memory leak
		Halos.push_back(tmpHalo);
	}
}




CHalos::~CHalos(){

}


//Initialize the halos in my own fake datasett
void CHalos::initialize_Halos(){
	nrHalos = 8;
	CHalo* oldHalo = Halos[0];
	Halos.clear();
	nrinHalo.clear();
	
	for (int i = 0; i < nrHalos; i++){
		CHalo* tmpHalo = new CHalo();

		Halos.push_back(tmpHalo);
	}

	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	for (int i = 0; i < nrParticles;i++){
		Halos[(oldHalo->getParticle(i)->get_P()).Quadrant()]->addParticle(oldHalo->getParticle(i));
	}
	
	for (int i = 0; i < nrHalos;i++){
		nrinHalo.push_back(Halos[i]->getnrParticles());
	}
}




//Sort halos by size, not existing yet
void CHalos::HaloSort(){

}



//Print out all halos
void CHalos::printHalos(){
	for (int i = 0;i < nrHalos; i++){
		cout << "__________________________________" << endl;
		cout << "								   " << endl;
		cout << "Halo nr: " << i << endl;
		cout << "Nr of particles in halo: " << nrinHalo[i] << endl;
		cout << "__________________________________" << endl;
		cout << endl;
	}
}


//Add halo to the existing ones
void CHalos::addHalo(CHalo* inHalo){
	Halos.push_back(inHalo);
}





//Add halos to the existing ones
void CHalos::addHalos(CArray* inArray){
	int oldnrHalos = nrHalos;
	int oldnrParticles = nrParticles;

	int newnrHalos = inArray->get(0);
	nrHalos += newnrHalos;
	vector<int> tmpnrinHalo;
	int newnrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	nrParticles += newnrParticles;

	int particle_count = 0;

	cout << "nrinHalo: " <<inArray->get(1) <<endl;
	for (int i = 0; i < newnrHalos; i++){
		nrinHalo.push_back(inArray->get(1+i));
		tmpnrinHalo.push_back(inArray->get(1+i));

		double tmpArray[tmpnrinHalo[i]*ParticleSize];
		cout << nrinHalo[i] << endl;
		for (int j = 0; j < tmpnrinHalo[i];j++){

			for (int k = 0; k < ParticleSize;k++){
				tmpArray[j*ParticleSize+k] = inArray->get(particle_count);
				particle_count++;
			}
		}

		CArray* tmpCArray = new CArray(tmpnrinHalo[i]*ParticleSize, tmpArray);
		CHalo* tmpHalo = new CHalo(tmpCArray); // <- Memory leak
		Halos.push_back(tmpHalo);
	}
}





//Convert from all halos to one array
CArray*	 CHalos::Halos2Array(){
	//rewrite this when time, but seems to work atm

	double* Array = new double [ParticleSize*nrParticles+nrHalos+1]; // Memory leak
	int particle_count = 1+nrHalos;
	double* tmpArray;
	Array[0] = nrHalos;

	for (int i = 0; i<nrHalos;i++){
		Array[i+1] = nrinHalo[i];
		for (int j=0;j<nrinHalo[i];j++){
			tmpArray = Halos[i]->get(j)->Particle2Array();
			for (int k = 0; k < ParticleSize;k++){
				Array[particle_count] = tmpArray[k];
				particle_count++;
			}
		}
	}

	return new CArray(ParticleSize*nrParticles+nrHalos+1,Array); //Memory leak
}



//Return total nr of particles
int CHalos::getnrParticles(){
	return nrParticles;
}



//return nr of particles in a halo
int CHalos::getnrinHalo(int element){
	return nrinHalo[element];
}



//Return a halo
CHalo* CHalos::getHalo(int element){
	return Halos[element];
}




//Return nr of halos
int CHalos::getnrHalos(){
	return nrHalos;
}




//Return nr of halos
int CHalos::sizeHalos(){
	return nrHalos;
}




//Remove halo nr element from CHalos
void CHalos::removeHalo(int element){
	nrinHalo.erase(nrinHalo.begin()+element);
	Halos.erase(Halos.begin() + element);
}




//Add two CHalos. Not tested, so unsure if correct
CHalos CHalos::operator+(CHalos* inCHalo){
	int innrParticles = inCHalo->getnrParticles();
	int innrHalos = inCHalo->getnrHalos();
	int particle_count = nrHalos+innrHalos+1;
	
	CArray* resHalos = new CArray(ParticleSize*(nrParticles+innrParticles)+nrHalos+innrHalos+1);
	double tmpArray[ParticleSize];

	resHalos[0]=nrParticles+innrParticles;

	for (int i = 0; i<nrHalos;i++){
		resHalos[particle_count] = nrinHalo[i];
		particle_count++;
	}

	for (int i = 0; i<innrHalos;i++){
		resHalos[particle_count] = inCHalo->getnrinHalo(i);
		particle_count++;
	}

	for (int i = 0; i<nrHalos;i++){
		CArray* tmpHaloArray = Halos[i]->Halo2Array();
		for (int j = 0;j < tmpHaloArray->len();j++){
			resHalos[particle_count] = tmpHaloArray->get(j);
			particle_count++;
		}
	}

	for (int i = 0; i<innrHalos;i++){
		CArray* tmpHaloArray = inCHalo->getHalo(i)->Halo2Array();
		for (int j = 0;j < tmpHaloArray->len();j++){
			resHalos[particle_count] = tmpHaloArray->get(j);
			particle_count++;
		}
	}
	return CHalos(resHalos);
}





//Get data from my own type of input file
//For testing purposes only
void CHalos::get_Data(string filename){
	vector<string> strData;
	ifstream file(filename.c_str());
	string line;
	int nr = 1;
	
	vector<double> tmpData;

	if (file.is_open()){
		getline(file,line);
		split(strData, line, is_any_of("\t "));

		data_size = strData.size();
		tmpData.push_back(-1);
		for (int i = 0; i < data_size; i++){
			tmpData.push_back(atof(strData[i].c_str()));
		}

		
		while (file.good()){
			getline(file,line);
			split(strData, line, is_any_of(" "));
			tmpData.push_back(-1);
			for (int i = 0; i < data_size; i++){
				tmpData.push_back(atof(strData[i].c_str()));
			}
			nr++;
		}
		file.close();
	}

	else cout << "Unable to open file" << endl;
	nrinHalo.push_back(nr);
	nrParticles = nr;

	double tmpArray [nr*ParticleSize];

	for (int i = 0;i<nr*ParticleSize;i++){
		tmpArray[i] = tmpData[i];
	}


	Halos.push_back(new CHalo (new CArray (nr*ParticleSize,tmpArray)));
}


//Returns CParticles* for a given halo
CParticles* CHalos::getCParticles(int element){
	return Halos[element]->getCParticles();
}



//Print out all particles one by one
void CHalos::print(){
	for (int i = 0;i<Halos.size();i++){
		Halos[i]->print();
	}
}



//Master process
void CHalos::master(){
	CMPI MPI;
	int count = 0;
	int processor;
	int size = MPI.getSize();
	CHalos FinalHalos;
	MPI_Request Req [size-1];
	vector<CArray*> Array (size-1);
	CParticle tmpParticle;


	//Initialize, sending one halo to each processor
	for (int p = 1; p < size; p++){
		cout << "Initializing for processor nr: " << p << endl;

		Array[p-1] = Halos[count]->Halo2Array();//Halo2Array(Halos[count]);
		//Array[p-1]->print();
		MPI.End(p,0);
		Array[p-1]->send(p);
		Array[p-1]->recieve(p,&Req[p-1]);
		count++;
	}


	cout << "-------------------------------------------------" << endl;
	cout << "Finished distributing halos to each processor" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << nrHalos << endl;
	//Send halo to processor as soon as a processor finishes
	while (count < nrHalos) {
		cout << "Calculating for halo nr: " << count + 1 << endl;
		//Listening for a processor to finish
		processor = MPI.listener(Req);
		FinalHalos.addHalos(Array[processor-1]);

		Array[processor-1] =  Halos[count]->Halo2Array();
		MPI.End(processor,0);

		Array[processor-1]->front(Array[processor-1]->len()/tmpParticle.getParticleSize());
		Array[processor-1]->front(1);

		Array[processor-1]->send(processor);
		Array[processor-1]->recieve(processor,&Req[processor-1]);
		count++;

	}
	//Waiting for all processors to finish their last task
	MPI.WaitAll(Req);

	//Send end signal to all processors
	for (int p = 1;p < size;p++){
		MPI.End(p,1);
	}
}



//Slave processor, listening for data from the master processor
//Then does something with the data before sending it back to the
//master processor
void CHalos::slave(){

	CArray HalosArray;
	CMPI MPI;
	int flag;
	int rank = MPI.getRank();

	CParticle tmpParticle;

	while (true) {
		if (MPI.ifEnd() == 1) break;
		HalosArray.recieve_slave();
		
		//cout << "Slave " << rank << " recieved halo" << endl;
		CHalos SlaveHalos (&HalosArray);

		//slaveParticles.DoSomething();

		SlaveHalos.Halos2Array()->send_slave();
	}
}





//Load a binary file from a N-body simulation into memory
void CHalos::LoadBin(string Filename){
	ifstream f(Filename.c_str(), ios::in | ios::binary);
	
	cout << "---------------------------------" << endl;
	cout << "Reading file..." << endl;

	unsigned int count = -1;

	//Reading binary file into memory
	f.read((char *)&count, sizeof(unsigned int));
	particle_save* block = new particle_save[count];
	f.read((char *)block, sizeof(particle_save)*count);

	
	Halos.clear();
	nrinHalo.clear();
	nrHalos = 1;

	CHalo* tmpHalo = new CHalo();
	Halos.push_back(tmpHalo);

	cout << "Copying data..." << endl;
	count = 1000;
	cout << "Nr of particles: "<< count << endl;

	//Saving data into existing structure
	//Saving all Particles into the first halo in Halos, acces with Halos[0]
	for (int i=0;i<count;i++) {
		CParticle* tmpParticle = new CParticle() ;

		tmpParticle->Set_Position(block[i].P.x,block[i].P.y,block[i].P.z);
		tmpParticle->Set_Velocity(block[i].V.x,block[i].V.y,block[i].V.z);
		tmpParticle->Set_Acceleration(0,0,0);

		tmpHalo->addParticle(tmpParticle);
	}

	cout << "Done loading!" << endl;
	cout << "---------------------------------" << endl;
	f.close();
	delete[] block;

	nrParticles = count;
	nrinHalo.push_back(nrParticles);
}





//Save positions for each particle belonging to a halo to a text file,
//together with which halo it belongs too 
void CHalos::saveP(){
	fstream file;
	CVector tmpP;

	file.open("positions.dat", ios::out);

	//Saves position data for each particle to file
	for (int i = 0;i<nrHalos;i++){
		for (int j = 0;j<nrinHalo[i];j++){
			tmpP = Halos[i]->getParticle(j)->get_P();
			file << tmpP.x() << " " << tmpP.y()<< " " << tmpP.z()<< " " <<	i << endl;
		}
	}
	
	file.close();
}





//Calculating Friend of Friend using recursion, without a grid.
//Scales as N^2
//The following 3 methods are used only for this
void CHalos::FriendOfFriendN2(){
	int HaloLimit = 10;
	vector<CHalo*> tmpHalos;

	allParticles = *Halos[0]->getCParticles();
	searchParticle = Halos[0]->getParticle(0);
	CParticle* Particle = searchParticle;

	//Create a linked list of all particles
	Particle->prev=NULL;
	for (int i=1; i < nrParticles;i++){
		Particle->setFlag(0);
		Particle->next = allParticles[i];
		Particle->next->prev = Particle;
		Particle = Particle->next;
	}
	Particle->setFlag(0);
	Particle->next = NULL;


	cout << "---------------------------------" << endl;
	cout << "Calculating Friend of Friend(scaling as N^2)" << endl;
	cout << "." << endl;
	cout << ".." << endl;
	cout << "..." << endl;

	//Using recursion to link all particles belonging to a halo
	while (true){
		Particle = findParticle();

		if (Particle == NULL) break;
		else {
			CHalo* tmpHalo = new CHalo();
			tmpHalos.push_back(tmpHalo);

			findNeighbors(Particle, tmpHalo);
		}
	}

	//Only saving halos that has more than 10 particles, updating nrinHalos
	Halos.clear();
	nrinHalo.clear();
	for (int i = 0; i < tmpHalos.size(); i++){
		if (tmpHalos[i]->getnrParticles() > HaloLimit){
			Halos.push_back(tmpHalos[i]);
			nrinHalo.push_back(tmpHalos[i]->getnrParticles());
		}
		nrHalos = Halos.size();
	}

	cout << "Finished calculating Friend of Friends" << endl;
	cout << "---------------------------------" << endl;
}

//This might be obsolete with removing particles from the list
//Finds the next particle that has no halo and returns it
CParticle* CHalos::findParticle(){
	while (true){
		if (searchParticle->getFlag() == 0)
			return searchParticle;

		searchParticle = searchParticle->next;

		if (searchParticle == NULL)
			return NULL;
	}
}


void CHalos::findNeighbors(CParticle* inParticle, CHalo* inHalo){
	double b = 0.02;

	inParticle->setFlag(1);
	inParticle->RemoveFromList();
	inHalo->addParticle(inParticle);

	CHalo FriendList;

	for (int i = 0; i<allParticles.getnrParticles();i++){
		if (allParticles[i]->getFlag()==0){
			double distance = (inParticle->get_P() - allParticles[i]->get_P()).Length();

			if (distance < b){
				allParticles[i]->setFlag(1);
				//allParticles->RemoveFromList()
				FriendList.addParticle(allParticles[i]);
			}
		}
	}

	if (FriendList.getnrParticles() != 0){
		for (int i = 0; i<FriendList.getnrParticles();i++){
			findNeighbors(FriendList[i],inHalo);
		}
	}
}






//Friend of Friend methode that uses a grid to speed up the calculations
//Scales as log(N)
void CHalos::FriendOfFriendGrid(){

}






//Do not use this. Way to slow method. It is not tested, but seems to run
void CHalos::FriendOfFriendN3(){
	double b = 0.2;
	int otherHaloID,thisHaloID;
	CHalo* oldHalo = Halos[0];
	CHalo* noHalo = new CHalo();

	Halos.clear();
	nrinHalo.clear();

	for (int i=0;i<nrParticles;i++){
		cout << "Running FoF for particle nr: " << i << endl;
		CParticle* thisParticle = oldHalo->getParticle(i);
		thisHaloID = thisParticle->getHalo();

		for (int j=0;j<nrParticles;j++){
			if (i!=j) {
				CParticle* otherParticle = oldHalo->getParticle(j);
				otherHaloID = otherParticle->getHalo();
				thisHaloID = thisParticle->getHalo();
				double distance = (thisParticle->get_P() - otherParticle->get_P()).Length();
				
				//If the particles are within linking distance of each other
				if (distance < b ){
					cout <<"thisHaloID: "<<thisHaloID<< "\t otherHaloID: "<<otherHaloID << endl;
					//If both particles have no halo,
					//create a new halo and add both particles to that halo
					if (otherHaloID == -1 and thisHaloID == -1){
						cout << "None have a halo, assigning both haloID: " << nrHalos << endl;
						oldHalo->getParticle(i)->setHalo(nrHalos);
						oldHalo->getParticle(j)->setHalo(nrHalos);

						Halos.push_back(new CHalo());

						Halos[nrHalos]->addParticle(oldHalo->getParticle(i));
						Halos[nrHalos]->addParticle(oldHalo->getParticle(j));
						nrinHalo.push_back(2);
						nrHalos++;
					}

					//Test if both have a halo, but not the same halo.
					//Then add the smaller halo to the larger,
					//delete the smaller from Halos and
					//update HaloID for each particle in the following halos.
					else if (thisHaloID != -1 and otherHaloID != -1 and	 thisHaloID != otherHaloID){
						Halos[thisHaloID]->addHalo(Halos[otherHaloID]);
						nrinHalo[thisHaloID] += nrinHalo[otherHaloID];

						for (int m = 0; m<nrinHalo[otherHaloID];m++){
							Halos[otherHaloID]->getParticle(m)->setHalo(thisHaloID);
						}
						
						//For each halo
						for (int k = otherHaloID+1;k < nrHalos;k++){
							//for each particle in halo
							for (int l = 0;l<nrinHalo[k];l++){
								Halos[k]->getParticle(l)->decreaseHalo();
							}
						}

						nrHalos--;
						Halos.erase(Halos.begin()+otherHaloID);
						nrinHalo.erase(nrinHalo.begin()+otherHaloID);
					}

					//If the other particle has a halo, add this particle to
					//the halo the other particle has
					else if (thisHaloID == -1 and otherHaloID != -1){
						cout << "Only other particle has a halo" << endl;
						Halos[otherHaloID]->addParticle(oldHalo->getParticle(i));
						Halos[otherHaloID]->getParticle(nrinHalo[otherHaloID])->setHalo(otherHaloID);
						nrinHalo[otherHaloID]++;

					}

					else if (otherHaloID == -1 and thisHaloID != -1){
						cout << "Only this particle has a halo" << endl;
						//oldHalo->getParticle(j)->setHalo(thisHaloID);
						Halos[thisHaloID]->addParticle(oldHalo->getParticle(j));
						Halos[thisHaloID]->getParticle(nrinHalo[thisHaloID])->setHalo(thisHaloID);
						nrinHalo[thisHaloID]++;
					}
				}
			}
		}
	}
}
