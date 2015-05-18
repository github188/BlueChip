/*
 * =====================================================================================
 *
 *       Filename:  VideoProc.hpp
 *
 *    Description:  class for video stream process
 *
 *        Version:  1.0
 *        Created:  2015年05月16日 22时41分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef CVIDEOPROC_H_
#define CVIDEOPROC_H_

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

#include "ConGPS.hpp"
#include "ConSendData.hpp"

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

		//GPS
		CConGPS* conGPS;

		//send data to remote database
		CConSendData* conSendData;
};

#endif
