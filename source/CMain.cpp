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
	n[0]->savePhi(myConstants::constants.outPhi);
	n[2]->savePhi("Phi2.dat");
	n[8]->savePhi("Phi3.dat");
	n[16]->savePhi("Phi4.dat");
	n[32]->savePhi("Phi5.dat");
	n[64]->savePhi("Phi6.dat");	
	n[128]->savePhi("Phi7.dat");
	
	n.saveSize(myConstants::constants.outSize);
	//n.saveP(myConstants::constants.outPosition);
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

