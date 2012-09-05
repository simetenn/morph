#include "CVector.h"



class CParticle : public CVector {
 public:
  
  CParticle();
  CParticle(double* in_array);
  ~CParticle();
  
    
  void Set_Position(double Px, double Py, double Pz);
  void Set_Velocity(double Vx, double Vy, double Vz);
  void Set_Acceleration(double Ax, double Ay, double Az);
  void Set_Mass(double in_M);
  void Set_Charge(double in_C);
  void Set_Data(vector<double> data);

  double* Particle2Array();

  int get_ID();
  double get_Mass();
  CVector& get_P();
  CVector& get_V();
  CVector& get_A();
 

  double Ekin();
  CVector Momentum();
  void Move(double dt);
  
  
  void print_Particle();
  

  CVector P,V,A;
  
  protected:
  
  
  double Mass, Charge;
  int ID;
  
  static int ID_Generator,ParticleSize;

  void Generate_ID();
    


};
