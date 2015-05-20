#ifndef LOG_H_
#define LOG_H

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
		void Mark(int n);
	private:
		char logfile[64];

};
#endif
