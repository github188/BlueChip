
// AutoBusCountV2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoBusCountV2.h"
#include "AutoBusCountV2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMERCNT 80

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
bool stop=false;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAutoBusCountV2Dlg 对话框




CAutoBusCountV2Dlg::CAutoBusCountV2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoBusCountV2Dlg::IDD, pParent)
	, m_iInLinePos(0)
	, m_iOutLinePos(0)
	, m_iRoiTopPos(0)
	, m_iRoiBottomPos(0)
	, m_iManMaxHeight(0)
	, m_dLongitude(0)
	, m_dLatitude(0)
	, m_iGetOn(0)
	, m_iGetOff(0)
	, m_oRoiRealTopPos(0)
	, m_iRoiRealHeight(0)
	, m_sBusName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoBusCountV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOWWIN_STATIC, m_conShowWin);
	DDX_Text(pDX, IDC_EDIT1, m_iInLinePos);
	DDV_MinMaxInt(pDX, m_iInLinePos, 0, 576);
	DDX_Text(pDX, IDC_EDIT2, m_iOutLinePos);
	DDV_MinMaxInt(pDX, m_iOutLinePos, 0, 576);
	DDX_Text(pDX, IDC_EDIT3, m_iRoiTopPos);
	DDX_Text(pDX, IDC_EDIT4, m_iRoiBottomPos);
	DDX_Text(pDX, IDC_EDIT5, m_iManMaxHeight);
	DDX_Text(pDX, IDC_EDIT6, m_dLongitude);
	DDX_Text(pDX, IDC_EDIT7, m_dLatitude);
	DDX_Text(pDX, IDC_EDIT8, m_iGetOn);
	DDV_MinMaxInt(pDX, m_iGetOn, 0, 55);
	DDX_Text(pDX, IDC_EDIT9, m_iGetOff);
	DDV_MinMaxInt(pDX, m_iGetOff, 0, 55);
	DDX_Text(pDX, IDC_EDIT14, m_oRoiRealTopPos);
	DDX_Text(pDX, IDC_EDIT15, m_iRoiRealHeight);
	DDX_Text(pDX, IDC_EDIT16, m_sBusName);
}

BEGIN_MESSAGE_MAP(CAutoBusCountV2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CAutoBusCountV2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CAutoBusCountV2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CAutoBusCountV2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &CAutoBusCountV2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CAutoBusCountV2Dlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON6, &CAutoBusCountV2Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CAutoBusCountV2Dlg 消息处理程序

BOOL CAutoBusCountV2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

    //TODO:连接GPS
	//conGPS = new CConGPS();
	//int flag=conGPS->Init();
	//while(flag==0)
	//{
	//	Sleep(1000);
	//	flag=conGPS->Init();
	//}
	//double la=conGPS->latitude;
	//double lo=conGPS->longitude;

	//读入数据
	conVariable = new CConVariable();
	if(!conVariable->InputVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("初始化变量失败！");
		return FALSE;
	}
	//读入车牌号码
	if(!conVariable->ImReadBusName(m_sBusName))
	{
		::AfxMessageBox("读入车牌号码失败!");
		return FALSE;
	}
	
	this->UpdateData(false);

	//初始化数据库连接
	conMySQL = new CConMySQL();
	if(!conMySQL->Init())
	{
		::AfxMessageBox("数据库连接失败！");
		return FALSE;
	}

	//初始化采集卡信息
	if ( VCAInitSdk() != S_OK )
	{
		::AfxMessageBox("UV200驱动初始化失败！");
		EndDialog(0);
		return FALSE;		
	}
	int m_nDevNum;
	VCAGetDevNum(&m_nDevNum);
	if ( !m_nDevNum )
	{
		::AfxMessageBox("请确定UV200驱动程序是否安装成功！");
		return FALSE;
	}
	CSize szVidSize;
	szVidSize.cx = 720;
	szVidSize.cy = 576;
	VCAConnectDevice( 0, FALSE, m_conShowWin, szVidSize, Source_AV, 25, VideoSubType_YUY2 );

/*
	//初始化视频处理
	videoProc = new CVideoProc();
	if(!videoProc->Init())
	{
		::AfxMessageBox("视频处理初始化失败");
		return FALSE;
	}
*/
	checkDoorStat=new CCheckDoorStat();
	if(!checkDoorStat->GetFileData())
	{
		::AfxMessageBox("导入门口标识数据失败");
		return FALSE;
	}
	open=false;

	// 调用数人数的主程序
	p=new byte[720*576*3+1];
	m_Image=cvCreateImageHeader(cvSize(720,576),IPL_DEPTH_8U,3);	
	SetTimer(1,TIMERCNT,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutoBusCountV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutoBusCountV2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutoBusCountV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoBusCountV2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
	if(!conVariable->ComfirmVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("变量导入不成功！");
	}
}


void CAutoBusCountV2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!conVariable->ReturnNormal(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("变量复原不成功！");	
	}
	this->UpdateData(false);
}


