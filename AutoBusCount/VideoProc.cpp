#include "StdAfx.h"
#include "VideoProc.h"

#define V1_5_0

#define EDGE_THRESH 70


CVideoProc::CVideoProc(void)
{
	m_iIn=0;
	m_iOut=0;
	m_iOnboard=0;
	imagegrey=NULL;
	m_bInit=false;
	m_bImage=10;
	m_x=0;	
	m_width=720;
	m_height=100;
	m_rheight=10;
	m_y=288-(int)m_height*0.5;
	rect=cvRect(m_x,m_y,m_width,m_height); //检测区大小
	rect1=cvRect(0,0,m_width,10);
	rect2=cvRect(0,m_height-m_rheight,m_width,m_rheight);
	line=288;
	tmp_Onboard=0;
///////V1.5.0////////////
	m_bIn=false;
	m_bOut=false;
	m_iLineIn=50.0;
	m_iLineOut=526.0;
	m_bLineIn=false;
	m_bLineOut=false;
///////////////////////
	framecnt=0;
	high = 2000;
	low = 1500;
	up=FALSE;
	isup=FALSE;
	isin=FALSE;
	singleflag = FALSE;
	nFrmNum = 0;
	lastrawtime = 0;
    objforori1=0;
	objforori2=0;
	objpix=0;//压线的像素数目
    last_objpix=0;
    lastnFrmNum = 0;
	m_highlow=2500;

}


CVideoProc::~CVideoProc(void)
{
}

