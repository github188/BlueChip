/*
 * =====================================================================================
 *
 *       Filename:  main4gps.cc
 *
 *    Description:  process for GPS detection  
 *
 *        Version:  1.0
 *        Created:  2015年03月20日 13时07分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), Lauren.luo@extremevision.mo
 *        Company:  Extreme Vision Ltd.
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"
#include "shmdata.hpp"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

using namespace std;

int main(int argc,char* argv[])
{
		int running=1;
		void *shm = NULL;
		shared_use_st *shared = NULL;
		//char buffer[BUFSIZ + 1];
		int shmid;
		/* create share memory */
		shmid=shmget((key_t)atoi(argv[1]),sizeof(shared_use_st),0666|IPC_CREAT);
		if(shmid==-1)
		{
				fprintf(stderr,"shmget failed\n");
				exit(EXIT_FAILURE);
		}
		shm = shmat(shmid,(void*)0,0);
		if(shm==(void*)-1)
		{
				fprintf(stderr,"shmat failed\n");
				exit(EXIT_FAILURE);
		}
		printf("Memory attached at %X\n",(int)shm);
		shared = (shared_use_st*) shm;
		shared->written=0;
		/* init GPS */
		CConGPS* conGPS=new CConGPS();
		char** current_location;
		*current_location=new char[20];
		bool arrived=false;
		while(running)
		{
                                //int ret=conGPS->CompareLocation(current_location);
				if(conGPS->CompareLocation(current_location)&&!arrived)
				{
						//if(conGPS->ComfirmArrive())
						{
							arrived = true;
							shared->written=-1;
							//*current_location: arrive location
							cout<<"arrive:"<<*current_location<<endl;
							strncpy(shared->text,*current_location,TEXT_SZ);
							shared->written=1;
						}
				}
				else if(!conGPS->CompareLocation(current_location)&&arrived)
				{
						//if(!conGPS->ComfirmArrive())
						{
							arrived=false;
                                                        cout<<"leave:"<<*current_location<<endl;
							shared->written=0;
						}
				}
                                cout<<conGPS->GetLatitude()<<" "<<conGPS->GetLongitude()<<endl;
				
			        sleep(1);
		}
		if(shmdt(shm)==-1)
		{
				fprintf(stderr,"shmdt failed\n");
				exit(EXIT_FAILURE);
		}
		sleep(2);
		exit(EXIT_SUCCESS);
		delete conGPS;
		return 0;
}

