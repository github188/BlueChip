#include "StdAfx.h"
#include "ConMySQL.h"


CConMySQL::CConMySQL(void)
{
	myCont = new MYSQL;
}


CConMySQL::~CConMySQL(void)
{
	mysql_close(myCont);
	delete myCont;
}

int CConMySQL::Init()
{
	const char user[] = "s610637db0";         //username
    const char pswd[] = "9a92b6fc";         //password
    const char host[] = "43.243.123.198";    //or"127.0.0.1"
    const char table[] = "s610637db0";        //database
    unsigned int port = 3306;           //server port  

	mysql_init(myCont);

	if(!mysql_real_connect(myCont,host,user,pswd,table,port,NULL,0))
	{
		return 0;
	}
	mysql_set_character_set(myCont,"utf-8") ;

	ifstream infile("data/busname.dat",ios::in);
	if(!infile)
	{
		return 0;
	}
	infile>>busName;
	infile.close();

	ifstream infile2("data/position.dat");//此处默认的文件打开方式为“以输出的方式打开”
	int n=0;//用来表示说读/写文本的行数
	char str[200];
	while(!infile2.eof())
	{
		infile2.getline(str, sizeof(str));//此处默认的终止标识符为‘\n’
		n++;
	}
	infile2.close();

	ifstream infile3("data/position.dat",ios::in);
	if(!infile3)
	{
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		//char* position_name;
		int pos;
		double longitude;
		double latitude;
		infile3>>pos;
		infile3>>longitude;
		infile3>>latitude;
		vector<double> lola;
		lola.push_back(longitude);
		lola.push_back(latitude);
		positions.insert(pair<int,vector<double>>(pos,lola));
		lola.clear();
	}

	infile3.close();

	return 1;
}

int CConMySQL::SendData(char* pre_time,char* current_time,double pre_longitude,double current_longitude,double pre_latitude,double latitude,int people)
{
	//TODO:匹配最接近的经纬度，获取他的地点名
	char* start_position,*end_position;
	//TODO:给用比较法
	map<int,vector<double> >::iterator it=positions.begin();
	while(it!=positions.end())
	{
		if(abs(it->second[0]-pre_longitude)>0.01&&abs(it->second[1]-pre_latitude)>0.01)
		{
			switch(it->first)
			{
				case 1: 
					start_position="关闸";
					break;
				case 2:
					start_position="新濠天地";
					break;
			}
		}
		++it;
	}
	map<int,vector<double>>::iterator itt=positions.begin();
	while(itt!=positions.end())
	{
		if(abs(itt->second[0]-current_longitude)>0.01&&abs(itt->second[1]-latitude)>0.01)
		{
			switch(it->first)
			{
				case 1: 
					end_position="关闸";
					break;
				case 2:
					end_position="新濠天地";
					break;
			}
		}
		++itt;
	}
	char* sql;
	if(mysql_query(myCont,sql)!=0)
	{
		return 0;
	}
	return 1;
}
