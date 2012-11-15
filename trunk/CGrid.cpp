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
			//for (int k = 0;k<Width;k++){
			//	Grid[i][j][k].clear();
			//}
		}
	}
}


void CGrid::Populate(CParticles* inParticles){
	for (int i = 0; i < inParticles->getNrParticles(); i++){
		addParticle(inParticles->get(i));
	}
}


CVector CGrid::getPosition(CParticle* inParticle){
	//cout << "in getPosition" << endl;
	//inParticle->getP().print();
	CVector pos = (inParticle->getP() - (Min))/Delta;
	//pos.Add(Width);
	//pos = CVector(pos.x()/Delta.x(),pos.y()/Delta.y(),pos.z()/Delta.z());
	
	//return (inParticle->getP() - (Min))/Delta;
	return CVector(((int) pos.x()),((int) pos.y()),((int) pos.z()));
}


int CGrid::getWidth() {
	  return Width;
}


void CGrid::addParticle(CParticle* inParticle){
	CVector tmpPosition = getPosition(inParticle);

	//CVector tmpPosition(1,1,1);
	//tmpPosition.Set(1,1,1);
	//CParticles* p = (Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()]);
	//cout << p << endl;
	//p->print();//->addParticle(inParticle);
	inParticle->setFlag(0);
	Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()].push_back(inParticle);
	/*if (Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()] == NULL){
		Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()] = inParticle;
	}
	else{
		Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()]->push_back(inParticle);
		}*/
	//cout << "there" << endl;
	//tmpPosition.print();
}

void CGrid::removeParticle(CParticle* inParticle){
	CVector tmpPosition = getPosition(inParticle);
	Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()].remove(inParticle);
}

void CGrid::eraseParticleIf(CParticle* inParticle){
	CVector tmpPosition = getPosition(inParticle);
	list<CParticle*> tmpList= Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()];

	for (list<CParticle*>::iterator it = tmpList.begin(); it!=tmpList.end(); it++) {
		if (inParticle == *it ){
			//cout << "erasing particle" << endl;
			Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()].erase(it);
			return;
		}
	}
}


/*void CGrid::eraseParticleIf(list<CParticle*>::iterator it){
	CVector tmpPosition = getPosition(*it);
	list<CParticle*> tmpList= Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()];

	for (list<CParticle*>::iterator ittest = tmpList.begin(); ittest!=tmpList.end(); ittest++) {
		if (it == ittest ){
			Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()].erase(it);
			return;
		}
	}
	}*/

void CGrid::eraseParticle(list<CParticle*>::iterator it){
	CVector tmpPosition = getPosition(*it);
	Grid[tmpPosition.x()][tmpPosition.y()][tmpPosition.z()].erase(it);
}


list<CParticle*> CGrid::get(int x, int y, int z) {


	x = x % Width;
	y = y % Width;
	z = z % Width;


	return Grid[x][y][z];
}

list<CParticle*> CGrid::getPeriodic(int x, int y, int z) {

	x = x % Width;
	y = y % Width;
	z = z % Width;


	return Grid[x][y][z];
}


list<CParticle*>::iterator CGrid::getBegin(int inx, int iny, int inz){
	return Grid[inx][iny][inz].begin();
}

list<CParticle*>::iterator CGrid::getEnd(int inx, int iny, int inz){
	return Grid[inx][iny][inz].end();
}


/*void CGrid::print(){
	for (int i = 0; i < Width; i++){
		for (int j = 0;j < Width; j++){
			for (int k = 0;k < Width; k++){
				Grid[i][j][k].print();
			}
		}
	}
	}*/
