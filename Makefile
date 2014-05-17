# Makefile from:: http://ubuntuforums.org/showthread.php?t=1204739

Sources = main.cpp task.cpp workday.cpp agenda.cpp shell.cpp fileparser.cpp
Executable = AgendaGenerator

CFlags=-c -Wall -g -Iinc -std=c++11
LDFlags=
ObjectDir=build/
SourceDir=src/
BinDir=bin/

CC=g++
RM=rm

###################################################
#	DO NOT TOUCH BELOW HERE

###################################################

# COMPILE
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): $(CObjects)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) $(CFlags) $< -o $@

clean:
	$(RM) $(CObjects)
