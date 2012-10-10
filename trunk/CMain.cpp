#include "CMain.h"

Constants myConstants::constants;


void CMain::master() {
	CHalos m;
	//a.get_Data ("particles.dat");
	cout << myConstants::constants.test << endl;
	m.LoadBin("particles_keep.dat");
	//a.print();
	//a.initialize_Halos();
	m.FriendOfFriendN2();
	m.printHalos();
	m.saveP();
	//m.master();
	//m.printHalos();
}

void CMain::slave(){

	CHalos s;
	//s.slave();
}

