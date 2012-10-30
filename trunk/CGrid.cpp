#include "CGrid.h"
#include <iostream>

using namespace std;



CGrid::CGrid(){
	Width = 0;
}

CGrid::CGrid(CVector* inMin, CVector* inMax, int inWidth){
	initialize(inMin,inMax, inWidth);
}


CGrid::~CGrid(){
}


void CGrid::initialize(CVector* inMin, CVector* inMax, int inWidth){
	Width = inWidth;
	Min = *inMin;
	Max = *inMax;

	Delta = (Max-Min)/(double)Width;
	Grid.clear();

	Grid.resize(Width);
		for (int i = 0; i < Width; i++){
		Grid[i].resize(Width);
		for (int j = 0;j < Width;j++){
			Grid[i][j].resize(Width);
			/*for (int k = 0;k<Width;k++){
				CParticles* tmpParticles = new CParticles();
				Grid[i][j][k] = tmpParticles;
				}*/
		}
	}
	
	}


void CGrid::Populate(CParticles* inParticles){
	for (int i = 0; i < inParticles->getNrParticles(); i++){
		addParticle(inParticles->get(i));
	}
}


CVector CGrid::getPosition(CParticle* inParticle){
	CVector pos = (inParticle->getP() + (Min))/Delta;
	//pos.Add(Width);
	//pos =CVector(pos.x()/Delta.x(),pos.y()/Delta.y(),pos.z()/Delta.z());
	return CVector(((int) pos.x())+Width,((int) pos.y())+Width,((int) pos.z())+Width);
}


void CGrid::addParticle(CParticle* inParticle){
	CVector tmpPosition = getPosition(inParticle);
	//tmpPosition.print();
	//CVector tmpPosition(1,1,1);
	//tmpPosition.Set(1,1,1);
	//CParticles* p = (Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()]);
	//cout << p << endl;
	//p->print();//->addParticle(inParticle);
	(Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()]).addParticle(inParticle);
	(Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()]).setFlag(0);
	//cout << "there" << endl;
	//tmpPosition.print();
}


CParticles* CGrid::get(int x, int y, int z) {
	if (x<0) x=0;
	if (y<0) y=0;
	if (z<0) z=0;
	if (x>=Width) x = Width-1;
	if (y>=Width) y = Width-1;
	if (z>=Width) z = Width-1;

	return &Grid[x][y][z];
}

CParticles* CGrid::getPeriodic(int x, int y, int z) {
	if (x<0) x+=Width;
	if (y<0) y+=Width;
	if (z<0) z+=Width;
	if (x>=Width) x-=Width;
	if (y>=Width) y-=Width;
	if (z>=Width) z-=Width;

	return &Grid[x][y][z];
}

void CGrid::print(){
	for (int i = 0; i < Width; i++){
		for (int j = 0;j < Width; j++){
			for (int k = 0;k < Width; k++){
				Grid[i][j][k].print();
			}
		}
	}
}
