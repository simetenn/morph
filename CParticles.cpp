#include "CParticles.h"

using namespace std;
using namespace boost;

CParticles::CParticles(){
	nrParticles = 0;
	nrHalos = 0;
}

CParticles::~CParticles(){
	for (int i = 0; i < nrParticles;i++){
		delete Particles[i];// <- correct?
	}
}

//Creates CParticles from an Array formated in a specific way.
//nr of Halos : nr of particles in 1st Halo :  nr of particles in 2nd Halo : ... : ParticleArray : ParticleArray : ...
CParticles::CParticles(CArray* inArray){
	nrHalos = inArray->get(0);

	//Gives warning if the length of the array is not compatible with the size of a particle
	if ((inArray->len()-1-nrHalos) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	vector<double> tmpArray (ParticleSize);

	Halos.resize(nrHalos);
	int particle_count = 0;


	//Loop over all halos and all particles in each halo
	for (int i = 0; i<nrHalos;i++){
		for (int j = 0;j < inArray->get(i+1);j++){
			//Gets the particle data for a single particle, stored in tmpArray
			for (int k = 0; k < ParticleSize;k++){
				tmpArray[k] = inArray->get(particle_count*ParticleSize+1+nrHalos+k);
			}

			//Create a new particle from tmpArray
			Particles.push_back(new CParticle); //Slow way to do this?? //<- memory leak?
			Particles[particle_count]->Set_Data(tmpArray);
			//Store the particle in correct halo
			Halos[i].push_back(Particles[particle_count]);
			particle_count++;
		}
		//Halos.push_back(tmpParticles);
		//tmpParticles.clear();
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


//Initialize the halos in my own fake datasett
void CParticles::initialize_Halos(){
	nrHalos = 8;
	Halos.resize(nrHalos);
	for (int i = 0; i < nrParticles;i++){
		Halos[(Particles[i]->get_P()).Quadrant()].push_back(Particles[i]);
	}
}


//Print information for each halo
void CParticles::print_Halos(){
	for (int i = 0;i < nrHalos; i++){
		cout << "__________________________________" << endl;
		cout << "								   " << endl;
		cout << "Halo nr: " << i << endl;
		cout << "Nr of particles in halo: " << Halos[i].size() << endl;
		cout << "__________________________________" << endl;
		//for (int j = 0;j < Halos[i].size();j++){
		//Halos[i][j]->print_Particle();
		//}
	}
}


//Convert from one halo to an array
CArray*	 CParticles::Halo2Array(vector<CParticle*> in_vector){//pointer
	double* Array = new double [ParticleSize*in_vector.size()+2]; // Memory leak
	Array[0] = 1;
	Array[1] = in_vector.size();
	for (int i = 0; i < in_vector.size();i++){

		double* tmpArray = in_vector[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j+2] = tmpArray[j];
		}
	}
	return new CArray(ParticleSize*in_vector.size()+2,Array); //Memory leak
}


//Convert from several halos to one array
CArray*	 CParticles::Halos2Array(){//pointer
	double* Array = new double [ParticleSize*nrParticles+nrHalos+1]; // Memory leak
	int HaloSize;
	int particle_count = 1+nrHalos;
	double* tmpArray;
	Array[0] = nrHalos;

	for (int i = 0; i<nrHalos;i++){
		//cout << "Halo nr:" << i << endl;
		//cout << Halos[i].size() << endl;

		HaloSize = Halos[i].size();
		Array[i+1] = HaloSize;
		for (int j=0;j<HaloSize;j++){
			tmpArray = Particles[j]->Particle2Array();
			for (int k = 0; k < ParticleSize;k++){
				Array[particle_count] = tmpArray[k];
				particle_count++;
			}
		}
	}

	return new CArray(ParticleSize*nrParticles+nrHalos+1,Array); //Memory leak
}


//Add a halo to the exsisting ones
void CParticles::addHalos(CArray* inArray){
	int oldnrHalos = nrHalos;

	int newnrHalos = inArray->get(0);
	nrHalos += newnrHalos;

	int newnrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	int oldnrParticles = nrParticles;
	nrParticles += newnrParticles;

	int particle_count = 0;
	//vector<CParticle* > tmpParticles;
	vector<double> tmpArray (ParticleSize);

	Halos.resize(nrHalos);

	for (int i = 0; i<newnrHalos;i++){
		for (int j = 0;j < inArray->get(i+1);j++){
			for (int k = 0; k < ParticleSize;k++){
				tmpArray[k] = inArray->get(particle_count*ParticleSize+1+newnrHalos+k);
			}


			//takes up extra
			Particles.push_back(new CParticle); //Slow way to do this??
			Particles[particle_count+oldnrParticles]->Set_Data(tmpArray);
			Halos[i].push_back(Particles[oldnrParticles+particle_count]);
			//tmpParticles.push_back(new CParticle); //Slow way to do this??
			//tmpParticles[j]->Set_Data(tmpArray);
			particle_count++;
		}

		//Halos.push_back(tmpParticles);
		//tmpParticles.clear();
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




void CParticles::HaloSort(){

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
