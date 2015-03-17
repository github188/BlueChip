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

#include "tool/evgetgps.hpp"
using namespace std; 

#define DATAFILE "../data/locations.dat"
#define RADIU 0.0001

CConGPS::CConGPS()
{
	getGPS=new EVGetGPS;
	latitude=0.00f;
	longitude=0.00f;
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
		cout<<"init failed !"<<endl;
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

int CConGPS::AddLocationGPS()
{
	ofstream outfile(DATAFILE,ios::app);
	if(!outfile)
	{
		return 0;
	}
	outfile<<latitude<<" "<<longitude;
	outfile.close();
	return 1;
}

int CConGPS::DeleteLocationGPS(int i)
{
	vector<double> la;
	vector<double> lo;
	ifstream inFile(DATAFILE);
	while(!inFile.eof()){
		double _la,_lo;
		inFile>>_la>>_lo;
		la.push_back(_la);
		lo.push_back(_lo);
	}
	la.erase(la.begin()+i);
	lo.erase(lo.begin()+i);
	inFile.close();
	ofstream outfile(DATAFILE,ios::out);
	if(!outfile)
	{
		return 0;
	}
	for(int i=0;i<la.size();i++)
	{
		outfile<<la[i]<<" "<<lo[i];
	}
	outfile.close();
	return 1;
}

int CConGPS::Reset()
{
	ofstream outfile(file,ios::out);
	if(!outfile)
	{
		return 0;
	}
	outfile.close();
	return 1;
}

int CConGPS::Init()
{
	ifstream inFile(DATAFILE);
	while(!inFile.eof()){
		double _la,_lo;
		char* _location;
		inFile>>_la>>_lo>>_location;
		g_latitude.push_back(_la);
		g_longitude.push_back(_lo);
		g_location.push_back(_location);
	}
	inFile.close();
	m_init=true;
	if(g_latitude.size()==0)
	{
		return 0;
	}
	return 1;
}

int CConGPS::CompareLocation(char* location)
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
			done=true;
		}
		for(int i=0;i<g_latitude.size();i++)
		{	
			if(abs(latitude-g_latitude[i])<RADIU && abs(longitude-g_longitude[i])<RADIU)
			{
				location=g_location[i];
				return 1;
			}
		}
		return 0;
	}
}


