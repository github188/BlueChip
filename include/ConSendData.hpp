#ifndef CCONSENDDATA_H_
#define CCONSENDDATA_H_

#include "database/evmysql.hpp"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

class CConSendData
{
	public:
		CConSendData();
		~CConSendData();
		int SendArriveSignal(char* des);
		int SendLeaveSignal(char* dep);
		int GetData(int in,int out);
	protected:
		int Init();
		int CheckNetwork();
		int SendData();
		string delta_time(const char* src_starttime,const char* src_arrivetime);
	private:
		EVMySql* evMySql;
		char* db_addr;
		char* db_user;
		char* db_pswd;
		char* db_name;
		unsigned int port;
		string busid;
		string current_date;
		string current_departure;
		string current_dep_time;
		string current_destination;
		string current_des_time;
		string current_duration;
		int last_num;
		
};

#endif
