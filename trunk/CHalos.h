//#include <iostream>
#include "CHalo.h"
//#include "CArray.h"



class CHalos : public CHalo{

 public:
	CHalos();
	~CHalos();
	
	void HaloSort();
	void print_Halos();
	void initialize_Halos();

	
	CArray* Halos2Array();
	CArray* Array2Halos(CArray* inArray);

	void addHalos(CArray* inArray);
	
 protected:
	int nrHalos;
	vector<int> nrinHalo;
	vector<CHalo*> Halos;


};
