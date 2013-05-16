
##############################################################################
##                                                                          ##
##  COPYRIGHT (C) 2013 -- Eivind Storm Aarnæs (eistaa)                      ##
##                     -- eiv.s.aa@eistaa.com                               ##
##                                                                          ##
##    This program is free software: you can redistribute it and/or modify  ##
##    it under the terms of the GNU General Public License as published by  ##
##    the Free Software Foundation, either version 3 of the License, or     ##
##    (at your option) any later version.                                   ##
##                                                                          ##
##    This program is distributed in the hope that it will be useful,       ##
##    but WITHOUT ANY WARRANTY; without even the implied warranty of        ##
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ##
##    GNU General Public License for more details.                          ##
##                                                                          ##
##############################################################################


# shell used by make
SHELL = /bin/sh
# prerequisites path (: separated list)
VPATH = .


# -----------------------------------------------------------
#                       START OF CONFIG
# -----------------------------------------------------------


PROJECT    = MORPH

TARGET = LINUX #OS_X
# Home directory of the acw program
#HOME = /home/simen/Master/mybody-mpi/source

SOURCEDIR  = ./source
BUILDDIR   = ./build
#/home/simen/Master/mybody-mpi/source

# location to look for header files
INCLUDES   = -I$(SOURCEDIR)
INCLUDES  += -I/sw/include
INCLUDES  +=

# libraries to link with
LIBS       =
LIBS      +=

# compiler
CC         = mpic++

# compiler specific flags
CFLAGS     = -Wall -O0 -g -D$(TARGET)
# linker flags
LDFLAGS    = -Wall

# object files to compile
OBJS       = main.o CMain.o CArray.o CMPI.o CVector.o CParticle.o \
			 CParticles.o CHalo.o CHalos.o CUtil.o CGrid.o

# source extension (c / cpp / cxx / ...)
SOURCEEXT = cpp


# -----------------------------------------------------------
#                        END OF CONFIG
# -----------------------------------------------------------


##  SETUP  ##
 ## ----- ##

# compiled object files
COMPOBJS = $(patsubst %,$(BUILDDIR)/%,$(OBJS))
# source files from object files
SRCS = $(patsubst %.o,$(SOURCEDIR)/%.$(SOURCEEXT),$(OBJS))

##  TARGETS  ##
 ## ------- ##

# executed on 'make' or 'make all'
.PHONY: all
all: $(BUILDDIR)/$(PROJECT)

# make $(BUILDDIR) only if it does not exist
$(BUILDDIR)/$(PROJECT): $(COMPOBJS)
	$(CC) -o $(PROJECT) $(COMPOBJS) $(LDFLAGS) $(LIBS)

# make any file stem.o from $(SOURCEDIR)/stem.$(SOURCEEXT)
# $@ -- name of current target, (left of : , %.o)
# $^ -- name of prerequisites, (right of : , %.$(SOURCEEXT))
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.$(SOURCEEXT) | $(BUILDDIR)
	$(CC) $(INCLUDES) $(LIBS) -c $(CFLAGS) -o $@ $^

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o $(PROJECT)

.PHONY: distclean
distclean:
	rm -rf $(BUILDDIR)

