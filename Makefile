SHELL=/bin/sh

DIR_INC=./include
DIR_SRC=./src
DIR_OBJ=./obj
DIR_BIN=./bin
DIR_LIB=./lib
DIR_3RD=./3rdparty
#opencv
DIR_3RD_OPENCV=${DIR_3RD}/opencv
DIR_3RD_OPENCV2=${DIR_3RD}/opencv2
DIR_LIB_OPENCV=${DIR_LIB}/lib_opencv-2.4.9_x86
#mysql
DIR_3RD_MYSQL=${DIR_3RD}/mysql
DIR_LIB_MYSQL=${DIR_LIB}/lib_mysql6.1.5_i686
#extremevision
DIR_INC_EXTREMEVISION = ../include
DIR_LIB_EXTREMEVISION = ${DIR_LIB}/lib_extremevision

$(shell mkdir -p ${DIR_OBJ})
$(shell mkdir -p ${DIR_BIN})

CC=g++
CXXFLAGS=-g -Wall -I${DIR_INC} -I${DIR_3RD} -I${DIR_INC_EXTREMEVISION} -I${DIR_3RD_OPENCV} -I${DIR_3RD_OPENCV2} -I${DIR_3RD_MYSQL}
LDFLAGS = -L${DIR_LIB} -L${DIR_LIB_OPENCV} -Wl,-rpath=../lib/lib_opencv-2.4.9_x86 -L${DIR_LIB_MYSQL} -Wl,-rpath=../lib/lib_mysql6.1.5_i686 -L${DIR_LIB_EXTREMEVISION} -Wl,-rpath=../${DIR_LIB_EXTREMEVISION}
SRC=$(wildcard ${DIR_SRC}/*.cc)
OBJ=$(patsubst %.cc,${DIR_OBJ}/%.o,$(notdir $(SRC)))

TARGET = Bus_Counting_V3.0

BIN_TARGET = ${DIR_BIN}/${TARGET}

LIBS_OPENCV = -lopencv_core -lopencv_highgui -lopencv_calib3d -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_video
LIBS_MYSQL = -lmysqlclient
LIBS_EXTREMEVISION = -levtool -levdatabase

${BIN_TARGET} : ${OBJ}
	$(CC) $(OBJ) -o $@ $(LDFLAGS) ${LIBS_EXTREMEVISION} ${LIBS_OPENCV} ${LIBS_MYSQL} -lpthread
${DIR_OBJ}/%.o: ${DIR_SRC}/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@
.PHONY:clean
clean:
	rm ${DIR_OBJ} ${DIR_BIN} -rf;
