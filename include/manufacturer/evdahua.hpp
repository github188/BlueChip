/*
 * =====================================================================================
 *
 *       Filename:  evdahua.hpp
 *
 *    Description:  head file of dahua
 *
 *        Version:  1.0
 *        Created:  2015年01月31日 15时59分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */


#ifndef EVDAHUA_H_
#define EVDAHUA_H_

#include <stdio.h>
#include <iostream>

#include "dhnetsdk.h"

using namespace std;

class EVDahua
{
	public:
		EVDahua();
		~EVDahua();
		/* initialize the SDK with information */
		int Init(const char* IPaddress,const int Port,const char* UserName,const char* Password,const int Channel,const int ID);
		int SaveData();
	protected:
		char* GetFileName(int ID);
		void CreateNewStr(const char* src1,const char* src2,char* dest);
};

#endif
