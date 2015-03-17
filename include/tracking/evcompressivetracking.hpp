/*
 * =====================================================================================
 *
 *       Filename:  evcompressivetracking.hpp
 *
 *    Description:  class of compressive tracking
 *
 *        Version:  1.0
 *        Created:  2015年03月08日 16时00分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVCOMPRESSIVETRACKING_H_
#define EVCOMPRESSIVETRACKING_H_

#include "core/core.hpp"
#include "imgproc/imgproc.hpp"

#include <vector>

using namespace std;
using namespace cv;

class EVCompressiveTracking
{
	public:
		EVCompressiveTracking();
		~EVCompressiveTracking();
private:
	int featureMinNumRect;
	int featureMaxNumRect;
	int featureNum;
    vector<vector<Rect> > features;
    vector<vector<float> > featuresWeight;
	int rOuterPositive;
	vector<Rect> samplePositiveBox;
	vector<Rect> sampleNegativeBox;
	int rSearchWindow;
	Mat imageIntegral;
	Mat samplePositiveFeatureValue;
	Mat sampleNegativeFeatureValue;
	vector<float> muPositive;
	vector<float> sigmaPositive;
	vector<float> muNegative;
	vector<float> sigmaNegative;
	float learnRate;
	vector<Rect> detectBox;
	Mat detectFeatureValue;
	RNG rng;

private:
	void HaarFeature(Rect& _objectBox, int _numFeature);
	void sampleRect(Mat& _image, Rect& _objectBox, float _rInner, float _rOuter, int _maxSampleNum, vector<Rect>& _sampleBox);
	void sampleRect(Mat& _image, Rect& _objectBox, float _srw, vector<Rect>& _sampleBox);
	void getFeatureValue(Mat& _imageIntegral, vector<Rect>& _sampleBox, Mat& _sampleFeatureValue);
	void classifierUpdate(Mat& _sampleFeatureValue, vector<float>& _mu, vector<float>& _sigma, float _learnRate);
	bool radioClassifier(vector<float>& _muPos, vector<float>& _sigmaPos, vector<float>& _muNeg, vector<float>& _sigmaNeg,
						Mat& _sampleFeatureValue, float& _radioMax, int& _radioMaxIndex);
public:
	bool processFrame(Mat& _frame, Rect& _objectBox);
	void init(Mat& _frame, Rect& _objectBox);

}

#endif

