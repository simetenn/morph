#include <mpi.h>
#include <vector>

//extern int size;

class CMPI {
 
 private:
  //int m_argc;
  //char **m_argv;

  

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
  int listener(MPI_Request* Req);
  
  int getRank();
  int getSize();
  
  void isEnd();
  void End();
  int testEnd();
  
 protected:
  
  int size, rank;
  //int rank;
  MPI_Request endReq [1];
  //MPI_Status* Stat_receive;
  int argc; 
  char **argv;
  
  
  //MPI_Status* Stat_receive;
 
};
