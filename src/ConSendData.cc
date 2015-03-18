#include "ConSendData.hpp"

#define DATABASE_FILE "../data/database.dat"
#define BUSID_FILE "../data/busid.dat"

CConSendData::CConSendData()
{
	db_addr=new char[20];
	db_user=new char[20];
	db_pswd=new char[20];
	db_name=new char[20];
	evMySql=new EVMySql();
	Init();
	last_num=0;
}

CConSendData::~CConSendData()
{
}

int CConSendData::SendArriveSignal(char* des)
{
	current_destination=des;
	time_t=time(0);
	strftime(current_des_time,64,"%H-%M-%S",localtime(&t));
	current_duration=delta_time(current_dep_time,current_des_time);
	return 0;
}

int CConSendData::SendLeaveSignal(char* dep)
{
	current_departure=des;
	time_t=time(0);
	strftime(current_dep_time,64,"%H-%M-%S",localtime(&t));
	return 0;
}

int CConSendData::GetData(int in,int out)
{
	int num=in-(out-last_num);
	last_num=num;
	if(CheckNetwork())
	{
		SendData();
	}
	else
	{
  		//TODO:save to waiting list
	}
	return 0;
}

int CConSendData::Init()
{
	ifstream inFile(DATABASE_FILE);
	while(!inFile.eof()){
		inFile>>db_addr>>db_user>>db_pswd>>db_name>>port;
	}
	inFile.close();
	evMySql->Init((const char*)db_addr,(const char*)db_user,(const char*)db_pswd,(const char*)db_name,port,NULL,0);
	ifstream inFile(BUSID_FILE);
	char* _busid=new char[30];
	while(!inFile.eof()){
		inFile>>_busid;
	}
	busid=_busid;
	inFile.close();
	char tmp_date[64];
	time_t=time(0);
	strftime(tmp_date,sizeof(tmp_date),"%Y-%m-%d",localtime(&t));
	puts(tmp_date);
	current_date=tmp_date;
	return 0;
}

int CConSendData::CheckNetwork()
{
	//TODO: 
	return 1; //network access
}

int CConSendData::SendData()
{
	//TODO:Send waiting list

	char c_num[10];
	sprintf(c_num,"%d",num);
	string sql;
	sql="insert into t_record(BusId,Date,StartTime,ArriveTime,Duration,Departure,Destination,Passenger) values(";
	sql+="'";
	sql+=busid;
	sql+="','";
	sql+=current_date;
	sql+="','";
	sql+=curent_dep_time;
	sql+="','";
	sql+=current_des_time;
	sql+="','";
	sql+=current_duration;
	sql+="','";
	sql+=current_departure;
	sql+="','";
	sql+=current_destination;
	sql+="',";
	sql+=c_num;
	sql+=")";
	cout<<sql.data()<<endl;
	if(!mySql->Insert(sql.data()));
	{
		return 0;
	}
	return 0;
}

string CConSendData::delta_time(const char* src_starttime,const char* src_arrivetime)
{
	char* starttime=new char(64);
	char* arrivetime=new char(64);
	strcpy(starttime,src_starttime);
	strcpy(arrivetime,src_arrivetime);
	const char *d=":";
	vector<int> start;
	char *p=strtok((char*)starttime,d);
	while(p)
	{
	int n=atoi(p);
	start.push_back(n);
	printf("%d\n",n);
	p=strtok(NULL,d);
	}
	vector<int> arrive;
	char *q=strtok((char*)arrivetime,d);
	while(q)
	{
	int m=atoi(q);
	arrive.push_back(m);
	printf("%d\n",m);
	q=strtok(NULL,d);
	}
	int starttime_second=start[0]*3600+start[1]*60+start[2];
	int arrivetime_second=arrive[0]*3600+arrive[1]*60+arrive[2];
	int delta=arrivetime_second-starttime_second;
	int hour=floor(delta/3600);
	int minite=floor((delta%3600)/60);
	int second=delta-hour*3600-minite*60;
	char h[10];
	sprintf(h,"%d",hour);
	char m[10];
	sprintf(m,"%d",minite);
	char s[10];
	sprintf(s,"%d",second);
	string duration=h;
	duration += ":";
	duration += m;
	duration += ":";
	duration += s;
	return duration;
}
