/*
 * =====================================================================================
 *
 *       Filename:  ctl_del_gps.cc
 *
 *    Description:  execute delete location gps data
 *
 *        Version:  1.0
 *        Created:  2015年03月18日 00时52分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"

#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc,char* argv[])
{
	CConGPS* conGPS=new CConGPS();
	conGPS->DeleteLocationGPS(atoi(argv[1]));
	delete conGPS;
	return 0;
	
}


