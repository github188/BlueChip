#ifndef  RGB_GAUSSIAN_FGD_H
#define  RGB_GAUSSIAN_FGD_H

//#include <cxcore.h>
//#include <cv.h>
#include <cvaux.h>
#include <stdio.h>

class CRGBGaussianFGD:public CvFGDetector
{
protected:
	int m_nFrameIdx;
	int m_nWidth, m_nHeight;
	float m_fScale; // resize the input image to a small one. width=(m_nWidth*m_fScale)

	float m_fAlpha;
	float m_fThreash; //m_fThreash* sigma
	IplImage * m_pMean,* m_pMean8U;
	IplImage * m_pSigma;
	IplImage * m_pFGMask;

	void ReInit(int w, int h);
	void UnInit();
public:
	CRGBGaussianFGD();
	~CRGBGaussianFGD();

	IplImage* GetMask()
	{
		return m_pFGMask;
	};

	IplImage* GetMean()
	{
		return m_pMean8U;
	};
	/* process current image */
	void  Process(IplImage* pFrame);
	/* release foreground detector */
	void  Release() {delete this;};
};

#endif
