/*
 * =====================================================================================
 *
 *       Filename:  evusbstream.h
 *
 *    Description:  head file for using v4l to get video data from usb collector
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 18时22分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _V4L2_H_
#define _V4L2_H_

#include <stdio.h>
#include <stdlib.h> //stdio.h and stdlib.h are needed by perror function
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> //O_RDWR
#include <unistd.h>
#include <sys/mman.h> //unistd.h and sys/mman.h are needed by mmap function
#include <stdbool.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <time.h>

#include "cv.h"
#include "highgui.h"
using namespace cv;

#include "Encoder.hpp"
#include "VideoProc.hpp"

typedef struct _v4l2_struct
{
	int fd;
	struct v4l2_capability capability;
}v4l2_device;

typedef struct
{
	void* start;
	int length;
}BUFTYPE;

class CUsbStream
{
	public:
        	CUsbStream();
       		~CUsbStream();
		int open_camer_device();
		void close_camer_device(int fd);
		int init_camer_device(int fd);
		int process_image(void *addr,int length);
		int start_capturing(int fd);
		int read_frame(int fd);
		int mainloop(int fd);
		void stop_capturing(int fd);
		void uninit_camer_device(int fd);
		/***2015.2.12 added by Lauren***/
		void set_device(char* device_name);
		/* 2015.5.17 added by Lauren */
		void Process();
	protected:
		int init_mmap(int fd);
		uchar* p;
		IplImage* m_Image;
		IplImage* cv_img;
		char* device;
	private:
		int m_height;
		int m_width;
        	BUFTYPE* user_buf;
        	int n_buffer;
		/* 2015.5.17 added by Lauren */
		CVideoProc* videoProc;
	        CvFont font;
        	char datentime[64];
		//CvVideoWriter* video; //save as video
		CEncoder* encoder;
		char filename[64];
		int h264_fd;
        int nFrame;
};

#endif

