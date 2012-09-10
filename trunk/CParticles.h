#include <iostream>
#include <fstream>
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
	void initialize_CParticles(CArray* inArray);
	
	//void Array2Particles(CArray* inArray);
	//void sendHalo(int halonr)
	void master();
	void slave();
	int size();


	CParticle* operator[](int element);

	void LoadBin(string Filename);

	// Particle Save structure: Keep only P and V!
	struct particle_save {
		CVector P, V;
		unsigned int halo;
	};

	void SeparateClustersMPI();

	

 protected:
	vector<CParticle*> Particles;
	int nrParticles,data_size;


};