int CVideoProc::Init(IplImage* m_image)
{
	image=cvCloneImage(m_image);
	grayframe = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
	imagegrey = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	absdiff_1 = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	absdiff_2 = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	absdiff = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	absthresh = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	absthresh_2 = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	preimagegrey = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
	prepreimagegrey = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
	gray = cvCreateImage(cvSize(720,576),IPL_DEPTH_8U,1);
	edge = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	cvZero(preimagegrey);
	cvZero(prepreimagegrey);
	cvZero(gray);
	return 1;
}
int CVideoProc::Process(IplImage* image)
{	
	/*******初始化*****************/
	if(!m_bInit)
	{
		if(Init(image))
		{
			m_bInit=true;
			return 1;
		}
		return 0;
	}
	/*******背景建模*****************/
	fgdetector.Process(image);
//	//cvRectangle(grayframe,cvPoint(0,0),cvPoint(50,50),CV_RGB(255,0,0),1,CV_AA,0);
	grayframe = fgdetector.GetMask();	
//#ifdef DEBUG
//grayframe->origin=IPL_ORIGIN_BL;
//	cvNamedWindow("grayframe");
//	cvShowImage("grayframe",grayframe);
//grayframe->origin=IPL_ORIGIN_TL;
//#endif
	/******帧差********************/
	cvCvtColor(image,imagegrey, CV_BGR2GRAY);////当前帧->frame[0]
	cvAbsDiff(imagegrey, preimagegrey, absdiff); 
	//cvAbsDiff(preimagegrey, prepreimagegrey, absdiff_2); 
	//cvAdd(absdiff_1,absdiff_2,absdiff);
	cvThreshold(absdiff, absthresh, 20, 255.0, CV_THRESH_BINARY);//二值化前景图
	cvErode(absthresh, absthresh, 0, 1);	
	cvDilate(absthresh, absthresh, 0, 1);
#ifdef DEBUG
	absthresh->origin=IPL_ORIGIN_BL;
	cvNamedWindow("absthresh");
	cvShowImage("absthresh",absthresh);
	absthresh->origin=IPL_ORIGIN_TL;
#endif
	cvCopy(preimagegrey,prepreimagegrey);	
	cvCopy(imagegrey,preimagegrey);	
	/**头发检测 轮廓投影 - 滤波 -  填充 *********************************************************************************/	
	if(m_bImage>0) 
	{
		m_bImage--;
		return 0;
	}
	int p = CalHist(absthresh);//返回区域个数

	if((destination[0].y+destination[0].height > 80 )&&(destination[0].height>40))
	{
		//DrawRect(absthresh,destination[0],CV_RGB(255,255,255));
		//DrawRect(image,destination[0],CV_RGB(0,255,0));
	}
	if((p>1)&&(destination[1].height>40)) //说明两个人连续上车
	{
		//DrawRect(absthresh,destination[1],CV_RGB(255,255,255));
		//DrawRect(image,destination[1],CV_RGB(0,255,0));
		destination[0]=destination[1];
	}	
#ifdef DEBUG
	image->origin = IPL_ORIGIN_BL;
	cvNamedWindow("image");
	cvShowImage("image",image);
	image->origin = IPL_ORIGIN_TL;
#endif
	/*****************边缘***********************************************************/
//#ifdef DEBUG
//	//cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);
	cvSmooth( absthresh, edge, CV_BLUR, 3, 3, 0, 0 );//滤波函数，在这里貌似不起作用，因为产生的结果被下面的函数产生的结果覆盖
	cvNot( absthresh, edge );//按位取反函数，在这里貌似不起作用，因为产生的结果被下面的函数产生的结果覆盖
    cvCanny(absthresh, edge, EDGE_THRESH, EDGE_THRESH*3, 3);//边缘检测
//	//cvRectangle(edge,cvPoint(m_x,m_y),cvPoint(m_x+m_width,m_y+m_height),CV_RGB(255,0,0),1,CV_AA,0);
////	edge->origin = IPL_ORIGIN_BL;
////	DrawPicToHDC(edge, IDC_STATIC_PIC3,1);	
////	edge->origin = IPL_ORIGIN_TL;		
//#endif
	/************************方向检测***********************************************************/
	CvMemStorage *pStorage = NULL;    
	pStorage = cvCreateMemStorage(0);   
	CvSeq *pConInner = NULL;  
	CvSeq *pContour = NULL;     
	cvFindContours(absthresh,pStorage,&pContour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cvZero(absthresh);
	cvDrawContours(absthresh, pContour, CV_RGB(255, 255, 255), CV_RGB(255, 255, 255), 2, CV_FILLED, 8, cvPoint(0, 0));    
	//nFrmNum++;
	//设定检测框
	//cvSetImageROI(image,rect);	
	//cvCvtColor(image, gray, CV_BGR2GRAY);//背景检测直接用temp,改一下
	//cvThreshold(gray, gray, 75, 255, CV_THRESH_BINARY_INV);
	Findcontour(absthresh,gray,destination[0]);
	gray=cvCloneImage(absthresh);
	cvSetImageROI(gray,rect);	
#ifdef DEBUG
	gray->origin = IPL_ORIGIN_BL;
	cvNamedWindow("gray");
	cvShowImage("gray",gray);
	gray->origin = IPL_ORIGIN_TL;
#endif
	last_objpix=objpix;
	if(up==TRUE) isup=TRUE;
	else isup=FALSE;
	
	objpix=cvCountNonZero(gray);
	if(nFrmNum==0)
	{
		low=objpix;
		high=objpix;
		nFrmNum++;
	}
	if (objpix-last_objpix>=0)
		up=TRUE;
	else up=FALSE;
	if (isup==FALSE&&up==TRUE&&objpix<low&&!isin)// 进来的话，low不再更新,否则，
		//low是最小极小值
	{	
		low=objpix;
		//cout<<objpix<<","<<nFrmNum<<endl;
	}

	if(objpix-low>m_highlow && !isin && up )//上升阶段才可能进入
	{
		isin=TRUE;//进来就不管up或down了，不断更新high保证最大峰值，并探测下降程度
		cvSetImageROI(gray,rect1);
		objforori1=cvCountNonZero(gray);
		cvResetImageROI(gray);
		cvSetImageROI(gray,rect2);
		objforori2=cvCountNonZero(gray);
		cvResetImageROI(gray);
		high=objpix;
	}
	if (isup==FALSE&&up==TRUE&&isin)
	{	
		low=objpix;
	}
	if(isin&&isup&&!up)//进来没出去时，就要保证high为最大极大值
	{
		high=(high>objpix?high:objpix);
	}
	if(high-objpix>m_highlow && isin&&destination[0].width>50)//出去
	{
		isin=FALSE;
		cvSetImageROI(gray,rect1);
		objforori1-=cvCountNonZero(gray);
		cvResetImageROI(gray);
		cvSetImageROI(gray,rect2);
		objforori2=cvCountNonZero(gray)-objforori2;
		cvResetImageROI(gray);
		if(objforori2+objforori1>0)
		{	
#ifdef V1_4_0
			m_iIn++;
			Beep(440,25);
			return 1;
#endif
#ifdef V1_5_0
			m_bIn=true;
#endif
		}
		else 
		{	
#ifdef V1_4_0
			m_iOut++;
			Beep(440,25);
			return 2;
#endif
#ifdef V1_5_0
			m_bOut=true;
#endif
		}
	}
#ifdef V1_5_0
	if(((float)destination[0].y+(destination[0].height*0.5)-m_iLineIn)*((float)predestination[0].y+(predestination[0].height*0.5)-m_iLineIn)<0.00f)	
	{
		if(((float)destination[0].y+(destination[0].height*0.5)-m_iLineIn)<0.00f)
		{
			m_bLineIn=true;
			if(m_bIn)
			{
				m_iIn++;
				m_bLineIn=false;
				m_bIn=false;
				Beep(440,250);
				return 1;
			}
		}
	}	
	if(((float)destination[0].y+(destination[0].height*0.5)-m_iLineOut)*((float)predestination[0].y+(predestination[0].height*0.5)-m_iLineOut)<0.00f)	
	{
		if(((float)destination[0].y+(destination[0].height*0.5)-m_iLineOut)>0.00f)
		{
			m_bLineOut=true;
			if(m_bOut)
			{
				m_iOut++;
				m_bLineOut=false;
				m_bOut=false;
				Beep(440,25);
				return 2;
			}
		}
	}	
	predestination[0]=destination[0];
#endif
	return 0;
}
/************************************************************************/
/* 在原有二值图的基础上找出 边缘轮廓 要预测     直接将预测的结果显示出来

这里应该有一个修正 边缘的操作 尽可能多地去掉背景*/
/************************************************************************/
void CVideoProc::Findcontour(IplImage *gray,IplImage *mask,CvRect rect)
{
	CvPoint leftpoint[700],rightpoint[700];//,toppoint[700],bottompoint[700];
	int i,j,leftcnt,rightcnt;//,topcnt,bottomcnt;
	BYTE *tempchar;

	//==========left edge=======================================================
	leftcnt=0;
	for(i=rect.y+rect.height-1 ; i >=rect.y;i--) 
	{
		for(j=rect.x;j<rect.x+rect.width;j++)
		{
			tempchar = ((uchar*)(mask->imageData + mask->widthStep*i));
			if(tempchar[j]) 
			{
				leftpoint[leftcnt].x = j;
				leftpoint[leftcnt++].y = i;
				break;
			}
		}
		if(j==rect.x+rect.width)// 未找到点就是说断层了 
		{
			leftpoint[leftcnt].x=leftpoint[leftcnt-1].x;
			leftpoint[leftcnt].y=i;
			leftcnt++;
		}
	}
	//=============right edge=====================================================

	rightcnt=0;
	for(i=rect.y+rect.height-1 ; i > rect.y;i--) 
	{	
		for(j=rect.x+rect.width-1; j >=rect.x;j--)
		{
			tempchar = ((uchar*)(mask->imageData + mask->widthStep*i));
			if(tempchar[j]) 
			{
				rightpoint[rightcnt].x=j;
				rightpoint[rightcnt++].y=i;
				break;
			}
		}
		if(j==rect.x-1)// 未找到点 就是说断层了 
		{
			rightpoint[rightcnt].x=rightpoint[rightcnt-1].x;
			rightpoint[rightcnt].y=i;
			rightcnt++;
		}
	}

	/**************filling  contour**********************/
	for(i=0;i<rightcnt;i++)//y 连续的
		cvLine(mask,leftpoint[i],rightpoint[i],cvScalar(255,255,255,0),1,8,0);
}
/************************************************************************
找出直方图中的片断 不为零的
标准是 两端连续10个为0  
thresh 存储的是histbin 的下标  临时函数将 线段处理了 

int flag : 0-x  1-y              Y 方向上的合并力度可以加大

找出所有段中最长的一段  

************************************************************************/
int CVideoProc::FindSegmentx(int *histdat, int length, int *thresh0, int *thresh1)
{
	int i,j,x0,x1,k;
	int temp1[640],temp0[640];

	x0=0;
	x1=0;
	int totalpix=0,temptotal=0;
	for(i=0;i<length;i++)
		totalpix+=histdat[i];

	//寻找起始段和终止段
	if(histdat[0]!=0) temp0[x0++]=0; //第一点特例 
	for(i=1;i<length;i++)
	{
		if((histdat[i-1]==0)&&(histdat[i]!=0)) temp0[x0++]=i;
		if((histdat[i-1]!=0)&&(histdat[i]==0)) temp1[x1++]=i;
	}
	if(histdat[length-1]!=0) temp1[x1++]=i; //最后一点特例 

	
	//对段 _--_ 进行预处理  反复处理不然就只处理了一次
	while(1)
	{
		k=0;
		for(i=0;i<x0;i++)   
		{
			//temptotal=0;
			//for(j=temp0[i];j<temp1[i];j++)		temptotal+=histdat[j];||(temptotal*10<totalpix)

			if(temp1[i]-temp0[i]<10)//去掉这个段
			{
				for(j=i;j<x0-1;j++)
				{
					temp1[j]=temp1[j+1];
					temp0[j]=temp0[j+1];
				}
				x0--;
				x1--;
				k++;
			}
		}
		if(k==0)  break; //说明没有可以合并的了 
	}
	//修正--------------__----------------这种情况 合并
	while(1)
	{
		k=0;
		for(i=0;i<x0-1;i++) 
		{
			if(temp0[i+1]-temp1[i]<5) //合并
			{
				for(j=i;j<x0-1;j++)
				{
					temp1[j]=temp1[j+1];
					if(j+2<x0) temp0[j+1]=temp0[j+2];
				}
				x0--;
				x1--;
				k++;
			}
		}
		if(k==0)  break; //说明没有可以合并的了 
	}

	j=0;
	for(i=0;i<x0;i++)
	{
		if(temp1[i]!=0)
		{
			thresh0[j]=temp0[i];
			thresh1[j]=temp1[i];
			j++;
		}
	}
	return j;
}

/************************************************************************/
/* 分别在小，y方向作直方图 求出目标的区域  椭圆或者矩形   
对二值图像进行处理  0  -  255              */
/************************************************************************/

int CVideoProc::CalHist(IplImage* src)
{
	int i,j,k,p,x,numx,numy,m,n;
	int histx[720],histy[720];
	BYTE *temp_label;
	int threshx0[720],threshx1[720];
	int threshy0[720],threshy1[720];

/*	threshx0 = new int(image->width);
	threshx1 = new int(image->width);
	threshy0 = new int(image->height);
	threshy1 = new int(image->height);
*/
	IplImage *pimg = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1); 
//	cvNamedWindow("hdimxy",1);
	for(i=0;i<src->width;i++) histx[i]=0;
	for(i=0;i<src->height;i++) histy[i]=0;//////

	for(i=0;i<src->height;i++)
		for(j=0;j<src->width;j++)
		{
			temp_label = ((BYTE*)(src->imageData + src->widthStep*i));
			p=temp_label[j];
			if(p) 
			{
				histx[j]++;
			}
		}
	for(j=0;j<src->width;j++) 
	{
		if(histx[j]<3)  
			histx[j]=0;
	}

	//对X直方图进行预处理 得到片断
 	numx=FindSegmentx((int *)histx,src->width,(int *)threshx0,(int *)threshx1);
	p = 0;
	k=0; //初始值
	if(numx>1) 
	{
		for(i=0;i<numx;i++)
			for(j=threshx0[i];j<threshx1[i];j++)
			{
				if(p < threshx1[i]-threshx0[i])
				{
					p = threshx1[i]-threshx0[i];
					k = i;
				}
			}
	}

	//分别将x片断投影到Y轴 计算各自直方图 并重新获取段信息clock();
	
	//for(k=0;k<numx;k++)
	//k=0;
	m=0;
	{
		for(i=0;i<240;i++) histy[i]=0;
		for(i=0;i<src->height;i++)
			for(j=threshx0[k];j<threshx1[k];j++)
			{
				temp_label = ((BYTE*)(src->imageData + src->widthStep*i));
				p=temp_label[j];
				if(p) 
				{
					histy[i]++;
				}
			}
/*
		for( i = 0;i < (pimg->height);i++)
		{
			for ( j = 0;j < (pimg->width);j++)
			{
				cvSet2D(pimg,i,j,cvScalar(255, 255, 255));
			}
		}
	 
		 for(x=0;x<pimg->width;x+=10) //原始数据
			cvCircle(pimg,cvPoint(x,src->height-3),1,cvScalar(190,190,190),1,1,0);
*/
   		numy=FindSegmenty((int *)histy,src->height,(int *)threshy0,(int *)threshy1);
		//if(numy>1) //说明两个人连续上车
		if(numy>1) numy=2;
		for(n=0;n<numy;n++)
		{
			destination[n].x      = threshx0[k];
			destination[n].width  = threshx1[k]-threshx0[k];
			destination[n].y      = threshy0[n];
			destination[n].height = threshy1[n]-threshy0[n];
		}
	}
	/*
	delete(threshx0);
	delete(threshx1);
	delete(threshy0);
	delete(threshy1);*/
	cvReleaseImage(&pimg);
 	return m;
}
/************************************************************************
找出直方图中的片断 不为零的
标准是 两端连续10个为0  
thresh 存储的是histbin 的下标
  临时函数将 线段处理了 
       ,int flag : 0-x  1-y              Y 方向上的合并力度可以加大 
************************************************************************/
int CVideoProc::FindSegmenty(int *histdat, int length, int *thresh0, int *thresh1)
{
	int i,j,k,x0,x1;
	int temp1[240],temp0[240];

	x0=0;
	x1=0;
	int totalpix=0,temptotal=0;
	for(i=0;i<length;i++)
		totalpix+=histdat[i];

	//寻找起始段和终止段
	if(histdat[0]!=0) temp0[x0++]=0; //第一点特例 
	for(i=1;i<length;i++)
	{
		if((histdat[i-1]==0)&&(histdat[i]!=0)) temp0[x0++]=i;
		if((histdat[i-1]!=0)&&(histdat[i]==0)) temp1[x1++]=i;
	}
	if(histdat[length-1]!=0) temp1[x1++]=i; //最后一点特例 

	
	//对段 _--_ 进行预处理  反复处理不然就只处理了一次
	while(1)
	{
		k=0;
		for(i=0;i<x0;i++)   
		{
			temptotal=0;
			for(j=temp0[i];j<temp1[i];j++)		temptotal+=histdat[j];

			if((temp1[i]-temp0[i]<10)||(temptotal*10<totalpix))//去掉这个段
			{
				for(j=i;j<x0-1;j++)
				{
					temp1[j]=temp1[j+1];
					temp0[j]=temp0[j+1];
				}
				x0--;
				x1--;
				k++;
			}
		}
		if(k==0)  break; //说明没有可以合并的乐 
	}
	//修正--------------__----------------这种情况 合并
	while(1)
	{
		k=0;
		for(i=0;i<x0-1;i++) 
		{
			if(temp0[i+1]-temp1[i]<20) //合并
			{
				for(j=i;j<x0-1;j++)
				{
					temp1[j]=temp1[j+1];
					if(j+2<x0) temp0[j+1]=temp0[j+2];
				}
				x0--;
				x1--;
				k++;
			}
		}
		if(k==0)  break; //说明没有可以合并的乐 
	}

	//重新赋值给 destination[] 变量
	j=0;
	for(i=0;i<x0;i++)
	{
		if(temp1[i]!=0)
		{
			thresh0[j]=temp0[i];
			thresh1[j]=temp1[i];
			j++;
		}
	}
	return j;
}
void CVideoProc::DrawRect(IplImage *img, CvRect rect,CvScalar cvbgr)
{
	
	cvLine(img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y),cvbgr,3,8,0);
	cvLine(img,cvPoint(rect.x+rect.width,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),cvbgr,3,8,0);
	cvLine(img,cvPoint(rect.x+rect.width,rect.y+rect.height),cvPoint(rect.x,rect.y+rect.height),cvbgr,3,8,0);
	cvLine(img,cvPoint(rect.x,rect.y+rect.height),cvPoint(rect.x,rect.y),cvbgr,3,8,0);
}

void CVideoProc::Zero()
{
	m_iIn=0;
	m_iOut=0;
	m_iOnboard=0;
}
