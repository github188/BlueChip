/*
 * =====================================================================================
 *
 *       Filename:  shmdata.hpp
 *
 *    Description:  share data structure
 *
 *        Version:  1.0
 *        Created:  2015年03月20日 21时28分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Luo Yun (Lauren), Lauren.luo@extremevision.mo
 *        Company:  Extreme Vision Ltd.
 *
 * =====================================================================================
 */

#ifndef SHADATA_H_
#define SHADATA_H_

#define TEXT_SZ 2048

struct shared_use_st
{
		int written; //a flag. -1:data is being written; 0:data is readable and counting cannot begin; 1:data is readable and counting can begin
		char text[TEXT_SZ]; // content of read or write
};

#endif


