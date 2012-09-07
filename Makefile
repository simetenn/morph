#include "../mybody/mybody/source/CHalo.h"
#include "../mybody/mybody/source/CHaloFinder.h"


CC = mpic++
#CC = g++
VPATH = .:/~/Master/mybody/mybody/source

CFlags = -g -Wall
SOURCES = main.cpp CArray.cpp CMPI.cpp CVector.cpp CParticle.cpp CParticles.cpp #CHaloFinder.cpp CHalo.cpp #CArray.h
EXECUTABLE = main
SOURCEDIR = ~/Master/mybody/mybody
#OSOURCES = CHalo.cpp CHaloFinder.cpp CHaloList.cpp
#vpath %.cpp ~/Master/mybody/mybody/sources
#INCLUDES =-I/sw/include  -I$(SOURCEDIR)  -I$(FITSDIR) -I$(HOME)

#. PHONY : all
#. PHONY : clean

all:
	$(CC) -o $(EXECUTABLE) $(CFLAGS) $(SOURCES)

main:
	$(CC) -o $(EXECUTABLE) $(CFLAGS) main.cpp

CArray.o:
	$(CC) -c $(CFLAGS) CArray.cpp

CMPI.o:
	$(CC) -c $(CFLAGS) CMPI.cpp

CVector.o:
	$(CC) -c $(CFLAGS) CVector.cpp

CParticle.o:
	$(CC) -c $(CFLAGS) CParticle.cpp


clean:
	rm -f *.o $(EXECUTABLE)
