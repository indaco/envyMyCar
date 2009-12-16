#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sources/street.o \
	${OBJECTDIR}/sources/utilities/LogFile.o \
	${OBJECTDIR}/sources/core/MessageHandler.o \
	${OBJECTDIR}/sources/core/Application.o \
	${OBJECTDIR}/sources/main_clt.o \
	${OBJECTDIR}/sources/process_message.o \
	${OBJECTDIR}/sources/circuit.o \
	${OBJECTDIR}/sources/myclient/buildings.o \
	${OBJECTDIR}/sources/core/EventHandler.o \
	${OBJECTDIR}/sources/myclient/road.o \
	${OBJECTDIR}/sources/race_simulation.o \
	${OBJECTDIR}/sources/game_client.o \
	${OBJECTDIR}/sources/myclient/skybox.o \
	${OBJECTDIR}/sources/myclient/mycircuit.o \
	${OBJECTDIR}/sources/simple_circuit_creator.o \
	${OBJECTDIR}/sources/actions.o \
	${OBJECTDIR}/sources/myclient/tree.o \
	${OBJECTDIR}/sources/myclient/mycar.o \
	${OBJECTDIR}/sources/utilities/tga.o \
	${OBJECTDIR}/sources/myclient/TestEventHandler.o \
	${OBJECTDIR}/sources/packaging.o \
	${OBJECTDIR}/sources/plylib.o \
	${OBJECTDIR}/sources/utilities/myfunctions.o \
	${OBJECTDIR}/sources/myclient/terrain.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/vcg_client

dist/Debug/GNU-Linux-x86/vcg_client: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lQtCore -lQtNetwork -lGL -lGLU -lGLEW -lglut `sdl-config --libs` -o dist/Debug/GNU-Linux-x86/vcg_client  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/sources/street.o: sources/street.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/street.o sources/street.cpp

${OBJECTDIR}/sources/utilities/LogFile.o: sources/utilities/LogFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/utilities
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/utilities/LogFile.o sources/utilities/LogFile.cpp

${OBJECTDIR}/sources/core/MessageHandler.o: sources/core/MessageHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/core
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/core/MessageHandler.o sources/core/MessageHandler.cpp

${OBJECTDIR}/sources/core/Application.o: sources/core/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/core
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/core/Application.o sources/core/Application.cpp

${OBJECTDIR}/sources/main_clt.o: sources/main_clt.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/main_clt.o sources/main_clt.cpp

${OBJECTDIR}/sources/process_message.o: sources/process_message.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/process_message.o sources/process_message.cpp

${OBJECTDIR}/sources/circuit.o: sources/circuit.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/circuit.o sources/circuit.cpp

${OBJECTDIR}/sources/myclient/buildings.o: sources/myclient/buildings.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/buildings.o sources/myclient/buildings.cpp

${OBJECTDIR}/sources/core/EventHandler.o: sources/core/EventHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/core
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/core/EventHandler.o sources/core/EventHandler.cpp

${OBJECTDIR}/sources/myclient/road.o: sources/myclient/road.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/road.o sources/myclient/road.cpp

${OBJECTDIR}/sources/race_simulation.o: sources/race_simulation.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/race_simulation.o sources/race_simulation.cpp

${OBJECTDIR}/sources/game_client.o: sources/game_client.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/game_client.o sources/game_client.cpp

${OBJECTDIR}/sources/myclient/skybox.o: sources/myclient/skybox.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/skybox.o sources/myclient/skybox.cpp

${OBJECTDIR}/sources/myclient/mycircuit.o: sources/myclient/mycircuit.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/mycircuit.o sources/myclient/mycircuit.cpp

${OBJECTDIR}/sources/simple_circuit_creator.o: sources/simple_circuit_creator.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/simple_circuit_creator.o sources/simple_circuit_creator.cpp

${OBJECTDIR}/sources/actions.o: sources/actions.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/actions.o sources/actions.cpp

${OBJECTDIR}/sources/myclient/tree.o: sources/myclient/tree.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/tree.o sources/myclient/tree.cpp

${OBJECTDIR}/sources/myclient/mycar.o: sources/myclient/mycar.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/mycar.o sources/myclient/mycar.cpp

${OBJECTDIR}/sources/utilities/tga.o: sources/utilities/tga.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/utilities
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/utilities/tga.o sources/utilities/tga.cpp

${OBJECTDIR}/sources/myclient/TestEventHandler.o: sources/myclient/TestEventHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/TestEventHandler.o sources/myclient/TestEventHandler.cpp

${OBJECTDIR}/sources/packaging.o: sources/packaging.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/packaging.o sources/packaging.cpp

${OBJECTDIR}/sources/plylib.o: sources/plylib.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/plylib.o sources/plylib.cpp

${OBJECTDIR}/sources/utilities/myfunctions.o: sources/utilities/myfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/utilities
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/utilities/myfunctions.o sources/utilities/myfunctions.cpp

${OBJECTDIR}/sources/myclient/terrain.o: sources/myclient/terrain.cpp 
	${MKDIR} -p ${OBJECTDIR}/sources/myclient
	$(COMPILE.cc) -g -w -I../nvmc/sf -I../nvmc/src/common -I/usr/include/qt4 -o ${OBJECTDIR}/sources/myclient/terrain.o sources/myclient/terrain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/vcg_client

# Subprojects
.clean-subprojects:
