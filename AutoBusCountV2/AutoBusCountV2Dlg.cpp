
// AutoBusCountV2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoBusCountV2.h"
#include "AutoBusCountV2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMERCNT 80

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
bool stop=false;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAutoBusCountV2Dlg �Ի���




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


// CAutoBusCountV2Dlg ��Ϣ�������

BOOL CAutoBusCountV2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    //TODO:����GPS
	//conGPS = new CConGPS();
	//int flag=conGPS->Init();
	//while(flag==0)
	//{
	//	Sleep(1000);
	//	flag=conGPS->Init();
	//}
	//double la=conGPS->latitude;
	//double lo=conGPS->longitude;

	//��������
	conVariable = new CConVariable();
	if(!conVariable->InputVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("��ʼ������ʧ�ܣ�");
		return FALSE;
	}
	//���복�ƺ���
	if(!conVariable->ImReadBusName(m_sBusName))
	{
		::AfxMessageBox("���복�ƺ���ʧ��!");
		return FALSE;
	}
	
	this->UpdateData(false);

	//��ʼ�����ݿ�����
	conMySQL = new CConMySQL();
	if(!conMySQL->Init())
	{
		::AfxMessageBox("���ݿ�����ʧ�ܣ�");
		return FALSE;
	}

	//��ʼ���ɼ�����Ϣ
	if ( VCAInitSdk() != S_OK )
	{
		::AfxMessageBox("UV200������ʼ��ʧ�ܣ�");
		EndDialog(0);
		return FALSE;		
	}
	int m_nDevNum;
	VCAGetDevNum(&m_nDevNum);
	if ( !m_nDevNum )
	{
		::AfxMessageBox("��ȷ��UV200���������Ƿ�װ�ɹ���");
		return FALSE;
	}
	CSize szVidSize;
	szVidSize.cx = 720;
	szVidSize.cy = 576;
	VCAConnectDevice( 0, FALSE, m_conShowWin, szVidSize, Source_AV, 25, VideoSubType_YUY2 );

/*
	//��ʼ����Ƶ����
	videoProc = new CVideoProc();
	if(!videoProc->Init())
	{
		::AfxMessageBox("��Ƶ�����ʼ��ʧ��");
		return FALSE;
	}
*/
	checkDoorStat=new CCheckDoorStat();
	if(!checkDoorStat->GetFileData())
	{
		::AfxMessageBox("�����ſڱ�ʶ����ʧ��");
		return FALSE;
	}
	open=false;

	// ������������������
	p=new byte[720*576*3+1];
	m_Image=cvCreateImageHeader(cvSize(720,576),IPL_DEPTH_8U,3);	
	SetTimer(1,TIMERCNT,NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAutoBusCountV2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAutoBusCountV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutoBusCountV2Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(true);
	if(!conVariable->ComfirmVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("�������벻�ɹ���");
	}
}


void CAutoBusCountV2Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!conVariable->ReturnNormal(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight))
	{
		::AfxMessageBox("������ԭ���ɹ���");	
	}
	this->UpdateData(false);
}


void CAutoBusCountV2Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	stop=false;
	SetTimer(1,TIMERCNT,NULL);
}


void CAutoBusCountV2Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
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
		//�˴����ͼ�������
		/*
		if(checkDoorStat->CheckDoorOpen(m_Image)) //��⿪��
		{
			open=true;
		}
		if(open){
			videoProc->GetVar(m_iInLinePos,m_iOutLinePos,m_iRoiTopPos,m_iRoiBottomPos,m_iManMaxHeight,m_oRoiRealTopPos,m_iRoiRealHeight);
			videoProc->Process(m_Image);
			m_iGetOn=videoProc->GetInNum();
			m_iGetOff=videoProc->GetOutNmu();
			if(checkDoorStat->CheckDoorClose(m_Image)) //������
			{
				open=false;
				//TODO:��¼��ǰ����ʱ��;�γ�ȣ��������һ�ι��ž�γ�Ȳ���ϴ�������ʱ��ֻ��Ϊ�г�ʱ�䣬ͬʱ�������ݵ����ݿ⣬�������㣬��������γ�ȵĵص�
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
	//�������ݵ�����
	this->UpdateData(false);
*/
	}
	if(stop)
		KillTimer(1);

	//TODO:�ж��Ƿ���Ҫ��������

	CDialogEx::OnTimer(nIDEvent);
}


void CAutoBusCountV2Dlg::OnBnClickedButton6()
{
	// �궨�ſڱ�ʶ
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
