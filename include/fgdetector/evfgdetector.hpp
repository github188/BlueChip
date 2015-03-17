/*
 * =====================================================================================
 *
 *       Filename:  evfgdetector.hpp
 *
 *    Description:  head file of foreground detector process
 *
 *        Version:  1.0
 *        Created:  2015年02月13日 01时41分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVFGDETECTOR_H_
#define _EVFGDETECTOR_H_

#include "evifgdetector.hpp"
#include <opencv.hpp>
#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>

using namespace cv;

class EVFGDetectorThreeDiff
{
	public:
		EVFGDetectorThreeDiff();
		~EVFGDetectorThreeDiff();
		/* main process */
		void Process(const Mat& inputFrame);
		Mat GetMask() const;
	protected:
		inline void Update(const Mat& m_pDiffMask);
	private:
		Mat m_pDiffMask;
		Mat m_pDiffMask1;
		Mat m_pDiffMask2;
		Mat m_pMask;
		Mat m_pMask1;
		Mat m_pMask2;	
		int m_iControl;

};

class EVFGDetector:public EVIFGDetector
{
	public:
		EVFGDetector();
		~EVFGDetector();
		virtual void Process(const Mat& frame,Mat* mask);
	private:
		bool m_bInit;
		Mat background;
		int m_traintime;
};

#endif

