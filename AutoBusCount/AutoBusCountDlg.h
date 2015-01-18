
// AutoBusCountDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "sdk_uv200.h"

#include "Date.h"
#include "VideoProc.h"
#include "Info.h"


// CAutoBusCountDlg dialog

class CAutoBusCountDlg : public CDialogEx
{
// Construction
public:
	int m_nDevNum;
	CAutoBusCountDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AUTOBUSCOUNT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_conShowWin;
	afx_msg void OnBnClickedButton1();

private:
	bool m_bStop;
public:
	afx_msg void OnBnClickedButton2();

};

