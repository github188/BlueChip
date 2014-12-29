
// AutoBusCount.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "AutoBusCountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoBusCountApp

BEGIN_MESSAGE_MAP(CAutoBusCountApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CRITICAL_SECTION CriticalSection;

// CAutoBusCountApp construction

CAutoBusCountApp::CAutoBusCountApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_nPowerTime = 0;
}


// The one and only CAutoBusCountApp object

CAutoBusCountApp theApp;


// CAutoBusCountApp initialization

BOOL CAutoBusCountApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	//关闭屏幕保护和电源管理

	SystemParametersInfo( SPI_SETSCREENSAVEACTIVE,
		FALSE,
		0,
		SPIF_SENDCHANGE); 

	SystemParametersInfo(SPI_GETPOWEROFFTIMEOUT,
		0,
		&m_nPowerTime,
		SPIF_UPDATEINIFILE);

	SystemParametersInfo(SPI_SETPOWEROFFTIMEOUT,
		0,
		NULL,
		SPIF_UPDATEINIFILE);

	InitializeCriticalSection(&CriticalSection);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CAutoBusCountDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAutoBusCountApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,
		TRUE,
		NULL,
		SPIF_SENDCHANGE);

	if(m_nPowerTime > 0)
		SystemParametersInfo(SPI_SETPOWEROFFTIMEOUT,
		m_nPowerTime,
		NULL,		
		SPIF_UPDATEINIFILE);


	DeleteCriticalSection(&CriticalSection);

	return CWinApp::ExitInstance();
}


