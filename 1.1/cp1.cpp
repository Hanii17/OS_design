#include <iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string>

const int BUF_SIZE=1024;

using namespace std;

int main(int args,char *argv[])
{
  int f_sourse,f_target;


  //判断命令行参数个数
  if(args!=3)
  {
     cout<<"Error of args num !\n";
     return -1;
  }

  //打开源文件
  if((f_sourse=open(argv[1],O_RDONLY))==-1)
  {
   cout<<"Error of opening sourse file!\n";
   return -1;
  }

  //打开或创建目标文件
  if((f_target=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1)
  {
    cout<<"Error of opening target file!\n";
    return -1;
  }
  int read_nums,write_nums;
  char buffer[BUF_SIZE];
  //进行拷贝操作
  while(1){
    read_nums=read(f_sourse,buffer,BUF_SIZE);
    if(read_nums==0)
     break;
   else if(read_nums==-1)
    {
    cout<<"read error!\n";
    return -1;
    }
    else if(read_nums>0)
      write_nums=write(f_target,buffer,read_nums);
    else if(write_nums==-1)
    {
    cout<<"write error!\n";
    return -1;
    }
    
    }
  close(f_sourse);
  close(f_target);
    return 0;
}
