#include "CHalos.h"

using namespace std;


int main(int argc, char **argv){
	int rank,size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (rank == 0) {

		CHalos a;
		a.get_Data ("particles.dat");
		//a.LoadBin("particles_keep.dat");
		a.initialize_Halos();
		//a.printHalos();
		a.master();
		//a.printHalos();
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	}

	else {
		CHalos b;
		b.slave();
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Finalize();
	}
}
