
// AutoBusCountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "AutoBusCountDlg.h"
#include "afxdialogex.h"

#include <time.h>

#include <cv.h>

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h> 
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CDate* date;
extern CVideoProc* videoProc;
extern CInfo* info;
bool g_stop=false;
MYSQL myCont;
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) //�ص�����
{
	/***��ʾʱ��************************************************/
	time_t t = time(0); 
    char tmp_date[64]; 
	char tmp_time[64];
    strftime( tmp_date, sizeof(tmp_date), "%Y-%m-%d",localtime(&t) ); 
	strftime( tmp_time, sizeof(tmp_time), "%H:%M",localtime(&t) ); //����%S��������Ҫ�t����ȥ
    puts( tmp_date ); 
	puts(tmp_time);
	date->m_sDate=tmp_date;
	date->m_sTime=tmp_time;
	/***�����Ƿ��\��************************************************/
	if(g_stop){
		date->UpdateData(false);
		return;
	}
	HANDLE m_hdl;
	VCACopyToClipBoard(0);
	OpenClipboard(NULL);
	if(IsClipboardFormatAvailable(CF_DIB))
	{		
		m_hdl=GetClipboardData(CF_DIB);
		LPBITMAPINFO lpBI=(LPBITMAPINFO)GlobalLock(m_hdl);
		void* pDIBBits=(void*)(lpBI+1);
		GlobalUnlock(m_hdl);
		EmptyClipboard();
		CloseClipboard();				
		byte* p=new byte[720*576*3+1];			
		memcpy(p,pDIBBits,720*576*3);	
		IplImage* m_Image=cvCreateImageHeader(cvSize(720,576),IPL_DEPTH_8U,3);		
		//cvNamedWindow("m_Image",CV_WINDOW_AUTOSIZE);		
		cvSetData(m_Image,p,720*3);
		cvFlip(m_Image,m_Image,0);	
		int feedback=videoProc->Process(m_Image);
		/**********����������ʾ********************************/
		switch(feedback)
		{
		case 1:
			date->m_iIn=videoProc->GetInNum();
			break;
		case 2:
			date->m_iOut=videoProc->GetOutNmu();
			break;
		case 3:
			/***�г̽Y�����ς�����************************************************/
			char *start=videoProc->start; //���ο�ʼʱ��
			char *end=tmp_time; //���ν���ʱ��
			date->m_iIn=videoProc->GetInNum();
			date->m_iOut=videoProc->GetOutNmu();
			char *c_in;
			itoa(date->m_iIn,c_in,10);
			int ratio=(date->m_iIn/55+1.0e-6) *100;
			char *c_ratio;
			itoa(ratio,c_ratio,10);
			string sql="insert into t_master_businfo(BusId,Date,Begin,End,Number,DirectName,FullRatio) values("
				+date->m_sMachineID+","
				+date->m_sDate+","
				+(*start)+","
				+(*end)+","
				+(*c_in)+","
				+date->m_sDirection+","
				+(*c_ratio)+")";
			const char* s =sql.data();
			mysql_query(&myCont,s);
			/***�г̽Y�����{������************************************************/
			videoProc->Zero(); //�г̽Y������Ք���
			if(date->m_sDate=="ـ��-�P�l")
			{
				date->m_sDate="�P�l-ـ��";
			}
			else 
				date->m_sDate="ـ��-�P�l";
			break;
		}
		date->m_iIn=videoProc->GetInNum();
		date->m_iOut=videoProc->GetOutNmu();
		date->m_iOnBoard=videoProc->GetOnboardNmu();
		/**********����������ʾ********************************/
		date->UpdateData(false);
		//cvShowImage("m_Image",m_Image);
		delete p;
	}
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutoBusCountDlg dialog




CAutoBusCountDlg::CAutoBusCountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoBusCountDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoBusCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_STATIC, m_conShowWin);
}

BEGIN_MESSAGE_MAP(CAutoBusCountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoBusCountDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoBusCountDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

// CAutoBusCountDlg message handlers
BOOL CAutoBusCountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,940,576,SWP_NOZORDER);
	CenterWindow();

	//������Ƶ��ʾ�ؼ���λ��
	CWnd *pWnd;
	pWnd = GetDlgItem( IDC_SHOW_STATIC); //��ȡ�ؼ�ָ�룬IDC_EDIT1Ϊ�ؼ�ID��
	pWnd->MoveWindow( CRect(0,0,720,576) );	
	////���ð�ťλ��:��ͣ��ť
	//CWnd *pWnd_Stop;
	//pWnd_Stop = GetDlgItem( IDC_BUTTON1); //��ȡ�ؼ�ָ�룬IDC_EDIT1Ϊ�ؼ�ID��
	//pWnd_Stop->MoveWindow( CRect(720,450,100,30) );	
	//////���ð�ťλ�ã�ȡ����ť
	//CWnd *pWnd_Cancel;
	//pWnd_Cancel = GetDlgItem( IDCANCEL); //��ȡ�ؼ�ָ�룬IDC_EDIT1Ϊ�ؼ�ID��
	//pWnd_Cancel->MoveWindow( CRect(720,400,100,30) );	

	// TODO: Add extra initialization here
	if ( VCAInitSdk() != S_OK )
	{
		::AfxMessageBox("UV200������ʼ��ʧ�ܣ�");
		EndDialog(0);
		return FALSE;		
	}

	VCAGetDevNum(&m_nDevNum);
	m_nDevNum = 1;
	if ( !m_nDevNum )
	{
		::AfxMessageBox("��ȷ��UV200���������Ƿ�װ�ɹ���");
		return FALSE;
	}
	CSize szVidSize;
	szVidSize.cx = 720;
	szVidSize.cy = 576;
	VCAConnectDevice( 0, FALSE, m_conShowWin, szVidSize, Source_AV, 25, VideoSubType_YUY2 );

	m_bStop=false;

	date=new CDate();
	date->Create(IDD_DATE_DIALOG,this);
	date->ShowWindow(SW_SHOW);
	date->MoveWindow(720,0,200,250);

	//info=new CInfo();
	//info->Create(IDD_DIALOG1,this);
	//info->ShowWindow(SW_SHOW);
	//info->MoveWindow(720,200,200,150);

	videoProc=new CVideoProc();

	const char user[] = "s610637db0";         //username
    const char pswd[] = "9a92b6fc";         //password
    const char host[] = "43.243.123.198";    //or"127.0.0.1"
    const char table[] = "s610637db0";        //database
    unsigned int port = 3306;           //server port     

	mysql_init(&myCont);

	bool connect=mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0);

	mysql_query(&myCont, "SET NAMES UTF8"); 
	//::AfxMessageBox(connect);
	SetTimer(1,80,TimerProc);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoBusCountDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAutoBusCountDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		 CDialog::OnPaint();//Ҫ��ֹ�������   
        // CPaintDC   dc(this);   
        // CRect   rect;   
        // GetClientRect(&rect);   
        // CDC   dcMem;   
        // dcMem.CreateCompatibleDC(&dc);   
        // CBitmap   bmpBackground;   
        // bmpBackground.LoadBitmap(IDB_BITMAP3);   
        //         //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   
        // BITMAP   bitmap;   
        // bmpBackground.GetBitmap(&bitmap);   
        // CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
        // dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
        //bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoBusCountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ͣ
void CAutoBusCountDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(g_stop)
	{
		g_stop=false;
	}
	else
		g_stop=true;
}

//����
void CAutoBusCountDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	videoProc->m_iIn=0;
	videoProc->m_iOut=0;
	videoProc->m_iOnboard=0;
}
