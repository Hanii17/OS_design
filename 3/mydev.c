#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>


char test_msg[1024]="the original information";
int my_major=0;

static int myopen(struct inode *inode,struct file *file){
	printk("mydevice open successfully\n");
	return 0;
}

static int myrelease(struct inode *inode,struct file *file)
{
	printk("mydevice released\n");
	return 0;
}

static ssize_t myread(struct file *file1,char __user *buf,size_t size,loff_t *pos)
{
	if(raw_copy_to_user(buf,test_msg,sizeof(test_msg)))
	{
	  return -2;
	}
	return sizeof(test_msg);

}
static ssize_t mywrite(struct file *file1,const char __user *buf,size_t size,loff_t *pos)
{
	if(raw_copy_from_user(test_msg,buf,sizeof(test_msg)))
	{
	  return -2;
	}
	return sizeof(test_msg);

}

struct file_operations myfops = {
    .open =myopen,
    .release=myrelease,
    .read =myread,
    .write =mywrite,
};

static int __init myinit(void){
int result;
   result=register_chrdev(0,"drive_hzy",&myfops);
   if(result<0){
       printk("error:can not register the device\n");
       return -1;
   }
   else {
     my_major=result;
       printk("<1>hehe,the device has been registered!\n");
       printk("<1>the virtual device was assigned major number %d.\n",result);
       printk("<1>To talk to the driver,create a dev file with\n");
       printk("<1>'mknod/dev/my c %d 0'\n",result);
       printk("<1>Remove the dev and the file when done\n");
   }
  return 0;

}

static void __exit myexit(void){
    unregister_chrdev(my_major,"drive_hzy");
    printk("<1>unloading the device\n");
}


MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);
