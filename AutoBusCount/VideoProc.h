#pragma once

#include <cv.h>
#include <highgui.h>
#include "rgbgmfgd.h"

using namespace cv;
using namespace std;
class CVideoProc
{
public:
	CVideoProc(void);
	~CVideoProc(void);
	/****************************
	@return 0：无更新；
	@return 1 : 进入一个，m_sIn+1；
	@return 2 : 出去一个，m_sOut+1;
	@return 3 : m_sIn,m_sOut清零；
	****************************/
	int Process(IplImage* m_image);
	inline int GetInNum(){
		return m_iIn;
	};
	inline int GetOutNmu(){
		return m_iOut;
	};
	inline int GetOnboardNmu(){
		return m_iOnboard;
	};
	int CalHist(IplImage* src);
	void Findcontour(IplImage *gray,IplImage *mask,CvRect rect);
	int FindSegmentx(int *histdat, int length, int *thresh0, int *thresh1);
	int FindSegmenty(int *histdat, int length, int *thresh0, int *thresh1);
	void DrawRect(IplImage *img, CvRect rect,CvScalar cvbgr);
	void Zero();
	CvRect destination[2];
	CvRect predestination[2];
	char start[64]; //开始行车
	int m_iIn;
	int m_iOut;
	int m_iOnboard;
protected:
	int Init(IplImage* image);
private:
	IplImage* image ; 
	bool m_bInit; //是否初始化
	int m_bImage; //是否第一帧
	CRGBGaussianFGD fgdetector;
	IplImage *grayframe,*imagegrey,*preimagegrey,*prepreimagegrey,*absdiff_1,*absdiff_2,*absdiff,*absthresh,*edge,*gray;
	int tmp_Onboard;
	CvRect rect; //检测区
	int line; //检测线
};
extern CVideoProc* videoProc;

