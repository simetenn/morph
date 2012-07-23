#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "CParticle.h"
using namespace boost;


class CParticles : public CParticle {
 public:
  CParticles();
  ~CParticles();
  
  void get_Data(string filename);
  void print_Particles();
  void print_Halos();
  void initialize_Halos();
  
 protected:
  vector<CParticle*> Particles;
  vector<vector<CParticle*> > Halos;
  int nrParticles,nrHalos ;
  

};
