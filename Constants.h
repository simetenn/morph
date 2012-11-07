#pragma once

#include "CIniFile.h"


class Constants {
 public:

	int ParticleSize, HaloLimit,Width;
	double b,PhaseDistance,f,LinkingLength;
	string inFile, outFile,haloFile;
	
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
		
	}
};


class myConstants {
 public:
	static Constants constants;
};
