#include "CMain.h"
#include <sstream>

Constants myConstants::constants;

void CMain::master() {
	CHalos m;
	CHalos* n;

	//m.loadClaudio(myConstants::constants.inFile);
	m.loadMax(myConstants::constants.inFile);
	//m.loadHalos("singleHaloWithPhi2.bin");
	//m.CalculateAllStatistics();
	//m.printHalos();


	m.FriendOfFriendGrid();
	m.HaloSort();

	n = m.master();
	
	//cout << n->outsideVir() << endl;
	//cout << n->getNrParticles() << endl;
	
	//n.saveHalos("splitHalos.dat");
	//n->CalculateAllStatistics();
	
	//n->HaloSort();
	n->CalculateAllStatistics();
	n->saveMass("mass.dat");
	n->saveData("data.dat");
	
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

