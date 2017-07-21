#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#define SIZE 10

static int int_param;
static char *string_param="world";
static int array_param[SIZE];
static int num;

module_param(int_param, int, 0644);
module_param(string_param, charp, 0644);
module_param_array(array_param, int, &num, 0644);


EXPORT_SYMBOL(hello_foo);

static int __init hello_init(void){
	int i;
	printk(KERN_INFO "Welcome to Pro2A_2 module.\n");
	printk(KERN_INFO "Params: int_param:%d;\n",int_param);
	printk(KERN_INFO "        string_param:%s;\n",string_param);
	printk(KERN_INFO "        array_param:%d",array_param[0]);
	for (i=1;i<num;++i){
	printk(KERN_INFO "                    %d",array_param[i]);
}
	printk(KERN_INFO "\n");
	return 0;
}

static void __exit hello_exit(void){
	printk(KERN_INFO "You are leaving Pro2A_2 module.\n");
}
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test");
MODULE_AUTHOR("Houxiang Ji");
module_init(hello_init);
module_exit(hello_exit);
