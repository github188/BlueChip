#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>

int main()
{
		printf("Content-Type:text/html;charset=utf-8\n\n");
		printf("Hello,world\n");

		int len;
		char* lenstr,poststr[20];
		char id[100];
		lenstr=getenv("CONTENT_LENGTH");
		len=atoi(lenstr);
		fgets(poststr,len+1,stdin);
		sscanf(poststr,"id=%s",id);
		printf("%s\n",id);

		std::string cmd("/root/Project_Master_Macau_System/bin/GPS_del");
		cmd += " ";
		cmd += id;
		printf("%s\n",cmd.data());

		int ret=system(cmd.data());
		printf("%d",ret);
		return 0;
}
