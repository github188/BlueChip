//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef BLUECHIP_INC_GPS_INTERFACE_H_
#define BLUECHIP_INC_GPS_INTERFACE_H_

typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
}date_time;

typedef struct{
	date_time D;
	char status;
	double latitude;
	double longitude;
	char NS;
	char EW;
	double speed;
	double high;
}GPS_INFO;

class IConGPS{
	public:
		IConGPS();
		~IConGPS();
		int initGpsDev();
		void readGpsDev();
		double get_latitude();
		double get_longitude();
		//@return 1: data available
		//@return 0: data not avilable		
		int get_status();
	protected:
		int set_opt(int fd,int nSpeed,int nBits,char nEvent,int nStop);
		void receive();
		int openGpsDev();
		int closeGpsDev();
		void gps_parse();
		double get_double_number(char* s);
		double get_locate(double temp);
		int get_comma(int num,char* str);
		void UTC2BTC(date_time* GPS);
	private:
		GPS_INFO* GPS;
		int Gpsfd;
		int baud;
		char* GpsName;
		char GPS_BUF[1024];
};

#endif //BLUECHIP_INC_INTERFACE_H_

