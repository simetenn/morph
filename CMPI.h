#include <mpi.h>

class CMPI {
 private:
  int m_argc;
  char **m_argv;

 public:
  CMPI() {};
  CMPI(int argc, char **argv);
  void initialize_CMPI(int argc, char **argv);
  ~CMPI();
  
  //Send and receive an array from the master node
  void send_array_master(double* master_send_array, int processor, int length);
  void send_array_master_all(double* master_send_array, int length);
  double* receive_array_master(int processor, int& master_length);
  
  //void receive_array_master_all(double** results, int length);
  double** receive_array_master_all(int& length);
  //Send and receive an array from a slave node
  void send_array_slave(double* slave_send_array, int length);
  //void receive_array_slave(double* slave_receive_array, int slave_length);
  double* receive_array_slave(int& slave_length);

  int size, rank;

 protected:
  
  
  MPI_Request* Req_receive;
  int argc; 
  char **argv;
  
  //MPI_Status* Stat_receive;
 
};
