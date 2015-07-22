//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#include "video_proc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <math.h>

typedef unsigned char BYTE;

CVideoProc::CVideoProc(){
        //init params
    	m_bInit=false;
    	m_bImage=10;
    	framecnt=0;
    	high = 2000;
    	low = 1500;
    	up=FALSE;
    	isup=FALSE;
    	isin=FALSE;
    	singleflag = FALSE;
    	nFrmNum = 0;
    	objpix=0;
        last_objpix=0;
        lastnFrmNum = 0;
    	m_highlow=2500;
    	objforori1=0;
    	objforori2=0;
        m_menxian=75;
        //direction
        in = false;
        conCount = new ConCount();
        conGPS = new CConGPS();
        conGPS->Init();

        conSenddata=new CConSendData();
        passager=0;
        send=false;
        des=new char[64];
        dep=new char[64];
        dep="";
}

CVideoProc::~CVideoProc(){
       
}

int CVideoProc::Init(IplImage* m_image){
    	image=cvCreateImage(cvSize(m_image->width,m_image->height),IPL_DEPTH_8U,1);
    	gray=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
    	cvZero(gray);
    	imagegrey=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
    	preimagegrey=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
    	absdiff=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
    	absthresh=cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U,1);
    	/* init variables */
        m_x = 220;
    	//m_width=image->width-2*m_x;
        m_width=250;
    	m_height=100;
    	//m_y=(int)(0.5*image->height-0.5*m_height);
        m_y=250;
    	rect=cvRect(m_x,m_y,m_width,m_height);
    	rect1=cvRect(m_x,m_y,m_width,10);
    	rect2=cvRect(m_x,m_y+m_height-10,m_width,10);
        return 1;
}

int CVideoProc::CheckStatus(){
    int k=conGPS->ShowLocation();
    switch(k){
            case 0:return 0;
            case 1:return 0;
            case 2:
                   {
//                           if(send){
//                                   send=false;
//                                   //end time.
//                                   conGPS->CompareLocation(&des);
//                                   conSenddata->SendArriveSignal(des);
//                                   //send data.
//                                  conSenddata->GetData(passager);
//                                   passager=0;

//                           }
//                           //begin time
//                           dep=des;
//                           conSenddata->SendLeaveSignal(dep);
                           return 1;
                           //break;
                   }
            case 3:
                   {
//                           if(send){
//                               send=false;
//                               //begin time.
//                               conGPS->CompareLocation(&dep);
//                               conSenddata->SendLeaveSignal(dep);
//                           }
                            return 1;
                           //break;
                   }
            case 4:
                   {
//                           if(!send){
//                               send=true;
//                               //end time.
//                               conGPS->CompareLocation(&des);
//                               conSenddata->SendArriveSignal(des);
//                               //send data.
//                               conSenddata->GetData(passager);
//                               passager=0;
//                           }
                           return 1;
                   }
    }
}

/* **********************************************************************************
 * rect:                 inside(onboard)                                            *
 *  ___________________________|________________________________________            *
 * |////////////////////////////////////////////////////////////////////| -->rect1  *
 * |____________________________________________________________________|           *
 * |                                                                    |           *
 * |                                                                    |           *
 * |____________________________________________________________________|           *
 * |////////////////////////////////////////////////////////////////////| -->rect2  *
 * |____________________________________________________________________|           *
 *                            outside                                               *
 * **********************************************************************************/
