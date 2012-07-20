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
  
  void Get_data(string filename);
  void print_Particles();

 protected:
  vector<CParticle*> Particles;
  int nrParticles;
  

};
