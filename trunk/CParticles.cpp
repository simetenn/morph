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

CParticles::CParticles(CArray* inArray){
  nrHalos = 1;
  if (inArray->len() % ParticleSize != 0) {
    cout << "Warning: Length of array not compatible with ParticleSize"<< endl;
  }
  nrParticles = inArray->len()/ParticleSize;
  vector<double> tmpArray (ParticleSize);
  for (int i = 0; i < nrParticles;i++){
    
    for (int j = 0; j < ParticleSize;j++){
      tmpArray[j] = inArray->get(i*ParticleSize + j);
    }

    Particles.push_back(new CParticle); //Slow way to do this??
    Particles[i]->Set_Data(tmpArray);
  }
}

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
    //Particles[0]->print_Particle();
    
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

void CParticles::print_Particles(){
  for (int i = 0; i < nrParticles;i++){
    Particles[i]->print_Particle();
  }
}


void CParticles::initialize_Halos(){
  nrHalos = 8;
  Halos.resize(nrHalos);
  for (int i = 0; i < nrParticles;i++){
    Halos[(Particles[i]->get_P()).Quadrant()].push_back(Particles[i]);
  }
    

}

void CParticles::print_Halos(){
  for (int i = 0;i < nrHalos; i++){
    cout << "__________________________________" << endl;
    cout << "                                  " << endl;
    cout << "Halo nr: " << i << endl;
    cout << "Nr of particles in halo: " << Halos[i].size() << endl;
    cout << "__________________________________" << endl;
    /*for (int j = 0;j < Halos[i].size();j++){
      Halos[i][j]->print_Particle();
      }*/
  }
}

CArray*  CParticles::Halo2Array(vector<CParticle*> in_vector){//pointer
  double* Array = new double [ParticleSize*in_vector.size()]; // Memory leak
  for (int i = 0; i < in_vector.size();i++){
    
    double* tmpArray = in_vector[i]->Particle2Array();
    for (int j = 0; j < ParticleSize;j++){
      Array[i*ParticleSize+j] = tmpArray[j];
    }
  }
  return new CArray(ParticleSize*in_vector.size(),Array); //Memory leak
}



CArray*  CParticles::Halos2Array(){//pointer
  double* Array = new double [ParticleSize*nrParticles+nrHalos+1]; // Memory leak
  int HaloSize;
  int particle_count = 1+nrHalos;
  Array[0] = nrHalos;
  for (int i = 0; i<nrHalos;i++){
    HaloSize = Halos[i].size();
    Array[i+1] = HaloSize;
    for (int j=0;j<HaloSize;j++){
      double* tmpArray = Particles[j]->Particle2Array();
      for (int k = 0; k < ParticleSize;k++){
	Array[particle_count] = tmpArray[j];
	particle_count++;
      }
    }
  }
  return new CArray(ParticleSize*nrParticles+nrHalos+1,Array); //Memory leak
}

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
  
  for (int i = 0; i<newnrHalos;i++){
    
    
    for (int j = 0;i < inArray->get(i+1);j++){
      
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








void CParticles::master(){
  MPI_Status Stat[size-1];
  int count = 0;
  int processor; 
  CParticles finalHalos;
  vector<CArray*> Array; 
  for (int p = 1;p<rank;p++){
    Array[p] = Halo2Array(Halos[count]);
    Array[p]->send(p);
    Array[p]->recieve(p);
    
    count++;
  }
  
  while (count < (nrHalos-size+1)) {
    
    MPI_Waitany(size-1,Req_receive,&processor,Stat);
    //Particles2Array(Halos[count])->send(processor)
    finalHalos.addHalos(Array[processor]);
    Array[processor] = Halo2Array(Halos[count]);
    Array[processor]->send(processor);
    Array[processor]->recieve(processor);
    count++;
    
    
  }

}


/*CParticles CParticles::operator+(CParticles inParticles){
  CParticles tmp;
  
  
  for (int i =0; i< length;i++) {
    tmp.array[i] = array[i] + number;
  }
  return ;
  }*/


void CParticles::slave(){
  CArray* HalosArray;
  while (true) {
    HalosArray->recieve_slave();
    CParticles slaveParticles (HalosArray);
    //slaveParticles.DoSomething();
    HalosArray = slaveParticles.Halos2Array();
    HalosArray->send_slave();
  }
}


void CParticles::HaloSort(){

}
