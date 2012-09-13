#include "CHalos.h"

using namespace std;


CHalos::CHalos(){
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
}

CHalos::CHalos(CArray* inArray){
	nrHalos = inArray->get(0);
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	int particle_count = 1+nrHalos;
	nrParticles = (inArray->len()-1-nrHalos)/ParticleSize;

	for (int i = 0; i < nrHalos; i++){
		nrinHalo.push_back(inArray->get(1+i));

		double tmpArray[nrinHalo[i]];
		for (int j = 0; j < nrinHalo[i];j++){
			tmpArray[j] = inArray->get(particle_count);
			particle_count++;
		}
		int tmpInt = nrinHalo[i];
		CArray* tmpCArray = new CArray(tmpInt, tmpArray);
		CHalo* tmpHalo = new CHalo(tmpCArray); // <- Memory leak
		Halos.push_back(tmpHalo);
	}
}


CHalos::~CHalos(){

}


//Initialize the halos in my own fake datasett
void CHalos::initialize_Halos(){
	nrHalos = 8;
	Halos.resize(nrHalos);
	CParticle tmpParticle;
	ParticleSize = tmpParticle.getParticleSize();
	/*for (int i = 0; i < nrParticles;i++){
	//Halos.push_back(Particles[i]);
	Halos[(Halo[i]->get_P()).Quadrant()].push_back(Halo[i]);
	}

	for (int i = 0; i < nrHalos;i++){
	nrinHalo.push_back(Halos[i]->size());
	}*/
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


void CHalos::addHalo(CHalo* inHalo){
	Halos.push_back(inHalo);
}






//Add a halo to the existing ones
void CHalos::addHalosArray(CArray* inArray){
	/*int oldnrHalos = nrHalos;

	  int newnrHalos = inArray->get(0);
	  nrHalos += newnrHalos;

	  int newnrParticles = (inArray->len()-1-nrHalos)/ParticleSize;
	  int oldnrParticles = nrParticles;
	  nrParticles += newnrParticles;

	  int particle_count = 0;
	  //vector<CParticle* > tmpParticles;
	  vector<double> tmpArray (ParticleSize);

	  //Halos.resize(nrHalos);
	  CHalo* tmpHalo;


	  for (int i = 0; i<newnrHalos;i++){
	  Halos.push_back(CHalo* tmpHalo (Particles));

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
	  }*/
}



CHalos* CHalos::Array2Halos(CArray* inArray){

}





//Convert from several halos to one array
CArray*	 CHalos::Halos2Array(){//pointer

	//rewrite this when time, but seems to work atm

	double* Array = new double [ParticleSize*nrParticles+nrHalos+1]; // Memory leak
	int particle_count = 1+nrHalos;
	double* tmpArray;
	Array[0] = nrHalos;

	for (int i = 0; i<nrHalos;i++){
		//cout << "Halo nr:" << i << endl;
		//cout << Halos[i].size() << endl;

		Array[i+1] = nrinHalo[i];
		for (int j=0;j<nrinHalo[i];j++){
			tmpArray = Halos[i]->get(j)->Particle2Array();
			for (int k = 0; k < ParticleSize;k++){
				Array[particle_count] = tmpArray[k];
				particle_count++;
			}
		}
	}

	return new CArray(ParticleSize*nrParticles+nrHalos+1,Array); //Memory leak
}



int CHalos::sizeHalos(){
	return nrHalos;
}








//Master process
void CHalos::master(){
	/*CMPI MPI;

	  int count = 0;
	  int processor;
	  int size = MPI.getSize();
	  CParticles finalHalos;

	  MPI_Request Req [size-1];
	  vector<CArray*> Array (size-1);

	  //Initialize, sending one halo to each processor
	  for (int p = 1;p<size;p++){
	  cout << "Initializing for processor nr: " << p << endl;
	  //Array.push_back(Halo2Array(Halos[count]));
	  Array[p-1] = Halo2Array(Halos[count]);
	  MPI.End(p,0);
	  Array[p-1]->send(p);
	  Array[p-1]->recieve(p, &Req[p-1]);
	  count++;
	  }

	  cout << "-------------------------------------------------" << endl;
	  cout << "Finished distributing halos to each processor" << endl;
	  cout << "-------------------------------------------------" << endl;
	  //Send halo to processor as soon as a processor finishes
	  while (count < nrHalos) {
	  cout << "Finished with halo nr: " << count +1 << endl;
	  processor = MPI.listener(Req);
	  finalHalos.addHalos(Array[processor-1]);
	  Array[processor-1] = Halo2Array(Halos[count]);
	  MPI.End(processor,0);
	  Array[processor-1]->send(processor);
	  Array[processor-1]->recieve(processor,&Req[processor-1]);
	  count++;

	  }

	  MPI.WaitAll(Req);

	  for (int p = 1;p < size;p++){
	  MPI.End(p,1);
	  }*/
}



//slave processor
void CHalos::slave(){

	/*CArray HalosArray;
	  CMPI MPI;
	  int flag;

	  while (true) {
	  if (MPI.ifEnd() == 1) break;
	  HalosArray.recieve_slave();
	  CParticles slaveParticles (&HalosArray);

	  //slaveParticles.print_Particles();
	  //slaveParticles.DoSomething();

	  slaveParticles.Halos2Array()->send_slave();
	  }*/
}
