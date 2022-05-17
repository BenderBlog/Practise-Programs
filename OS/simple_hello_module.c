/* SPDX-License-Identifier: GPL-2.0-only
 *
 * simple_hello_module.c
 *
 * A pretty simple module which say hello in the kernel.
 *
 * Notice that these code are released under GPLv2 only, the same as
 * linux kernel. Not the SuperBart Public Domain Software License!
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>

/* Init this kernel module */
static int __init syscall_start(void)
{
    printk("SIMPLE HELLO MODULE: If I rolling and thumbing and rocking all night long.");
    return 0;
}

/* Uninstall this kernel module */
static void __exit syscall_end(void)
{
    pr_alert("SIMPLE HELLO MODULE: Had to cry for today.");
}

module_init(syscall_start);
module_exit(syscall_end);

MODULE_LICENSE("GPL");
