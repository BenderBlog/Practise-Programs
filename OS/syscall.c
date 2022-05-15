/* SPDX-License-Identifier: GPL-2.0-only
 *
 * syscall.c
 *
 * The same syscall as experiment 1, but in kernel module.
 *
 * Disables page protection at a processor level by changing the 16th bit
 * in the cr0 register (could be Intel specific).
 *
 * Change cr0 register to add new syscall entry in the sys_call_table.
 *
 * For KPROBE analyze sys_call_table, and others.
 * https://github.com/sysprog21/lkmpg/blob/master/examples/syscall.c
 *
 * For experiment code & pt_regs.
 * https://moefactory.com/3041.moe
 *
 * Based on example by Peter Jay Salzman and
 * https://bbs.archlinux.org/viewtopic.php?id=139406
 *
 * Notice that these code are released under GPLv2 only, the same as
 * linux kernel. Not the SuperBart Public Domain Software License!
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>

/* Use kprobes to get sys_call_table. */
#define HAVE_KPROBES 1
#include <linux/kprobes.h>

/* The list of system calls */
#include <linux/unistd.h>
/* Hard_coded syscall number, may vary in terms of the kernel version.
 * Check <linux/unistd.h> for further detail. Mine is <asm/unistd_64.h>
 * Notice that must use somewhere between 330 and 424. Or it may not work */
#define __NR_os_exp_in_module 335

/* Store the sys_call_table */
static unsigned long **sys_call_table;

/* A pt_regs to pass the input value to the syscall properly */
typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);

/* Backup the original address at sys_call_table[__NR_os_exp_in_module] */
static asmlinkage int (*original_call)(void);

/* The same function as experiment 1. Copied from Robotxm */
static asmlinkage int os_exp_in_module(const struct pt_regs *regs)
{
    /* Avoid -Wdeclaration-after-statement, which is not allowed in C90 */
    long id;
    long result;
    id = (long)regs->di;
    result = id % (id % 2 == 0 ? 1000000 : 100000);
    printk("SYSCALL MODULE: id = %ld result = %ld",id,result);
    return result;
}

/* Use KPROBE to get the address of sys_call_table.
   Should be used in any out-of-box kernel, since every kernel has this. */
static unsigned long **aquire_sys_call_table(void)
{
    unsigned long (*kallsyms_lookup_name)(const char *name);
    struct kprobe kp = {
        .symbol_name = "kallsyms_lookup_name",
    };

    if (register_kprobe(&kp) < 0)
        return NULL;
    kallsyms_lookup_name = (unsigned long (*)(const char *name))kp.addr;
    unregister_kprobe(&kp);
    return (unsigned long **)kallsyms_lookup_name("sys_call_table");
}

/* write_cr0 kernel function had removed in v5.3. Fallback to asm. */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 3, 0)
static inline void __write_cr0(unsigned long cr0)
{
    asm volatile("mov %0,%%cr0" : "+r"(cr0) : : "memory");
}
#else
#define __write_cr0 write_cr0
#endif

/* Enable to write sys_call_table by setting the 16th bit of the cr0 register as 1 */
static void enable_write_protection(void)
{
    unsigned long cr0 = read_cr0();
    set_bit(16, &cr0);
    __write_cr0(cr0);
}

/* Disable to write sys_call_table by setting the 16th bit of the cr0 register as 0 */
static void disable_write_protection(void)
{
    unsigned long cr0 = read_cr0();
    clear_bit(16, &cr0);
    __write_cr0(cr0);
}

/* Init this kernel module */
static int __init syscall_start(void)
{
    if (!(sys_call_table = aquire_sys_call_table()))
    {
        printk("SYSCALL MODULE: Unable to get sys_call_table!");
        return -1;
    }

    printk("SYSCALL MODULE: Get sys_call_table at 0x%lx", sys_call_table);
    disable_write_protection();
    original_call = (void *)sys_call_table[__NR_os_exp_in_module];
    sys_call_table[__NR_os_exp_in_module] = (unsigned long *)os_exp_in_module;
    enable_write_protection();

    printk("SYSCALL MODULE: Now you could load syscall in %d. Which at 0x%lx",__NR_os_exp_in_module, sys_call_table[__NR_os_exp_in_module]);
    return 0;
}

/* Uninstall this kernel module */
static void __exit syscall_end(void)
{
    if (!sys_call_table)
    {
        printk("SYSCALL MODULE: Unable to get sys_call_table!");
        return;
    }

    /* Return the system call back to normal */
    if (sys_call_table[__NR_os_exp_in_module] != (unsigned long *)os_exp_in_module)
    {
        pr_alert("SYSCALL MODULE: Somebody else also played with the open system call");
        pr_alert("SYSCALL MODULE: The system may be left in an unstable state.");
    }

    disable_write_protection();
    sys_call_table[__NR_os_exp_in_module] = (unsigned long *)original_call;
    enable_write_protection();
    pr_alert("SYSCALL MODULE: Sucessful uninstalled.");
}

module_init(syscall_start);
module_exit(syscall_end);

MODULE_LICENSE("GPL");

/* Makefile at follow
 * obj-m += syscall.o
 * PWD := $(CURDIR)
 * all:
 * 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
 * clean:
 * 	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
 */
