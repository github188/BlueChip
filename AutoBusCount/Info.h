#pragma once


// CInfo �Ի���

class CInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ����ͷID
	CString m_sCameraID;
	// ���ƺ���
	CString m_BusID;
	afx_msg void OnBnClickedOk();
};
extern CInfo* info;
