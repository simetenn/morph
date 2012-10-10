#pragma once

#include "CIniFile.h"


class Constants {
 public:

	int test;

	Constants() {

		CIniFile IniFile;
		
		IniFile.load("mybody.ini");
		test = IniFile.getdouble("test");
		
		// load inifile
	}


};


//Constants myConstants::constants;

class myConstants {
 public:
	static Constants constants;
};
