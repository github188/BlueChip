/*
 * =====================================================================================
 *
 *       Filename:  evgetgei.hpp
 *
 *    Description:  generate GEI
 *
 *        Version:  1.0
 *        Created:  2015年03月03日 20时26分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVGETGEI_H_
#define EVGETGEI_H_

#include <iostream>
#include <stdio.h>

#include "core/core.hpp"
#include "imgproc/imgproc.hpp"
#include "highgui/highgui.hpp"

#include <vector>

using namespace cv;
using namespace std;

class EVGetGEI
{
	public:
		EVGetGEI();
		/* open a fold with silhouettes */
		explicit EVGetGEI(const char* folderpath);
		~EVGetGEI();
		Mat GenerateGEI(vector<Mat> silhouettes,int height,int width);
	protected:
		int FindContours(Mat image);
		Mat Resize(Mat image,int height,int width);
		Mat CalGei(vector<Mat> silhs);
	private:
		char* gei_name;
		Mat gei; //current gei image
};

#endif
