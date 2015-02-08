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
	int Init();
	int GetVar(const int m1,const int m2, const int m3,const int m4,const int m5,const int m6,const int m7);
	/****************************
	@return 0���޸��£�
	@return 1 : ����һ����m_sIn+1��
	@return 2 : ��ȥһ����m_sOut+1;
	@return 3 : m_sIn,m_sOut���㣻
	****************************/
	int Process(IplImage* m_image);
	inline int GetInNum(){
		return m_iIn; //�ϳ�
	};
	inline int GetOutNmu(){
		return m_iOut; //�³�
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
	char start[64]; //��ʼ�г�
	int m_iIn;
	int m_iOut;
	int m_iOnboard;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_rheight;
	/**��ͷ��ⷽ��*********************************************/
	int nFrmNum;
	CvRect rect1,rect2;
	int framecnt;
	int frameseqcnt[5];
	bool singleflag;
	int high ;
	int low ;
	bool up;
	bool isup;
	bool isin;

    time_t rawtime; 
	time_t lastrawtime ;

//	frame->origin = image->origin ;
//	grayframe->origin = image->origin ;
//���ڷ����������

    int objforori1;
	int objforori2;
	
	int objpix;//ѹ�ߵ�������Ŀ
    int last_objpix;
    int lastnFrmNum ;

	int m_highlow;
	/**��ͷ��ⷽ��*********************************************/
protected:
	int Init(IplImage* image);
private:
	IplImage* image ; 
	bool m_bInit; //�Ƿ��ʼ��
	int m_bImage; //�Ƿ��һ֡
	//CRGBGaussianFGD fgdetector;
	IplImage *grayframe,*imagegrey,*preimagegrey,*prepreimagegrey,*absdiff_1,*absdiff_2,*absdiff,*absthresh,*edge,*gray,*absthresh_2;
	int tmp_Onboard;
	CvRect rect; //�����
	int line; //�����
///////V1.5.0///////////
	bool m_bIn;
	bool m_bOut;
	float m_iLineIn;
	float m_iLineOut;
	bool m_bLineIn;
	bool m_bLineOut;
//////////////////////
	int m_iManMaxHeight;
	int m_iRoiRealTopPos;
	int m_iRoiRealHeight;
};

