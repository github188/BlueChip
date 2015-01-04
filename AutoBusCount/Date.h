#pragma once

#include "afxwin.h"

// CDate 对话框
class CDate : public CDialogEx
{
	DECLARE_DYNAMIC(CDate)

public:
	CDate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDate();

// 对话框数据
	enum { IDD = IDD_DATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 当前日期
	CString m_sDate;
	// 当前时间
	CString m_sTime;
	// 摄像头ID
	CString m_sCameraID;
	// 车牌号码
	CString m_sBusID;
	// 当前上车人数
	int m_iIn;
	// 当前下车人数
	int m_iOut;
	// 车上人数
	int m_iOnBoard;
	// 行驶方向
	CString m_sDirection;
	//摄像头序列号
	int m_iCameraID;
	// //设备号
	CString m_sMachineID;
};

extern CDate* date;
