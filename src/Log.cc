#include "Log.hpp"

#include "stdio.h"

CLog::CLog()
{
	FILE* pp = popen("mkdir /root/logs/","r");
	pclose(pp);
	time_t t = time(0);
	strftime(logfile,sizeof(logfile),"/root/logs/%Y%m%d.dat",localtime(&t));
}

CLog::~CLog()
{
}

void CLog::Mark(int n)
{
    time_t t = time(0);
    char ctime[64];
    strftime(ctime,sizeof(ctime),"%H:%M:%S",localtime(&t));
    ofstream outfile(logfile,ios::app);
    if(!outfile)
    {
        perror("Fail to open waiting list!\n");
        return;
    }
    outfile<<ctime<<" "<<n<<endl;
    outfile.close();
    return;
}

