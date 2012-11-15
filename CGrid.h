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

	void removeParticle(CParticle* inParticle);	
	void eraseParticle(list<CParticle*>::iterator it);
	
	list<CParticle*> get(int x, int y, int z);
	list<CParticle*> getPeriodic(int x, int y, int z);

	void print();

	int getWidth();

	list<CParticle*>::iterator getBegin(int inx, int iny, int inz);
	list<CParticle*>::iterator getEnd(int inx, int iny, int inz);
	//list<CParticle*>::iterator getEnd();

	
 protected:
	vector<vector<vector< list<CParticle*> > > > Grid;
	int Width,NrParticles,NrGridBoxes,NrHalos;
	CVector Min, Max, Delta;
};
