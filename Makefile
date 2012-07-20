CC = mpic++
#CC = g++
CFlags = -g -Wall
SOURCES = main.cpp CArray.cpp CMPI.cpp CVector.cpp CParticle.cpp CParticles.cpp #CArray.h
EXECUTABLE = main
VPATH = .

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