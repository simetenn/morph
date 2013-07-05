#pragma once

#include "CIniFile.h"



class Constants {
 public:

	int ParticleSize, HaloLimit,Width,NrLinking;
	int HaloSize,NrParticles2File, MaxHalos, NrParticlesDouble, minUnbind;
	int LinkingLenghtScale, ArrayExtraSize, NrShells, minParticlesShell;
	double b,PhaseDistance,f,LinkingLength,rhovir, HaloSeed, BoxSize;
	double ScaleDensity, RhoC, OmegaD, Mass, G;
	double convMass, convDistance, convVelocity, convAcceleration;
	string inFile, outFile,haloFile, DataFile;
	string source, inData, outData, outSize,outPosition,outPhi, outBounding;
	
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
		NrParticlesDouble  = IniFile.getdouble("NrParticlesDouble");
		LinkingLenghtScale = IniFile.getdouble("LinkingLenghtScale");
		ArrayExtraSize = IniFile.getdouble("ArrayExtraSize");
		minUnbind = IniFile.getdouble("minUnbind");
		
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
		convMass = IniFile.getdouble("convMass");
		convDistance = IniFile.getdouble("convDistance");
		convVelocity = IniFile.getdouble("convVelocity");
		convAcceleration = IniFile.getdouble("convAcceleration");
		NrShells = IniFile.getdouble("NrShells");
		minParticlesShell= IniFile.getdouble("minParticlesShell");

		//Load strings
		inFile = IniFile.getstring("inFile");
		outFile = IniFile.getstring("outFile");
		haloFile = IniFile.getstring("haloFile");
		DataFile = IniFile.getstring("DataFile");
		source = IniFile.getstring("source");
		inData = IniFile.getstring("inData");
		outData = IniFile.getstring("outData");
		outSize = IniFile.getstring("outSize");
		outPosition = IniFile.getstring("outPosition");
		outPhi = IniFile.getstring("outPhi");
		outBounding = IniFile.getstring("outBounding");
		//outBounding = IniFile.getstring("outBonding");
	}
};


class myConstants {
 public:
	static Constants constants;
};
