/*
 * =====================================================================================
 *
 *       Filename:  evcountwithdirect.hpp
 *
 *    Description:  simple count with direction and this class can also be used for counting passengers on the bus.
 *
 *        Version:  1.0
 *        Created:  2015年02月17日 01时21分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVCOUNTWITHDIRECT_H_
#define _EVCOUNTWITHDIRECT_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

class EVCountWithDirect
{
	public:
		EVCountWithDirect();
		~EVCountWithDirect();
		/* @param image:foreground binary image */
		int Process(IplImage* image);
		int Zero();
		int GetUpNum();
		int GetDownNum();
		inline IplImage* GetGray()
		{
			return gray;
		};
	protected:
		int CalHist(IplImage* src);
		void Findcontour(IplImage* gray,IplImage* mask,CvRect rect);
		int FindSegmentx(int* histdat,int length,int* thresh0,int* thresh1);
		int FindSegmenty(int* histdat,int length,int* thresh0,int* thresh1);
		void DrawRect(IplImage* img,CvRect rect,CvScalar cvbgr);
		int Init(IplImage* image);
	private:
		CvRect destination[2];
		char start[64]; 
		int m_iIn;
		int m_iOut;
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		int nFrmNum;
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
	    	int lastnFrmNum ;

		int m_highlow;
		
		IplImage* image,*imagegrey,*preimagegrey,*absdiff,*absthresh,*gray; 
		bool m_bInit; 
		int m_bImage; 
		
		CvRect rect; 
		CvRect rect1;
		CvRect rect2;
		int objforori1;
		int objforori2;
	
		int m_iManMaxHeight;

};

#endif
