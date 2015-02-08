
// AutoBusCountV2Dlg.h : 头文件
//

#pragma once

#include "resource.h"	

#include <time.h>

#include <cv.h>
#include <highgui.h>

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>

#include "sdk_uv200.h"
#include "ConMySQL.h"
#include "VideoProc.h"
#include "ConVariable.h"
#include "ConGPS.h"
#include "CheckDoorStat.h"
#include "afxwin.h"

using namespace std;
// CAutoBusCountV2Dlg 对话框
class CAutoBusCountV2Dlg : public CDialogEx
{
// 构造
public:
	CAutoBusCountV2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOBUSCOUNTV2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CConMySQL* conMySQL;
	CConVariable* conVariable;
	CVideoProc* videoProc;
	CConGPS* conGPS;
	CCheckDoorStat* checkDoorStat;
	CStatic m_conShowWin; //视频显示窗口
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	// m1:进入线与上边缘的距离
	int m_iInLinePos;
	// m2:离开线与下边缘的距离
	int m_iOutLinePos;
	// m3:ROI的上边缘
	int m_iRoiTopPos;
	// m4:ROI的下边缘
	int m_iRoiBottomPos;
	// m5:行人最大高度
	int m_iManMaxHeight;
	// 经度
	double m_dLongitude;
	// 纬度
	double m_dLatitude;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 本次上车人数
	int m_iGetOn;
	// 本次下车人数
	int m_iGetOff;
	// ROI上边缘位置
	int m_oRoiRealTopPos;
	// ROI高度
	int m_iRoiRealHeight;
	/****数据指针****/
	void* pDIBBits;
	byte* p;
	IplImage* m_Image;

	/***开门***/
	bool open;

	/**本次与上一次的关门时间**/
	char current_time[64];
	char pre_time[64];
	/**本次与上一次的经纬度信息**/
	double current_longitude;
	double pre_longitude;
	double current_latitude;
	double pre_latitude;

	afx_msg void OnBnClickedButton6();
	// 车牌号码
	CString m_sBusName;
};
