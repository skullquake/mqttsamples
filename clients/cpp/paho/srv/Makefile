ifndef TOOLCHAINDIR
	TOOLCHAINDIR=
endif
ifndef PREFIX
	PREFIX=
endif
ifndef POSTFIX
	POSTFIX=
endif
ifdef $(word 1, PREFIX)
	SEP0=-
else
	SEP0=
endif
ifdef $(word 1, POSTFIX)
	SEP1=-
else
	SEP1=
endif
#removed os arch detection as it fails in msys2
CXX=$(TOOLCHAINDIR)$(PREFIX)$(SEP0)g++$(SEP1)$(POSTFIX)
CC=$(TOOLCHAINDIR)$(PREFIX)$(SEP0)gcc$(SEP1)$(POSTFIX)
AR=$(TOOLCHAINDIR)$(PREFIX)$(SEP0)ar$(SEP1)$(POSTFIX)
LD=$(TOOLCHAINDIR)$(PREFIX)$(SEP0)ld$(SEP1)$(POSTFIX)
STRIP=$(TOOLCHAINDIR)$(PREFIX)$(SEP0)strip
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
OBJDIR=$(OBJROOT)/$(PREFIX)$(SEP1)$(POSTFIX)/
OBJS=$(addprefix $(OBJDIR),$(patsubst %.c,%.o ,$(patsubst %.cpp,%.o,$(SRC))))
MAKEFILEPATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
CURRENTDIRNAM:=$(notdir $(patsubst %/,%,$(dir $(MAKEFILEPATH))))
ifneq (,$(findstring djgpp,$(PREFIX)))
	BINNAM=a
else
	BINNAM=$(CURRENTDIRNAM)
endif
RUNSCRIPT=$(BINDIR)run$(SCREXT)
BUILDROOT=build
BINDIR=$(BUILDROOT)/$(PREFIX)$(SEP1)$(POSTFIX)/
BIN=$(BINDIR)$(BINNAM)$(BINEXT)
#$(BINDIR)/$(BINNAM)$(SEP0)$(BINPREFIX)$(SEP1)$(BINPOSTFIX)$(SEP2)$(GCCVERSION)$(BINEXT)
ifneq (,$(findstring mingw,$(PREFIX)))
	BINEXT=.exe
	SCREXT=.bat
else ifneq (,$(findstring djgpp,$(PREFIX)))
	BINEXT=.exe
	SCREXT=.bat
else ifneq (,$(findstring linux,$(PREFIX)))
	BINEXT=.out
	SCREXT=.sh
else
	BINEXT=.out
	SCREXT=.sh
endif
ifneq (,$(findstring mingw,$(PREFIX)))
	DSOEXT=.dll
else ifneq (,$(findstring djgpp,$(PREFIX)))
	DSOEXT=.dxe
else ifneq (,$(findstring linux,$(PREFIX)))
	DSOEXT=.so
else
	DSOEXT=.so
endif
LIBDIR=./build/$(PREFIX)$(SEP1)$(POSTFIX)/
LIBPREFIX=lib
LIBDIR=./build/$(PREFIX)$(SEP1)$(POSTFIX)/lib
ifneq (,$(findstring mingw,$(PREFIX)))
	UPX=upx
else ifneq (,$(findstring djgpp,$(PREFIX)))
	UPX=upx
else ifneq (,$(findstring linux,$(PREFIX)))
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
CXXFLAGS+=-O2
CXXFLAGS+=-I./src
CXXFLAGS+=-I./src/quickjspp
CXXFLAGS+=-I./src/crow
CXXFLAGS+=-std=c++17
CXXFLAGS+=-fpermissive
#CXXFLAGS+=-DCROW_ENABLE_LOGGING
CXXFLAGS+=-DCROW_STATIC_DIRECTORY=\"./public/\"
CXXFLAGS+=-DCROW_STATIC_ENDPOINT=\"/public/\<path\>\"
ifneq (,$(findstring djgpp,$(PREFIX)))
	#8.3 workarounds
	CXXFLAGS+=-DLIBPOSTFIX=\"\"
	#note _ prefix
	CXXFLAGS+=-DENTRYPOINT=\"_appmain\"
else
	CXXFLAGS+=-DLIBPOSTFIX=\"$(SEP0)$(BINPREFIX)$(SEP1)$(BINPOSTFIX)$(SEP2)$(GCCVERSION)\"
	CXXFLAGS+=-DENTRYPOINT=\"appmain\"
endif
CXXFLAGS+=-DDSOEXT=\"$(DSOEXT)\"
CXXFLAGS+=-DGCCVERSION=\"$(GCCVERSION)\"
LDFLAGS+=-L$(LIBDIR)
LDFLAGS+=-lpaho-mqtt3a
#LDFLAGS+=-lpaho-mqtt3c
LDFLAGS+=-lpaho-mqttpp3
LDFLAGS+=-lpthread
LDFLAGS+=-lboost_system
LDFLAGS+=-lz
LDFLAGS+=-ldl
# --------------------------------------------------------------------------------
ifneq (,$(findstring djgpp,$(PREFIX)))
	#import libs
	LIBNAMS=$(shell (ls $(LIBDIR)|grep libi|cut -f1 -d".")|cut -c4-)
else
	#libs
	LIBNAMS=$(shell (ls $(LIBDIR)|cut -f1 -d".")|cut -c4-)
endif
LIBFLAGS=$(addprefix -l,$(LIBNAMS))
# --------------------------------------------------------------------------------
ifneq (,$(findstring djgpp,$(PREFIX)))
else ifneq (,$(findstring mingw,$(PREFIX)))
else
	LDFLAGS+=-Wl,-rpath=./lib
	LDFLAGS+=-Wl,-rpath=$(LIBDIR)
endif
# --------------------------------------------------------------------------------
ifneq (,$(findstring mingw,$(PREFIX)))
	LDFLAGS+=-static
endif
ifneq (,$(findstring mingw,$(PREFIX)))
	# wrap dso dynspec: start
	ifneq (,$(findstring win32,$(POSTFIX)))
		LDFLAGS+=-Wl,-Bdynamic
	else
		LDFLAGS+=-Wl,-Bdynamic
	endif
endif
LDFLAGS+=$(LIBFLAGS)
ifneq (,$(findstring mingw,$(PREFIX)))
	# wrap dso dynspec: end
	ifneq (,$(findstring win32,$(POSTFIX)))
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
ifneq (,$(findstring mingw,$(PREFIX)))
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "@echo off" > $(RUNSCRIPT)
	@echo "setlocal" >> $(RUNSCRIPT)
	@echo "set PATH=.\lib;%PATH%" >> $(RUNSCRIPT)
	@echo ".\\\$(BINNAM)$(BINEXT)" >> $(RUNSCRIPT)
else ifneq (,$(findstring djgpp,$(PREFIX)))
$(RUNSCRIPT):compress
	@echo "creating runscript for $(BIN)..."
	@echo "@echo off" > $(RUNSCRIPT)
	@echo "set PATH=.\lib;%PATH%" >> $(RUNSCRIPT)
	@echo "set LD_LIBRARY_PATH=.\lib" >> $(RUNSCRIPT)
	@echo ".\\\$(BINNAM)$(BINEXT)" >> $(RUNSCRIPT)
else ifneq (,$(findstring linux,$(PREFIX)))
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
