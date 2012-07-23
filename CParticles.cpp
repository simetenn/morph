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

void CParticles::get_Data(string filename){
  vector<string> strData;
  
  ifstream file(filename.c_str());
  string line;
  
  if (file.is_open()){
    
    getline(file,line);
    split(strData, line, is_any_of("\t "));
    
    int length = strData.size();
    vector<double> tmpData (length);
    
    
    for (int i = 0; i < length; i++){
      tmpData[i] = atof(strData[i].c_str());
    }
      
    Particles.push_back(new CParticle);
    Particles[0]->Set_data(tmpData);
    //Particles[0]->print_Particle();
    
    int nr = 1;
    while (file.good()){
      getline(file,line);
      split(strData, line, is_any_of(" "));
      
      for (int i = 0; i < length; i++){
	tmpData[i] = atof(strData[i].c_str());
      }
      
      Particles.push_back(new CParticle);
      Particles[nr]->Set_data(tmpData);
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
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    cout << "Halo nr: " << i << endl;
    cout << "nr of particles in halo: " << Halos[i].size() << endl;
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    for (int j = 0;j < Halos[i].size();j++){
      Halos[i][j]->print_Particle();
    }
  }
}

