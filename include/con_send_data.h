//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef CCONSENDDATA_H_
#define CCONSENDDATA_H_

#include "mysql_interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

class CConSendData : public IMySql {
	public:
		CConSendData();
		~CConSendData();
		int SendArriveSignal(char* des);
		int SendLeaveSignal(char* dep);
		int GetData(int in,int out);
		inline void GetDeparture(char* dep){
			current_departure = dep;
		}
		inline void GetDestination(char* des){
			current_destination = des;
		}
		inline void GetStartTime(char* start){
			current_dep_time=start;	
		}
		inline void GetEndTime(char* end){
			current_des_time = end;
		}
        int SendData(char* start,char* end,char* des,char* dep,int passager);
        int InitConSendData();
    protected:
		int SendData();
		string delta_time(const char* src_starttime,const char* src_arrivetime);		
		int SaveToWaitingList(char* sql);
		int ReadWaitingList();
		int SaveToLocal(string busid,
				string current_date,
				string current_dep_time,
				string current_des_time,
				string current_duration,
				string current_departure,
				string current_destination,
				string c_num);
	private:
		char* db_addr;
		char* db_user;
		char* db_pswd;
		char* db_name;
		unsigned int port;
		string busid;
		string current_date;
		string current_departure;
		vector<char*> waiting_list;
		string current_dep_time;
		string current_destination;
		string current_des_time;
		string current_duration;
		int num;
		int last_num;
		bool db_init;
};

#endif //BLUECHIP_INC_CON_SEND_DATA_H_
