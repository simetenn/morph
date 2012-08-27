//#include "CArray.h"
//#include "CVector.h"
#include "CParticles.h"
//#include <vector>
//#include <mpi.h>
using namespace std;

int size, rank;

int main(int argc, char **argv){
  //CMPI MPI (argc,argv);
  //CMPI MPI
  //MPI.initialize_CMPI(argc,argv);
  //Master node
  int rank,size;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  

  if (rank == 0) {
        
    CParticles a;
    a.get_Data ("particles.dat");
    //a.print_Particles();
    a.initialize_Halos();
    //a.print_Halos();
    cout << "tralala" << endl;
    a.master();
    cout << "master" << endl;
    MPI_Barrier(MPI_COMM_WORLD);
    cout << "master" << endl;
    MPI_Finalize();
  }
      
  
  else {
    CParticles b;
    b.slave();
    cout << "same slave"<< endl;
    MPI_Barrier(MPI_COMM_WORLD);
    cout << "same slave"<< endl;
    MPI_Finalize();
  }
  //MPI_Finalize();

}
