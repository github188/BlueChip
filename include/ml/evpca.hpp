/*
 * =====================================================================================
 *
 *       Filename:  evpca.hpp
 *
 *    Description:  class of pca training
 *
 *        Version:  1.0
 *        Created:  2015年03月06日 20时40分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVPCA_H_
#define EVPCA_H_

#include "core/core.hpp"
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"

#include <vector>

using namespace cv;
using namespace std;

class EVPca
{
	public:
		EVPca();
		~EVPca();
		/* @param imgs: imgs with the same size
		 * @param principal_compent: number of principal compents */
		Mat Process(vector<Mat> imgs,int principal_compent);
		/* before using this function,use Process() first */
		Mat Project(Mat sample);
	private:
		PCA pca;
		bool flag;
};


#endif

