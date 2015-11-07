#include<linux/module.h>
#include<linux/sched.h>
#include<linux/printk.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>

MODULE_DESCRIPTION("Hello World !!");
MODULE_LICENSE("GPL");

static char *command = "NULL";
static int pid = -1;

//pass command when install module
module_param(command, charp, S_IRUSR);
module_param(pid, int, S_IRUSR);

//create file
static int hello_proc_show(struct seq_file *m, void *v)
{
	struct task_struct *task;
	//command == "showall"
	if(!strcmp(command, "showall"))
	{
		seq_printf(m, "All of processes:\n");		
		for_each_process(task)
			seq_printf(m, "\t[%d] %s\n", task->pid, task->comm);
	}	
	//command == "parentchild"
	else if(!strcmp(command, "parentchild"))
	{
		seq_printf(m, "Parent of pid=%d:\n", pid);
		//find parent
		for_each_process(task)
			if(task->pid == pid)
				seq_printf(m, "\t[%d] %s\n", task->parent->pid, task->parent->comm);
	
		seq_printf(m, "Child of pid=%d:\n", pid);
		//find child
		for_each_process(task)
			if(task->parent->pid == pid)
				seq_printf(m, "\t[%d] %s\n", task->pid, task->comm);
		
	}
		
	return 0;
}

//use single open to create file
static int hello_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, hello_proc_show, NULL);
}

//file_operations struct to create file in /proc
static const struct file_operations hello_proc_fops = {
	.owner = THIS_MODULE,
	.open = hello_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

//function to initialize module
static int init_func(void)
{
	if(strcmp(command, "NULL"))
		proc_create("hw2_proc", 0, NULL, &hello_proc_fops);	

	return 0;
}

//function to exit module
static void cleanup_func(void)
{
	remove_proc_entry("hw2_proc", NULL);
	printk("Goodbye world!\n");
}

module_init(init_func);
module_exit(cleanup_func);
