#include <iostream>
#include <fstream>
//#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "CParticle.h"
#include "CArray.h"
using namespace boost;


class CParticles : public CParticle{
 public:
  CParticles();
  CParticles(CArray* inArray);
  ~CParticles();
  
  void get_Data(string filename);
  void print_Particles();
  void print_Halos();
  void initialize_Halos();
  CArray* Halo2Array(vector<CParticle*> in_vector);
  CArray* Halos2Array();
  CArray* Array2Halos(CArray* inArray);
  //void Array2Particles(CArray* inArray);
  void HaloSort();
  //void sendHalo(int halonr)
  void addHalos(CArray* inArray);
  void master();
  void slave();

 protected:
  vector<CParticle*> Particles;
  vector<vector<CParticle*> > Halos;
  int nrParticles,nrHalos,data_size;
  

};