void CAutoBusCountV2Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	delete conMySQL;
	delete conVariable;
	delete videoProc;
	delete conGPS;
	delete p;
	cvReleaseImage(&m_Image);
	CDialogEx::OnCancel();
}


void CAutoBusCountV2Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	stop=false;
	SetTimer(1,TIMERCNT,NULL);
}


void CAutoBusCountV2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码	
	KillTimer(1);
	stop=true;
}

void CAutoBusCountV2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	this->UpdateData(true);
	HANDLE m_hdl;
	VCACopyToClipBoard(0);
	::OpenClipboard(0);
	if(IsClipboardFormatAvailable(CF_DIB))
	{		
		m_hdl=GetClipboardData(CF_DIB);
		LPBITMAPINFO lpBI=(LPBITMAPINFO)GlobalLock(m_hdl);
		pDIBBits=(void*)(lpBI+1);
		GlobalUnlock(m_hdl);
		EmptyClipboard();
		CloseClipboard();						
		memcpy(p,pDIBBits,720*576*3);		
		cvSetData(m_Image,p,720*3);
		cvFlip(m_Image,m_Image,0);
#ifdef _DEBUG
		m_Image->origin=IPL_ORIGIN_BL;
		cvNamedWindow("m_Image",CV_WINDOW_AUTOSIZE);		
		cvShowImage("m_Image",m_Image);
		m_Image->origin=IPL_ORIGIN_TL;
#endif
		checkDoorStat->CheckDoorOpen(m_Image);
		//此处添加图像处理程序
		/*
		if(checkDoorStat->CheckDoorOpen(m_Image)) //检测开门
		{
			open=true;
		}
		if(open){
			videoProc->GetVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight);
			videoProc->Process(m_Image);
			m_iGetOn=videoProc->GetInNum();
			m_iGetOff=videoProc->GetOutNmu();
			if(checkDoorStat->CheckDoorClose(m_Image)) //检测关门
			{
				open=false;
				//TODO:记录当前关门时间和经纬度，如果与上一次关门经纬度差异较大，则两次时间只差为行车时间，同时发送数据到数据库，客流清零，且两个经纬度的地点
				time_t t = time(0); 
				strftime( current_time, sizeof(current_time), "%H:%M:%S",localtime(&t) ); 
				current_longitude=conGPS->GetLongitude();
				current_latitude=conGPS->GetLatitude();
				if(abs(current_longitude-pre_longitude)>0.01&&abs(current_latitude-pre_latitude)>0.01)
				{
					conMySQL->SendData(pre_time,current_time,pre_longitude,current_longitude,pre_latitude,current_latitude,m_iGetOn);
				}
				else
				{
					*pre_time=*current_time;
					pre_longitude=current_longitude;
					pre_latitude=current_latitude;
				}
					
			}
		}
	}
	//更新数据到界面
	this->UpdateData(false);
*/
	}
	if(stop)
		KillTimer(1);

	//TODO:判断是否需要发送数据

	CDialogEx::OnTimer(nIDEvent);
}


void CAutoBusCountV2Dlg::OnBnClickedButton6()
{
	// 标定门口标识
	CvRect rect;
	HANDLE m_hdl;
	::OpenClipboard(0);
	IplImage* img=cvCreateImageHeader(cvSize(720,576),IPL_DEPTH_8U,3);	
	if(IsClipboardFormatAvailable(CF_DIB))
	{
		byte* p=new byte[720*576*3+1];	    
		m_hdl=GetClipboardData(CF_DIB);
		LPBITMAPINFO lpBI=(LPBITMAPINFO)GlobalLock(m_hdl);
		pDIBBits=(void*)(lpBI+1);
		GlobalUnlock(m_hdl);
		EmptyClipboard();
		CloseClipboard();						
		memcpy(p,pDIBBits,720*576*3);		
		cvSetData(img,p,720*3);
		cvFlip(img,img,0);
	}
	if(!checkDoorStat->GetFlagPosition(rect,img))
	{
		return ;
	}
	return;
}
