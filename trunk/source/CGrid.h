#pragma once

#include <vector>
#include "CParticles.h"

class CGrid{
 public:
	//Initializes an empty grid with 0 size
	CGrid();
	//Initialize the grid
	CGrid(CVector* inMin, CVector* inMax, int inWidth);
	~CGrid();

	//Remove all particles from the grid
	void clear();
	
	//Initialize the grid with minimum and maximum vector and the width of the grid
	void initialize(CVector* inMin, CVector* inMax, int inWidth);

	//Get the position of a given particle in the grid
	CVector getPosition(CParticle* inParticle);

	//Populate the grid with a set of particles, using periodic boundary conditions
	void Populate(CParticles* inParticles);
	//Add a particle to the grid, using periodic boundary conditions
	void addParticle(CParticle* inParticle);

	//CParticle* get(int x, int y, int z);
	//Get all particles at a given position in the grid, using periodic boundary conditions
	CParticle* getPeriodic(int x, int y, int z);

	//Get the width of the grid
	int getWidth() {
	  return Width;
	}
	
 protected:
	vector<CParticle*> Grid;
	int Width,NrParticles,NrGridBoxes,NrHalos;
	CVector Min, Max, Delta;
};
