/*
 * =====================================================================================
 *
 *       Filename:  ConGPS.hpp
 *
 *    Description:  Class CConGPS for setting the gps data
 *
 *        Version:  1.0
 *        Created:  2015年03月17日 17时21分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef CONGPS_H_
#define CONGPS_H_

#include "tool/evgetgps.hpp"

#include <vector>
#include <iostream>
using namespace std; 
class CConGPS
{
	public:
		CConGPS();
		~CConGPS();
		/*******Setting GPS Data***********************************/
		/* Getting GPS data
		 * @return 1: data available
		 * @return 0: data not availabe*/
		int Process();
		/* add a new lacation's gps data in the file */
		int AddLocationGPS();
		/* delete a specific data in the data file
		 * @param i: the i row in the data which would be delete */
		int DeleteLocationGPS(int i);
		/* clear all data and reset new ones */
		int Reset();
		/*******Main Funtion***********************************/
		/* compare the current location with the setting location
		 * @return 1: compare match
		 * @return 0: compare not match
		 * @return location:*/
		int CompareLocation(char** location);
	protected:
		int Init();
	private:
		EVGetGPS* getGPS;
		double latitude;
		double longitude; 
		vector<double> g_latitude;
		vector<double> g_longitude;
		vector<char*> g_location;
		bool m_init;

};

#endif

