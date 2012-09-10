#include "CParticles.h"

using namespace std;
using namespace boost;

CParticles::CParticles(){
	nrParticles = 0;
}

CParticles::~CParticles(){
	for (int i = 0; i < nrParticles;i++){
		delete Particles[i];// <- correct?
	}
}

//Creates CParticles from an Array formated in a specific way.
//nr of Halos : nr of particles in 1st Halo :  nr of particles in 2nd Halo : ... : ParticleArray : ParticleArray : ...
CParticles::CParticles(CArray* inArray){
	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len())/ParticleSize;
	vector<double> tmpArray (ParticleSize);
	int particle_count = 0;

	for (int i = 0; i<nrParticles;i++){
		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(particle_count*ParticleSize+j);
		}

		Particles.push_back(new CParticle); //Slow way to do this?? //<- memory leak?
		Particles[particle_count]->Set_Data(tmpArray);
		//Store the particle in correct halo
		particle_count++;
	}
}


void CParticles::initialize_CParticles(CArray* inArray){
	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}
	nrParticles = (inArray->len())/ParticleSize;
	vector<double> tmpArray (ParticleSize);
	int particle_count = 0;

	for (int i = 0; i<nrParticles;i++){
		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(particle_count*ParticleSize+j);
		}

		Particles.push_back(new CParticle); //Slow way to do this?? //<- memory leak?
		Particles[particle_count]->Set_Data(tmpArray);
		//Store the particle in correct halo
		particle_count++;
	}
}


//Get data from my own type of input file
void CParticles::get_Data(string filename){
	vector<string> strData;

	ifstream file(filename.c_str());
	string line;

	if (file.is_open()){
		getline(file,line);
		split(strData, line, is_any_of("\t "));

		data_size = strData.size();
		vector<double> tmpData (data_size);

		for (int i = 0; i < data_size; i++){
			tmpData[i] = atof(strData[i].c_str());
		}

		Particles.push_back(new CParticle);
		Particles[0]->Set_Data(tmpData);

		int nr = 1;
		while (file.good()){
			getline(file,line);
			split(strData, line, is_any_of(" "));

			for (int i = 0; i < data_size; i++){
				tmpData[i] = atof(strData[i].c_str());
			}

			Particles.push_back(new CParticle); //Memory leak?
			Particles[nr]->Set_Data(tmpData);
			//Particles[nr]->print_Particle();
			nr++;
		}
		file.close();
	}

	else cout << "Unable to open file" << endl;

	nrParticles = Particles.size();
}


//Print particles
void CParticles::print_Particles(){
	for (int i = 0; i < nrParticles;i++){
		Particles[i]->print_Particle();
	}
}




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





//Master process
void CParticles::master(){
	CMPI MPI;

	int count = 0;
	int processor;
	int size = MPI.getSize();
	CParticles finalHalos;

	MPI_Request Req [size-1];
	vector<CArray*> Array (size-1);

	//Initialize, sending one halo to each processor
	for (int p = 1;p<size;p++){
		cout << "Initializing for processor nr: " << p << endl;
		//Array.push_back(Halo2Array(Halos[count]));
		Array[p-1] = Halo2Array(Halos[count]);
		MPI.End(p,0);
		Array[p-1]->send(p);
		Array[p-1]->recieve(p, &Req[p-1]);
		count++;
	}

	cout << "-------------------------------------------------" << endl;
	cout << "Finished distributing halos to each processor" << endl;
	cout << "-------------------------------------------------" << endl;
	//Send halo to processor as soon as a processor finishes
	while (count < nrHalos) {
		cout << "Finished with halo nr: " << count +1 << endl;
		processor = MPI.listener(Req);
		finalHalos.addHalos(Array[processor-1]);
		Array[processor-1] = Halo2Array(Halos[count]);
		MPI.End(processor,0);
		Array[processor-1]->send(processor);
		Array[processor-1]->recieve(processor,&Req[processor-1]);
		count++;

	}

	MPI.WaitAll(Req);

	for (int p = 1;p < size;p++){
		MPI.End(p,1);
	}
}


/*CParticles CParticles::operator+(CParticles inParticles){
  CParticles tmp;


  for (int i =0; i< length;i++) {
  tmp.array[i] = array[i] + number;
  }
  return ;
  }*/



//slave processor
void CParticles::slave(){

	CArray HalosArray;
	CMPI MPI;
	int flag;

	while (true) {
		if (MPI.ifEnd() == 1) break;
		HalosArray.recieve_slave();
		CParticles slaveParticles (&HalosArray);

		//slaveParticles.print_Particles();
		//slaveParticles.DoSomething();

		slaveParticles.Halos2Array()->send_slave();
	}
}



void CParticles::LoadBin(string Filename){
	ifstream f(Filename.c_str(), ios::out | ios::binary);

	cout << "reading file..." << endl;
	unsigned int count = -1;
	f.read((char *)&count, sizeof(unsigned int));
	particle_save* block = new particle_save[count];
	f.read((char *)block, sizeof(particle_save)*count);


	cout << "Copying blocks.." << endl;
	for (int i=0;i<count;i++) {
		Particles.push_back(new CParticle); //Memory leak?
		Particles[i]->P=block[i].P;
		Particles[i]->V=block[i].V;
		Particles[i]->Set_Acceleration(0,0,0);
	}

	cout << "Done loading!" << endl;

	f.close();
	delete[] block;
}


int CParticles::size(){
	return nrParticles;
}


/*int CParticles::sizeHalos(){
  return nrHalos;
  }*/


void CParticles::SeparateClustersMPI(){
	/*double maxV = 0;
	  for (int i=0;i<nrParticles;i++) {
	  maxV = max(Particles[i]->V.Length(), maxV);
	  }
	  B = 1.0/maxV/100.0; // why?
	  cout << " B: " << B << endl;

	  for (int i = 0, i < nrParticles,i++){

	  }
	*/


}
