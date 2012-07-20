#include "CVector.h"



class CParticle : public CVector {
 public:
  
  CParticle();
  ~CParticle();
 
    
  void Set_Position(double Px, double Py, double Pz);
  void Set_Velocity(double Vx, double Vy, double Vz);
  void Set_Acceleration(double Ax, double Ay, double Az);
  void Set_Mass(double in_M);
  void Set_Charge(int in_C);
  void Set_data(vector<double> data);

  int Get_ID();
  double Get_Mass();//experimental, add for all values or remove this
  
  double Ekin();
  CVector Momentum();
  void Move(double dt);
  
  
  void print_Particle();
  

  protected:
  
  CVector P,V,A;
  double Mass;
  int Charge,ID;
  
  static int ID_Generator;

  void Generate_ID();
    


};
