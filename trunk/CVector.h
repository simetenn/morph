#include <vector>
using namespace std;

class CVector{
 public:

  CVector();
  CVector(double in_x, double in_y, double in_z);
  CVector(vector<double> in_Vector);
  CVector(const CVector& in_Vector);

  ~CVector();

  void print();
  double& operator[](int element);
  CVector operator+(const CVector& other) const;
  //CVector operator+(int number);
  CVector Add(double number) const;
  
  CVector operator-(const CVector& other) const;
  CVector Subtract(double number) const;
  
  CVector operator/(double number) const;
  CVector operator*(double number) const;
  
  int getDimensions();
  
  double Length2() const;
  double Length() const;
  
  CVector Normalize() const;

  CVector Cross(const CVector& other) const;
  double Dot(const CVector& other) const;
  
  double Sum() const;
  
  void Set(double x,double y,double z);

  double x();
  double y();
  double z();
    
  double Quadrant();

 protected:
  //double x,y,z;
  vector<double> Vector;
  //double* Vector;
  int Dimensions; 

};
