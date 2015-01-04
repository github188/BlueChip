// Info.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoBusCount.h"
#include "Info.h"
#include "afxdialogex.h"


// CInfo �Ի���

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


// CInfo ��Ϣ�������


void CInfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(true);
	CDialogEx::OnOK();
}
