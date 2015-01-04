#include "stdafx.h"
#include "rgbgmfgd.h"
#include "highgui.h"
CRGBGaussianFGD::CRGBGaussianFGD()
{
	m_nFrameIdx  = -1;
	m_nWidth = 0;
	m_nHeight = 0;
	m_fScale = 4.0f/8.0f;
	
	m_fAlpha = 0.001f;
	m_fThreash = 2.8f; 
	m_pMean = NULL;
	m_pSigma = NULL; 
	m_pFGMask = NULL;
}

CRGBGaussianFGD::~CRGBGaussianFGD()
{
	UnInit();
}

void CRGBGaussianFGD::Process(IplImage* pFrame)
{
//	cvNamedWindow("bkgrd");
//	cvShowImage("bkgrd",m_pMean);
	if(!pFrame) 
	{
		if(m_pFGMask) cvZero(m_pFGMask);
		return ;
	}
	if(pFrame->nChannels != 3)
	{
		fprintf(stderr, "the input for CRGBGaussianFGD::Process must be RGB image.\n"); 
		return ;
	}

	CvSize small_size = cvSize(cvRound(pFrame->width*m_fScale), cvRound(pFrame->height*m_fScale));

	IplImage * pImage8U = cvCreateImage(small_size, IPL_DEPTH_8U, 3);

	if(pFrame->width != m_nWidth || pFrame->height != m_nHeight)
	{
		ReInit(pFrame->width, pFrame->height);
		cvResize(pFrame, pImage8U);
		cvConvert(pImage8U, m_pMean);

		int i,j,c;
		for(i=0;i<m_pSigma->width;i++)
		for(j=0;j<m_pSigma->height;j++)
		for(c=0;c<m_pSigma->nChannels;c++)
			CV_IMAGE_ELEM(m_pSigma, float, j, i*m_pSigma->nChannels+c) = 10.f;
	}

	m_nFrameIdx++;

	IplImage * pImage = cvCreateImage(small_size, IPL_DEPTH_32F, 3);
	IplImage * pDiff = cvCreateImage(small_size, IPL_DEPTH_32F, 3);
	IplImage * pFGMask = cvCreateImage(small_size, IPL_DEPTH_8U, 1);
	
	cvResize(pFrame, pImage8U);
	cvConvert(pImage8U, pImage);
	cvReleaseImage(&pImage8U);
	
	cvSmooth(pImage, pImage);
	cvAbsDiff(pImage, m_pMean, pDiff);

	{ //foreground
		int i,j,c;
		//float alpha;
		//if(m_nFrameIdx<300)
		//	alpha = m_fAlpha * 300 / (m_nFrameIdx+1);
		//else
		//	alpha = m_fAlpha;

		for(i=0; i<pFGMask->width; i++)
		for(j=0; j<pFGMask->height; j++)
		{
			CV_IMAGE_ELEM(pFGMask, unsigned char, j, i) = 255 * (
				CV_IMAGE_ELEM(pDiff,float,j,i*3  ) > m_fThreash*CV_IMAGE_ELEM(m_pSigma,float,j,i*3  ) ||
				CV_IMAGE_ELEM(pDiff,float,j,i*3+1) > m_fThreash*CV_IMAGE_ELEM(m_pSigma,float,j,i*3+1) ||
				CV_IMAGE_ELEM(pDiff,float,j,i*3+2) > m_fThreash*CV_IMAGE_ELEM(m_pSigma,float,j,i*3+2)   );
			
			/*
			{//shadow detect. using method in paper KaewTrakulPong "An improved adaptive background mixture model for real-time tracking with shadow detection"
				float bright_sig = ( CV_IMAGE_ELEM(m_pSigma,float,j,i*3) + 
									CV_IMAGE_ELEM(m_pSigma,float,j,i*3+1) + 
									CV_IMAGE_ELEM(m_pSigma,float,j,i*3+2) );
				float bright_alpha = ( CV_IMAGE_ELEM(pImage,float,j,i*3) + CV_IMAGE_ELEM(pImage,float,j,i*3+1) + CV_IMAGE_ELEM(pImage,float,j,i*3+2) )/( CV_IMAGE_ELEM(m_pMean,float,j,i*3) + CV_IMAGE_ELEM(m_pMean,float,j,i*3+1) + CV_IMAGE_ELEM(m_pMean,float,j,i*3+2) );
				float color_dist = fabs(CV_IMAGE_ELEM(pImage,float,j,i*3)-bright_alpha*CV_IMAGE_ELEM(m_pMean,float,j,i*3)) +
									fabs(CV_IMAGE_ELEM(pImage,float,j,i*3+1)-bright_alpha*CV_IMAGE_ELEM(m_pMean,float,j,i*3+1)) +
									fabs(CV_IMAGE_ELEM(pImage,float,j,i*3+2)-bright_alpha*CV_IMAGE_ELEM(m_pMean,float,j,i*3+2)) ;
				//if(color_dist < bright_sig*2.5f && bright_alpha <1.0f && bright_alpha>0.7f) //shadow
				//	CV_IMAGE_ELEM(pFGMask, unsigned char, j, i) = 0;
			}//shadow detect
			//CV_IMAGE_ELEM(pFGMask, unsigned char, j, i) = MIN((255/20*CV_IMAGE_ELEM(m_pSigma, float, j, i*3)), 255);
			*/
			
			//update
			for(c=0;c<3;c++)
			{
				float diff = CV_IMAGE_ELEM(pDiff, float, j, i*3+c);
				float sig = CV_IMAGE_ELEM(m_pSigma, float, j, i*3+c);
				float rho;
				//  1 / (2*PI)^0.5 = 0.3989
				if(m_nFrameIdx<30)
					rho = m_fAlpha; //0.1f - (0.1f - m_fAlpha)/300*m_nFrameIdx;
				else
					rho = m_fAlpha/1;// /10.f; //float(m_fAlpha*0.3989f/sig*exp(-1*diff*diff/sig/sig/2)); 

				CV_IMAGE_ELEM(m_pMean, float, j, i*3+c) = CV_IMAGE_ELEM(m_pMean, float, j, i*3+c)*(1.0f-rho)
														+CV_IMAGE_ELEM(pImage, float, j, i*3+c)*rho;
				
				CV_IMAGE_ELEM(m_pSigma, float, j, i*3+c) = float(sqrt((1.0f-rho)*sig*sig + rho*diff*diff));
				//CV_IMAGE_ELEM(m_pSigma, float, j, i*3+c) = float( (1.0f-sqrt(rho) )*sig + sqrt(rho)*diff);
				if(CV_IMAGE_ELEM(m_pSigma, float, j, i*3+c) < 4.0f)
					CV_IMAGE_ELEM(m_pSigma, float, j, i*3+c) = 4.0f;
			}
		}
	}//foreground

	//remove noise
	if(m_fScale < 0.5f)
	{
		cvErode(pFGMask, pFGMask, 0, 1);
		cvDilate(pFGMask, pFGMask, 0, 1);
	}
	
	cvResize(pFGMask, m_pFGMask, CV_INTER_NN);
	cvConvert(m_pMean, m_pMean8U);
	cvReleaseImage(&pFGMask);
	cvReleaseImage(&pImage);
	cvReleaseImage(&pDiff);
}

void CRGBGaussianFGD::ReInit(int w, int h)
{
	UnInit();//make sure to release all memory allocated.
	m_nWidth = w;
	m_nHeight = h;

	CvSize small_size = cvSize(cvRound(m_nWidth*m_fScale), cvRound(m_nHeight*m_fScale));

	m_pMean8U  = cvCreateImage(small_size, IPL_DEPTH_8U, 3); cvZero(m_pMean8U);
	m_pMean = cvCreateImage(small_size, IPL_DEPTH_32F, 3); cvZero(m_pMean);
	m_pSigma = cvCreateImage(small_size, IPL_DEPTH_32F, 3); cvZero(m_pSigma);
	m_pFGMask = cvCreateImage(cvSize(w,h), IPL_DEPTH_8U, 1); cvZero(m_pFGMask);
}

void CRGBGaussianFGD::UnInit()
{
	m_nFrameIdx  = -1;
	m_nWidth = 0;	
	m_nHeight = 0;

	cvReleaseImage(&m_pMean8U);
	cvReleaseImage(&m_pMean);
	cvReleaseImage(&m_pSigma);
	cvReleaseImage(&m_pFGMask);
}
