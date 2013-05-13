#include "CMain.h"

Constants myConstants::constants;


void CMain::testCArray(){
	CArray a (10);

	for (int i = 0; i < 10; i++) {
		a[i] = i;
	}
	for (int i = 0; i < 20; i++) {
		a.push_back(i+10);
	}
	
	
	for (int i = 0; i < 3; i++) {
		CArray* tmp = new CArray ((1+i));
		a.add(tmp);
	}
	a.print();
	
	
}

void CMain::master() {
	CHalos m;
	CHalos* n;

	m.loadClaudio(myConstants::constants.inFile);
	//m.loadHalos("splitHalosRamses.bin");
	//m.loadGadget("halo_plum");
	//m.CalculateAllStatistics();
	//m.printHalos();
	//exit(1);
	m.FriendOfFriendGrid();
	//m.saveHalos("splitHalosPlum.bin");
	//exit(0);
	n = m.master();
	//n.saveHalos("splitHalos.dat");
	//n.CalculateAllStatistics();
	/*n.HaloSort();
	n.CalculatePhiSpherical();
	n[0]->savePhi(myConstants::constants.outPhi);
	n[2]->savePhi("Phi2.dat");
	n[8]->savePhi("Phi3.dat");
	n[16]->savePhi("Phi4.dat");
	n[32]->savePhi("Phi5.dat");
	n[64]->savePhi("Phi6.dat");	
	n[128]->savePhi("Phi7.dat");*/
	//n->printHalos();
	n->saveSize(myConstants::constants.outSize);
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

