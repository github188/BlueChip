/*
 * =====================================================================================
 *
 *       Filename:  evgmfgdetector.hpp
 *
 *    Description: improve gaussian modeling 
 *
 *        Version:  1.0
 *        Created:  2015年02月25日 23时11分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */
#ifndef _EVGMFGDETECTOR_H_
#define _EVFGMGDETECTOR_H_

#include "evifgdetector.hpp"
#include "video/background_segm.hpp"
#include "video/video.hpp"

class EVGMFgDetector:public EVIFGDetector
{
	public:
		EVGMFgDetector();
		~EVGMFgDetector();
		virtual void Process(const Mat& frame,Mat* mask);
		void Process(Mat& img);
		Mat GetMask();
		/* TODO:
		 * train threshold params for foreground detector,params have been set default by the function Init() if do not use this function
		 * @return 1: new reasonable params have been set *
		 * @return 0: new params are not yet ready,do not use the function Process() until this return 1*/
		int TrainParams(const Mat& frame);
		/* TODO:To identify whether the target is a pedestrain or not. It will be better to use automatic method. */
		int PedestrainIdentify();
		int Init(const Mat& first_frame);
		/* Rects from this function will be a little bigger than normal rects of contours, as the function have used Camshift to make it more accurate */
		vector<Rect> GetTargetWindows();
	protected:
		void ImproveTargetWindow(const Mat& frame);
		void BackgroundOTSU(Mat gray);
	private:
		bool m_bInit;
		Mat mask2;
		BackgroundSubtractorMOG2 mog;
		/* Train params */
		int MAX_WIDTH;
		int MIN_WIDTH;
		int MAX_HEIGHT;
		int MIN_HEIGHT;
		int MAX_SIZE;
		int MIN_SIZE;
		int OUST;
		/* Train params end */
		Mat _frame;
		vector<Rect> targetWindows;
};

#endif
