#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

static int test;
module_param(test, int, 0644);


static int __init hello_init(void){
	printk("KERN_ERR Greeting from my_module!\n");
	printk("KERN_ERR Params:test:%d\n", test);
	return 0;
}


static void __exit hello_exit(void){
	printk("KERN_ERR Bye!\n");
}

module_init(hello_init);

module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TEST");
MODULE_AUTHOR("Wen Bo");

