#include "StdAfx.h"
#include "ConGPS.h"
CConGPS::CConGPS(void)
{
}


CConGPS::~CConGPS(void)
{
}

PCWSTR CConGPS::GUIDToString(REFGUID guid, PWSTR psz, UINT cch)
{
	StringFromGUID2(guid, psz, cch);
    return psz;
}

int CConGPS::Init()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
	if(SUCCEEDED(hr))
	{
		CComPtr<ILocation> spLocation;
		if (SUCCEEDED(spLocation.CoCreateInstance(CLSID_Location))) 
		{
			IID REPORT_TYPES[] = { IID_ILatLongReport };
			if (FAILED(spLocation->RequestPermissions(NULL, REPORT_TYPES, ARRAYSIZE(REPORT_TYPES), TRUE))) // TRUE means a synchronous request
            {
                //wprintf(L"Warning: Unable to request permissions.\n");
				return 0;
            }
			LOCATION_REPORT_STATUS status = REPORT_NOT_SUPPORTED; // The LOCATION_REPORT_STATUS enumeration is defined in LocApi.h in the SDK

                if (SUCCEEDED(spLocation->GetReportStatus(IID_ILatLongReport, &status))) // Get the status of this report type
                {
                    bool fCachedData = true;
                    switch (status) // If there is an error, print the error
                    {
                    case REPORT_RUNNING:
                        // If the status for the current report is running, then don't print any additional message
                        fCachedData = false;
                        break;
                    case REPORT_NOT_SUPPORTED:
                        //wprintf(L"\nNo devices detected.\n");
						return 0;
                        break;
                    case REPORT_ERROR:
                        //wprintf(L"\nReport error.\n");
						return 0;
                        break;
                    case REPORT_ACCESS_DENIED:
                        //wprintf(L"\nAccess denied to reports.\n");
						return 0;
                        break;
                    case REPORT_INITIALIZING:
                        //wprintf(L"\nReport is initializing.\n");
						return 0;
                        break;
                    }

                    if (true == fCachedData)
                    {
                        //wprintf(L"The following is cached data:\n");
						return 0;
                    }
                }

                CComPtr<ILocationReport> spLocationReport; // This is our location report object
                CComPtr<ILatLongReport> spLatLongReport; // This is our LatLong report object

                // Get the current location report,
                // then get the ILatLongReport interface from ILocationReport,
                // then ensure it isn't NULL
                if ((SUCCEEDED(spLocation->GetReport(IID_ILatLongReport, &spLocationReport))) &&
                    (SUCCEEDED(spLocationReport->QueryInterface(&spLatLongReport))))
                {
                    // Print the Report Type GUID
                    wchar_t szGUID[64];
                    //wprintf(L"\nReportType: %s", GUIDToString(IID_ILatLongReport, szGUID, ARRAYSIZE(szGUID)));

                    // Print the Timestamp
                    SYSTEMTIME systemTime;
                    //if (SUCCEEDED(spLatLongReport->GetTimestamp(&systemTime)))
                    //{
                        //wprintf(L"\nTimestamp: YY:%d, MM:%d, DD:%d, HH:%d, MM:%d, SS:%d, MS:%d\n",
                            //systemTime.wYear,
                            //systemTime.wMonth,
                            //systemTime.wDay,
                            //systemTime.wHour,
                            //systemTime.wMinute,
                            //systemTime.wSecond,
                            //systemTime.wMilliseconds);
                   // }

                    // Print the Sensor ID GUID
                    //GUID sensorID = {0};
                    /*if (SUCCEEDED(spLatLongReport->GetSensorID(&sensorID)))
                    {
                        wprintf(L"SensorID: %s\n", GUIDToString(sensorID, szGUID, ARRAYSIZE(szGUID)));
                    }*/
                    latitude = 0;longitude = 0; 
                    //DOUBLE altitude = 0, errorRadius = 0, altitudeError = 0;
                    // Print the Latitude
                    if (!SUCCEEDED(spLatLongReport->GetLatitude(&latitude)))
                    {
                        /*wprintf(L"Latitude: %f\n", latitude);*/
						return 0;
                    }

                    // Print the Longitude
                    if (!SUCCEEDED(spLatLongReport->GetLongitude(&longitude)))
                    {
                        /*wprintf(L"Longitude: %f\n", longitude);*/
						return 0;
                    }

                    //// Print the Altitude
                    //if (SUCCEEDED(spLatLongReport->GetAltitude(&altitude)))
                    //{
                    //    wprintf(L"Altitude: %f\n", altitude);
                    //}
                    //else
                    //{
                    //    // Altitude is optional and may not be available
                    //    wprintf(L"Altitude: Not available.\n");
                    //}

                    //// Print the Error Radius
                    //if (SUCCEEDED(spLatLongReport->GetErrorRadius(&errorRadius)))
                    //{
                    //    wprintf(L"Error Radius: %f\n", errorRadius);
                    //}

                    //// Print the Altitude Error
                    //if (SUCCEEDED(spLatLongReport->GetAltitudeError(&altitudeError)))
                    //{
                    //    wprintf(L"Altitude Error: %f\n", altitudeError);
                    //}
                    //else
                    //{
                    //    // Altitude Error is optional and may not be available
                    //    wprintf(L"Altitude Error: Not available.\n");
                    //}
                }

                Sleep(1000); // Sleep for one second before checking for the next report
		}
		else
			return 0;
	}
	else
		return 0;
	return 1;
}

double CConGPS::GetLongitude()
{
	return 0;
}
double CConGPS::GetLatitude()
{
	return 0;
}
