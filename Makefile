VPATH	= .

# target might be WINDOWS, OS_X or LINUX

TARGET = LINUX #OS_X
# Home directory of the acw program
#HOME = /home/simen/Master/mybody-mpi/source

SOURCEDIR = .#/home/simen/Master/mybody-mpi/source

INCLUDES =-I/sw/include  -I$(SOURCEDIR)  
# library dir


# compiler specific flags
CFLAGS =  -O3 -D$(TARGET) 

FFLAGS =  $(LIBINCLUDE)  


PROJECT = main

_obj 	=  main.o CMain.o CArray.o CMPI.o CVector.o CParticle.o CParticles.o CHalo.o CHalos.o CUtil.o CGrid.o 

obj = $(patsubst %,$(SOURCEDIR)/%,$(_obj))

CC = mpic++ 

default: $(PROJECT)

$(PROJECT):  $(obj) 
	$(CC)  -L$(LIBDIR)  $(INCLUDES) -o $(PROJECT) $(obj) $(FFLAGS)  

%.o: %.cpp
	$(CC) -c -o $@ $^ $(INCLUDES) $(CFLAGS)   

clean:	
	rm *.o  main	


