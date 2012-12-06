#pragma once

#include <vector>
#include "CParticles.h"

class CGrid{
 public:
	CGrid();
	CGrid(CVector* inMin, CVector* inMax, int inWidth);
	~CGrid();

	void initialize(CVector* inMin, CVector* inMax, int inWidth);

	CVector getPosition(CParticle* inParticle);

	void Populate(CParticles* inParticles);
	void addParticle(CParticle* inParticle);

	CParticle* get(int x, int y, int z);
	CParticle* getPeriodic(int x, int y, int z);

	void print();

	int getWidth() {
	  return Width;
	}
	
 protected:
	vector<vector<vector<CParticle* > > > Grid;
	int Width,NrParticles,NrGridBoxes,NrHalos;
	CVector Min, Max, Delta;
};
