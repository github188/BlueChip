#pragma once


// CInfo 对话框

class CInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 摄像头ID
	CString m_sCameraID;
	// 车牌号码
	CString m_BusID;
	afx_msg void OnBnClickedOk();
};
extern CInfo* info;
