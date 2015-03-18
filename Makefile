SHELL=/bin/sh

DIR_INC=./include
DIR_SRC=./src
DIR_OBJ=./obj
DIR_BIN=./bin
DIR_LIB=./lib
#extremevision
DIR_LIB_EXTREMEVISION = ${DIR_LIB}/lib_extremevision

$(shell mkdir -p ${DIR_OBJ})
$(shell mkdir -p ${DIR_BIN})

CC=g++
CXXFLAGS=-g -Wall -I${DIR_INC}
LDFLAGS = -L${DIR_LIB} -L${DIR_LIB_EXTREMEVISION} -Wl,-rpath=../lib -Wl,-rpath=../lib/lib_extremevision
SRC=$(wildcard ${DIR_SRC}/*.cc)
OBJ=$(patsubst %.cc,${DIR_OBJ}/%.o,$(notdir $(SRC)))

TARGET = Bus_Counting_V1.0

BIN_TARGET = ${DIR_BIN}/${TARGET}

LIBS_EXTREMEVISION = -levtool

${BIN_TARGET} : ${OBJ}
	$(CC) $(OBJ) -o $@ $(LDFLAGS) ${LIBS_EXTREMEVISION} -lpthread
${DIR_OBJ}/%.o: ${DIR_SRC}/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@
.PHONY:clean
clean:
	rm ${DIR_OBJ} ${DIR_BIN} -rf;
