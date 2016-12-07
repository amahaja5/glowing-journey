###################################################
# Nick Skacel
# Avi Mahajan
# Adapted from Ben Mitchell's solution to HW8
#
###################################################

###############################
# Compiler commands
###############################
GCC = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Wextra -g -I../include

###############################
# pa.hpp variables
###############################
# where to look for .hpp files
INC_DIR = ../include
# where to put .o files
OBJ_DIR = ./obj
# where to put executables
BIN_DIR = ../bin
 
# make sure the output directories exists...
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

###############################
# targets 
###############################

all: $(BIN_DIR)/a10 $(BIN_DIR)/unitTest

test: $(BIN_DIR)/unitTest
	$(BIN_DIR)/unitTest

$(BIN_DIR)/a10: $(OBJ_DIR)/a10.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/DocumentCollection.o 
	$(GCC) $(CPPFLAGS) $(OBJ_DIR)/a10.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/DocumentCollection.o -o $(BIN_DIR)/a10

#comment out for now
$(BIN_DIR)/unitTest: $(OBJ_DIR)/unitTests-NgramCollection.o $(OBJ_DIR)/unitTestDriver.o $(OBJ_DIR)/NgramCollection.o
	$(GCC) $(CPPFLAGS) $(OBJ_DIR)/unitTestDriver.o $(OBJ_DIR)/unitTests-NgramCollection.o $(OBJ_DIR)/NgramCollection.o -o $(BIN_DIR)/unitTest

$(OBJ_DIR)/a10.o: a10.cpp 
	$(GCC) $(CPPFLAGS) -O3 -c a10.cpp -o $(OBJ_DIR)/a10.o

$(OBJ_DIR)/unitTestDriver.o: unitTestDriver.cpp 
	$(GCC) $(CPPFLAGS) -c unitTestDriver.cpp -o $(OBJ_DIR)/unitTestDriver.o

$(OBJ_DIR)/unitTests-NgramCollection.o: unitTests-NgramCollection.cpp 
	$(GCC) $(CPPFLAGS) -c unitTests-NgramCollection.cpp -o $(OBJ_DIR)/unitTests-NgramCollection.o

$(OBJ_DIR)/NgramCollection.o: NgramCollection.cpp $(INC_DIR)/NgramCollection.hpp 
	 $(GCC) $(CPPFLAGS) -O3 -c NgramCollection.cpp -o $(OBJ_DIR)/NgramCollection.o

$(OBJ_DIR)/DocumentCollection.o: DocumentCollection.cpp $(INC_DIR)/DocumentCollection.hpp $(INC_DIR)/NgramCollection.hpp
	 $(GCC) $(CPPFLAGS) -O3 -c DocumentCollection.cpp -o $(OBJ_DIR)/DocumentCollection.o


###############################
# "utility" rules
###############################
# the .PHONY line says these targets aren't expected to generate files named after the target
.PHONY: clean test

# clean up generated files
clean:
	@echo removing generated files...
	@rm -f $(OBJ_DIR)/*.o 
