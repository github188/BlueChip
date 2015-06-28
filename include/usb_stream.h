//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef BLUECHIP_INC_USB_STREAM_H_
#define BLUECHIP_INC_USB_STREAM_H_

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

#include "gmm4busybackground.h"
#include "encoder.h"
#include "video_proc.h"

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

//Class CUsbStream is designed for getting video stream for usb device.
//Using the interface of V4l2.
//It can be set to save the encoded(h.264) videos for each hour.
//Default device name is set to be "/dev/video0".
//If the device name do not equals to the default name, you can use the
//function set_device to set an new device name.
class CUsbStream
{
	public:
        	CUsbStream();
       		~CUsbStream();
		//For setting device name when the current device is not video0.
		void set_device(char* device_name);
		//For setting the ftps for saving videos
		//@param save_fps: saving one for every "every_frame" frames.
		//@param dir: the saving dir of the videos.  
		//example: 
		//set_save(5,"/root/videos/");
		int set_save(int save_fps=2,char* dir=NULL);
		//An whole process,intergrate all related funcitons.
		//If needing to set device or set save, function set_device and 
		void Process();
	protected:
		int open_camer_device();
		void close_camer_device(int fd);
		int init_camer_device(int fd);
		//Function for image processing.
		int process_image(void *addr,int length);
		int start_capturing(int fd);
		int read_frame(int fd);
		int mainloop(int fd);
		void stop_capturing(int fd);
		void uninit_camer_device(int fd);
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
                //Instance of gmm4busybackground.
                dbs::GMM4BusyBackground* gmm4busybackground;
		//Instance of video processing.
		CVideoProc* videoProc;
	        CvFont font;
        	char datentime[64];
		//Instance of video encoder.
		CEncoder* encoder;
		//Encoded video file(Each hour for each file).
		char filename[64];
		int h264_fd;
        	int nFrame;
		int saveFps;
		bool bSave;
		char* init_dir;
};
#endif //BLUECHIP_INC_USB_STREAM_H_

