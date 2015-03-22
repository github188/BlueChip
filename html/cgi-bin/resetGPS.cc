#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>

int main()
{
		printf("Content-Type:text/html;charset=utf-8\n\n");
		printf("Hello,world\n");

		std::string cmd("/root/Project_Master_Macau_System/bin/GPS_reset");

		printf("%s\n",cmd.data());

		int ret=system(cmd.data());
		printf("%d",ret);
		return 0;
}
