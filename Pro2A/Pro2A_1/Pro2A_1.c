#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void){
	printk(KERN_INFO "Welcome to Pro2A_1 module.\n");
	return 0;
}

static void __exit hello_exit(void){
	printk(KERN_INFO "You are leaving Pro2A_1 module.\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test");
MODULE_AUTHOR("Houxiang Ji");
module_init(hello_init);
module_exit(hello_exit);

