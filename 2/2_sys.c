/*************************************************************************
 SYSCALL_DEFINE2(mycall_cp,const char*,s_file,const char*,t_file)
 {
   char buf[512];
   int fd_from,fd_to,readnum,writenum;
   
   mm_segment_t old_fs=get_fs();
   set_fs(get_ds());
 
   //open                                                                   
   fd_from = sys_open(s_file,O_RDONLY,S_IRUSR);
   if(fd_from==-1)
   {
       printk("open source file error!");
       return -1;
   }
   fd_to = sys_open(t_file,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
   if(fd_to==-1)
   {
       printk("open target file errpr!");
       return -1;
   }

   while(1)
   {
       readnum=sys_read(fd_from,buf,sizeof(buf));
       if(readnum==-1)
       {
           printk("read error!");
           return -2;
       }
       else if(readnum==0)
       {
           break;
       }
       else
       {
           writenum=sys_write(fd_to,buf,readnum);    
            if(writenum==-1)
           {                                                                
               printk("write error");
               return -2;
           }
           else if(writenum!=readnum)             
	             return -3;
       }
   }
 
   sys_close(fd_from);
   sys_close(fd_to);
   set_fs(old_fs);
   return 0; }



