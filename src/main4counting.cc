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

int main(int argc,char* argv[])
{
		//sleep(10);
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
                IplImage* input_image=usbStream->GetImage(fd);
				if(/*shared->written*/1)
				{
						if(!arrive)
						{
							cout<<"Arrive Signal..."<<endl;
							arrived
							arrive=true;
							//conSendData->SendArriveSignal(shared->text);
                            //conSendData->GetData(countWithDirect->GetUpNum(),countWithDirect->GetDownNum());
                            countWithDirect->Zero();
						}
						int ret=countWithDirect->Process(input_image);  
						if(ret>0)
						{
								cout<<countWithDirect->GetUpNum()<<endl;
						}
                                        /* For test */    
                                        cvNamedWindow("Input_Image",1);
	                                    cvShowImage("Input_Image",input_image);
                                        int key=cvWaitKey(1);
		                                if(key==27)
		                                {
                                                        cout<<"leave signal..."<<endl;
                                                        conSendData->SendLeaveSignal(shared->text);
                                                        //conSendData->GetData(countWithDirect->GetUpNum(),countWithDirect->GetDownNum());
		                                }
                                                if(key=='c')
		                                {
                                                        cout<<"arrive signal..."<<endl;
                                                        conSendData->SendArriveSignal(shared->text);
                                                        conSendData->GetData(countWithDirect->GetUpNum(),countWithDirect->GetDownNum());
                                                        countWithDirect->Zero();
		                                }
												if(key=='o')
												{
														cout<<countWithDirect->GetUpNum()<<" "<<countWithDirect->GetDownNum()<<endl;
														running=0;
												}
						/* For test end  */

				}
				else if(!shared->written&&arrive)
				{
						//left
						cout<<"Leave Signal..."<<endl;
						arrive=false;
						conSendData->SendLeaveSignal(shared->text);
				}
				else
                                {
						sleep(1);
                                }
                                cvReleaseImage(&input_image);
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


