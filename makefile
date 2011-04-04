# Configurações dos usuários do makefile. Cada usuário tem um arquivo para trabalhar
# Para correta utilização coloque esses caminhos em um arquivo chamado makefile.conf
#PANDAPATH = /home/heekinho/panda3d-1.6.1
#SIMDUNASPATH = /home/heekinho/workspace/calangos/src
#PYTHONPATH = /usr/include/python2.6

include makefile.conf


.SUFFIXES: .c .cpp .cxx .cc .h .hh


# Compiler Names:
C++		= 	g++
CC		= 	gcc
RANLIB  	= 	ranlib


# Flags for C++ compiler:
CFLAGS			= 	-g -Wno-deprecated -fPIC -O2

CXXFLAGS 		= 	-g -Wno-deprecated -Wno-write-strings -fPIC -O2

INCFLAGS 		= 	-I$(PYTHONPATH) -I$(PANDAPATH)/built/include \
				-I$(PANDAPATH)/thirdparty/linux-libs-a/nspr/include \
				-I/usr/include/panda3d \
				-I/usr/local/panda3d/include \

# Libraries to link with:
MATLIB			= 	-lm
GLLIBS			= 	-lGL -lGLU
GLUTLIB			= 	-lglut
GLUILIB			= 	-lglui
OMLIBS			=	-lOM_CORE -lOM_TOOLS	

LIBPANDA		= 	-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub  #-lpandanspr4

LIBPATH 		= 	-L/usr/lib/panda3d -L$(PANDAPATH)/built/lib \
				-L$(PANDAPATH)/thirdparty/linux-libs-a/nspr/lib \
				-L/usr/local/panda3d/lib
				#-L/usr/X11R6/lib/X11 \

LDFLAGS 		= 	$(LIBPANDA)


# Simdunas main program build rules
SUBDIRS = src src/animals src/animals/predators src/animals/prey src/animals/lizards \
		  src/cameras src/gui src/gui/screen src/gui/screen/menu src/gui/screen/inGame src/base \
		  src/gui/hint src/gui/widgets src/vegetation src/weather src/world src/player src/gui/editor \

INCFLAGS += $(patsubst %,-I%,$(SUBDIRS))

SRC := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cxx))
HEADERFILES := $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))

OBJECTFILES := $(patsubst src/%.cxx,src/%.o$,$(SRC))


# Targets
all:	simdunas

simdunas:	$(HEADERFILES) $(OBJECTFILES)
		@echo "Linking ...."
		$(CXX) $(CPPFLAGS) $(LIBPATH) $(OBJECTFILES) $(LDFLAGS) -o simdunas
		
.cxx.o: $*.h
	@echo "Compiling C++ code ...."
	$(C++) -o $*.o -c $(CXXFLAGS) $(INCFLAGS) $*.cxx
	
clean:
	rm simdunas $(OBJECTFILES)
