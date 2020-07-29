#include<stdio.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

int main(int argc,const char*argv[])
{
	if(argc==3)
	{
		long int ret=syscall(335,argv[1],argv[2]);
		printf("syscall return : %ld\n",ret);
	}
	else
	{
		printf("plz enter copy files when run exe\n");
	}
	return 0;
}
