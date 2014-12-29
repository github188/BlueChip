
// AutoBusCountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "AutoBusCountDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	, m_iIn(0)
	, m_iOut(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoBusCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_iIn);
	DDV_MinMaxInt(pDX, m_iIn, 0, 55);
	DDX_Text(pDX, IDC_EDIT3, m_iOut);
	DDV_MinMaxInt(pDX, m_iOut, 0, 55);
	DDX_Control(pDX, IDC_SHOW_STATIC, m_conShowWin);
}

BEGIN_MESSAGE_MAP(CAutoBusCountDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
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

	// TODO: Add extra initialization here
	if ( VCAInitSdk() != S_OK )
	{
		::AfxMessageBox("UV200驱动初始化失败！");
		EndDialog(0);
		return FALSE;		
	}

	VCAGetDevNum(&m_nDevNum);
	m_nDevNum = 1;
	if ( !m_nDevNum )
	{
		::AfxMessageBox("请确定UV200驱动程序是否安装成功！");
		return FALSE;
	}
	CSize szVidSize;
	szVidSize.cx = 720;
	szVidSize.cy = 576;
	VCAConnectDevice( 0, FALSE, m_conShowWin, szVidSize, Source_AV, 25, VideoSubType_YUY2 );

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAutoBusCountDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

