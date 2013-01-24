#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m,n;
		
	m.loadClaudio(myConstants::constants.inFile);
	//m.loadData(myConstants::constants.DataFile);
	//m.print();
	//cout << m.getNrParticles() << endl;
	m.FriendOfFriendGrid();
	//m.save(myConstants::constants.DataFile,myConstants::constants.NrParticles2File);
	//m.FriendOfFriendN2();
	//m.printHalos();
	n = *m.master();
	//n.CalculateAllStatistics();
	n.HaloSort();
	n.CalculatePhiSpherical();
	n[10]->savePhi(myConstants::constants.outPhi);
	n.saveSize(myConstants::constants.outSize);
	//n.saveP(myConstants::constants.outPosition);
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

