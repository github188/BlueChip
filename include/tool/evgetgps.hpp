/*
 * =====================================================================================
 *
 *       Filename:  evgetgps.hpp
 *
 *    Description:  head file of getting gps infomation, design for ttyUSB0 
 *
 *        Version:  1.0
 *        Created:  2015年02月07日 21时48分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVGETGPS_H_
#define _EVGETGPS_H_

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

class EVGetGPS
{
	public:
		EVGetGPS();
		~EVGetGPS();
		int initGpsDev();
		void readGpsDev();
		double get_latitude();
		double get_longitude();
		/***************************
		@return 1: data available
		@return 0: data not avilable
		***************************/
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

#endif

