#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class CConVariable
{
public:
	CConVariable(void);
	~CConVariable(void);
	int ComfirmVar(const int m1, const int m2, const int m3, const int m4, const int m5,const int m6, const int m7); //确认新变量值
	int InputVar(int& m1, int& m2, int& m3, int& m4, int& m5,int& m6,int& m7); //导入变量值
	int ReturnNormal(int& m1, int& m2, int& m3, int& m4, int& m5,int& m6,int& m7); //恢复原来数据
	int ImReadBusName(CString& busname);
	
};

