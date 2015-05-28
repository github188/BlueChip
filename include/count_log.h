#ifndef BLUECHIP_INC_COUNT_LOG_H_
#define BLUECHIP_INC_COUNT_LOG_H_

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

class CLog
{
	public:
		CLog();
		~CLog();
		/* @param n: when the number change,     */
		/* the num of current passager.          */
		/* -----------Log format---------------- */
		/* Time  number                          */
		void Mark(int n,char* ctime,double latitude,double longitude);
	private:
		char logfile[64];

};
#endif //BLUECHIP_INC_COUNT_LOG_H_
