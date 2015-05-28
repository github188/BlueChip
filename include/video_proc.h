//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef BLUECHIP_INC_VIDEO_PROC_H_
#define BLUECHIP_INC_VIDEO_PROC_H_

#include "objdetect/objdetect.hpp"
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "core/core.hpp"
#include "cv.h"
#include "highgui.h"
using namespace cv;

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#include "con_gps.h"
#include "con_send_data.h"
#include "count_log.h"

enum Status
{
	onRoad,
	onRest,
	Boarding,
	Debusing
};

class CVideoProc
{
        public:
        	CVideoProc();
		~CVideoProc();
		void InitClassifier();
		/* @param frame: input gray frame */
		int Process(const Mat frame);
	protected:
        	int CalHist(IplImage* src);
        	void Findcontour(IplImage* gray,IplImage* mask,CvRect rect);
        	int FindSegmentx(int* histdat,int length,int* thresh0,int* thresh1);
        	int FindSegmenty(int* histdat,int length,int* thresh0,int* thresh1);
            	int Init(IplImage* image);
                void DrawRect(IplImage* img,CvRect rect,CvScalar cvbgr);
		int FindHead(Mat frameROI_grey);
		void CheckStatus();
        private:
		//Status of bus
		Status status;

		//head classifier
		CascadeClassifier head_cascade;

		//foreground area
        	CvRect destination[2];

		//passenger number
        	int m_iIn;

		//direction detect area
        	int m_x;
        	int m_y;
        	int m_width;
        	int m_height;
		
		//latest start time
		char* start;
		//earliest  end time
		char* end;
		
		//frame number
        	int nFrmNum;

		//hair detect threshold
		int m_menxian;

		//variables for detect direction
        	int framecnt;
        	int frameseqcnt[5];
        	bool singleflag;
        	int high ;
        	int low ;
        	bool up;
        	bool isup;
        	bool isin;
        	int objpix;
            	int last_objpix;
            	int lastnFrmNum;
        	int m_highlow;
        	IplImage* image,*imagegrey,*preimagegrey,*absdiff,*absthresh,*gray;
        	bool m_bInit;
        	int m_bImage;
        	CvRect rect;
        	CvRect rect1;
        	CvRect rect2;
        	int objforori1;
        	int objforori2;
		//direction
		bool in;

		//GPS
		CConGPS* conGPS;

		//send data to remote database
		CConSendData* conSendData;

	        //Log
        	CLog* log;

		//location
		char* current_location;
		char* dep;
		char* des;
};

#endif //BLUECHIP_INC_VIDEO_PROC_H_
