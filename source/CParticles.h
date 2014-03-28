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
	//Get Particles
	vector<CParticle*>* getParticles();

	//Add a particle to CParticles
	void addParticle(CParticle* inParticle);
	//Add a particle to CParticles, withouth updating the other halo information
	void addParticleSimple(CParticle* inParticle);
	//Add several particles to CParticles
	void addParticles(CParticles* inParticles);
	//remove particle from CParticles
	void removeParticle(int element);

	
	//Convert CParticles to a CArray on the form
	//[ParticleArray 1, ParticleArray 2, ParticleArray 3, ... , ParticleArray N]
	CArray* Particles2Array();

	//Set the flag of all particles in CParticles
	void setFlag(int inFlag);
	int getFlag();

	//Calculate the gravitational potential of all particles, using the paricles acceleration
	void calculatePhi(CVector& MeanP);
	
	//Set Nr of particles
	void setNrParticles(int Nr);

	
	//Removes all particles in CParticles from a linked list
	void RemoveFromList();
	
	//Copy a CParticles to a new CParticles object
	void copy(CParticles& p); 
	//Clear and remove all information from CParticles, it does not delete particles from the memory
	void clear();

	//Delete all information from CParticles, also deletes particles from the memory
	void kill();
	
 protected:
	vector<CParticle*> Particles;
	int NrParticles,ParticleSize,flag;
};
