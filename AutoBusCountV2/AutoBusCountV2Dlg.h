
// AutoBusCountV2Dlg.h : ͷ�ļ�
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
// CAutoBusCountV2Dlg �Ի���
class CAutoBusCountV2Dlg : public CDialogEx
{
// ����
public:
	CAutoBusCountV2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOBUSCOUNTV2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CStatic m_conShowWin; //��Ƶ��ʾ����
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	// m1:���������ϱ�Ե�ľ���
	int m_iInLinePos;
	// m2:�뿪�����±�Ե�ľ���
	int m_iOutLinePos;
	// m3:ROI���ϱ�Ե
	int m_iRoiTopPos;
	// m4:ROI���±�Ե
	int m_iRoiBottomPos;
	// m5:�������߶�
	int m_iManMaxHeight;
	// ����
	double m_dLongitude;
	// γ��
	double m_dLatitude;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �����ϳ�����
	int m_iGetOn;
	// �����³�����
	int m_iGetOff;
	// ROI�ϱ�Եλ��
	int m_oRoiRealTopPos;
	// ROI�߶�
	int m_iRoiRealHeight;
	/****����ָ��****/
	void* pDIBBits;
	byte* p;
	IplImage* m_Image;

	/***����***/
	bool open;

	/**��������һ�εĹ���ʱ��**/
	char current_time[64];
	char pre_time[64];
	/**��������һ�εľ�γ����Ϣ**/
	double current_longitude;
	double pre_longitude;
	double current_latitude;
	double pre_latitude;

	afx_msg void OnBnClickedButton6();
	// ���ƺ���
	CString m_sBusName;
};
