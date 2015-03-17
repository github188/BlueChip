/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年03月18日 02时37分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#include "ConGPS.hpp"

#include <stdio.h>
#include <pthread.h>

int main()
{
	CConGPS* conGPS=new CConGPS();
	char* current_location;
	while(1)
	{
		if(conGPS->CompareLocation(current_location))
		{
			cout<<current_location<<endl;
		}
	}
	return 0;
}


