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
		//h.LoadBin(myConstants::constants.inFile);
		h.LoadData(myConstants::constants.haloFile);
		//h.printHalos();
		//h.FriendOfFriendGrid();
		h.printHalos();
		h.CalculateAllStatistics();
		//h.FriendOfFriendPhaseSpace();
		h.printHalos();
		h.saveP();
		//h[6]->saveHalo();
	}
	MPI_Finalize();
 
}
