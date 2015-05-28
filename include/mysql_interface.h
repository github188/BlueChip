//Copyright(c) 2015 ExtremeVision Ltd. All rights reserved.
//Use of the source code is governed by a LPGL-style.
//License that can be found in the LICENSE file.
//Author: Yun Luo(lauren.luo@extremevision.mo).

#ifndef BLUECHIP_INC_MYSQL_INTERFACE_H_
#define BLUECHIP_INC_MYSQL_INTERFACE_H_

#include "mysql.h"

class IMySql
{
	public:
		IMySql();
		~IMySql();
		int Init(const char* db_addr,
				const char* db_user,
				const char* db_pswd,
				const char* db_name,
				unsigned int port);
		int Close();
		int Insert(const char* sql);
	private:
		MYSQL mysql;

};

#endif //BLUECHIP_INC_MYSQL_INTERFACE_H_