int CVideoProc::Process(const Mat frame){
    /************************* check location ****************************/
    if(!CheckStatus()){
        return 0;
    }else{
        std::cout<<"gps reach.."<<std::endl;
        return 1;
    }
    /*************************check location end *************************/


    	IplImage image_tmp = (IplImage)(frame);
    	image = &image_tmp;

    	/************************** Init *****************************/
        if(!m_bInit){
            if(Init(image)){
                    m_bInit=true;
                    return 1;
            }
            return 0;
        }

        /****************** foreground detection **********************/
        //cvCvtColor(image,imagegrey,CV_BGR2GRAY); //For rgb frame use
    	cvCopy(image,imagegrey); //For gray frame use
        cvAbsDiff(imagegrey,preimagegrey,absdiff);
        cvThreshold(absdiff,absthresh,20,255.0,CV_THRESH_BINARY);
        cvErode(absthresh,absthresh,0,1);
        cvDilate(absthresh,absthresh,0,1);
        cvErode(absthresh,absthresh,0,1);
        cvCopy(imagegrey,preimagegrey);

        if(m_bImage>0){
            m_bImage--;
            return 0;
        }
	
        /***************** return number of area **********************/
/*        int p = CalHist(absthresh);

        if((destination[0].y+destination[0].height>80)&&(destination[0].height>40)){
            DrawRect(absthresh,destination[0],CV_RGB(255,255,255));
            DrawRect(image,destination[0],CV_RGB(0,255,0));
        }
        if((p>1)&&(destination[1].height>40)){ //two people
            DrawRect(absthresh,destination[1],CV_RGB(255,255,255));
            DrawRect(image,destination[1],CV_RGB(0,255,0));
        }
        //cvLine(absthresh,cvPoint(15,15),cvPoint(250,250),CV_RGB(255,255,255),3,8,0); //test line
        //cvShowImage("image",absthresh);

*/    	/************************ direction ***************************/

        if((rect.x+rect.width)>image->width||(rect.y+rect.height)>image->height){
            cout<<"(!)--rect is out of the image--"<<endl;
        }

    	cvSetImageROI(image,rect);
        cvSetImageROI(gray,rect);
        //cvCvtColor(image,gray,CV_BGR2GRAY); //for rgb use
        //cvCopy(image,gray); //for gray use
        cvThreshold(image,gray,m_menxian,255,CV_THRESH_BINARY_INV);
        //	cvShowImage("gray",gray);

        cvResetImageROI(gray);
        //cvShowImage("gray_rest",gray);
  
    	last_objpix=objpix;
    	if(up==TRUE){
        	isup=TRUE;
    	}
        else{
        	isup=FALSE;
        }

    	objpix=cvCountNonZero(gray);

    	if(nFrmNum==0){
        	low=objpix;
        	high=objpix;
            nFrmNum++;
    	}

    	if(objpix-last_objpix>=0)
        	up=TRUE;
    	else
            	up=FALSE;
    	if (isup==FALSE&&up==TRUE&&objpix<low&&!isin){
        	low=objpix;
    	}

    	if(objpix-low>m_highlow && !isin && up ){
        	isin=TRUE;
        	cvSetImageROI(gray,rect1);
        	objforori1=cvCountNonZero(gray);
        	cvResetImageROI(gray);
        	cvSetImageROI(gray,rect2);
        	objforori2=cvCountNonZero(gray);
        	cvResetImageROI(gray);
        	high=objpix;
    	}
    	if (isup==FALSE&&up==TRUE&&isin){
        	low=objpix;
    	}
    	if(isin&&isup&&!up){
        	high=(high>objpix?high:objpix);
    	}
    	if(high-objpix>m_highlow && isin){
        	isin=FALSE;
        	cvSetImageROI(gray,rect1);
        	objforori1-=cvCountNonZero(gray);
        	cvResetImageROI(gray);
        	cvSetImageROI(gray,rect2);
        	objforori2=cvCountNonZero(gray)-objforori2;
        	cvResetImageROI(gray);
            if(objforori2+objforori1<0){
                	in = true;
					printf("in\n");
			//conCount->CountProcess(in);
                	return 1;
        	}else if(objforori2+objforori1>0){
                	in = false;
					printf("out\n");
					
			//conCount->CountProcess(in);
                	return 1;
        	}
    	}

    	return 1;

}

