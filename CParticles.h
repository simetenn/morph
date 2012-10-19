#pragma once


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
	//Creates CParticles from a CArray on the following form:
	//ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N
	CParticles(CArray* inArray);
	~CParticles();


	//Sets a already existing CParticles to contain the values from
	//a CArray on the following form:
	//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
	//Similar to the constructor
	void set(CArray* inArray);

	//Print all particles
	void print();


	//return nr of Particles
	int getNrParticles();


	//Return particle nr #element
	CParticle* operator[](int element);
	//Return particle nr #element
	CParticle* get(int element);
	//CParticle* getParticle(int element);


	//Add a particle to CParticles
	void addParticle(CParticle* inParticle);
	//Add several particles to CParticles
	void addParticles(CParticles* inParticles);


	//Convert CParticles to a CArray on the form
	//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
	CArray* Particles2Array();

	//Set the flag of all particles in CParticles
	void setFlag(int inFlag);

	
 protected:
	vector<CParticle*> Particles;
	int NrParticles,data_size,ParticleSize;
};
