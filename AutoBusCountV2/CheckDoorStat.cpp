#include "StdAfx.h"
#include "CheckDoorStat.h"
#include <highgui.h>  
#include <stdio.h>  
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
cv::Mat org,dst,img,tmp;
int axis_x,axis_y;
void on_mouse(int event, int x, int y, int flags, void *ustc)
{
    static Point pre_pt = Point(-1,-1);//初始坐标
    static Point cur_pt = Point(-1,-1);//实时坐标
    char temp[16];
    if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆
    {
        org.copyTo(img);//将原始图片复制到img中
        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = Point(x,y);
        putText(img,temp,pre_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255),1,8);//在窗口上显示坐标
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);//划圆
        imshow("img",img);
    }
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数
    {
        img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));//只是实时显示鼠标移动的坐标
        imshow("img",tmp);
    }
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))//左键按下时，鼠标移动，则在图像上划矩形
    {
        img.copyTo(tmp);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(tmp,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        rectangle(tmp,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//在临时图像上实时显示鼠标拖动时形成的矩形
        imshow("img",tmp);
    }
    else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形
    {
        org.copyTo(img);
        sprintf(temp,"(%d,%d)",x,y);
        cur_pt = Point(x,y);
        putText(img,temp,cur_pt,FONT_HERSHEY_SIMPLEX,0.5,Scalar(0,0,0,255));
        circle(img,pre_pt,2,Scalar(255,0,0,0),CV_FILLED,CV_AA,0);
        rectangle(img,pre_pt,cur_pt,Scalar(0,255,0,0),1,8,0);//根据初始点和结束点，将矩形画到img上
        imshow("img",img);
        img.copyTo(tmp);
        //截取矩形包围的图像，并保存到dst中
        int width = abs(pre_pt.x - cur_pt.x);
        int height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height == 0)
        {
            printf("width == 0 || height == 0");
            return;
        }
        dst = org(Rect(min(cur_pt.x,pre_pt.x),min(cur_pt.y,pre_pt.y),width,height));
        namedWindow("dst");
        imshow("dst",dst);
		imwrite("door.jpg",dst);
        waitKey(0);
    }
	axis_x=min(cur_pt.x,pre_pt.x);
	axis_y=min(cur_pt.y,pre_pt.y);
}

CCheckDoorStat::CCheckDoorStat(void)
{
	
}


CCheckDoorStat::~CCheckDoorStat(void)
{
}

int CCheckDoorStat::GetFileData()
{
	ifstream infile("data/doorflag.dat",ios::in);
	if(!infile)
	{
		return 0;
	}
	infile>>FlagPosition.x;
	infile>>FlagPosition.y;
	infile>>FlagPosition.width;
	infile>>FlagPosition.height;
	infile.close();
	return 1;
}

int CCheckDoorStat::GetFlagPosition(CvRect& rect,IplImage* img2)
{
	Mat mtx(img2,1);
	mtx.copyTo(org);
	namedWindow("FlagPosition");
	imshow("FlagPosition",org);
	org.copyTo(tmp);
	org.copyTo(img);

	setMouseCallback("FlagPosition",on_mouse,0);//调用回调函数
	/*rect.x=axis_x;
	rect.y=axis_y;
	rect.width=dst.cols;
	rect.height=dst.rows;
	FlagPosition=rect;
	if(!SaveResult())
	{
		return 0;
	}*/
	return 1;
}
int CCheckDoorStat::SaveResult()
{
	ofstream outfile("data/doorflag.dat",ios::out);
	if(!outfile)
	{
		return 0;
	}
	outfile<<FlagPosition.x<<" "<<FlagPosition.y<<" "<<FlagPosition.width<<" "<<FlagPosition.height;
	outfile.close();
	return 1;
}
bool CCheckDoorStat::CheckDoorOpen(IplImage* img)
{
	//cvSetImageROI(img,cvRect(50,50,300,300));
	bool open=FindCircles(img);
#ifdef _DEBUG
	img->origin=IPL_ORIGIN_BL;
	cvNamedWindow("img");
	cvShowImage("img",img);
	img->origin=IPL_ORIGIN_TL;
#endif
	cvResetImageROI(img);
	return true;
}
bool CCheckDoorStat::CheckDoorClose(IplImage* img)
{
	cvSetImageROI(img,FlagPosition);
	return false;
}

