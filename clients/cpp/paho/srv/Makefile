ifndef TOOLCHAINDIR
	TOOLCHAINDIR=
endif
ifndef COMPILERPREFIX
	COMPILERPREFIX=
endif
ifndef COMPILERPOSTFIX
	COMPILERPOSTFIX=
endif
ifdef $(word 1, COMPILERPREFIX)
	SEP0=-
else
	SEP0=
endif
ifdef $(word 1, COMPILERPOSTFIX)
	SEP1=-
else
	SEP1=
endif
#removed os arch detection as it fails in msys2
CXX=$(TOOLCHAINDIR)$(COMPILERPREFIX)$(SEP0)g++$(SEP1)$(COMPILERPOSTFIX)
CC=$(TOOLCHAINDIR)$(COMPILERPREFIX)$(SEP0)gcc$(SEP1)$(COMPILERPOSTFIX)
AR=$(TOOLCHAINDIR)$(COMPILERPREFIX)$(SEP0)ar$(SEP1)$(COMPILERPOSTFIX)
LD=$(TOOLCHAINDIR)$(COMPILERPREFIX)$(SEP0)ld$(SEP1)$(COMPILERPOSTFIX)
STRIP=$(TOOLCHAINDIR)$(COMPILERPREFIX)$(SEP0)strip
MKDIR=/bin/mkdir
RM=/bin/rmdir
ECHO=/bin/echo
CP=/bin/cp
RM=/bin/rm
FIND=/bin/find
CPPCHECK=/usr/bin/cppcheck
GCCVERSION=$(shell $(CC) -dumpversion)
ifdef $(word 1, GCCVERSION)
	SEP2=-
else
	SEP2=
endif
#SRC+=./src/a.cpp
#SRC+=./src/config/config.cpp
SRCDIR=src
SRC:=$(shell find $(SRCDIR) -name '*.c' -o -name '*.cpp')
OBJROOT=./obj
OBJDIR=$(OBJROOT)/$(COMPILERPREFIX)$(SEP1)$(COMPILERPOSTFIX)/
OBJS=$(addprefix $(OBJDIR),$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SRC))))
MAKEFILEPATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
CURRENTDIRNAM:=$(notdir $(patsubst %/,%,$(dir $(MAKEFILEPATH))))
ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	BINNAM=a
else
	BINNAM=$(CURRENTDIRNAM)
endif
RUNSCRIPT=$(BINDIR)run$(SCREXT)
BUILDROOT=build
BINDIR=$(BUILDROOT)/$(COMPILERPREFIX)$(SEP1)$(COMPILERPOSTFIX)/
BIN=$(BINDIR)$(BINNAM)$(BINEXT)
#$(BINDIR)/$(BINNAM)$(SEP0)$(BINCOMPILERPREFIX)$(SEP1)$(BINCOMPILERPOSTFIX)$(SEP2)$(GCCVERSION)$(BINEXT)
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	BINEXT=.exe
	SCREXT=.bat
else ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	BINEXT=.exe
	SCREXT=.bat
else ifneq (,$(findstring linux,$(COMPILERPREFIX)))
	BINEXT=.out
	SCREXT=.sh
else
	BINEXT=.out
	SCREXT=.sh
endif
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	DSOEXT=.dll
else ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	DSOEXT=.dxe
else ifneq (,$(findstring linux,$(COMPILERPREFIX)))
	DSOEXT=.so
else
	DSOEXT=.so
endif
LIBDIR=./build/$(COMPILERPREFIX)$(SEP1)$(COMPILERPOSTFIX)/
LIBCOMPILERPREFIX=lib
LIBDIR=./build/$(COMPILERPREFIX)$(SEP1)$(COMPILERPOSTFIX)/lib
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	UPX=upx
else ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	UPX=upx
else ifneq (,$(findstring linux,$(COMPILERPREFIX)))
	UPX=echo skipping upx
else
	UPX=echo skipping upx
endif
CFLAGS+=-Wall
CFLAGS+=-O2
CFLAGS+=-I./src
CFLAGS+=-g
CFLAGS+=-MMD
CFLAGS+=-Wno-array-bounds
CFLAGS+=-Wno-format-truncation
CFLAGS+=-D_GNU_SOURCE
CFLAGS+=-DCONFIG_VERSION=\"2020-11-08\"
CFLAGS+=-DHAVE_STRUCT_TIMEVAL
CFLAGS+=-DENABLE_TCC
CFLAGS+=-DCS_P_UNIX
#dealing with leading underscores in embedded resources
ifneq (,$(findstring x86_64-w64-mingw32,$(TGT_MACHINE)))
	CFLAGS+=-DLEADING_UNDERSCORES
else
endif
CXXFLAGS+=-Wall
#CXXFLAGS+=-O2
CXXFLAGS+=-O3
CXXFLAGS+=-I./src
CXXFLAGS+=-I./src/quickjspp
CXXFLAGS+=-I./src/crow
CXXFLAGS+=-std=c++17
CXXFLAGS+=-fpermissive
CXXFLAGS+=-DCROW_ENABLE_LOGGING
CXXFLAGS+=-DCROW_STATIC_DIRECTORY=\"./public/\"
CXXFLAGS+=-DCROW_STATIC_ENDPOINT=\"/public/\<path\>\"
ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	#8.3 workarounds
	CXXFLAGS+=-DLIBCOMPILERPOSTFIX=\"\"
	#note _ prefix
	CXXFLAGS+=-DENTRYPOINT=\"_appmain\"
