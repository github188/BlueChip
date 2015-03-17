/*
 * =====================================================================================
 *
 *       Filename:  evlda.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月06日 21时46分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVLDA_H_
#define EVLDA_H_

#include "core/core.hpp"
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

class EVLda
{
	public:
		EVLda();
		~EVLda();
		/* @param mat: each row is a sample
		 * @param labels: labels
		 * @param classnum: class numbers */
		void Process(Mat mat,vector<int> labels,int classnum);
		void Process(vector<Mat> mats,vector<int> labels,int classnum);
		/* @return: the number of class which testmat belongs to */
		int Predict(Mat testmat);
	private:
		Mat eivector;
		vector<double> centers;
};

#endif
