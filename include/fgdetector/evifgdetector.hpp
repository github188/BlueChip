/*
 * =====================================================================================
 *
 *       Filename:  evifgdetector.hpp
 *
 *    Description:  the interface of foreground detector
 *
 *        Version:  1.0
 *        Created:  2015年03月07日 23时48分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVIFGDETECTOR_H_
#define EVIFGDETECTOR_H_

#include "core/core.hpp"
#include "imgproc/imgproc.hpp"
#include "highgui/highgui.hpp"

using namespace cv;

class EVIFGDetector
{
	public:
		virtual void Process(const Mat& frame,Mat* mask)=0;

};

#endif
