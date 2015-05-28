//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef BLUECHIP_INC_CON_GPS_H_
#define BLUECHIP_INC_CON_GPS_H_

#include "gps_interface.h"

#include <vector>
#include <iostream>
using namespace std; 

class CConGPS : public IConGPS
{
	public:
        	CConGPS();
		~CConGPS();
		//Setting GPS Data
		//Getting GPS data
		//@return 1: data available
		//@return 0: data not availabe
		int Process();
		//add a new lacation's gps data in the file
		int AddLocationGPS(char* location);
		//delete a specific data in the data file
		//@param i: the i row in the data which would be delete
		int DeleteLocationGPS(int i);
		//clear all data and reset new ones
		int Reset();
		//Main Funtion
		//compare the current location with the setting location
		//@return 1: compare match
		//@return 0: compare not match
		//@return location
		int CompareLocation(char** location=NULL);
		int Init();
	private:
		double latitude;
		double longitude; 
		vector<double> g_latitude;
		vector<double> g_longitude;
		vector<char*> g_location;
		bool m_init;

};

#endif

