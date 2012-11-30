#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m,n;
	//a.get_Data ("particles.dat");
	
	m.LoadBin(myConstants::constants.inFile);
	//a.print();
	//a.initialize_Halos();
	//m.FriendOfFriendN2();
	//m.printHalos();
	m.FriendOfFriendGrid();
	//m.printHalos();
	//m.saveP();
	n = *m.master();
	//n.printHalos();
	n.print();
	n.saveP();
	//m.printHalos();
}

void CMain::slave(){

	CHalos s;
	s.slave();
}

