//#include "CArray.h"
//#include "CVector.h"
#include "CParticles.h"
//#include <vector>
using namespace std;



int main(int argc, char **argv){
  CMPI MPI;
  MPI.initialize_CMPI(argc,argv);
  //Master node
  
  if (MPI.rank == 0) {
    CParticles a;
    a.get_Data ("particles.dat");
    //a.print_Particles();
    //a.initialize_Halos();
    //a.print_Halos();


  }

  
  else {

  }



  //CArray array;
  
  //array.linspace(0,9,10);
  //CArray array2(array.length,array.array);
  //array.print();
  //CArray array2;
  //array2.print();
  //cout << "sd " << endl;
  //array2 = array;
  //cout << "sd " << endl;
  //array2.print();
  //cout << "sd " << endl;
  
  //double sum = array.sum_MPI(argc, argv);
  //cout << sum << endl;

  //CVector b (2,1,2);
  //CVector c = a.Subtract(2);
  //c.print();
  //CVector d (1,1,1);
  //a.Cross(b).print();
  //cout << d.divide(4) << endl;
  //vector<double> Vector(3,0);
  //cout << Vector.size() << endl;  

  //CParticles a;
  //a.get_Data ("particles.dat");
  //a.print_Particles();
  //a.initialize_Halos();
  //a.print_Halos();
  /*a.Set_Position(1,1,1);
  a.Set_Velocity(1,1,1);
  a.Set_Acceleration(1,1,1);
  //a.Set_Mass(1);
  a.print_Particle();
  a.Move(1);
  a.print_Particle();*/
  



}
