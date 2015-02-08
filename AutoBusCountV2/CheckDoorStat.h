#pragma once
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;
using namespace cv;
class CCheckDoorStat
{
public:
	CCheckDoorStat(void);
	~CCheckDoorStat(void);
	int GetFileData();
	int GetFlagPosition(CvRect& retct,IplImage* img2);
	int SaveResult();
	bool CheckDoorOpen(IplImage* img);
	bool CheckDoorClose(IplImage* img);
protected:
	CvSeq* FindSquares4( IplImage* img );
	double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 );
	void drawSquares( IplImage* img, CvSeq* squares );
	bool FindCircles(IplImage* input_img);
	void RemoveNoise(IplImage * src);
private:
	CvRect FlagPosition;

};

