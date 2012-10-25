#pragma once

#include "CIniFile.h"


class Constants {
 public:

	int ParticleSize, HaloLimit;
	double b,PhaseDistance;
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
	}
};


class myConstants {
 public:
	static Constants constants;
};
