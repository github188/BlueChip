/*
 * =====================================================================================
 *
 *       Filename:  evfindcircle.hpp
 *
 *    Description:  head file of findcircle  
 *
 *        Version:  1.0
 *        Created:  2015年02月16日 01时39分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVFINDCIRCLE_H_
#define _EVFINDCIRCLE_H_

#include "cv.h"
#include "highgui.h"
#include <vector>
#include <map>
using namespace cv;
using namespace std;

class EVFindCircle
{
	public:
		EVFindCircle();
		~EVFindCircle();
		int Find(IplImage* input_img);
		vector<Point> GetCenters();
		vector<int> GetRadius();
	protected:
		void RemoveNoise(IplImage* src);
	private:
		vector<Point> centers;
		vector<int> radius;
};

#endif
