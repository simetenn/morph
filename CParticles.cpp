#include "CParticles.h"

using namespace std;
using namespace boost;

CParticles::CParticles(){
	nrParticles = 0;
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
}

CParticles::~CParticles(){
	for (int i = 0; i < nrParticles;i++){
		delete Particles[i];// <- correct?
	}
}

//Creates CParticles from an Array formated in a specific way.
//nr of Halos : nr of particles in 1st Halo :  nr of particles in 2nd Halo : ... : ParticleArray : ParticleArray : ...
CParticles::CParticles(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len())/ParticleSize;
	int particle_count = 0;
	
	for (int i = 0; i<nrParticles;i++){
		double* tmpArray = new double [ParticleSize];
		
		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(ParticleSize*i+j);
		}

		CParticle * tmpParticle = new CParticle(tmpArray);
		Particles.push_back(tmpParticle);
	}
}


//Write this in some other way.
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
/*void CParticles::get_Data(string filename){
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
  }*/


//Print particles
void CParticles::print(){
	for (int i = 0; i < nrParticles;i++){
		Particles[i]->print();
	}
}



void CParticles::set(CArray* inArray){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();

	if ((inArray->len()) % ParticleSize != 0) {
		cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
	}

	nrParticles = (inArray->len())/ParticleSize;
	int particle_count = 0;
	
	for (int i = 0; i<nrParticles;i++){
		double* tmpArray = new double [ParticleSize];
		
		for (int j = 0; j < ParticleSize;j++){
			tmpArray[j] = inArray->get(ParticleSize*i+j);
		}

		CParticle * tmpParticle = new CParticle(tmpArray);
		Particles.push_back(tmpParticle);
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

CParticle* CParticles::get(int element){
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






/*CParticles CParticles::operator+(CParticles inParticles){
  CParticles tmp;


  for (int i =0; i< length;i++) {
  tmp.array[i] = array[i] + number;
  }
  return ;
  }*/







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


int CParticles::getnrParticles(){
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


CArray* CParticles::Particles2Array(){//pointer
	//int ParticleSize =
	double* Array = new double [ParticleSize*nrParticles]; // Memory leak

	for (int i = 0; i < nrParticles;i++){
		double* tmpArray = Particles[i]->Particle2Array();
		for (int j = 0; j < ParticleSize;j++){
			Array[i*ParticleSize+j] = tmpArray[j];
		}
	}
	//return Array;
	return new CArray(ParticleSize*nrParticles,Array); //Memory leak
}



void CParticles::addParticle(CParticle* inParticle){
	nrParticles += 1;
	Particles.push_back(inParticle);
}


CParticle* CParticles::getParticle(int element){
	if (element >= nrParticles){
		cout << "Particle out of bounds" << endl;
	}
	else {
		return Particles[element];
	}
}
