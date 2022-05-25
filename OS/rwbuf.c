/* SPDX-License-Identifier: GPL-2.0-only
 *
 * rwbuf.c
 *
 * Copied from Robotxm, for the rwbuf experiment.
 *
 * Notice that these code are released under GPLv2 only, the same as
 * linux kernel. Not the SuperBart Public Domain Software License!
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>
// 用于 ioctl 命令
#define RW_CLEAR 0x909090
// 设备名称
#define DEVICE_NAME "rwbuf"
// 缓冲区最大长度
#define RWBUF_MAX_SIZE 1024
// 当前缓冲区长度，注意设置为 12 是因为要求在内核模块安装完成之后需要立刻能读出学号
// 注意有终止符
static int rwlen = 12;
// 缓冲区，初始值需要是学号以便能在设备安装后立刻读出
static char rwbuf[RWBUF_MAX_SIZE] = "20009200493";
// 锁机制，保证只能有一个打开的设备。0 为未打开，1 为已打开
static int inuse = 0;
/**
 * 打开设备
 * 
 * @return 0 表示成功，-1 表示失败
 */
int rwbuf_open(struct inode *inode, struct file *file)
{
    if (inuse == 0)
    {
        inuse = 1;
        // increase the use count in struct module
        try_module_get(THIS_MODULE);
        return 0;
    }
    else
        return -1;
}
/**
 * 关闭设备
 * 
 * @return 0 表示成功 
 */
int rwbuf_release(struct inode *inode, struct file *file)
{
    inuse = 0;
    // decrease the use count in struct module
    module_put(THIS_MODULE);
    return 0;
}
/**
 * 从设备中读取内容
 * 
 * @param buf 存放读取内容的缓冲区
 * @return 正数表示成功，-1 表示错误 
 */
ssize_t rwbuf_read(struct file *file, char *buf, size_t count, loff_t *f_pos)
{
    if (rwlen > 0 && rwlen <= RWBUF_MAX_SIZE)
    {
        printk("[rwbuf] Current rwbuf size is %ld, rwlen = %d.\n", strlen(rwbuf), rwlen);
        copy_to_user(buf, rwbuf, count);
        printk("[rwbuf] Read successful. After reading, rwlen = %d\n", rwlen);
        // 这里原先是想写个 0 的，以满足 cat 命令退出的需求。但是每次一执行 cat /dev/rwbuf 就报错。
        // 所以还是保持原样吧
        return count;
    }
    else if(rwlen == 0){
    	printk("[rwbuf] Read failed. Empty.");
    	return 0;
    }
    else
    {
        printk("[rwbuf] Read failed. rwlen = %d\n", rwlen);
        return -1;
    }
}
/**
 * 将内容写入到设备
 * 
 * @param buf 存放待写入内容的缓冲区
 * @return 正数表示成功，-1 表示错误 
 */
ssize_t rwbuf_write(struct file *file, const char *buf, size_t count, loff_t *f_pos)
{
    if (count > 0)
    {
    	//丢弃超越上限的部分
        if (count > RWBUF_MAX_SIZE - 1)
        {
            printk("[rwbuf] Input overflow! Count is %lu, larger than %d.\n",count,RWBUF_MAX_SIZE - 1);
            rwlen = RWBUF_MAX_SIZE - 1;
        }
        else
        {
            rwlen = count;
        }
        //读取成功返回0，否则是还差多少，就这样吧......
        //报错说忽略了返回值
        copy_from_user(rwbuf, buf, rwlen);
        rwbuf[rwlen]='\0'; //不得不留一位给\0
        printk("[rwbuf] Write successful. After writing, rwlen = %d\n", rwlen);
        return count;
    }
    else
    {
        printk("[rwbuf] Write failed. Length of string to be written = %lu\n", count);
        return -1;
    }
}
/**
 * ioctl 操作
 * 
 * @param arg 要执行的操作
 * @return 0 表示成功，-1 表示错误 
 */
long rwbuf_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("[rwbuf] [RW_CLEAR:%x],[cmd:%x]\n", RW_CLEAR, cmd);
    if (cmd == RW_CLEAR) // 清空缓冲区
    {
        rwlen = 0;
        printk("[rwbuf] Do ioctl successful. After doing ioctl, rwlen = %d\n", rwlen);
        return 0;
    }
    else // 无效命令
    {
        printk("[rwbuf] Do ioctl failed. rwlen = %d\n", rwlen);
        return -1;
    }
}
static struct file_operations rwbuf_fops =
{
    open : rwbuf_open,
    // 没这玩意卸载不了模块
    release : rwbuf_release,
    read : rwbuf_read,
    write : rwbuf_write,
    unlocked_ioctl : rwbuf_ioctl
};
static int __init rwbuf_init(void)
{
    int ret = -1;
    printk("[rwbuf] Initializing device...\n");
    // 60: 主设备号，与创建 /dev/rwbuf 时使用的对应
    // DEVICE_NAME: 上面定义的设备名称
    // &rwbuf_fops: VFS 相关
    ret = register_chrdev(60, DEVICE_NAME, &rwbuf_fops);
    if (ret != -1)
        printk("[rwbuf] Initialize successful\n");
    else
        printk("[rwbuf] Initialize failed\n");
    return ret;
}
static void __exit rwbuf_exit(void)
{
    unregister_chrdev(60, DEVICE_NAME);
    printk("[rwbuf] Uninstall successful\n");
}
module_init(rwbuf_init);
module_exit(rwbuf_exit);
MODULE_LICENSE("GPL");
