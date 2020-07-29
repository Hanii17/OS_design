/*************************************************************************
    > File Name: test_dev.c
    > Author: DHD
    > Mail: 
    > Created Time: Wed 29 Jul 2020 07:55:52 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(){
	int wd,rd;
	char buf[1024];
	char input[1024];

	int fd=open("/dev/mydev",O_RDWR | O_NONBLOCK);
	if(fd==-1)
	{
		printf("Open device failed\n");
	   return -1;
	}
	else
	{
		printf("Open device successfully\n");
	   rd=	read(fd,buf,sizeof(buf));
	   printf("read num:%d %s\n",rd,buf);

	   printf("plz input into device:");
	   fgets(input,sizeof(input),stdin);

	   wd=write(fd,input,sizeof(input));
	   printf("write num:%d\n",wd);
	   rd=read(fd,buf,sizeof(buf));
	   printf("read num:%d %s\n",rd,buf);
	   close(fd);
	   return 0;

	}
    
}