else
	CXXFLAGS+=-DLIBCOMPILERPOSTFIX=\"$(SEP0)$(BINCOMPILERPREFIX)$(SEP1)$(BINCOMPILERPOSTFIX)$(SEP2)$(GCCVERSION)\"
	CXXFLAGS+=-DENTRYPOINT=\"appmain\"
endif
CXXFLAGS+=-DDSOEXT=\"$(DSOEXT)\"
CXXFLAGS+=-DGCCVERSION=\"$(GCCVERSION)\"
#LDFLAGS+=-L$(LIBDIR)
LDFLAGS+=-lpaho-mqtt3a
#LDFLAGS+=-lpaho-mqtt3c
LDFLAGS+=-lpaho-mqttpp3
LDFLAGS+=-lpthread
LDFLAGS+=-lboost_system
LDFLAGS+=-lz
LDFLAGS+=-ldl
# --------------------------------------------------------------------------------
ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
	#import libs
	LIBNAMS=$(shell (ls $(LIBDIR)|grep libi|cut -f1 -d".")|cut -c4-)
else
	#libs
	LIBNAMS=$(shell (ls $(LIBDIR)|cut -f1 -d".")|cut -c4-)
endif
LIBFLAGS=$(addprefix -l,$(LIBNAMS))
# --------------------------------------------------------------------------------
ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
else ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
else
	LDFLAGS+=-Wl,-rpath=./lib
	LDFLAGS+=-Wl,-rpath=$(LIBDIR)
endif
# --------------------------------------------------------------------------------
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	LDFLAGS+=-static
endif
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	# wrap dso dynspec: start
	ifneq (,$(findstring win32,$(COMPILERPOSTFIX)))
		LDFLAGS+=-Wl,-Bdynamic
	else
		LDFLAGS+=-Wl,-Bdynamic
	endif
endif
LDFLAGS+=$(LIBFLAGS)
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
	# wrap dso dynspec: end
	ifneq (,$(findstring win32,$(COMPILERPOSTFIX)))
		LDFLAGS+=-Wl,-Bstatic
	else
		LDFLAGS+=-Wl,-Bstatic
	endif
endif
# --------------------------------------------------------------------------------
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif
all:$(RUNSCRIPT)
$(BIN):$(OBJS)
	@echo "generating $@..."
	@-$(MKDIR) -p $(@D)
	$(CXX) \
		$(OBJS) \
		$(LDFLAGS) \
		-o $(BIN) 
$(OBJDIR)%.o: %.c
	@echo "generating $@..."
	@-$(MKDIR) -p $(@D)
	@$(CC)\
		$(CFLAGS)\
		-c $<\
		-o $@
$(OBJDIR)%.o: %.cpp
	@echo "generating $@..."
	@-$(MKDIR) -p $(@D)
	@$(CXX)\
		$(CXXFLAGS)\
		-c $<\
		-o $@
strip:$(BIN)
	@echo "stripping $(BIN)..."
	@-$(STRIP) $(BIN) --strip-unneeded
compress:strip
	@echo "compressing $(BIN)..."
	@-$(UPX) $(BIN)
ifneq (,$(findstring mingw,$(COMPILERPREFIX)))
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "@echo off" > $(RUNSCRIPT)
	@echo "setlocal" >> $(RUNSCRIPT)
	@echo "set PATH=.\lib;%PATH%" >> $(RUNSCRIPT)
	@echo ".\\\$(BINNAM)$(BINEXT)" >> $(RUNSCRIPT)
else ifneq (,$(findstring djgpp,$(COMPILERPREFIX)))
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "@echo off" > $(RUNSCRIPT)
	@echo "set PATH=.\lib;%PATH%" >> $(RUNSCRIPT)
	@echo "set LD_LIBRARY_PATH=.\lib" >> $(RUNSCRIPT)
	@echo ".\\\$(BINNAM)$(BINEXT)" >> $(RUNSCRIPT)
else ifneq (,$(findstring linux,$(COMPILERPREFIX)))
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "#!/bin/bash" > $(RUNSCRIPT)
	@echo "./a.out" >> $(RUNSCRIPT)
else
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "#!/bin/bash"
	@echo "./a.out"
endif
run:$(BIN)
	@echo "running $(BIN)..."
	@$(BIN) ./js/init.js $(RUN_ARGS)
.phony:clean sta
clean:
	@echo "cleaning ..."
	@echo "removing $(BIN)..."
	@-rm $(BIN)
	@echo "removing $(OBJDIR)..."
	@-rm -rf $(OBJDIR)
cleanall:
	@echo "removing $(BUILDROOT)..."
	@-$(RM) -rf $(BUILDROOT)
	@echo "removing $(OBJROOT)..."
	@-$(RM) -rf $(OBJROOT)
sta:
	@$(ECHO) "performing static analysis on $(SRC)..."
	@$(CPPCHECK) --enable=all $(SRC)
test:
	@echo $(LIBNAMS)
	@echo $(LIBFLAGS)
	@echo $(BINDIR)
	@echo $(OBJROOT)
	@echo $(RUNSCRIPT)
	@echo $(CXXFLAGS)
