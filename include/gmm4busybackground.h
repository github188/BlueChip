//Copyright(c) 2015 Extreme Vision Ltd. All rights reserved.
//Author: Yun Luo(lauren.luo@extremevision.mo)
//File: gmm4busybackground.h
//This class construct an model to defend busy environment.

#ifndef DEFEND_BACKGROUND_SWITCHING_GMM4BUSYBACKGROUND_H_
#define DEFEND_BACKGROUND_SWITCHING_GMM4BUSYBACKGROUND_H_

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace dbs{

class GMM4BusyBackground{
public:
  GMM4BusyBackground();
  ~GMM4BusyBackground();
  void Process(const cv::Mat& frame,bool display=false);
  cv::Mat GetForeground();
  cv::Mat GetBackground();
  cv::Mat GetBackground2();
protected:
  int Init();
  void Display();
private:
  //use for background.
  cv::Mat background;
  cv::Mat background_gray;
  cv::BackgroundSubtractorMOG2 mog_bg;
  //use for secondary background.
  cv::Mat background2;
  cv::Mat background2_gray;
  cv::BackgroundSubtractorMOG2 mog_bg2;
  //use for foreground
  cv::Mat foreground;
  cv::BackgroundSubtractorMOG2 mog_fg;
  //frame size
  int frame_width;
  int frame_height;
};

} //namespace dbs

#endif //DEFEND_BACKGROUND_SWITCHING_GMM4BUSYBACKGROUND_H_
