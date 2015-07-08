//Copyright(c) 2015 Extreme Vision Ltd. All rights reserved.
//Author: Yun Luo(lauren.luo@extremevision.mo)
//File:con_count.h
//This class is designed for making comfirm of whether a new count 
//data should be regarded as an useful data and also deciding whether
//to send the data to the database.

#ifndef BLUECHIP_INC_CON_COUNT_H_
#define BLUECHIP_INC_CON_COUNT_H_

#include <time.h>
#include <stdio.h>

#include <vector>

#include "con_gps.h"
#include "con_send_data.h"
#include "count_log.h"

#define CHECK_NUM 5
#define DIRECT_THRESH 3 

struct CountInfo{
  char time[64];
  double latitude;
  double longitude;
  bool in;
};

enum BusStatus{
  GettingOn,
  GettingOff,
  None
};

class ConCount{

public:
  ConCount();
  ~ConCount();
  void CountProcess(const bool in);
protected:
  void PushBackRecord(const CountInfo countInfo);
  BusStatus CheckStatus();
  void Init();
private:
  BusStatus busStatus;
  BusStatus last_busStatus; //last bus status(not None).
  std::vector<CountInfo> record;
  //number of passager.
  int passager;
  //GPS
  CConGPS* conGPS;
  //strat time.
  char* start;
  //end time.
  char* end;
  //departure.
  char* dep;
  //destination.
  char* des; 
  //send data to database.
  CConSendData* conSendData;
  //log
  CLog* log;
};

#endif // BLUECHIP_INC_CON_COUNT_H_
