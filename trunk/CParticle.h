#include "CVector.h"
#include "Constants.h"


class CParticle{
 public:

	CParticle();
	
	//Create a particle from an array on the following form:
	//[HaloID,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
	CParticle(double* inArray);

	~CParticle();


	//Gives the next and previous particle in a linked list
	CParticle* next,*prev;
	//Removes the particle from a linked list
	void RemoveFromList();


	//Set the different values a particle has
	void setHalo(int element);
	void setMass(double in_M);
	void setCharge(double in_C);
	void setPosition(double Px, double Py, double Pz);
	void setVelocity(double Vx, double Vy, double Vz);
	void setAcceleration(double Ax, double Ay, double Az);

	//Set all data, given by a vector
	void setData(vector<double> data);

	void setP(CVector inP);
	void setV(CVector inV);


	//Get the different values a particle has
	int getID();
	int getHalo();
	double getMass();
	CVector& getP();
	CVector& getV();
	CVector& getA();
	int getParticleSize();


	//Get/set flag value.y
	//Used in FoF methods to tell if this particle has been tested yet or not
	void setFlag(int inFlag);
	int getFlag();


	//Convert a particle to an array on the form:
	//[HaloID,Mass,Charge,Px,Py,Pz,Vx,Vy,Vz,Ax,Ay,Az]
	double* Particle2Array();

	//Calculate the kinetic energy of a particle
	double Ekin();
	//Calculate the momentumof a particle
	CVector Momentum();
	//Move the particle one timestep
	void Move(double dt);
	//CalculatePhaseSpaceDistance between 2 particles
	double PhaseSpaceDistance(CParticle* p2, double inSigmaP, double inSigmaV);

	

	//Print out all the information contained in one particle
	void print();



	//Test if a particle has been assigned a halo
	int gotHalo();
	//Decreases the HaloID by one. Used by my inefficient FoF code
	void decreaseHalo();


	//put this private, and get the code to work in some way.
	CVector P,V,A;

 protected:
	static int ID_Generator;
	
	int ID, HaloID,ParticleSize,flag;
	double Mass, Charge;

	void Generate_ID();
};
