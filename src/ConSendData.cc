#include "ConSendData.hpp"

#define DATABASE_FILE "../data/database.dat"
#define BUSID_FILE "../data/busid.dat"
#define WAITING_FILE "../data/waitinglist.dat"
#define DATA_FILE "../data/data.dat"

CConSendData::CConSendData()
{
	db_addr=new char[20];
	db_user=new char[20];
	db_pswd=new char[20];
	db_name=new char[20];
	evMySql=new EVMySql();
	db_init=false;
	Init();
	last_num=0;
        current_dep_time="00:00:00";
        current_des_time="00:00:00";
        current_duration="00:00:00";
}

CConSendData::~CConSendData()
{
	delete db_addr;
	delete db_user;
	delete db_pswd;
	delete db_name;
	delete evMySql;
}

int CConSendData::SendArriveSignal(char* des)
{
	current_destination=des;
        char tmp_arrivetime[64];
	time_t t=time(0);
	strftime(tmp_arrivetime,sizeof(tmp_arrivetime),"%H:%M:%S",localtime(&t));
        current_des_time=tmp_arrivetime;
        if(current_dep_time!="00:00:00" && current_des_time!="00:00:00")
        {
	       current_duration=delta_time(current_dep_time.data(),current_des_time.data());
	}
        return 0;
}

int CConSendData::SendLeaveSignal(char* dep)
{
	current_departure=dep;
        char tmp_arrivetime[64];
	time_t t=time(0);
	strftime(tmp_arrivetime,sizeof(tmp_arrivetime),"%H:%M:%S",localtime(&t));
        current_dep_time=tmp_arrivetime;
        //current_duration=delta_time(current_des_time.data(),current_dep_time.data());
	return 0;
}

int CConSendData::GetData(int in,int out)
{
	num=in+out;
        if(num>55){num=55;}
        if(num<0){num=0;}
	last_num=num;
        if(current_dep_time!="00:00:00" && current_des_time!="00:00:00")
        {
	       SendData();
        }
	return 0;
}

int CConSendData::Init()
{
	/* get database information */
	ifstream inFile(DATABASE_FILE);
	while(!inFile.eof()){
		inFile>>db_addr>>db_user>>db_pswd>>db_name>>port;
	}
	inFile.close();
	/* Get bus id */
	inFile.open(BUSID_FILE);
	char* _busid=new char[30];
	while(!inFile.eof()){
		inFile>>_busid;
	}
	busid=_busid;
	inFile.close();
	/* Get date */
	char tmp_date[64];
	time_t t=time(0);
	strftime(tmp_date,sizeof(tmp_date),"%Y-%m-%d",localtime(&t));
	puts(tmp_date);
	current_date=tmp_date;
	/* init database connection */
	if(!evMySql->Init((const char*)db_addr,(const char*)db_user,(const char*)db_pswd,(const char*)db_name,port))
	{
		printf("Success to connet to database!\n");
		return 0;
	}
	db_init=true;
	return 1;
}

int CConSendData::SendData()
{
	if(ReadWaitingList()&&waiting_list.size()>0)
	{
		vector<char*>::iterator it=waiting_list.begin();
		while(it!=waiting_list.end())
		{
			if(evMySql->Insert(*it))
			{
				it=waiting_list.erase(it);
			}
			else
			{
				SaveToWaitingList(*it);
				++it;
			}
		}
	}
	char c_num[10];
	sprintf(c_num,"%d",num);
	string sql;
	sql="insert into t_record(BusId,Date,StartTime,ArriveTime,Duration,Departure,Destination,Passenger) values(";
	sql+="'";
	sql+=busid;
	sql+="','";
	sql+=current_date;
	sql+="','";
	sql+=current_dep_time;
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
	SaveToLocal(busid,current_date,current_dep_time,current_des_time,current_duration,current_departure,current_destination,c_num);
	//cout<<sql.data()<<endl;
	if(db_init)
	{
		if(!evMySql->Insert(sql.data()))
		{
			SaveToWaitingList((char*)sql.data());
			return 0;
		}
		return 1;
	}
	else
	{
		SaveToWaitingList((char*)sql.data());
		if(!evMySql->Init((const char*)db_addr,(const char*)db_user,(const char*)db_pswd,(const char*)db_name,port))
		{
			perror("Fail to connet to database!\n");
			return 0;
		}
		db_init=true;
		return 0;
	}
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
	//printf("%d\n",n);
	p=strtok(NULL,d);
	}
	vector<int> arrive;
	char *q=strtok((char*)arrivetime,d);
	while(q)
	{
	int m=atoi(q);
	arrive.push_back(m);
	//printf("%d\n",m);
	q=strtok(NULL,d);
	}
	int starttime_second=start[0]*3600+start[1]*60+start[2];
	int arrivetime_second=arrive[0]*3600+arrive[1]*60+arrive[2];
	int delta=arrivetime_second-starttime_second;
	int hour=floor(delta/3600);
	int minite=floor((delta%3600)/60);
	int second=delta-hour*3600-minite*60;
	char h[10];
	//sprintf(h,"%d",hour);
	char m[10];
	//sprintf(m,"%d",minite);
	char s[10];
	//sprintf(s,"%d",second);
	string duration=h;
	duration += ":";
	duration += m;
	duration += ":";
	duration += s;
	return duration;
}

int CConSendData::SaveToWaitingList(char* sql)
{
	ofstream outfile(WAITING_FILE,ios::app);
	if(!outfile)
	{
		perror("Fail to open waiting list!\n");
		return 0;
	}
	outfile<<sql<<endl;
	outfile.close();
	return 1;
}

int CConSendData::ReadWaitingList()
{
	FILE *fp;
	char* sqlline=new char[1024];
	if((fp=fopen(WAITING_FILE,"r"))==NULL)
	{
		perror("Fail to read waiting file.\n");
		return 0;
	}
	waiting_list.clear();
	while(!feof(fp))
	{
		fgets(sqlline,1024,fp);
                if(sqlline[0]!='\n')
                {
		     waiting_list.push_back(sqlline);
                }
	}
	fclose(fp);
        ofstream outfile(WAITING_FILE,ios::out);
        outfile.close();
	return 1;	
}

int CConSendData::SaveToLocal(string busid,string current_date,string current_dep_time,string current_des_time,string current_duration,string current_departure,string current_destination,string c_num)
{
	string data;
	data += busid;
	data += " ";
	data += current_date;
	data += " ";
	data += current_dep_time;
	data += " ";
	data += current_des_time;
	data += " ";
	data += current_duration;
	data += " ";
	data += current_departure;
	data += " ";
	data += current_destination;
	data += " ";
	data += c_num;
	
	ofstream outfile(DATA_FILE,ios::app);
	if(!outfile)
	{
		perror("Fail to open data.dat!\n");
		return 0;
	}
	outfile<<data.data()<<endl;
	outfile.close();
	return 1;
}
