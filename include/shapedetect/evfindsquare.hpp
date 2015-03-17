/*
 * =====================================================================================
 *
 *       Filename:  evfindsquare.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年02月16日 02时51分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */
#include "cv.h"
#include "highgui.h"

class EVFindSquare
{
	public:
		EVFindSquare();
		~EVFindSquare();
		CvSeq* Find(IplImage* img,CvMemStorage* storage);
		void DrawSquare(IplImage* img,CvSeq* squares);
	protected:
		double angle(CvPoint* pt1,CvPoint* pt2,CvPoint* pt0);
		

};
