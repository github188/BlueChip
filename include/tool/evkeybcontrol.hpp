/*
 * =====================================================================================
 *
 *       Filename:  evkeybcontrol.hpp
 *
 *    Description:  class of key board control
 *
 *        Version:  1.0
 *        Created:  2015年02月18日 04时45分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVKEYBCONTROL_H_
#define _EVKEYBCONTROL_H_

#include "core/core.hpp"
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"

using namespace cv;

class EVKeyBControl
{
	public:
		EVKeyBControl();
		~EVKeyBControl();
		int Control(Point& nw,Mat img);

};

#endif

