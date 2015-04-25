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

#include <time.h>

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
	double last_time=0.00f;
	int count=0;
	clock_t start,finish;
	while(1)
	{
		++count;
		start=clock();
        	int key=cvWaitKey(1);
        	IplImage* img=usbStream->GetImage(fd);
        //	cvShowImage("img",img);
		cvWriteFrame(video,img);
		finish=clock();
		//last_time+=(double)(finish-start)*1000/CLOCKS_PER_SEC;
		cvReleaseImage(&img);
        	if(key==27||count>1200) /* 1 minute */
        	{
            		break;
        	}
	}
	cout<<"!--end--!"<<endl;
	usbStream->stop_capturing(fd);
	usbStream->uninit_camer_device(fd);
	usbStream->close_camer_device(fd);
	return 0;
}

