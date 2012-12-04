#pragma once

#include "CIniFile.h"


class Constants {
 public:

	int ParticleSize, HaloLimit,Width,NrLinking, HaloSize,NrParticles2File;
	double b,PhaseDistance,f,LinkingLength,rhovir;
	string inFile, outFile,haloFile, DataFile;
	
	Constants() {
		CIniFile IniFile;
		IniFile.load("mybody.ini");

		ParticleSize = IniFile.getdouble("ParticleSize");
		b = IniFile.getdouble("b");
		HaloLimit = IniFile.getdouble("HaloLimit");
		Width = IniFile.getdouble("Width");
		inFile = IniFile.getstring("inFile");
		outFile = IniFile.getstring("outFile");
		haloFile = IniFile.getstring("haloFile");
		PhaseDistance = IniFile.getdouble("PhaseDistance");
		f = IniFile.getdouble("f");
		LinkingLength = IniFile.getdouble("LinkingLength");
		NrLinking = IniFile.getdouble("NrLinking");
		rhovir = IniFile.getdouble("rhovir");
		HaloSize = IniFile.getdouble("HaloSize");
		NrParticles2File = IniFile.getdouble("NrParticles2File");
		DataFile = IniFile.getstring("DataFile");
	}
};


class myConstants {
 public:
	static Constants constants;
};
