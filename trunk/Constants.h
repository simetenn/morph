#pragma once

#include "CIniFile.h"


class Constants {
 public:

	int ParticleSize, HaloLimit;
	double b,PhaseDistance,f;
	string inFile, outFile;
	
	Constants() {
		CIniFile IniFile;
		IniFile.load("mybody.ini");

		ParticleSize = IniFile.getdouble("ParticleSize");
		b = IniFile.getdouble("b");
		HaloLimit = IniFile.getdouble("HaloLimit");
		inFile = IniFile.getstring("inFile");
		outFile = IniFile.getstring("outFile");
		PhaseDistance = IniFile.getdouble("PhaseDistance");
		f = IniFile.getdouble("f");
	}
};


class myConstants {
 public:
	static Constants constants;
};