void CVideoProc::Findcontour(IplImage *gray,IplImage *mask,CvRect rect){
        CvPoint leftpoint[720],rightpoint[720];//,toppoint[700],bottompoint[700];
        int i,j,leftcnt,rightcnt;//,topcnt,bottomcnt;
        BYTE *tempchar;

        //==========left edge=======================================================
        leftcnt=0;
        for(i=rect.y+rect.height-1 ; i >=rect.y;i--){
            for(j=rect.x;j<rect.x+rect.width;j++){
                tempchar = ((uchar*)(mask->imageData + mask->widthStep*i));
                if(tempchar[j]){
                    leftpoint[leftcnt].x = j;
                    leftpoint[leftcnt++].y = i;
                    break;
                }
            }
            if(j==rect.x+rect.width){
                leftpoint[leftcnt].x=leftpoint[leftcnt-1].x;
                leftpoint[leftcnt].y=i;
                leftcnt++;
            }
        }
        //=============right edge=====================================================

        rightcnt=0;
        for(i=rect.y+rect.height-1 ; i > rect.y;i--){
            for(j=rect.x+rect.width-1; j >=rect.x;j--){
                tempchar = ((uchar*)(mask->imageData + mask->widthStep*i));
                if(tempchar[j]){
                    rightpoint[rightcnt].x=j;
                    rightpoint[rightcnt++].y=i;
                    break;
                }
            }
            if(j==rect.x-1){
                rightpoint[rightcnt].x=rightpoint[rightcnt-1].x;
                rightpoint[rightcnt].y=i;
                rightcnt++;
            }
        }

        /**************filling  contour**********************/
        for(i=0;i<rightcnt;i++)
            cvLine(mask,leftpoint[i],rightpoint[i],cvScalar(255,255,255,0),1,8,0);
}
int CVideoProc::FindSegmentx(int *histdat, int length, int *thresh0, int *thresh1){
        int i,j,x0,x1,k;
        int temp1[720],temp0[720];

        x0=0;
        x1=0;
        int totalpix=0/*,temptotal=0*/;
        for(i=0;i<length;i++)
            totalpix+=histdat[i];


        if(histdat[0]!=0) temp0[x0++]=0;
        for(i=1;i<length;i++){
            if((histdat[i-1]==0)&&(histdat[i]!=0)) temp0[x0++]=i;
            if((histdat[i-1]!=0)&&(histdat[i]==0)) temp1[x1++]=i;
        }
        if(histdat[length-1]!=0) temp1[x1++]=i;

        while(1){
            k=0;
            for(i=0;i<x0;i++){
                //temptotal=0;
                //for(j=temp0[i];j<temp1[i];j++)		temptotal+=histdat[j];||(temptotal*10<totalpix)

                if(temp1[i]-temp0[i]<10){
                    for(j=i;j<x0-1;j++){
                        temp1[j]=temp1[j+1];
                        temp0[j]=temp0[j+1];
                    }
                    x0--;
                    x1--;
                    k++;
                }
            }
            if(k==0)  break;
        }

        while(1){
            k=0;
            for(i=0;i<x0-1;i++){
                if(temp0[i+1]-temp1[i]<5){
                    for(j=i;j<x0-1;j++){
                        temp1[j]=temp1[j+1];
                        if(j+2<x0) temp0[j+1]=temp0[j+2];
                    }
                    x0--;
                    x1--;
                    k++;
                }
            }
            if(k==0)  break;
        }

        j=0;
        for(i=0;i<x0;i++){
            if(temp1[i]!=0){
                thresh0[j]=temp0[i];
                thresh1[j]=temp1[i];
                j++;
            }
        }
        return j;
}

