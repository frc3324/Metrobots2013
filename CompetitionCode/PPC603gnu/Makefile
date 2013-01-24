# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/Metrobots2013/CompetitionCode



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = CompetitionCode/$(MODE_DIR)/CompetitionCode.out \
	 CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage.o


#Rules

# CompetitionCode
ifeq ($(DEBUG_MODE),1)
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CompetitionCode/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
CompetitionCode/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
CompetitionCode/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
CompetitionCode/$(MODE_DIR)/% : IDE_DEFINES = 
CompetitionCode/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CompetitionCode/$(MODE_DIR)/% : DEFINES = 
CompetitionCode/$(MODE_DIR)/% : EXPAND_DBG = 0
CompetitionCode/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
CompetitionCode/$(MODE_DIR)/% : CPU = PPC603
CompetitionCode/$(MODE_DIR)/% : TOOL_FAMILY = gnu
CompetitionCode/$(MODE_DIR)/% : TOOL = gnu
CompetitionCode/$(MODE_DIR)/% : TOOL_PATH = 
CompetitionCode/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
CompetitionCode/$(MODE_DIR)/% : LIBPATH = 
CompetitionCode/$(MODE_DIR)/% : LIBS = 
CompetitionCode/$(MODE_DIR)/% : OBJ_DIR := CompetitionCode/$(MODE_DIR)

OBJECTS_CompetitionCode = CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage.o

CompetitionCode/$(MODE_DIR)/CompetitionCode.out : $(OBJECTS_CompetitionCode)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_CompetitionCode) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_CompetitionCode) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CompetitionCode/$(MODE_DIR)/CompetitionCode_compile_file : $(FILE) ;

_clean :: CompetitionCode/$(MODE_DIR)/CompetitionCode_clean

CompetitionCode/$(MODE_DIR)/CompetitionCode_clean : 
	$(TRACE_FLAG)if [ -d "CompetitionCode" ]; then cd "CompetitionCode"; rm -rf $(MODE_DIR); fi


# CompetitionCode_partialImage
ifeq ($(DEBUG_MODE),1)
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CompetitionCode_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
CompetitionCode_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h/wrn/coreip 
CompetitionCode_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
CompetitionCode_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
CompetitionCode_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CompetitionCode_partialImage/$(MODE_DIR)/% : DEFINES = 
CompetitionCode_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
CompetitionCode_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
CompetitionCode_partialImage/$(MODE_DIR)/% : CPU = PPC603
CompetitionCode_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
CompetitionCode_partialImage/$(MODE_DIR)/% : TOOL = gnu
CompetitionCode_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
CompetitionCode_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
CompetitionCode_partialImage/$(MODE_DIR)/% : LIBPATH = 
CompetitionCode_partialImage/$(MODE_DIR)/% : LIBS = 
CompetitionCode_partialImage/$(MODE_DIR)/% : OBJ_DIR := CompetitionCode_partialImage/$(MODE_DIR)

CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/drive.o : $(PRJ_ROOT_DIR)/drive.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/metrobot.o : $(PRJ_ROOT_DIR)/metrobot.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/atkjoystick.o : $(PRJ_ROOT_DIR)/util/atkjoystick.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/controller.o : $(PRJ_ROOT_DIR)/util/controller.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/gamepad.o : $(PRJ_ROOT_DIR)/util/gamepad.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/metropidcontroller.o : $(PRJ_ROOT_DIR)/util/metropidcontroller.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/vision.o : $(PRJ_ROOT_DIR)/vision.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_CompetitionCode_partialImage = CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/drive.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/metrobot.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/atkjoystick.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/controller.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/gamepad.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/metropidcontroller.o \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/vision.o

CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage.o : $(OBJECTS_CompetitionCode_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_CompetitionCode_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage_compile_file : $(FILE) ;

_clean :: CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage_clean

CompetitionCode_partialImage/$(MODE_DIR)/CompetitionCode_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "CompetitionCode_partialImage" ]; then cd "CompetitionCode_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/drive.d CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/metrobot.d CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/atkjoystick.d \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/controller.d CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/gamepad.d CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/util/metropidcontroller.d \
	 CompetitionCode_partialImage/$(MODE_DIR)/Objects/CompetitionCode/vision.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
