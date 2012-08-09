#include <mpi.h>
#include <vector>

//extern int size;

class CMPI {
 
 private:
  
 public:
  CMPI();
  CMPI(int argc, char **argv);
  void initialize_CMPI(int argc, char **argv);
  ~CMPI();
  
  //Send and receive an array from the master node
  void send_array_master(double* master_send_array, int processor, int length);
  void send_array_master_all(double* master_send_array, int length);
  double* receive_array_master(int processor, int& master_length, MPI_Request* Req);
  
  //void receive_array_master_all(double** results, int length);
  double** receive_array_master_all(int& length);
  //Send and receive an array from a slave node
  void send_array_slave(double* slave_send_array, int length);
  //void receive_array_slave(double* slave_receive_array, int slave_length);
  double* receive_array_slave(int& slave_length);
  int WaitOne(MPI_Request* Req);
  void WaitAll(MPI_Request* Req);
  
  //Test which slave processor finishes first and return processor nr
  int listener(MPI_Request* Req);
  
  int getRank();
  int getSize();
  
  //Start to listen for end signal in slave process
  void isEnd();
  //Send end signal from Master process to all slave processes
  void End();
  //Test if end signal is sent
  int testEnd();
  
 protected:
  
  int size, rank;
  MPI_Request* endReq;
  int argc; 
  char **argv;
  
};
