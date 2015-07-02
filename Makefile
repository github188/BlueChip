SHELL=/bin/sh

DIR_ROOT=/root/BlueChip

DIR_INC=${DIR_ROOT}/include
DIR_SRC=${DIR_ROOT}/src
DIR_OBJ=${DIR_ROOT}/obj
DIR_BIN=${DIR_ROOT}/bin
DIR_LIB=${DIR_ROOT}/lib
DIR_3RD=${DIR_ROOT}/3rdparty
#opencv
DIR_3RD_OPENCV=${DIR_3RD}/opencv
DIR_3RD_OPENCV2=${DIR_3RD}/opencv2
DIR_LIB_OPENCV=${DIR_LIB}/lib_opencv-2.4.9_x86
#mysql
DIR_3RD_MYSQL=${DIR_3RD}/mysql
DIR_LIB_MYSQL=${DIR_LIB}/lib_mysql6.1.5_i686
#x264
DIR_3RD_X264 = ${DIR_3RD}/x264
DIR_LIB_X264 = ${DIR_LIB}/lib_x264
#jrtp
DIR_3RD_JRTP = ${DIR_3RD}/jrtplib3
#DIR_LIB_JRTP = ${DIR_LIB}/lib_jrtp

$(shell mkdir -p ${DIR_OBJ})
$(shell mkdir -p ${DIR_BIN})

CC=g++
CXXFLAGS=-g -Wall -I${DIR_INC} -I${DIR_3RD} -I${DIR_3RD_OPENCV} -I${DIR_3RD_OPENCV2} -I${DIR_3RD_MYSQL} -I${DIR_3RD_X264} -I${DIR_3RD_JRTP}
LDFLAGS = -L${DIR_LIB} -L${DIR_LIB_OPENCV} -Wl,-rpath=${DIR_LIB_OPENCV} -L${DIR_LIB_MYSQL} -Wl,-rpath=${DIR_LIB_MYSQL} -L${DIR_LIB_X264} -Wl,-rpath=${DIR_LIB_X264} -L${DIR_LIB_JRTP} -Wl,-rpath=${DIR_LIB_JRTP}
SRC=$(wildcard ${DIR_SRC}/*.cc)
OBJ=$(patsubst %.cc,${DIR_OBJ}/%.o,$(notdir $(SRC)))

TARGET = Bus_Counting_V3.0

BIN_TARGET = ${DIR_BIN}/${TARGET}

LIBS_OPENCV = -lopencv_core -lopencv_highgui -lopencv_calib3d -lopencv_contrib -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_video
#LIBS_MYSQL = -lmysqlclient
LIBS_X264 = -lpthread -lx264 -lm #-ljrtp

${BIN_TARGET} : ${OBJ}
	$(CC) $(OBJ) -o $@ $(LDFLAGS) ${LIBS_OPENCV} ${LIBS_MYSQL} ${LIBS_X264}
${DIR_OBJ}/%.o: ${DIR_SRC}/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@
.PHONY:clean
clean:
	rm ${DIR_OBJ} ${DIR_BIN} -rf;
