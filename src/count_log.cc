//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#include "count_log.h"

#include "stdio.h"

CLog::CLog(){
	FILE* pp = popen("mkdir -p /root/logs/","r");
    if(!pp){
        perror("Fail to make log dir!\n");
    }
	pclose(pp);
	time_t t = time(0);
	strftime(logfile,sizeof(logfile),"/root/logs/%Y%m%d.log",localtime(&t));
    ofstream outfile(logfile,ios::app);
    if(!outfile){
        perror("Fail to open log file!\n");
        return;
    }
    outfile<<"Time    Latitude    Longitude   Count"<<endl;
    outfile.close();
}

CLog::~CLog(){
}

void CLog::Mark(int n, char* ctime,double latitude,double longitude){
    ofstream outfile(logfile,ios::app);
    if(!outfile){
        perror("Fail to open log file!\n");
        return;
    }
    outfile<<ctime<<" "<<latitude<<" "<<longitude<<" "<<n<<endl;
    outfile.close();
    return;
}

