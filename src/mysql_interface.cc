//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).


#include "mysql_interface.h"

#include <string.h>
#include <stdio.h>

IMySql::IMySql(){

}

IMySql::~IMySql(){
	Close();
}

int IMySql::Init(const char* db_addr,
		const char* db_user,
		const char* db_pswd,
		const char* db_name,
		unsigned int port){
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,
				db_addr,
				db_user,
				db_pswd,
				db_name,
				port,NULL,0)){
		printf("Failed to connect to Mysql!\n");
		return 0;
	}else{
		printf("Connect to Mysql successfully!\n");
		mysql_query(&mysql,"set names utf8");
		return 1;
	}
}

int IMySql::Close(){
	mysql_close(&mysql);
	return 1;
}

int IMySql::Insert(const char* sql){
	if(!mysql_query(&mysql,sql)){ //return 0 for insert success.
		//printf("insert failed!");
		return 1;
	}else{
		return 0;
	}
}
