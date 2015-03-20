/*
 * =====================================================================================
 *
 *       Filename:  main4counting.cc
 *
 *    Description:  process for counting while gps detected arrived.
 *
 *        Version:  1.0
 *        Created:  2015年03月21日 01时48分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), Lauren.luo@extremevision.mo
 *        Company:  Extreme Vision Ltd.
 *
 * =====================================================================================
 */

#include "shmdata.hpp"
#include "ConGPS.hpp"
#include "ConSendData.hpp"

#include "stream/evusbstream.hpp"
#include "counting/evcountwithdirect.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>

#define VIDEO_DEVICE "/dev/video0"

using namespace std;

int main()
{
		sleep(100);
		/* init video device */
		EVUsbStream* usbStream=new EVUsbStream();
		usbStream->set_device(VIDEO_DEVICE);
		usbStream->setSize(480,720);
		int fd;
		fd=usbStream->open_camer_device();
		usbSteam->init_camer_device(fd);
		/* init counting */
		EVCountWithDirect* countWithDirect=new EVCountWithDirect();
		/* init send data */
		CConSendData* conSendData=new CConSendData();
		/* begin running */
		int running=1;
		void *shm = NULL;
		shared_use_st *shared;
		int shmid;
		shmid=shmget((key_t)1234,sizeof(shared_use_st),0666|IPC_CREAT);
		if(shmid==-1)
		{
				fprintf(stderr,"shmget failed\n");
				exit(EXIT_FAILURE);
		}
		shm = shmat(shmid,0,0);
		if(shm==(void*)-1)
		{
				fprintf(stderr,"shmat failed\n");
				exit(EXIT_FAILURE);
		}
		printf("\nMemory attached at %X\n",(int)shm);
		shared = (shared_use_st*)shm;
		bool arrive=false;
		while(running)
		{
				if(share->written)
				{
						if(!arrive)
						{
							arrive=true;
							//arrive
							conSendData->SendArriveSignal(*current_location);
						}
						else
						{
							int ret=countWithDirect->Process(usbStream->GetImage(fd));
						}
				}
				else if(!share->written&&arrive)
				{
						//left
						countWithDirect->Zero();
						conSendData->SendLeaveSignal(*current_location);
				}
				else
						sleep(1);
		}
		if(shmdt(shm)==-1)
		{
				fprintf(stderr,"shmdt failed\n");
				exit(EXIT_FAILURE);
		}
		if(shmctl(shmid,IPC_RMID,0)==-1)
		{
				fprintf(stderr,"shmctl(IPC_RMID) failed\n");
				exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);

}

