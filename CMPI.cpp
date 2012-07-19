#include "CMPI.h"
#include <iostream>
using namespace std;

CMPI::CMPI(int argc, char **argv){
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Req_receive = new MPI_Request [size-1];
  //Stat_receive = new MPI_Status [size-1];
}

void CMPI::initialize_CMPI(int argc, char **argv){
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Req_receive = new MPI_Request [size-1];
  //Stat_receive = new MPI_Status [size-1];
}

CMPI::~CMPI(){
  MPI_Finalize();
  
  if (Req_receive != NULL){ 
    delete[] Req_receive;
  }
  
  /*if (results != NULL){
    for (int p=0; p < size; p++){
      delete[] results[p];
    }
    delete[] results;
    }*/
  //delete[] Stat_receive;
}
/*
void CMPI::CMPI(&argc, &argv){

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  }*/






void CMPI::send_array_master(double* master_send_array, int processor, int length){
  MPI_Request Req[2];
  //send the length
    MPI_Isend(&length,1,MPI_INT,processor,processor,MPI_COMM_WORLD, &Req[0]);
  //send the array
    MPI_Isend(master_send_array,length,MPI_DOUBLE,processor,processor+size,MPI_COMM_WORLD, &Req[1]);
}

//This is probably wrong, compare with receive_array_master_all
double* CMPI::receive_array_master(int processor, int& master_length){
  MPI_Status Stat;
  MPI_Recv(&master_length,1,MPI_INT,processor,processor+2*size,MPI_COMM_WORLD, &Stat);
  double* master_receive_array = new double [master_length]; 
  MPI_Irecv(master_receive_array,master_length,MPI_DOUBLE,processor,processor+3*size,MPI_COMM_WORLD, &Req_receive[processor-1]);
  
  return master_receive_array;
}


void CMPI::send_array_slave(double* slave_send_array, int length){
  MPI_Send(&length,1,MPI_INT,0,rank+2*size,MPI_COMM_WORLD);
  MPI_Send(slave_send_array,length,MPI_DOUBLE,0,rank+3*size,MPI_COMM_WORLD);
}


/*void CMPI::receive_array_slave(double* slave_receive_array, int slave_length){
  MPI_Status Stat;
  MPI_Recv(&slave_length,1,MPI_IN,Tda0,rank,MPI_COMM_WORLD,&Stat);
  
  //slave_receive_array = new double [slave_length]; //memory leak
  double tmp [slave_length]; //memory leak
  //cou t<< slave_receive_array <<endl;
  MPI_Recv(slave_receive_array,slave_length,MPI_DOUBLE,0,rank+size,MPI_COMM_WORLD,&Stat);
  //cout << tmp[1] <<endl;
  //slave_receive_array = tm;p
  cout << slave_receive_array[9] <<endl;
  }*/

double* CMPI::receive_array_slave(int& slave_length){
  MPI_Status Stat;
  MPI_Recv(&slave_length,1,MPI_INT,0,rank,MPI_COMM_WORLD,&Stat);
  double* slave_receive_array = new double [slave_length]; 
  MPI_Recv(slave_receive_array,slave_length,MPI_DOUBLE,0,rank+size,MPI_COMM_WORLD,&Stat);
    
  return slave_receive_array;
}


void CMPI::send_array_master_all(double* master_send_array, int length){
  //Add posibilities for all numbers of processors
  int average_array_length = length/(size-1);
  int reminder = length % (size-1);
  int sub_array_length = average_array_length;
  int array_start_index = 0;
  //cout << "new output" << endl;
  //cout << sub_array_length << endl;
  //cout << reminder << endl;
  for (int p=1; p < size; p++){
    if (p < reminder+1){
      sub_array_length = average_array_length+1;
    }
    else {
      sub_array_length = average_array_length;
    }
    
    CMPI::send_array_master(&master_send_array[array_start_index],p,sub_array_length);
    array_start_index += sub_array_length;
  }
    
}

/*void CMPI::receive_array_master_all(double** results, int length){
  
  MPI_Status Stat[size-1];
  MPI_Status Stat2;
  MPI_Request Req[size-1];
  results = new double* [size-1];
  for (int p=1; p < size; p++){
    //CMPI::receive_array_master(results[p],p,&length);
    MPI_Recv(&length,1,MPI_INT,p,p+2*size,MPI_COMM_WORLD, &Stat2);
    results[p-1] = new double [length];
    MPI_Irecv(results[p-1],length,MPI_DOUBLE,p,p+3*size,MPI_COMM_WORLD, &Req[p-1]);
  }
  MPI_Waitall(size-1,Req, Stat);
}*/


double** CMPI::receive_array_master_all(int& slave_length){
  
  MPI_Status Stat[size-1];
  MPI_Status Stat2;
  MPI_Request Req[size-1];
  double** result = new double*[size-1];
  
  for (int p=1; p < size; p++){
    //CMPI::receive_array_master(results[p],p,&length);
    MPI_Recv(&slave_length,1,MPI_INT,p,p+2*size,MPI_COMM_WORLD, &Stat2);
    result[p-1] = new double [slave_length];
    MPI_Irecv(result[p-1],slave_length,MPI_DOUBLE,p,p+3*size,MPI_COMM_WORLD, &Req[p-1]);
  }
  
  MPI_Waitall(size-1,Req, Stat);

  /*for (int i = 0;i<size-1;i++){
    cout << result[i][0] << endl;
    }*/
  
  return result;

}
