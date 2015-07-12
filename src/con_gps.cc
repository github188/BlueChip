//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#include "con_gps.h"

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
#include <math.h>

using namespace std; 

#define DATAFILE "/root/BlueChip/data/locations.dat"
#define RADIU 0.00001f

CConGPS::CConGPS(){
	latitude=0.000000;
	longitude=0.000000;
	m_init=false;
}

CConGPS::~CConGPS(){
}

int CConGPS::Process(){
    if(initGpsDev()==-1){
	//	cout<<"init failed !"<<endl;
		return 0;
	}
	bool done=false;
	int cnt=1;
	while(!done){
        readGpsDev();
        if(get_status()){
			cnt--;
			if(cnt==0){
                latitude=get_latitude();
                longitude=get_longitude();
				//cout<<latitude<<" "<<longitude<<endl;
				done=true;
			}
		}else{
			cnt=10;
		}
		sleep(1);
	}
	return 1;
}

int CConGPS::AddLocationGPS(char* location){
	ofstream outfile(DATAFILE,ios::app);
	if(!outfile){
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

int CConGPS::DeleteLocationGPS(int i){
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
	if(!outfile){
		return 0;
	}
	for(int i=0;i<la.size()-1;i++){
		outfile<<la[i]<<" "<<lo[i]<<" "<<loca[i]<<endl;
	}
	outfile.close();
	return 1;
}

int CConGPS::Reset(){
	ofstream outfile(DATAFILE,ios::out);
	if(!outfile){
		return 0;
	}
	outfile.close();
	return 1;
}

int CConGPS::Init(){
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
	if(g_latitude.size()==0){
		return 0;
	}
	for(int i=0;i<g_latitude.size()-1;i++){
		cout<<g_latitude[i]<<" "<<g_longitude[i]<<" "<<g_location[i]<<endl;
	}
    if(initGpsDev()==-1){
		//cout<<"init failed !"<<endl;
		return 0;
	}
	return 1;
}

int CConGPS::ShowLocation(){
		if(!m_init){
				if(!Init()){
						cout<<"Location GPS have not been set yet!"<<endl;
				}
				return 0;
		}else{
				readGpsDev();
				if(get_status()){
						latitude=get_latitude();
						longitude=get_longitude();
						std::cout<<latitude<<" "<<longitude<<endl;
				}
				for(int i=0;i<g_latitude.size()-1;i++){
                        if(abs(latitude-g_latitude[i])<0.00001&&abs(longitude-g_longitude[i]<0.00001)){
								//@return 2:xinlihua
								//@return 3:xinhaoi
								//@return 4:leave xinhaoi
								return i+2;
						}
						//cout<<g_latitude[i]<<" "<<g_longitude[i]<<endl;
				}
				return 1;
		}
}

int CConGPS::CompareLocation(char** location){
	if(!m_init){
		if(!Init()){
			cout<<"Location GPS have not been set yet!"<<endl;
		}
		return 0;
	}else{
        	readGpsDev();
        	if(get_status()){
            		latitude=get_latitude();
            		longitude=get_longitude();
			        std::cout<<latitude<<" "<<longitude;
                    double dis = 2.000000;
                    int n=0;
		
                    for(int i=0;i<g_latitude.size()-1;i++){
                    double _dis = abs(latitude-g_latitude[i])+abs(longitude-g_longitude[i]);
                    if(_dis<dis){
                        dis = _dis;
                        n = i;
				}
			}
			if(location!=NULL){
				*location = g_location[n];
			}
			return 1;
		}
		//sleep(1);
                //cout<<"location not get!"<<endl;
		return 0;
	}
}





