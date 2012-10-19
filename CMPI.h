#include <mpi.h>
#include <vector>

class CMPI {
 public:

	//Constructor, initialize MPI
	CMPI();
	//Constructor, initialize MPI
	CMPI(int argc, char **argv);
	//Initialize MPI
	void initialize_CMPI(int argc, char **argv);
	~CMPI();

	
	//Send and receive an array in the master node to/from a given processor
	void send_array_master(double* master_send_array, int processor, int length);
	double* receive_array_master(int processor, int& master_length, MPI_Request* Req);

	
	//Send and receive an array in a slave node
	void send_array_slave(double* slave_send_array, int length);
	double* receive_array_slave(int& slave_length);


	//Send and recieve all arrays. Specialized, not used in CArray.
	void send_array_master_all(double* master_send_array, int length);
	double** receive_array_master_all(int& length);
	
	
	//Wait for all/one processor to finish the current job
	void WaitAll(MPI_Request* Req);
	int WaitOne(MPI_Request* Req);
	
	//Test which slave processor finishes first
	//and return processor nr of the slave that finishes first
	int listener(MPI_Request* Req);

	//Return the rank of the current processor
	int getRank();
	//Return total nr of processors
	int getSize();

	
	//Sending signal to determine if the slave processor should stop waiting
	//for work or to keep working
	void End(int processor, int sendflag);
	//Test if master processor have sent signal to
	//stop work in slave processor or not
	int ifEnd();



 protected:
	int size, rank, argc;
	char **argv;
	MPI_Request* endReq;

};
