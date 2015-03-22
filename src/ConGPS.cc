/*
 * =====================================================================================
 *
 *       Filename:  ConGPS.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月17日 17时30分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <string>

#include "tool/evgetgps.hpp"
using namespace std; 

#define DATAFILE "/root/Project_Master_Macau_System/data/locations.dat"
#define RADIU 0.005 //about 500 meters

CConGPS::CConGPS()
{
	getGPS=new EVGetGPS;
	latitude=0.000000;
	longitude=0.000000;
	m_init=false;
}

CConGPS::~CConGPS()
{
	delete getGPS;
}

int CConGPS::Process()
{
	if(getGPS->initGpsDev()==-1)
	{
	//	cout<<"init failed !"<<endl;
		return 0;
	}
	bool done=false;
	int cnt=10;
	while(!done)
	{
		getGPS->readGpsDev();
		if(getGPS->get_status())
		{
			cnt--;
			if(cnt==0)
			{
				latitude=getGPS->get_latitude();
				longitude=getGPS->get_longitude();
				//cout<<latitude<<" "<<longitude<<endl;
				done=true;
			}
		}
		else
		{
			cnt=10;
		}
		sleep(2);
	}
	return 1;
}

int CConGPS::AddLocationGPS(char* location)
{
	ofstream outfile(DATAFILE,ios::app);
	if(!outfile)
	{
			printf("Content-Type:text/html/\n\n");
			printf("no data file found.\n");
			printf("%s\n",DATAFILE);
			return 0;
	}
	outfile<<latitude<<" "<<longitude<<" "<<location<<endl;
	printf("Content-Type:text/html/\n\n");
	printf("latitude:%lf,longitude:%lf\n",latitude,longitude);
	outfile.close();
	return 1;
}

int CConGPS::DeleteLocationGPS(int i)
{
	vector<double> la;
	vector<double> lo;
	vector<char*> loca;
	ifstream inFile(DATAFILE);
	while(!inFile.eof()){
		double _la,_lo;
		char* _location=new char[100];
		inFile>>_la>>_lo>>_location;
		la.push_back(_la);
		lo.push_back(_lo);
		loca.push_back(_location);
	}
	la.erase(la.begin()+i);
	lo.erase(lo.begin()+i);
	loca.erase(loca.begin()+i);
	inFile.close();
	ofstream outfile(DATAFILE,ios::out);
	if(!outfile)
	{
		return 0;
	}
	for(int i=0;i<la.size()-1;i++)
	{
		outfile<<la[i]<<" "<<lo[i]<<" "<<loca[i]<<endl;
	}
	outfile.close();
	return 1;
}

int CConGPS::Reset()
{
	ofstream outfile(DATAFILE,ios::out);
	if(!outfile)
	{
		return 0;
	}
	outfile.close();
	return 1;
}

int CConGPS::Init()
{
	ifstream inFile(DATAFILE,ios::in);
	while(!inFile.eof()){
		double _la,_lo;
		char* _location=new char[20];
		inFile>>_la>>_lo>>_location;
		g_latitude.push_back(_la);
		g_longitude.push_back(_lo);
		g_location.push_back(_location);
		//delete _location;
	}
	inFile.close();
	m_init=true;
	if(g_latitude.size()==0)
	{
		return 0;
	}
	for(int i=0;i<g_latitude.size()-1;i++)
	{
		//cout<<g_latitude[i]<<" "<<g_longitude[i]<<" "<<g_location[i]<<endl;
	}
	if(getGPS->initGpsDev()==-1)
	{
		//cout<<"init failed !"<<endl;
		return 0;
	}
	return 1;
}

int CConGPS::CompareLocation(char** location)
{
	if(!m_init)
	{
		if(!Init())
		{
			cout<<"Location GPS have not been set yet!"<<endl;
		}
		return 0;
	}
	else
	{
		getGPS->readGpsDev();
		if(getGPS->get_status())
		{
			latitude=getGPS->get_latitude();
			longitude=getGPS->get_longitude();
		
			for(int i=0;i<g_latitude.size()-1;i++)
			{	
				if(abs(latitude-g_latitude[i])<RADIU && abs(longitude-g_longitude[i])<RADIU)
				{
					cout<<"location get!"<<endl;
					if(location!=NULL)
					{
						*location=g_location[i];
					}
					return 1;
				}
				else
					cout<<"location not get!"<<endl;
			}
		}
		//sleep(1);
		return 0;
	}
}

int CConGPS::ComfirmArrive()
{
	int arr=0;
	for(int i=0;i<10;i++)
	{
		if(CompareLocation())
		{
			arr++;
		}
	}
	if(arr>5)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}




