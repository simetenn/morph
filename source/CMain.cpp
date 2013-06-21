#include "CMain.h"

Constants myConstants::constants;

void CMain::master() {
	CHalos m;
	CHalos* n;
	
	m.loadClaudio(myConstants::constants.inFile);
	//m.saveP("Halos.dat");
	//m.loadHalos("singleHalo2.dat");
	//m.loadGadget("multisubhalo_nfw.bin");
	//m.CalculateAllStatistics();
	//cout << m.getNrParticles() << endl;
	//m.print();
	//exit(1);

	m.FriendOfFriendGrid();
	//m.saveP("HalosFOF.dat");
	//m.getHalo(1)->saveHalo("Velocity1.dat");
	//m[22]->saveHaloBin("singleHalo.dat");
	//exit(0);
	//m.HaloSort();
	//m.saveHalos("testHalos.dat");
	//m.getHalo(125)->calculateVirBeta();
	//exit(1);
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
	//n->HaloSort();
	//n->saveHalos("splitHalos.dat");
	//n->getHalo(10)->calculateVirBeta ();
	cout << n->getNrParticles() << endl;
	n->saveSize(myConstants::constants.outSize);
	//n->saveP("HalosSplit.dat");
	//n->clear();
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}
