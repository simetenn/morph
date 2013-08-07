#include "CMain.h"
#include <sstream>

Constants myConstants::constants;

void CMain::master() {
	CHalos m;
	CHalos* n;

	//m.loadClaudio(myConstants::constants.inFile);
	//exit(1);
	//m.saveP("Halos.dat");
	//m.loadHalos("singleHaloWithPhi2.bin");
	//m.printHalos();
	//m.loadHalos("LCDM1.bin");
	//m.loadHalos("Halos.bin");
	//m.loadHalos("singleHalo.dat");
	//m.loadGadget("multisubhalo_nfw.bin");
	//m.CalculateAllStatistics();
	//m.printHalos();
	//cout << m.getNrParticles() << endl;
	//m.print();
	//exit(1);
	//m.FriendOfFriendGrid();
	//m[0]->saveP("HaloSingle.dat");
	//m.getHalo(1)->saveHalo("Velocity1.dat");
	//m[0]->saveHaloBin("singleHalo.dat");

	//exit(0);
	//m.HaloSort();
	//m.saveHalos("Halos.bin");
	//m.getHalo(125)->calculateVirBeta();
	//exit(1);
	n = m.master();
	

	//m.clear();
	//cout << n->outsideVir() << endl;
	//cout << n->getNrParticles() << endl;
	
	//n.saveHalos("splitHalos.dat");
	//n->CalculateAllStatistics();
	
	//n->HaloSort();
	/*cout <<"---------Here--------------" << endl;
	n->CalculatePhiSpherical();
	
	for (int i = 0; i < n->getNrHalos(); i++) {
		ostringstream save;
		save << "Phi"<< i << ".dat"; 
		n->getHalo(i)->savePhi(save.str());
		}*/
	
	//n->getHalo(1)->savePhi("Phi1.dat");
	//n->getHalo(10)->savePhi("Phi2.dat");
	//n->getHalo(21)->savePhi("Phi3.dat");
	//n->getHalo(41)->savePhi("Phi4.dat");
	//n->getHalo(56)->savePhi("Phi5.dat");
	//n->getHalo(130)->savePhi("Phi6.dat");
	//n->getHalo(450)->savePhi("Phi7.dat");
	//n->printHalos();
	//n->HaloSort();
	//n->saveHalos("splitHalos.dat");
	//n->getHalo(10)->calculateVirBeta ();
	//cout << n->getNrParticles() << endl;
	n->saveSize(myConstants::constants.outSize);
	n->saveMass("mass.dat");
	n->saveP("HalosSingleSplit.dat");
	//n->clear();
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

