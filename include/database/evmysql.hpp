/*
 * =====================================================================================
 *
 *       Filename:  evmysql.hpp
 *
 *    Description:  head file of controllong mysql
 *
 *        Version:  1.0
 *        Created:  2015年02月11日 17时46分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), lauren.luo@extremevision.mo
 *   Organization:  Extreme Vision
 *
 * =====================================================================================
 */

#ifndef _EVMYSQL_H_
#define _EVMYSQL_H_

#include "mysql.h"
class EVMySql
{
	public:
		EVMySql();
		~EVMySql();
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

#endif

