//#pragma once

#include "CHalos.h"
#include "Constants.h"

Constants myConstants::constants;


using namespace std;


int main(int argc, char **argv){
	int rank,size;
	//CMPI a;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		CHalos h;
		CHalos* h2 = new CHalos();
		CArray* a2 = new CArray();
		h.LoadBin(myConstants::constants.inFile);
		//h.LoadData(myConstants::constants.haloFile);
		//h.print();
		//h.printHalos();
		//h.saveP();
		//h.FriendOfFriendGrid();
		//h.printHalos();
		//h.print();
		h.save();
		//Constants::constants.PhaseDistance
		//h.CalculateAllStatistics();
		//h.getHalo(0)->printStatistics();
		//cout << h.getHalo(0)->LinkingLength() << endl;
		//h.getHalo(0)->createSubHalos();
		//cout << h.getHalo(0)->getTotalNrParticles() << endl;
		//h.getHalo(0)->SplitHalo(myConstants::constants.PhaseDistance);
		//h.getHalo(0)->saveStatX();
		//h.getHalo(0)->saveP();
		//h.getHalo(0)->printSubHalos();
		//h.SplitHalos();
		//h.FriendOfFriendPhaseSpace();
		//h.printHalos();
		//h.saveP();
		//h.saveSize();

		//h[2]->saveHalo();
		//exit(1);
		//h[427]->saveHalo();
		//exit(1);
		//Large halos
		//610,590,351,283


		/*MPI_Request Req;
		MPI_Status Stat;
		
		//cout << h.getHalo(0)->getNrParticles() << endl;
		CArray* Array = h.getHalo(0)->Halo2Array();
		
		Array->front(h.getHalo(0)->getNrParticles());
		
		Array->front(1);
		//Array->print();
		Array->send(1);
		a2->recieve(1,&Req);
		MPI_Wait (&Req, &Stat);
		a2->print();
		//Array->print();
		//a2->front(10038);
		//a2->front(1);
		
		h2->addHalos(a2);
		//h2->printHalos();
		//h2->saveP();
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();*/
		
	}
	
	/*else {

		CArray HalosArray;
		HalosArray.recieve_slave();
		CHalos SlaveHalos (&HalosArray);

		SlaveHalos.printHalos();
		//SlaveHalos.print();
		//Do something in each slave processor here
		//SlaveHalos.FriendOfFriendPhaseSpace();
		SlaveHalos.SplitHalos();
		//SlaveHalos.getHalo(0)->printSubHalos();
		SlaveHalos.getHalo(0)->SubHalos2Array()->send_slave();
		//tmp->front(1);
		//tmp->print();
		
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
		}*/
	MPI_Finalize();

	
	
}
