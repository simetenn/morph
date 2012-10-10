#include "CMain.h"

using namespace std;


int main(int argc, char **argv){
	int rank,size;
	//CMPI a;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (rank == 0) {
		CMain m;
		m.master();
		
		
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	}

	else {

		CMain s;
		//s.slave();
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	}
}
