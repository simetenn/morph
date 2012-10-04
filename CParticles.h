#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "CParticle.h"
#include "CArray.h"
using namespace boost;


class CParticles{
 public:
	CParticles();
	CParticles(CArray* inArray);
	~CParticles();

	//void get_Data(string filename);
	void print();
	void initialize_CParticles(CArray* inArray);
	void set(CArray* inArray);
	//void Array2Particles(CArray* inArray);
	//void sendHalo(int halonr)

	int getnrParticles();
	

	void addParticle(CParticle* inParticle);
	
	CParticle* operator[](int element);
	CParticle* get(int element);

	CArray* Particles2Array();
	
	
	void SeparateClustersMPI();

	void addParticles(CParticles* inParticles);

	CParticle* getParticle(int element);

 protected:
	vector<CParticle*> Particles;
	int nrParticles,data_size,ParticleSize;


};


//ToDo:
//  Move LoadBin to CHalos.
