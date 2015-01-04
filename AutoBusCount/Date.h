#pragma once

#include "afxwin.h"

// CDate �Ի���
class CDate : public CDialogEx
{
	DECLARE_DYNAMIC(CDate)

public:
	CDate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDate();

// �Ի�������
	enum { IDD = IDD_DATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ǰ����
	CString m_sDate;
	// ��ǰʱ��
	CString m_sTime;
	// ����ͷID
	CString m_sCameraID;
	// ���ƺ���
	CString m_sBusID;
	// ��ǰ�ϳ�����
	int m_iIn;
	// ��ǰ�³�����
	int m_iOut;
	// ��������
	int m_iOnBoard;
	// ��ʻ����
	CString m_sDirection;
	//����ͷ���к�
	int m_iCameraID;
	// //�豸��
	CString m_sMachineID;
};

extern CDate* date;
