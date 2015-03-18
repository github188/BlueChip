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

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* thread_gps(void* ptr)
{
	CConGPS* conGPS=new CConGPS();
	//conGPS->Process();
	char** current_location;
	*current_location=new char[20];
	while(1)
	{
		cout<<"This is a pthread."<<endl;
		if(conGPS->CompareLocation(current_location))
		{
			cout<<*current_location<<endl;
			return 0;
		}
	}
	delete current_location;
	delete conGPS;
}

void* thread(void* ptr)
{
	for(int i=0;i<3;i++)
	{
		sleep(1);
		cout<<"This is a pthread."<<endl;
	}
	return 0;
}

int main()
{
	pthread_t id;
	int ret = pthread_create(&id,NULL,thread_gps,NULL);
	if(ret)
	{
		cout<<"create pthread error!"<<endl;
		return 1;
	}
	/*for(int i=0;i<3;i++)
	{
		cout<<"This is the main process."<<endl;
		sleep(1);
	}*/
	pthread_join(id,NULL);
	return 0;
}

