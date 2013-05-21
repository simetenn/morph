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
	
	//m.loadClaudio(myConstants::constants.inFile);
	m.loadHalos("testHalos.dat");
	//m.loadGadget("halo_plum");
	//m.CalculateAllStatistics();
	//m.printHalos();
	//exit(1);

	//m.FriendOfFriendGrid();
	
	//m.saveHalos("splitHalosPlum.bin");
	//exit(0);
	m.HaloSort();
	//m.saveHalos("testHalos.dat");
	m.getHalo(11)->calculateVirBeta();
	exit(1);
	n = m.master();
	//m.clear();
	/*cout << n->outsideVir()<<endl;
	cout << n->getNrParticles() << endl;
	
	//n.saveHalos("splitHalos.dat");
	//n.CalculateAllStatistics();
	
	n->HaloSort();
	n->CalculatePhiSpherical();
	n->getHalo(1)->savePhi("Phi1.dat");
	n->getHalo(10)->savePhi("Phi2.dat");
	n->getHalo(21)->savePhi("Phi3.dat");
	n->getHalo(41)->savePhi("Phi4.dat");
	n->getHalo(56)->savePhi("Phi5.dat");
	n->getHalo(5)->savePhi("Phi6.dat");
	n->getHalo(9)->savePhi("Phi7.dat");
	//n->printHalos();*/
	n->HaloSort();
	n->saveHalos("testHalos.dat");
	n->getHalo(10)->calculateVirBeta();
	n->saveSize(myConstants::constants.outSize);
	//n->clear();
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

