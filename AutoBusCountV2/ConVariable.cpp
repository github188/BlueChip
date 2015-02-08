#include "StdAfx.h"
#include "ConVariable.h"


CConVariable::CConVariable(void)
{
}


CConVariable::~CConVariable(void)
{
}

int CConVariable::InputVar(int& m1, int& m2, int& m3, int& m4, int& m5,int& m6,int& m7)
{
	ifstream infile("data/variable.dat",ios::in);
	if(!infile)
	{
		return 0;
	}
	infile>>m1;
	infile>>m2;
	infile>>m3;
	infile>>m4;
	infile>>m5;
	infile>>m6;
	infile>>m7;
	infile.close();
	return 1;
}

int CConVariable::ComfirmVar(const int m1, const int m2, const int m3, const int m4, const int m5,const int m6, const int m7)
{
	ofstream outfile("data/variable.dat",ios::out);
	if(!outfile)
	{
		return 0;
	}
	outfile<<m1<<" "<<m2<<" "<<m3<<" "<<m4<<" "<<m5<<" "<<m6<<" "<<m7;
	outfile.close();
	return 1;
}

int CConVariable::ReturnNormal(int& m1, int& m2, int& m3, int& m4, int& m5,int& m6,int& m7)
{
	ifstream infile("data/original.dat",ios::in);
	if(!infile)
	{
		return 0;
	}
	infile>>m1;
	infile>>m2;
	infile>>m3;
	infile>>m4;
	infile>>m5;
	infile>>m6;
	infile>>m7;
	infile.close();
	if(!ComfirmVar(m1,m2,m3,m4,m5,m6,m7))
	{
		return 0;
	}
	return 1;
}

int CConVariable::ImReadBusName(CString& busname)
{
	char* bname=new char[1024];
	FILE *fp;
	if((fp = fopen("data/busname.dat","r")) == NULL)
	{
		return 0;
	}
	fscanf(fp,"%[^\n]",bname);
	busname=_T(bname);
	fclose(fp);
	return 1;
}

