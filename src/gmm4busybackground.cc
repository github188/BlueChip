//Copyright(c) 2015 Extreme Vision Ltd. All rights reserved.
//Author:Yun Luo(lauren.luo@extremevision.mo)
//File: gmm4busybackgrond.cc

#include "gmm4busybackground.h"

namespace dbs{

GMM4BusyBackground::GMM4BusyBackground(){
  frame_width=0;
  frame_height=0;
}

GMM4BusyBackground::~GMM4BusyBackground(){
}

cv::Mat GMM4BusyBackground::GetForeground(){
  return foreground;
}

cv::Mat GMM4BusyBackground::GetBackground(){
  return background;
}

cv::Mat GMM4BusyBackground::GetBackground2(){
  return background2;
}

void GMM4BusyBackground::Process(const cv::Mat& frame, bool display){
  //init frame size.
  if(frame_width==0&&frame_height==0){
    frame_width=frame.cols;
    frame_height=frame.rows;
    Init();
  }
  
  //process.
  mog_bg(frame,background,0.01);
  mog_bg.getBackgroundImage(background);
  mog_bg2(frame,background2,1);  
  mog_bg2.getBackgroundImage(background2);
  
  //frame diff.
  mog_bg.getBackgroundImage(background);
  cv::cvtColor(background,background_gray,CV_BGR2GRAY);
  mog_bg2.getBackgroundImage(background2);
  cv::cvtColor(background2,background2_gray,CV_BGR2GRAY);

  cv::absdiff(background_gray,background2_gray,foreground);
  cv::threshold(foreground,foreground,25,255,cv::THRESH_BINARY);
  cv::erode(foreground,foreground,cv::Mat());
  cv::dilate(foreground,foreground,cv::Mat());

  //display.
  if(display){
    Display();
  }
}

int GMM4BusyBackground::Init(){
  background = cv::Mat(frame_height,frame_width,CV_8UC3);
  background2 = cv::Mat(frame_height,frame_width,CV_8UC3);
  foreground = cv::Mat::zeros(frame_height,frame_width,CV_8UC1);
  background_gray=cv::Mat::zeros(frame_height,frame_width,CV_8UC1);
  background2_gray=cv::Mat::zeros(frame_height,frame_width,CV_8UC1);
  return 1;
}

void GMM4BusyBackground::Display(){
  cv::imshow("background",background);
  cv::imshow("background2",background2);
  cv::imshow("foreground",foreground);
}

} //namespace dbs
