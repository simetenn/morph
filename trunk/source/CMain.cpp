#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m,n;
	//a.get_Data ("particles.dat");
	
	//m.loadBin(myConstants::constants.inFile);
	m.loadData(myConstants::constants.DataFile);
	//a.print();
	//a.initialize_Halos();
	//m.FriendOfFriendN2();
	//m.printHalos();
	m.FriendOfFriendGrid();
	//m.printHalos();
	//n = *m.master();//->printHalos();
	//m.saveP();
	n = *m.master();
	n.HaloSort();
	//n.printHalos();
	n.saveSize(myConstants::constants.outSize);
	//n.print();
	n.saveP(myConstants::constants.outPosition);
	//m.printHalos();
}

void CMain::slave(){

	CHalos s;
	s.slave();
}

