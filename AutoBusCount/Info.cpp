// Info.cpp : 实现文件
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "Info.h"
#include "afxdialogex.h"


// CInfo 对话框

IMPLEMENT_DYNAMIC(CInfo, CDialogEx)

CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfo::IDD, pParent)
	, m_sCameraID(_T(""))
	, m_BusID(_T(""))
{

}

CInfo::~CInfo()
{
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sCameraID);
	DDX_Text(pDX, IDC_EDIT2, m_BusID);
}


BEGIN_MESSAGE_MAP(CInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// CInfo 消息处理程序


void CInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(true);
	CDialogEx::OnOK();
}
