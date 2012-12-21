#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m,n;
		
	m.loadClaudio(myConstants::constants.inFile);
	//m.loadData(myConstants::constants.DataFile);
	//m.printHalos();
	m.FriendOfFriendGrid();
	//m.printHalos();
	n = *m.master();
	n.CalculateAllStatistics();
	n.HaloSort();
	n.CalculatePhiSpherical();
	n[1]->savePhi(myConstants::constants.outPhi);
	n.saveSize(myConstants::constants.outSize);
	n.saveP(myConstants::constants.outPosition);
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

