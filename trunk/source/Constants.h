#pragma once

#include "CIniFile.h"



class Constants {
 public:

	int ParticleSize, HaloLimit,Width,NrLinking;
	int HaloSize,NrParticles2File, MaxHalos;
	double b,PhaseDistance,f,LinkingLength,rhovir, HaloSeed, BoxSize;
	double ScaleDensity, RhoC, OmegaD, Mass, G;
	string inFile, outFile,haloFile, DataFile;
	string source, data,outSize,outPosition,outPhi;
	
	Constants() {
		//Load ini-file
		CIniFile IniFile;

		#ifndef UIO
		IniFile.load("mybody.ini");
		#endif
		
		#ifdef UIO
		IniFile.load("mybodyUiO.ini");
		#endif
		
		//Load ints
		ParticleSize = IniFile.getdouble("ParticleSize");
		HaloLimit = IniFile.getdouble("HaloLimit");
		HaloSeed = IniFile.getdouble("HaloSeed");
		Width = IniFile.getdouble("Width");
		NrLinking = IniFile.getdouble("NrLinking");
		HaloSize = IniFile.getdouble("HaloSize");
		NrParticles2File = IniFile.getdouble("NrParticles2File");
		MaxHalos = IniFile.getdouble("MaxHalos");
		
		//Load doubles
		b = IniFile.getdouble("b");
		PhaseDistance = IniFile.getdouble("PhaseDistance");
		f = IniFile.getdouble("f");
		LinkingLength = IniFile.getdouble("LinkingLength");
		rhovir = IniFile.getdouble("rhovir");
		BoxSize = IniFile.getdouble("BoxSize");
		ScaleDensity = IniFile.getdouble("ScaleDensity");
		RhoC = IniFile.getdouble("RhoC");
		OmegaD = IniFile.getdouble("OmegaD");
		Mass = IniFile.getdouble("Mass");
		G = IniFile.getdouble("G");
		
		//Load strings
		inFile = IniFile.getstring("inFile");
		outFile = IniFile.getstring("outFile");
		haloFile = IniFile.getstring("haloFile");
		DataFile = IniFile.getstring("DataFile");
		source = IniFile.getstring("source");
		data = IniFile.getstring("data");
		outSize = IniFile.getstring("outSize");
		outPosition = IniFile.getstring("outPosition");
		outPhi = IniFile.getstring("outPhi");
	}
};


class myConstants {
 public:
	static Constants constants;
};
