#pragma once
#include <iostream>
#include <windows.h>
#include <atlbase.h>
#include <atlcom.h>
#include <conio.h>
#include <locationapi.h>
using namespace std;
 // Initializes ATL for this application. This also does CoInitialize for us
class CConGPS
{
public:
	CConGPS(void);
	~CConGPS(void);
	PCWSTR GUIDToString(REFGUID guid, PWSTR psz, UINT cch);
	int Init();
	DOUBLE latitude;
	DOUBLE longitude;
	double GetLongitude();
	double GetLatitude();
};

