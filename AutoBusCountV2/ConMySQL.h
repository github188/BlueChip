#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <mysql.h> 
#include <iostream>
#include <time.h>
#include <WinSock.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
class CConMySQL
{
public:
	CConMySQL(void);
	~CConMySQL(void);
	int Init();
	int SendData(char* pre_time,char* current_time,double pre_longitude,double current_longitude,double pre_latitude,double latitude,int people);
	int SaveToLocal();
private:
	MYSQL* myCont;
	char busName[20];
	map<int,vector<double> > positions;
};

