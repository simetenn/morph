#include "CHalos.h"

using namespace std;


CHalos::CHalos(){
}
CHalos::~CHalos(){
}



//Initialize the halos in my own fake datasett
void CHalos::initialize_Halos(){
	nrHalos = 8;
	Halos.resize(nrHalos);
	for (int i = 0; i < nrParticles;i++){
		//Halos.push_back(Particles[i]);
		(Halos[(Halo[i]->get_P())->Quadrant()]).push_back(Particles[i]);
	}

	for (int i = 0; i < nrHalos;i++){
		nrinHalo[i] = Halos.size();
	}
}








void CHalos::HaloSort(){

}

void CHalos::print_Halos(){
	for (int i = 0;i < nrHalos; i++){
		cout << "__________________________________" << endl;
		cout << "								   " << endl;
		cout << "Halo nr: " << i << endl;
		cout << "Nr of particles in halo: " << nrinHalo[i] << endl;
		cout << "__________________________________" << endl;
		//for (int j = 0;j < Halos[i].size();j++){
		//Halos[i][j]->print_Particle();
		//}
	}
}




//Add a halo to the existing ones
void CHalos::addHalos(CArray* inArray){
	int oldnrHalos = nrHalos;

	int newnrHalos = inArray->get(0);
	nrHalos += newnrHalos;

	int newnrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	int oldnrParticles = nrParticles;
	nrParticles += newnrParticles;

	int particle_count = 0;
	//vector<CParticle* > tmpParticles;
	vector<double> tmpArray (ParticleSize);

	//Halos.resize(nrHalos);
	CHalo tmpHalo ();
	Halos.push_back(tmpHalo);
	for (int i = 0; i<newnrHalos;i++){
		for (int j = 0;j < inArray->get(i+1);j++){
			for (int k = 0; k < ParticleSize;k++){
				tmpArray[k] = inArray->get(particle_count*ParticleSize+1+newnrHalos+k);
			}


			//takes up extra
			Particles.push_back(new CParticle); //Slow way to do this??
			Particles[particle_count+oldnrParticles]->Set_Data(tmpArray);
			Halos[i].push_back(Particles[oldnrParticles+particle_count]);
			//tmpParticles.push_back(new CParticle); //Slow way to do this??
			//tmpParticles[j]->Set_Data(tmpArray);
			particle_count++;
		}

		//Halos.push_back(tmpParticles);
		//tmpParticles.clear();
	}
}




//Convert from several halos to one array
CArray*	 CHalos::Halos2Array(){//pointer
	double* Array = new double [ParticleSize*nrParticles+nrHalos+1]; // Memory leak
	int HaloSize;
	int particle_count = 1+nrHalos;
	double* tmpArray;
	Array[0] = nrHalos;

	for (int i = 0; i<nrHalos;i++){
		//cout << "Halo nr:" << i << endl;
		//cout << Halos[i].size() << endl;

		HaloSize = Halos[i].size();
		Array[i+1] = HaloSize;
		for (int j=0;j<HaloSize;j++){
			tmpArray = Particles[j]->Particle2Array();
			for (int k = 0; k < ParticleSize;k++){
				Array[particle_count] = tmpArray[k];
				particle_count++;
			}
		}
	}

	return new CArray(ParticleSize*nrParticles+nrHalos+1,Array); //Memory leak
}



int CParticles::sizeHalos(){
	return nrHalos;
}
