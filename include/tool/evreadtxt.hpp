/*
 * =====================================================================================
 *
 *       Filename:  evreadtxt.hpp
 *
 *    Description:  head file of class CReadTxt
 *
 *        Version:  1.0
 *        Created:  2015年02月05日 00时39分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVREADTXT_H_
#define EVREADTXT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class EVReadTxt
{
	public:
		explicit EVReadTxt(const char* paramfile);
		~EVReadTxt();
		int GetSumLine();
		void InRead(string* IPaddress,
				string* Port,
				string* UserName,
				string* Pwsd,
				string* Channel,
				string* Manufacturer,
				string* ID);
	protected:
		const char* filename;
};
#endif

