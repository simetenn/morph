#include "CParticles.h"

using namespace std;
using namespace boost;

CParticles::CParticles(){
  nrParticles = 0;
}

CParticles::~CParticles(){
}

void CParticles::Get_data(string filename){
  vector<string> strData;
  
  ifstream file(filename.c_str());
  string line;
  //CParticle* tmpParticle;

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
