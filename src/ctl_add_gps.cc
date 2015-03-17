/*
 * =====================================================================================
 *
 *       Filename:  ctl_add_gps.cc
 *
 *    Description:  execute add new location gps data
 *
 *        Version:  1.0
 *        Created:  2015年03月17日 18时34分28秒
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
	if(conGPS->Process())
	{
		conGPS->AddLocationGPS();
	}
	delete conGPS;
	return 0;
}


