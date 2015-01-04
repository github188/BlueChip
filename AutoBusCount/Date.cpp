// Date.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "Date.h"
#include "afxdialogex.h"


// CDate 对话框

IMPLEMENT_DYNAMIC(CDate, CDialog)

CDate::CDate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDate::IDD, pParent)
	, m_sDate(_T(""))
	, m_sTime(_T(""))
	, m_iIn(0)
	, m_iOut(0)
	, m_iOnBoard(0)
	, m_sDirection(_T("賭場-關閘"))
	, m_iCameraID(477985692)
	, m_sMachineID(_T("EV001"))
{

}

CDate::~CDate()
{
}

void CDate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATE_STATIC, m_sDate);
	DDX_Text(pDX, IDC_TIME_STATIC, m_sTime);
	DDX_Text(pDX, IDC_EDIT3, m_iIn);
	DDV_MinMaxInt(pDX, m_iIn, 0, 55);
	DDX_Text(pDX, IDC_EDIT2, m_iOut);
	DDV_MinMaxInt(pDX, m_iOut, 0, 55);
	DDX_Text(pDX, IDC_EDIT1, m_iOnBoard);
	DDV_MinMaxInt(pDX, m_iOnBoard, 0, 55);
	DDX_Text(pDX, IDC_EDIT4, m_sDirection);
	DDX_Text(pDX, IDC_EDIT5, m_sMachineID);
}



BEGIN_MESSAGE_MAP(CDate, CDialog)
END_MESSAGE_MAP()


// CDate 消息处理程序
