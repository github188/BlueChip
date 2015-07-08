//Copyright(c) 2015 Extreme Vision Ltd. All rights reserved.
//Author:Yun Luo(lauren.luo@extremevision.mo)
//File:con_count.cc


#include "con_count.h"

ConCount::ConCount(){
  Init();
}

ConCount::~ConCount(){
}

void ConCount::Init(){
  //init bus status.
  busStatus=None;
  last_busStatus=None;
  //init passager.
  passager=0;
  //init GPS.
  //conGPS = new CConGPS();
  //conGPS->Init();
  //init time.
  start=new char(64);
  end=new char(64);
  start="00:00:00";
  end="00:00:00";
  //init location.
  dep=new char[20];
  des=new char[20];
  //init send data.
  conSendData = new CConSendData();
  //conSendData->InitConSendData();
  //init log
  //log = new CLog();
}

void ConCount::CountProcess(const bool in){
  //conGPS->ShowLocation();
  printf("%d\n",in);
  //get current time.
/*  time_t t = time(0);
  char now[64];
  strftime(now,sizeof(now),"%H:%M:%S",localtime(&t));
  CountInfo countinfo;
  countinfo.time[64]=now[64];
  countinfo.latitude=conGPS->get_latitude();
  countinfo.longitude=conGPS->get_longitude();
  countinfo.in=in;
  PushBackRecord(countinfo);
  //Get status.
  if(CheckStatus()!=None){
    if(busStatus==GettingOn){
      //\Getting On/\\.
      passager++;
      
    }else{
      //\Getting Off/\\.

      //send data.
      conSendData->SendData(start,end,des,dep,passager);

      //clear passagers.
      passager=0;
    }
  }*/
}

void ConCount::PushBackRecord(const CountInfo countInfo){
  //keep last several elements.
  record.push_back(countInfo);
  if(record.size()>CHECK_NUM){
    record.erase(record.begin());
  }
}

//\keep compare the records and recognize the status currently./\\.
BusStatus ConCount::CheckStatus(){
  if(record.size()<CHECK_NUM){
    busStatus=None;
    return busStatus;
  }
  //1. check GPS.
  for(int i=0;i<record.size()-1;i++){
    if(record[i].latitude!=record[i+1].latitude){
      busStatus=None;
      return busStatus;
    }
    if(record[i].longitude!=record[i+1].longitude){
      busStatus=None;
      return busStatus;
    }
  }
  //2. check direct.
  int direct_in=0;
  for(int i=0;i<record.size();i++){
    if(record[i].in){
      direct_in++;
    }
  }
  if(direct_in>DIRECT_THRESH){
    busStatus=GettingOn;
  }else{
    busStatus=GettingOff;
  }
  //3. compare last_busStatus.
  if(last_busStatus!=busStatus){
    if(busStatus==GettingOn){
      //\begin get on/\\.
      //add back all the passagers.
      for(int i=0;i<record.size();i++){ 
        if(record[i].in){
          passager++;
        }else{
          passager--;
        }
      }
      // record start time.
      char tmp_start[64];
      time_t t1=time(0);
      strftime(tmp_start,sizeof(tmp_start),"%H:%M:%S",localtime(&t1));
      start=tmp_start;  
      // get depature.
      conGPS->CompareLocation(&dep);   
    }else{
      // begin get off.
      char tmp_end[64];
      time_t t2=time(0);
      strftime(tmp_end,sizeof(tmp_end),"%H:%M:%s",localtime(&t2));
      end=tmp_end;
      // get destination.
      conGPS->CompareLocation(&des);
    }
  }
  last_busStatus=busStatus;
  return busStatus;
}
