/*
 * =====================================================================================
 *
 *       Filename:  ctl_reset_gps.cc
 *
 *    Description:  execute reset location gps data
 *
 *        Version:  1.0
 *        Created:  2015年03月18日 00时55分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"

int main()
{
	CConGPS* conGPS=new CConGPS();
	conGPS->Reset();
	delete conGPS;
	return 0;
}


