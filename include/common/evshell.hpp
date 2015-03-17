/*
 * =====================================================================================
 *
 *       Filename:  evcommon.h
 *
 *    Description:  class for using shell command
 *
 *        Version:  1.0
 *        Created:  2015年03月13日 14时26分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef EVCOMMON_H_
#define EVCOMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <sys/types.h>
#include <iostream>
using namespace std;

class EVShell
{
	public:
		EVShell();
		~EVShell();
		/* Function Desc: Use the shell command and get the shell comman result
 		* @param cmd: shell command.Before using the command,make sure the shell is available int system,if not, install first.
 		* @return resved: the result.
 		* @param print:"true" means print the result, "false" means not. */
		int32_t shell_exec(const char* cmd,vector<string> &resvec,bool print=false);
	protected:
		void shell_exec_output(vector<string> result,const string title);
};

#endif
