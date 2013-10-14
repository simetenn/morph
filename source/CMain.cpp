#include "CMain.h"
#include <sstream>

Constants myConstants::constants;

void CMain::master() {
	CHalos m;
	CHalos* n;

	//m.loadClaudio(myConstants::constants.inFile);
	m.loadMax(myConstants::constants.inFile);
	//exit(1);
	//m.saveP("Halos.dat");
	//m.loadHalos("singleHaloWithPhi2.bin");
	//m.printHalos();
	//m.loadHalos("Halos.bin");
	//m.loadHalos("Halos.bin");
	//m.loadHalos("singleHalo.dat");
	//m.loadGadget("multisubhalo_nfw.bin");
	//m.CalculateAllStatistics();
	//m.printHalos();
	//cout << m.getNrParticles() << endl;
	//m.print();
	//exit(1);


	m.FriendOfFriendGrid();
	m.HaloSort();

	/*m[50]->saveP("positions50.dat");
	m[150]->saveP("positions150.dat");
	m[250]->saveP("positions250.dat");
	m[350]->saveP("positions350.dat");
	m[500]->saveP("positions500.dat");
	m[1000]->saveP("positions1000.dat");
	m[2000]->saveP("positions2000.dat");
	m[5000]->saveP("positions5000.dat");
	m[10000]->saveP("positions10000.dat");*/


	/*m[50]->savePhi("PhiSingle1.dat");
	m[100]->savePhi("Phi2Single.dat");
	m[200]->savePhi("Phi3Single.dat");
	m[300]->savePhi("Phi4Single.dat");
	m[500]->savePhi("Phi5Single.dat");
	m[1000]->savePhi("Phi6Single.dat");
	m[5000]->savePhi("Phi7Single.dat");
	m[10000]->savePhi("Phi8Single.dat");
	m[20000]->savePhi("Phi9Single.dat");*/
	
	//exit(0);
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
	/*cout <"---------Here--------------" << endl;
	n->CalculatePhiSpherical();
	
	for (int i = 0; i < n->getNrHalos(); i++) {
		ostringstream save;
		save << "Phi"<< i << ".dat"; 
		n->getHalo(i)->savePhi(save.str());
		}*/
	
	/*n->getHalo(50)->savePhi("Phi1Single.dat");
	n->getHalo(150)->savePhi("Phi2Single.dat");
	n->getHalo(200)->savePhi("Phi3Single.dat");
	n->getHalo(300)->savePhi("Phi4Single.dat");
	n->getHalo(500)->savePhi("Phi5Single.dat");
	n->getHalo(1000)->savePhi("Phi6Single.dat");
	n->getHalo(5000)->savePhi("Phi7Single.dat");
	n->getHalo(10000)->savePhi("Phi8Single.dat");
	n->getHalo(15000)->savePhi("Phi9Single.dat");*/

	//n->getHalo(50)->saveP("positions50.dat");
	//n->getHalo(150)->saveP("positions150.dat");
	//n->getHalo(250)->saveP("positions250.dat");
	//n->getHalo(350)->saveP("positions350.dat");
	//n->getHalo(450)->saveP("positions450.dat");

	//n->HaloSort();
	//n->saveHalos("splitHalos.dat");
	//n->getHalo(10)->calculateVirBeta ();
	//cout << n->getNrParticles() << endl;
	//n->saveSize(myConstants::constants.outSize);
	n->CalculateAllStatistics();
	n->saveMass("mass.dat");
	n->saveData("data.dat");
	

	//n->saveP("HalosSingleSplit.dat");
	//n->clear();
	delete n;
}

void CMain::slave(){
	CHalos s;
	s.slave();
}

