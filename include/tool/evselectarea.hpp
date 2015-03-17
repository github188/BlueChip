/*
 * =====================================================================================
 *
 *       Filename:  evselectarea.hpp
 *
 *    Description:  head file of select area
 *
 *        Version:  1.0
 *        Created:  2015年02月15日 12时54分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVSELECTAREA_H_
#define _EVSELECTAREA_H_

#include <iostream>
#include <fstream>

#include "opencv.hpp"
#include "core/core.hpp"
#include "imgproc/imgproc.hpp"
#include "highgui/highgui.hpp"

using namespace cv;

class EVSelectArea
{
	public:
		EVSelectArea();
		~EVSelectArea();
		int Select(Mat original);
		int SaveToFile(const char* file);
};

#endif