int CVideoProc::CalHist(IplImage* src){
        int i,j,k,p/*,x*/,numx,numy,m,n;
        int histx[480],histy[720];
        BYTE *temp_label;
        int threshx0[480],threshx1[480];
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
            for(j=0;j<src->width;j++){
                temp_label = ((BYTE*)(src->imageData + src->widthStep*i));
                p=temp_label[j];
                if(p){
                    histx[j]++;
                }
            }
        for(j=0;j<src->width;j++){
            if(histx[j]<3)
                histx[j]=0;
        }

        numx=FindSegmentx((int *)histx,src->width,(int *)threshx0,(int *)threshx1);
        p = 0;
        k=0;
        if(numx>1){
            for(i=0;i<numx;i++)
                for(j=threshx0[i];j<threshx1[i];j++){
                    if(p < threshx1[i]-threshx0[i]){
                        p = threshx1[i]-threshx0[i];
                        k = i;
                    }
                }
        }

        //for(k=0;k<numx;k++)
        //k=0;
        m=0;
        {
            for(i=0;i<720;i++) histy[i]=0;
            for(i=0;i<src->height;i++){
                for(j=threshx0[k];j<threshx1[k];j++){
                    temp_label = ((BYTE*)(src->imageData + src->widthStep*i));
                    p=temp_label[j];
                    if(p){

                        histy[i]++;
                    }
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

             for(x=0;x<pimg->width;x+=10)
                cvCircle(pimg,cvPoint(x,src->height-3),1,cvScalar(190,190,190),1,1,0);
    */
            numy=FindSegmenty((int *)histy,src->height,(int *)threshy0,(int *)threshy1);
            //if(numy>1)
            if(numy>1) numy=2;
            for(n=0;n<numy;n++){
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

int CVideoProc::FindSegmenty(int *histdat, int length, int *thresh0, int *thresh1){
        int i,j,k,x0,x1;
        int temp1[480],temp0[480];

        x0=0;
        x1=0;
        int totalpix=0,temptotal=0;
        for(i=0;i<length;i++)
            totalpix+=histdat[i];

        if(histdat[0]!=0) temp0[x0++]=0;
        for(i=1;i<length;i++){
            if((histdat[i-1]==0)&&(histdat[i]!=0)) temp0[x0++]=i;
            if((histdat[i-1]!=0)&&(histdat[i]==0)) temp1[x1++]=i;
        }
        if(histdat[length-1]!=0) temp1[x1++]=i;

        while(1){
            k=0;
            for(i=0;i<x0;i++){
                temptotal=0;
                for(j=temp0[i];j<temp1[i];j++)
                    temptotal+=histdat[j];

                if((temp1[i]-temp0[i]<10)||(temptotal*10<totalpix)){
                    for(j=i;j<x0-1;j++){
                        temp1[j]=temp1[j+1];
                        temp0[j]=temp0[j+1];
                    }
                    x0--;
                    x1--;
                    k++;
                }
            }
            if(k==0)  break;
        }

        while(1){
            k=0;
            for(i=0;i<x0-1;i++){
                if(temp0[i+1]-temp1[i]<20){
                    for(j=i;j<x0-1;j++){
                        temp1[j]=temp1[j+1];
                        if(j+2<x0) temp0[j+1]=temp0[j+2];
                    }
                    x0--;
                    x1--;
                    k++;
                }
            }
            if(k==0)  break;
        }

        j=0;
        for(i=0;i<x0;i++){
            if(temp1[i]!=0){
                thresh0[j]=temp0[i];
                thresh1[j]=temp1[i];
                j++;
            }
        }
        return j;
}

void CVideoProc::DrawRect(IplImage *img, CvRect rect,CvScalar cvbgr){

        cvLine(img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y),cvbgr,3,8,0);
        cvLine(img,cvPoint(rect.x+rect.width,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),cvbgr,3,8,0);
        cvLine(img,cvPoint(rect.x+rect.width,rect.y+rect.height),cvPoint(rect.x,rect.y+rect.height),cvbgr,3,8,0);
        cvLine(img,cvPoint(rect.x,rect.y+rect.height),cvPoint(rect.x,rect.y),cvbgr,3,8,0);
}
