/*
 * =====================================================================================
 *  
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月18日 02时37分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "stream/evusbstream.hpp"

#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define VIDEO_DEVICE "/dev/video0"

using namespace std;

int main()
{
	/* init video device */
	EVUsbStream* usbStream=new EVUsbStream();
	usbStream->set_device(VIDEO_DEVICE);
	usbStream->setSize(480,720);
	int fd;
	fd=usbStream->open_camer_device();
	usbStream->init_camer_device(fd);
	usbStream->start_capturing(fd);
	/* init video writer */
	CvVideoWriter* video = cvCreateVideoWriter("test.avi",
			CV_FOURCC('X','V','I','D'),20,
			cvSize(720,480),1);
	while(1)
	{
        	int key=cvWaitKey(1);
        	IplImage* img=usbStream->GetImage(fd);
        	cvShowImage("img",img);
		cvWriteFrame(video,img);
        	if(key==27)
        	{
            		break;
        	}
	}
	usbStream->stop_capturing(fd);
	usbStream->uninit_camer_device(fd);
	usbStream->close_camer_device(fd);
	return 0;
}

