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

	CParticles* get(int x, int y, int z);
	CParticles* getPeriodic(int x, int y, int z);

	void print();
	
 protected:
	vector<vector<vector<CParticles > > > Grid;
	int Width,NrParticles,NrGridBoxes,NrHalos;
	CVector Min, Max, Delta;
};
