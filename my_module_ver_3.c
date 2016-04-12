#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#define S_IRUGO         (S_IRUSR|S_IRGRP|S_IROTH)

//static int test;
//module_param(test, int, 0644);
typedef int (read_proc_t)(char *page, char **start, off_t off, int count, int *eof, void *data);
//struct proc_dir_entry *create_proc_entry(const char *name, mode_t mode, struct proc_dir_entry *parent);
//struct proc_dir_entry *create_proc_read_entry(const char *name, mode_t mode, struct proc_dir_entry *base, read_proc_t *read_proc, void *data);

struct proc_dir_entry{
unsigned int low_ino;
unsigned short namelen;
const char *name;
mode_t mode;
nlink_t nlink;
uid_t uid;
gid_t gid;
loff_t size;
struct inode_operations *proc;
//read_proc_t *read_proc;
//write_proc_t *write_proc;
};


struct proc_dir_entry *entry;

static int hello_call (struct seq_file *m, void *v){
	printk(KERN_INFO "This is a test for proc file.\n");
	seq_printf(m, "Message from a Linux kernel module.\n");
	return 0;
}

static int hello_open(struct inode *inode, struct file *file){
	return single_open(file, hello_call, NULL);
}

static const struct file_operations proc_file_fops = {
.owner = THIS_MODULE,
.open = hello_open,
.read = seq_read,
.llseek = seq_lseek,
.release = single_release,
};

static int __init hello_init(void){
	printk(KERN_ERR "Greeting from my_module!\n");
	
	entry = proc_create("myproc", 0, NULL, &proc_file_fops); 
	if (!entry){
		printk(KERN_ERR "unable to create /proc/myproc\n");
		return -ENOMEM;
	}
	else{
		printk(KERN_ERR "Successfully create proc");
	}
	return 0;
	//proc_file_fops->mode 	 = S_IFREG | S_IRUGO; //regular file | user/group/others readable, by Tom Xue
	//proc_file_fops->uid 	 = 0;
	//proc_file_fops->gid 	 = 0;
	//proc_file_fops->size      = 37;
}

static void __exit hello_exit(void){
	remove_proc_entry("myproc", NULL);
	printk("KERN_ERR Bye!\n");
}

module_init(hello_init);

module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TEST");
MODULE_AUTHOR("Wen Bo");

