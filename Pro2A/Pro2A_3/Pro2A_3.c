#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/kernel.h>

static char *str = NULL;
static struct proc_dir_entry *myfolder;
static struct proc_dir_entry *hello;

static int mytest_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Message from a Linux Kernel Module.\n");
	seq_printf(m, "Current content is:%s\n", str);
	return 0;
}
static int my_open(struct inode *inode,struct file *test_file)
{
       return single_open(test_file, mytest_proc_show, NULL); 
}

static ssize_t my_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos){
	char *tmp = kzalloc((count +1), GFP_KERNEL);
	if (!tmp)	return -ENOMEM;
	
	if (copy_from_user(tmp, buffer, count)){
		kfree(tmp);
		return -EFAULT;
	}

	kfree(str);
	str = tmp;

	return count;
}



static struct file_operations my_fileops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = seq_read,
	.write = my_write,
 	.llseek  = seq_lseek,
 	.release = single_release,
};

static int __init hello_init(void)
{
	myfolder = proc_mkdir("myfolder", NULL);
        if(!myfolder)
	return -1;
	else{
		printk (KERN_INFO "Directory 'myfolder' created successfully in /proc.\n");
	}
        
	hello = proc_create("hello", 0666, myfolder, &my_fileops);
	if(!hello)
	return -1;
	else{
		printk (KERN_INFO "File 'hello' is created successfully in 'myfolder'.\n");
		return 0;
	}	
}

static void __exit hello_exit(void)
{
	printk(KERN_ERR "You are exiting the Pro2A_3 module.\n"); 
	kfree(str);
	remove_proc_entry("hello", myfolder);       
	remove_proc_entry("myfolder", NULL);
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test");
MODULE_AUTHOR("Houxiang Ji");
module_init(hello_init);
module_exit(hello_exit);
