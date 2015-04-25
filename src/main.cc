/*
 * =====================================================================================
 *  
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月18日 02时37分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"
#include "ConSendData.hpp"

#include "stream/evusbstream.hpp"
#include "counting/evcountwithdirect.hpp"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define VIDEO_DEVICE "/dev/video0"

using namespace std;

bool g_arrive=false;
int main()
{
	/* init GPS */
	CConGPS* conGPS=new CConGPS();
	char** current_location;
	*current_location=new char[20];
	/* init video device */
	EVUsbStream* usbStream=new EVUsbStream();
	usbStream->set_device(VIDEO_DEVICE);
	usbStream->setSize(480,720);
	int fd;
	fd=usbStream->open_camer_device();
	usbStream->init_camer_device(fd);
	usbStream->start_capturing(fd);
	/* init counting */
	EVCountWithDirect* countWithDirect=new EVCountWithDirect();
	/* init send data */
	CConSendData* conSendData=new CConSendData();
	while(1)
	{
		if(conGPS->CompareLocation(current_location)&&g_arrive) //arrived
		{
			cout<<"arrive:"<<*current_location<<endl;
            conSendData->SendArriveSignal(*current_location);
			/********** begin counting *************/
			bool stop=false;
			while(!stop)
			{
				int ret=countWithDirect->Process(usbStream->GetImage(fd));
				if(!conGPS->CompareLocation())
				{	
					if(!conGPS->ComfirmArrive()) //left
					{
						/*****Send Data***********/
                        conSendData->GetData(countWithDirect->GetUpNum(),countWithDirect->GetDownNum());
						stop=true;
						g_arrive=false;
						countWithDirect->Zero();
						conSendData->SendLeaveSignal(*current_location);
					}
				}
			}
			sleep(1);
		}
		else if(conGPS->CompareLocation(current_location)&&!g_arrive)  //arriving
		{
			if(conGPS->ComfirmArrive())
			{
				g_arrive=true;
			}
			sleep(1);
		}
		else if(!conGPS->CompareLocation(current_location)&&g_arrive)  //leaving
		{
			if(!conGPS->ComfirmArrive())
			{
				g_arrive=false;
			}
			sleep(1);
		}
		else  //left
		{			
			sleep(1);
		}
	}
	delete countWithDirect;
	usbStream->stop_capturing(fd);
	usbStream->uninit_camer_device(fd);
	usbStream->close_camer_device(fd);
	delete current_location;
	delete conGPS;
	
	return 0;
}

