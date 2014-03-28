#include "CGrid.h"
#include <iostream>

using namespace std;


//Initializes an empty grid with 0 size
CGrid::CGrid(){
	Width = 0;
}

//Initialize the grid
CGrid::CGrid(CVector* inMin, CVector* inMax, int inWidth){
	initialize(inMin,inMax, inWidth);
}


CGrid::~CGrid(){
	//clear();
}

//Remove all particles from the grid
void CGrid::clear(){
	Grid.clear();
}

//Initialize the grid with minimum and maximum vector and the width of the grid
void CGrid::initialize(CVector* inMin, CVector* inMax, int inWidth){
	Width = inWidth;
	Min = *inMin;
	Max = *inMax;

	Delta = (Max-Min)/(double)Width;
	Grid.clear();
	Grid.resize(Width*Width*Width);
	for (int i = 0; i < Width*Width*Width; i++) {
		Grid[i] = NULL;
	}
}

//Populate the grid with a set of particles, using periodic boundary conditions
void CGrid::Populate(CParticles* inParticles){
	for (int i = 0; i < inParticles->getNrParticles(); i++){
		addParticle(inParticles->get(i));
	}
}

//Get the position of a given particle in the grid
CVector CGrid::getPosition(CParticle* inParticle){
	CVector pos = (inParticle->getP() - (Min))/Delta;
	return CVector((int) (pos.x()) % Width,(int)( pos.y())% Width,(int) (pos.z())% Width);
}

//Add a particle to the grid, using periodic boundary conditions
void CGrid::addParticle(CParticle* inParticle){
	CVector tmpPosition = getPosition(inParticle);

	int x = (int)tmpPosition.x() % Width;
	int y = (int)tmpPosition.y() % Width;
	int z = (int)tmpPosition.z() % Width;

	inParticle->setFlag(0);
	if (Grid[x + y*Width + z*Width*Width] == NULL){
		Grid[x + y*Width + z*Width*Width] = inParticle;
	}
	else{
		Grid[x + y*Width + z*Width*Width]->attachParticle(inParticle);
	}
}

/*CParticle* CGrid::get(int x, int y, int z) {


	x = x % Width;
	y = y % Width;
	z = z % Width;


	return Grid[x + y*Width + z*Width*Width];
	}*/

//Get all particles at a given position in the grid, using periodic boundary conditions
CParticle* CGrid::getPeriodic(int x, int y, int z) {

	x = x % Width;
	y = y % Width;
	z = z % Width;


	return Grid[x + y*Width + z*Width*Width];
}
