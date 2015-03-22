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
		char location[100];
		lenstr=getenv("CONTENT_LENGTH");
		len=atoi(lenstr);
		fgets(poststr,len+1,stdin);
		sscanf(poststr,"location=%s",location);
		printf("%s\n",location);

		std::string cmd("/root/Project_Master_Macau_System/bin/GPS_add");
		cmd += " ";
		cmd += location;
		printf("%s\n",cmd.data());

		int ret=system(cmd.data());
		printf("%d",ret);
		return 0;
}
