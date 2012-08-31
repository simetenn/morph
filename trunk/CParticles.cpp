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
//nr of Halos : nr of particles in each Halo : ... : ParticleArray : ParticleArray : ...
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
  
  for (int i = 0; i<nrHalos;i++){
    for (int j = 0;j < inArray->get(i+1);j++){
      //Gets the particle data for a single particle, stored in tmpArray
      for (int k = 0; k < ParticleSize;k++){
	tmpArray[k] = inArray->get(particle_count*ParticleSize+1+nrHalos+k);
      }
            
      //takes up extra 
      //Create a new particle from tmpArray
      Particles.push_back(new CParticle); //Slow way to do this?? //<- memory leak?
      Particles[particle_count]->Set_Data(tmpArray);
      //Store the particle in correct halo
      Halos[i].push_back(Particles[particle_count]);
      //Halos[i].push_back(Particles[particle_count]);
      //tmpParticles.push_back(new CParticle); //Slow way to do this??
      //tmpParticles[j]->Set_Data(tmpArray);
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
    cout << "                                  " << endl;
    cout << "Halo nr: " << i << endl;
    cout << "Nr of particles in halo: " << Halos[i].size() << endl;
    cout << "__________________________________" << endl;
    //for (int j = 0;j < Halos[i].size();j++){
    //Halos[i][j]->print_Particle();
    //}
  }
}


//Convert from one halo to an array
CArray*  CParticles::Halo2Array(vector<CParticle*> in_vector){//pointer
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
CArray*  CParticles::Halos2Array(){//pointer
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








void CParticles::master(){
  CMPI MPI;

  int count = 0;
  int processor; 
  int size = MPI.getSize();
  CParticles finalHalos;
  
  MPI_Request Req [size-1];
  vector<CArray*> Array (size-1);
  //Not needed
  /*for (int i =0;i<size-1;i++){
    Array[i] = new CArray ();
    }*/


  //Initialize, sending one halo to each processor
  for (int p = 1;p<size;p++){
    cout << "Initializing for processor nr: " << p << endl;
    //Array.push_back(Halo2Array(Halos[count]));
    Array[p-1] = Halo2Array(Halos[count]);
    MPI.End(p,0);
    Array[p-1]->send(p);
    //Probably can be kept it as it is, as Array is an array of pointers to CArray objects. Might otherwise be problems with changing length of arrays
    //Array[p-1]->print();
    Array[p-1]->recieve(p, &Req[p-1]);
    //return 0;
    count++;
  }
  
  cout << "-------------------------------------------------" << endl;
  cout << "Finished distributing halos to each processor" << endl;
  cout << "-------------------------------------------------" << endl;
  //Send halo to processor as soon as a processor finishes
  while (count < nrHalos) {
    cout << "Finished with halo nr: " << count +1 << endl;
    processor = MPI.listener(Req);
    //cout << "Finished in processor: " << processor  << endl;        
    finalHalos.addHalos(Array[processor-1]);
    Array[processor-1] = Halo2Array(Halos[count]);
    MPI.End(processor,0);
    Array[processor-1]->send(processor);
    Array[processor-1]->recieve(processor,&Req[processor-1]);
    count++;
    //MPI_Request Req [size-1];
    
  }
  
  //if (size != MPI.getRank()) MPI.WaitAll(Req);
  MPI.WaitAll(Req);
  cout << "<<sending end signal to slaves>>" << endl;
  //MPI.End();
  
  for (int p = 1;p < size;p++){
    MPI.End(p,1);
  }
  
  cout <<"end of master" << endl;
}


/*CParticles CParticles::operator+(CParticles inParticles){
  CParticles tmp;
  
  
  for (int i =0; i< length;i++) {
    tmp.array[i] = array[i] + number;
  }
  return ;
  }*/


void CParticles::slave(){
  
  //  CArray tmpArray;
  //CArray* HalosArray = &tmpArray;
  CArray HalosArray;
  CMPI MPI;
  //cout << "size "<< size << endl;
  
  //for (int i = 0;i<8;i++) {
  int flag;
  //int test = 0;
  while (true) {
    
  //for (int i = 0;i<8;i++){  
    //cout << MPI.testEnd() << endl;
    //if (MPI.testEnd() == 1) {
    //  cout << "<<recieved end signal>>" << endl;
    //  break;
    //}
    
    if (MPI.ifEnd() == 1) break;
    HalosArray.recieve_slave();
    //HalosArray.print();
    CParticles slaveParticles (&HalosArray);
    //slaveParticles.print_Particles();
    //slaveParticles.DoSomething();


    slaveParticles.Halos2Array()->send_slave();
    //resArray->send_slave();
    //test++;

  }
  cout << "finished loop" << endl;
}




void CParticles::HaloSort(){

}


