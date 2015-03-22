#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include "tool/evgetgps.hpp"
using namespace std;
#define COM1 "/dev/ttyUSB0"
#define DEFAULT_BAUD_RATE 4800
EVGetGPS::EVGetGPS()
{
	GpsName=NULL;
	Gpsfd=0;
	for(int i=0;i<1024;i++)
	{
	GPS_BUF[i]=0;
	}
	GPS=new GPS_INFO;
	GPS->latitude=0.000000;
	GPS->longitude=0.000000;
	memset(GPS,0,sizeof(GPS_INFO));
}
EVGetGPS::~EVGetGPS()
{
	delete GPS;
	closeGpsDev();
}
double EVGetGPS::get_latitude()
{
	return GPS->latitude;
}
double EVGetGPS::get_longitude()
{
	return GPS->longitude;
}
int EVGetGPS::get_status()
{
	if(GPS->status=='A')
	{
		//printf("data available\n");
		return 1;
	}
	else
	{
		//printf("data not available\n");
		return 0;
	}
}
int EVGetGPS::initGpsDev()
{
	Gpsfd=openGpsDev();
	if(Gpsfd<0)
	{
		//cout<<"open device failed!"<<endl;
		return -1;
	}
	if(set_opt(Gpsfd,DEFAULT_BAUD_RATE,8,'N',1)==-1)
	{
		//cout<<"set_opt failed!"<<endl;
		return -1;
	}
	return 0;
}
double EVGetGPS::get_double_number(char* s)
{
	char buf[128];
	int i;
	double rev;
	i=get_comma(1,s);
	strncpy(buf,s,i);
	buf[i]=0;
	rev=atof(buf);
	return rev;
}
double EVGetGPS::get_locate(double temp)
{
	int m;
	double n;
	m=(int)temp/100;
	n=(temp-m*100)/60;
	n=n+m;
	return n;
}
int EVGetGPS::get_comma(int num,char* str)
{
	int i,j=0;
	int len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]==',')
		{
			j++;
		}
		if(j==num)
			return i+1;
	}
	return 0;
}
void EVGetGPS::UTC2BTC(date_time* GPS)
{
	GPS->second++;
	if(GPS->second>59)
	{
		GPS->second=0;
		GPS->minute++;
		if(GPS->minute>59)
		{
			GPS->minute=0;
			GPS->hour++;
		}
	}
	GPS->hour+=8;
	if(GPS->hour>23)
	{
		GPS->hour-=24;
		GPS->day+=1;
		if(GPS->month==2||
		GPS->month==4||
		GPS->month==6||
		GPS->month==9||
		GPS->month==11)
		{
			if(GPS->day>30)
			{
				GPS->day=1;
				GPS->month++;
			}
		}
		else{
			if(GPS->day>31)
			{
				GPS->day=1;
				GPS->month++;
			}
		}
		if(GPS->year%4==0){
			if(GPS->day>29&& GPS->month==2)
			{
				GPS->day=1;
				GPS->month++;
			}
		}
		else
		{
			if(GPS->day>28 && GPS->month==2)
			{
				GPS->day=1;
				GPS->month++;
			}
		}
		if(GPS->month>12)
		{
			GPS->month-=12;
			GPS->year++;
		}
	}
}
void EVGetGPS::readGpsDev()
{
	receive();
	gps_parse();
}
int EVGetGPS::set_opt(int fd,int nSpeed,int nBits,char nEvent,int nStop)
{
	struct termios newtio,oldtio;
	if(tcgetattr(fd,&oldtio)!=0)
	{
	//perror("SetupSerial 1");
	return -1;
	}
	bzero(&newtio,sizeof(newtio));
	newtio.c_cflag |= CLOCAL|CREAD;
	newtio.c_cflag&=~CSIZE;
	switch(nBits)
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
}
switch(nEvent)
{
case 'O':
newtio.c_cflag |= PARENB;
newtio.c_cflag |= PARODD;
newtio.c_cflag |= (INPCK|ISTRIP);
break;
case 'E':
newtio.c_cflag |= (INPCK|ISTRIP);
newtio.c_cflag |= PARENB;
newtio.c_cflag &= ~PARODD;
break;
case 'N':
newtio.c_cflag &= ~PARENB;
break;
}
switch(nSpeed)
{
case 2400:
cfsetispeed(&newtio,B2400);
cfsetospeed(&newtio,B2400);
break;
case 4800:
cfsetispeed(&newtio,B4800);
cfsetospeed(&newtio,B4800);
break;
case 9600:
cfsetispeed(&newtio,B9600);
cfsetospeed(&newtio,B9600);
break;
case 115200:
cfsetispeed(&newtio,B115200);
cfsetospeed(&newtio,B115200);
break;
case 460800:
cfsetispeed(&newtio,B460800);
cfsetospeed(&newtio,B460800);
break;
default:
cfsetispeed(&newtio,B9600);
cfsetospeed(&newtio,B9600);
break;
}
if(nStop==1)
{
newtio.c_cflag&=~CSTOPB;
}
else if(nStop==2)
{
newtio.c_cflag |= CSTOPB;
}
newtio.c_cc[VTIME]=0;
newtio.c_cc[VMIN]=0;
tcflush(fd,TCIFLUSH);
if((tcsetattr(fd,TCSANOW,&newtio))!=0)
{
return -1;
}
return 0;
}
void EVGetGPS::receive()
{
memset(GPS_BUF,0,1024);
int nread=read(Gpsfd,GPS_BUF,1024);
if(nread>0){
//printf("\n GPS DATALen=%d\n",nread);
GPS_BUF[nread]='\0';
//printf("GPS %s \n",GPS_BUF);
}
}
int EVGetGPS::openGpsDev()
{
Gpsfd=open("/dev/ttyUSB0",O_RDWR|O_NONBLOCK);
if(Gpsfd<0)
{
close(Gpsfd);
return -1;
}
return Gpsfd;
}
int EVGetGPS::closeGpsDev()
{
close(Gpsfd);
return 0;
}
void EVGetGPS::gps_parse()
{
int i=0;
int j=0;
char buf[1024];
while(GPS_BUF[i]!='\0')
{
if(GPS_BUF[i]=='\n')
{
int tmp;
char c;
c=GPS_BUF[j+6];
//cout<<c<<endl;
if(c=='C')
{
//GPRMC
int k=i-j;
memset(buf,0,k+1);
for(int m=0;m<k;m++)
{
buf[m]=GPS_BUF[j+1+m];
}
buf[k]='\0';
//printf("$GPRMC: %s \n",buf);
/*parse*/
GPS->D.hour=(buf[7]-'0')*10+(buf[8]-'0');
GPS->D.minute=(buf[9]-'0')*10+(buf[10]-'0');
GPS->D.second=(buf[11]-'0')*10+(buf[12]-'0');
tmp=get_comma(9,buf);
GPS->D.day=(buf[tmp+0]-'0')*10+(buf[tmp+1]-'0');
GPS->D.month=(buf[tmp+2]-'0')*10+(buf[tmp+3]-'0');
GPS->D.year=(buf[tmp+4]-'0')*10+(buf[tmp+5]-'0')+2000;
GPS->status=buf[get_comma(2,buf)];
GPS->latitude=get_locate(get_double_number(&buf[get_comma(3,buf)]));
GPS->NS=buf[get_comma(4,buf)];
GPS->longitude=get_locate(get_double_number(&buf[get_comma(5,buf)]));
GPS->EW=buf[get_comma(6,buf)];
GPS->speed=get_double_number(&buf[get_comma(7,buf)]);
UTC2BTC(&GPS->D);
}
if(c=='A')
{
//cout<<"A"<<endl;
//GPGGA
GPS->high=get_double_number(&buf[get_comma(9,buf)]);
}
j=i;
}
i++;
}
}
