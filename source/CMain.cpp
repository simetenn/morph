#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m,n;

	//m.loadClaudio(myConstants::constants.inFile);
	m.loadData(myConstants::constants.DataFile);
	//m.print();
	
	//cout << m.getNrParticles() << endl;
	//m.FriendOfFriendGrid();
	//m.saveP("positionsFOF.dat");
	//m.save(myConstants::constants.DataFile,myConstants::constants.NrParticles2File);
	//m.FriendOfFriendN2();
	//m.CalculateAllStatistics();
	
	/*m[5]->saveHalo("velocity0.dat");
	m[6]->saveHalo("velocity1.dat");
	m[7]->saveHalo("velocity2.dat");
	m[8]->saveHalo("velocity3.dat");
	m[9]->saveHalo("velocity4.dat");
	m[10]->saveHalo("velocity5.dat");
	m[11]->saveHalo("velocity6.dat");
	m[12]->saveHalo("velocity7.dat");
	m[13]->saveHalo("velocity8.dat");
	m[14]->saveHalo("velocity9.dat");*/

	m[0]->createSubHalos();
	
	m.printHalos();
	//n = *m.master();
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
	
	m.saveSize(myConstants::constants.outSize);
	//n.saveP(myConstants::constants.outPosition);

}

void CMain::slave(){
	CHalos s;
	s.slave();
}

