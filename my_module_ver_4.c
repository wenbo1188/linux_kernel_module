#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h> //proc_fs
#include <linux/seq_file.h> //seq_file
#include <linux/fs.h> //struct file,struct inode
#include <linux/sched.h>    //next_task()

static void *ps_seq_start(struct seq_file *s,loff_t *pos){
struct task_struct *task;

seq_printf(s,"%s\t%s\t%s\n","pid","ctx","comm"); //读取格式

if(*pos>0)
return NULL;
else{
task=next_task(current);
return task;
}
}

static void *ps_seq_next(struct seq_file *s,void *v,loff_t *pos){
struct task_struct *task=(struct task_struct *)v;
++*pos;
if(task->pid== current->pid){
return NULL;
}else{
task=next_task(task);
return task;
}
}

static void ps_seq_stop(struct seq_file *s,void *v){}

static int ps_seq_show(struct seq_file *s,void *v){
//rwlock_t lock = RW_LOCK_UNLOCKED;
struct task_struct *task=(struct task_struct *)v;
//read_lock(&lock);

seq_printf(s,"%d\t%d\t%s\n",task->pid,task->ctx,task->comm);

//read_unlock(&lock);
return 0;
}

static struct seq_operations ps_seq_ops = {
.start = ps_seq_start,
.next = ps_seq_next,
.stop = ps_seq_stop,
.show = ps_seq_show
};

static int ps_open(struct inode *inode,struct file *file){
return seq_open(file,&ps_seq_ops);
}

static struct file_operations ps_file_ops = {
.owner = THIS_MODULE,
.open = ps_open,
.read  =  seq_read,
.llseek = seq_lseek,
.release= seq_release
};



static int __init hello_init(void){
struct proc_dir_entry *entry;
entry = proc_create("myproc",0,NULL,&ps_file_ops);
return 0;
}

static void __exit hello_exit(void){
remove_proc_entry("myproc",NULL);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TEST");
MODULE_AUTHOR("Wen Bo");