void CCheckDoorStat::RemoveNoise(IplImage * src)
{
	//get the size of input_image (src)
     CvSize size = cvSize( src->width & -2, src->height & -2 ); 

    //create  temp-image
    IplImage* pyr = cvCreateImage( cvSize(size.width/2, size.height/2), 
                                   src->depth, src->nChannels ); 
    
    cvPyrDown( src, pyr, 7 );			//pyr DOWN
    cvPyrUp( pyr, src, 7 );				//and UP
    cvReleaseImage(&pyr);               //release temp
}
bool CCheckDoorStat::FindCircles(IplImage* input_img)
{
	// DO SOME DECLARARTIONS
 // FOR ALL TYPES "Cv.." LOOK AT OPENCV-DOC !!

        CvMemStorage *storage;
        int header_size, i, count,length, width;
        CvSeq *contour;
        CvBox2D * myBox;
        CvPoint *PointArray;
        CvPoint2D32f *PointArray32f;
        CvPoint myCenter;

// ALLOCATE SOME MEMORY        
        myBox= (CvBox2D *) malloc(sizeof(CvBox2D));
        header_size = sizeof(CvContour);
        storage = cvCreateMemStorage (1000); // For FindContours.


	// ECTRACT WIDTH AND HEIGHT OF THE INPUT-IMAGE

        int w = input_img->width;
        int h = input_img->height;

	// CREATE TEMPORARY IMAGES
	// ONE FOR THE "CANNY" AND ONE FOR PREPROCESSING

	//THIS IS FOR CANNY - 1 CHANNEL (GRAY)
	//SAME SIZE AS INPUT
        IplImage* m_tmp8uC1= cvCreateImage(
                                          cvSize(w ,h ),   
                                          IPL_DEPTH_8U,1); //GRAY

       
        

        //CONVERT THE RESULT TO GRAY
		cvCvtColor(input_img, m_tmp8uC1, CV_RGB2GRAY);
       
		//PREPROCESSING OF YOUR CHOICE
        //HERE WE DO A SIMPLE PYRDOWN/PYRUP TO REMOE NOISE

		RemoveNoise(m_tmp8uC1);

        // NOW THE 1ST "ESSENTIAL" FUNCTION
        // CANNY IS A KIND OF EDGE-DETECTION
        // THE RESULT IS BLACK/WHITE WITH ONLY THE CONTOURS (WHITE)
        cvCanny(m_tmp8uC1, m_tmp8uC1, 0, 255,5 );
   

                // NOW THE 2ND "ESSENTIAL" FUNCTION
                //THIS FUNCTION SEPARATES ALL CONTOURS
                // LOOK AT THE DOC !!!! AGAIN
                cvFindContours (m_tmp8uC1 , storage, &contour,
					  header_size, CV_RETR_EXTERNAL,
					  CV_CHAIN_APPROX_SIMPLE);

                // GO THROUGH ALL CONTOURS
                while(contour!=NULL)
                {
                if(CV_IS_SEQ_CURVE(contour))
                {
                        // HOW MANY POITS HAS THE CONTOUR ??
                        count = contour ->total;
                       
                        //ALLOC MEM
                        PointArray = (CvPoint *)malloc(count * sizeof(CvPoint));
                       
                        //COPY THE POINTS TO A ARRAY
                        cvCvtSeqToArray(contour, PointArray, CV_WHOLE_SEQ);

                        // ALLOC MEM
                        PointArray32f = (CvPoint2D32f *)
							malloc((count + 1) * sizeof(CvPoint2D32f));

                        //CONVERT THE ARRAY TO A 2ND (32FLOAT)
                        // THIS WE NEED FOR cvFitELLIPSE

                        for (i=0; i<count-1; i++)
                        {                              
                                PointArray32f[i].x = (float)(PointArray[i].x);
                                PointArray32f[i].y = (float)(PointArray[i].y);
                        }
                                PointArray32f[i].x = (float)(PointArray[0].x);
                                PointArray32f[i].y = (float)(PointArray[0].y);        

                                //FOR DEBUGGING YOU CAN DRAW THECONTOUR
                                //cvDrawContours(input_img,
								// contour,RGB(0,0,255),RGB(0,255,0),0);

                        //cvFITELLIPSE NEEDS MIN. 6 POINTS
                        // IS IT ?
                        if (count>=7)
                        {
                                //FIND THE BEST FITTING ELLIPSE INTHIS CONTOUR
                                cvFitEllipse(PointArray32f, count,myBox);
                               
                                //ECTRACT THE RESULTS FROM "myBox"
                                //CENTER
                                myCenter.x = (int) myBox->center.x;
                                myCenter.y = (int) myBox->center.y;
                               
                                //HEIGHT AND WITH (THE 2 AXES OF THE ELLIPSE)
                                length  =(int)myBox->size.height;
                                width = (int)myBox->size.width;
                               
                                //AND THE ANGLE
                                float myAngle= myBox->angle;

                                // IS THE ELLIPSE INSIDE THE IMAGE ??
                                if ((myCenter.x>150) && (myCenter.y >150)&&length<30&&width<30&&(myCenter.x < 300) && (myCenter.y <300))
                                {      
                                        //DRAW A CIRCLE
                                        cvCircle(input_img,myCenter,
								(int)length/2 ,cvScalar(0,0,255));
                               
                                        //DRAW THE ELLIPSE
                                       // cvEllipse(input_img,
                                                      /*  myCenter,
                                                        cvSize (
                                                               (int)width/2,
                                                               (int)length/2) ,
                                                               -myBox->angle,
                                                               0,360,cvScalar(0,255,0),1);*/
                                }
                               
                        }
                        free(PointArray32f );
                        free(PointArray );
                }
                // GOT TO THE NEXT CONTOUR (IF ANY)
                contour = contour->h_next;
        }      
        free (contour);
        free (myBox);            
        cvReleaseImage(&m_tmp8uC1);
        cvReleaseMemStorage(&storage);
		return true;
}
double CCheckDoorStat::angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{
	double dx1 = pt1->x - pt0->x;
 double dy1 = pt1->y - pt0->y;
 double dx2 = pt2->x - pt0->x;
 double dy2 = pt2->y - pt0->y;
 return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
void CCheckDoorStat::drawSquares( IplImage* img, CvSeq* squares )
{
	CvSeqReader reader;
 IplImage* cpy = cvCloneImage( img );
 int i;
 cvStartReadSeq( squares, &reader, 0 );
 // read 4 sequence elements at a time (all vertices of a square)
 for( i = 0; i < squares->total; i += 4 )
 {
  CvPoint pt[4], *rect = pt;
  int count = 4;
  // read 4 vertices
  CV_READ_SEQ_ELEM( pt[0], reader );
  CV_READ_SEQ_ELEM( pt[1], reader );
  CV_READ_SEQ_ELEM( pt[2], reader );
  CV_READ_SEQ_ELEM( pt[3], reader );
  // draw the square as a closed polyline
  cvPolyLine( cpy, &rect, &count, 1, 1, CV_RGB(0,255,0), 2, CV_AA, 0 );
 }
 cvShowImage( "square detection demo", cpy );
 cvReleaseImage( &cpy );
}
CvSeq* CCheckDoorStat::FindSquares4( IplImage* img )
{
	int thresh = 50;
IplImage* img =NULL;
IplImage* img0 = NULL;
CvMemStorage* storage =NULL;
	CvSeq* contours;
 int i, c, l, N = 11;
 CvSize sz = cvSize( img->width & -2, img->height & -2 ); 
 
 IplImage* timg = cvCloneImage( img );
 IplImage* gray = cvCreateImage( sz, 8, 1 );
 IplImage* pyr = cvCreateImage( cvSize(sz.width/2, sz.height/2), 8, 3 );
 IplImage* tgray;
 CvSeq* result;
 double s, t;
 // 创建一个空序列用于存储轮廓角点
 CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );
 cvSetImageROI( timg, cvRect( 0, 0, sz.width, sz.height ));
 // 过滤噪音
 cvPyrDown( timg, pyr, 7 );
 cvPyrUp( pyr, timg, 7 );
 tgray = cvCreateImage( sz, 8, 1 );
 // 红绿蓝3色分别尝试提取
 for( c = 0; c < 3; c++ )
 {
  // 提取 the c-th color plane
  cvSetImageCOI( timg, c+1 );
  cvCopy( timg, tgray, 0 );
  // 尝试各种阈值提取得到的（N=11）
  for( l = 0; l < N; l++ )
  {
   // apply Canny. Take the upper threshold from slider
   // Canny helps to catch squares with gradient shading  
   if( l == 0 )
   {
    cvCanny( tgray, gray, 0, thresh, 5 );
    //使用任意结构元素膨胀图像
    cvDilate( gray, gray, 0, 1 );
   }
   else
   {
    // apply threshold if l!=0:
    cvThreshold( tgray, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );
   }
   // 找到所有轮廓并且存储在序列中
   cvFindContours( gray, storage, &contours, sizeof(CvContour),
    CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0) );
   // 遍历找到的每个轮廓contours
   while( contours )
   {
     //用指定精度逼近多边形曲线
    result = cvApproxPoly( contours, sizeof(CvContour), storage,
     CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
                  
    if( result->total == 4 &&
     fabs(cvContourArea(result,CV_WHOLE_SEQ)) > 500 &&
     fabs(cvContourArea(result,CV_WHOLE_SEQ)) < 100000 &&
     cvCheckContourConvexity(result) )
    {
     s = 0;
     for( i = 0; i < 5; i++ )
     {
      // find minimum angle between joint edges (maximum of cosine)
      if( i >= 2 )
      {
       t = fabs(angle(
        (CvPoint*)cvGetSeqElem( result, i ),
        (CvPoint*)cvGetSeqElem( result, i-2 ),
        (CvPoint*)cvGetSeqElem( result, i-1 )));
       s = s > t ? s : t;
      }
     }
     // if 余弦值 足够小，可以认定角度为90度直角
     //cos0.1=83度，能较好的趋近直角
     if( s < 0.1 )  
      for( i = 0; i < 4; i++ )
       cvSeqPush( squares,
       (CvPoint*)cvGetSeqElem( result, i ));
    }
    // 继续查找下一个轮廓
    contours = contours->h_next;
   }
  }
 }
 cvReleaseImage( &gray );
 cvReleaseImage( &pyr );
 cvReleaseImage( &tgray );
 cvReleaseImage( &timg );
 return squares;
}
