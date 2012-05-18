PANDAPATHINCLUDE = /usr/include/panda3d
PANDAPATHLIB = /usr/lib/panda3d
PYTHONPATH = /usr/include/python2.6

.SUFFIXES: .c .cpp .cxx .cc .h .hh

# Compiler Names:
C++		= 	g++
CC		= 	gcc
RANLIB  	= 	ranlib


# Flags for C++ compiler:
CFLAGS			= 	-g -Wno-deprecated -fPIC -O2

CXXFLAGS 		= 	-g -Wno-deprecated -Wno-write-strings -fPIC -O2

INCFLAGS 		= 	-I$(PYTHONPATH) \
					-I$(PANDAPATHINCLUDE)

# Libraries to link with:
MATLIB			= 	-lm
GLLIBS			= 	-lGL -lGLU
GLUTLIB			= 	-lglut
GLUILIB			= 	-lglui
OMLIBS			=	-lOM_CORE -lOM_TOOLS	

LIBPANDA		= 	-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct  #-lpandanspr4

LIBPATH 		= 	-L$(PANDAPATHLIB)

LDFLAGS 		= 	$(LIBPANDA)

# Simdunas main program build rules
SUBDIRS = src src/animals src/animals/predators src/animals/prey src/animals/lizards \
		  src/cameras src/gui src/gui/screen src/gui/screen/menu src/gui/screen/inGame src/base \
		  src/gui/hint src/gui/widgets src/vegetation src/weather src/world src/player \
		  src/player/health src/gui/editor src/gui/screen/inGame/window

INCFLAGS += $(patsubst %,-I%,$(SUBDIRS))
SRC := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cxx))
HEADERFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))
OBJECTFILES := $(patsubst src/%.cxx,src/%.o$,$(SRC))


# Targets
all: simdunas

simdunas:	$(HEADERFILES)	$(OBJECTFILES)
		@echo "Linking ...."
		$(CXX) $(CPPFLAGS) $(LIBPATH) $(OBJECTFILES) $(LDFLAGS) -o simdunas
	
.cxx.o: $*.h
	@echo "Compiling: " $*
	@($(C++) -o $*.o -c $(CXXFLAGS) $(INCFLAGS) $*.cxx)

clean:
	rm -f simdunas $(OBJECTFILES)
