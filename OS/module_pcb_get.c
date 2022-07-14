/* SPDX-License-Identifier: GPL-2.0-only
 *
 * pcb_get_module.c
 *
 * Get the specific process' information and write it to the log.
 *
 * Notice that these code are released under GPLv2 only, the same as
 * linux kernel. Not the SuperBart Public Domain Software License!
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

/* Actually the same as string.h. From this file:
 * We don't want strings.h stuff being used by user stuff by accident */
#include <linux/string.h>

/* For for_each_process() macro */
#include <linux/sched/signal.h>

/* For read and write files to file, or stdin */
#include <linux/fs.h>
#include <linux/uaccess.h>

/* A struct which store the Process Control Block */
struct task_struct *p;

/* The name of the process which we need to find */
char process_to_find[TASK_COMM_LEN] = "my_thread";

/* The name of the file that we need to write to
 * So the syslog is in the hard drive, so... */
char write_to[] = "/var/log/pcb_get_module_information.log";

/* Init this kernel module */
static int __init module_start(void)
{
    /* Write something to a file,
     * loff_t is the recent places to write */
    struct file *fp;
    loff_t pos;
    char buffer[1024] = {'\0'};

    fp = filp_open(write_to, O_RDWR | O_CREAT, 0644);
    printk("PCB GET MODULE: Getting a process...");
    for_each_process(p)
    {
        /* The process we are looking at,
         * using get_task_comm to get the value */
        char searching_process[TASK_COMM_LEN] = {'\0'};
        get_task_comm(searching_process,p);
        /* Find the same process */
        if (strncmp(searching_process,process_to_find,10) == 0)
        {
            printk("PCB GET MODULE: Found! Process %s pid %d.",searching_process,p->pid);
            printk("Now writing to %s.",write_to);
            /* Prepare for the thing to write
             * I am too lazy to print out all the information in the PCB. Fxxk jwc. */
            sprintf(buffer,"Process %s pid %d\n", searching_process, p->pid);
            goto end;
        }
        else
        {
            continue;
        }
    }
    printk("PCB GET MODULE: Not found process %s.",process_to_find);
    sprintf(buffer,"Process %s not found.\n", process_to_find);
    goto end;
end:
    pos = fp->f_inode->i_size;
    /* Note that vfs_read & vfs_write had removed in v4.14
     * Use kernel_write and kernel_read instead. */
    kernel_write(fp, buffer, sizeof(buffer), &pos);
    filp_close(fp,NULL);
    return 0;
}

/* Uninstall this kernel module */
static void __exit module_end(void)
{
    pr_alert("PCB GET MODULE: Now exit.");
}

module_init(module_start);
module_exit(module_end);

MODULE_LICENSE("GPL");

