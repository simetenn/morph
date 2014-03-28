#include "CMain.h"

using namespace std;


int main(int argc, char **argv){
	int rank,size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (rank == 0) {
		//Run the master process
		CMain m;
		m.master();
		
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	} else {
		//Run the slave processes
		CMain s;
		s.slave();

		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	}
	
	return 0;
}
