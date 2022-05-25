代码版权信息：

**有些**代码的授权是 GPLv2 ，与 linux 内核授权相同，不是 SuperBart 公有领域授权协议！

Note that **some** code are released under GPLv2 only,the same as the linux kernel. Not the SuperBart Public Domain Software License.

# 操作系统课程设计实验报告

## 专题1 内核引导
1.  题目要求以及软硬件配置
	* 编译内核，其中版本号需要自行修改
	* 软件：Arch Linux Rolling
	* 硬件：AMD Ryzen 4750U 16 核心 + 16GB 内存
2. 内核引导的关键步骤
   1. 系统自行检查后，加载 UEFI 固件
   2. UEFI 固件寻找引导器（比如 GRUB ），或者像我这样，使用 EFISTUB，直接使用内核文件( vmlinuz 文件)来引导系统。
   3. 如果是引导器的话，得让引导器找内核镜像文件( vmlinuz 文件 )。
   4. 最后加载 img 文件，引导内核，启动第一个进程 systemd，进入系统。
3. 结合自己的uname命令实验结果，说明uname命令结果中的各项数据的含义
   * Linux: 内核名称
   * superbart-lapton: 电脑名称，也就是 `/etc/hostname`
   * 5.17.9-...: 内核发行号
   * #1 ZEN...: 编译时间等内核发行信息
   * x86_64: 架构名称
   * GNU/Linux: 系统名称(不是发行版名称)
4. 大致步骤
   1. 先下载 linux-zen 的 PKGBUILD
   2. 修改 PKGBUILD，去掉 docs 文档软件包的构建，修改 pkgbase 字段。
   3. 执行 makepkg 生成内核安装包和头文件安装包，并安装之。
   4. 更新引导，我的电脑上是需要用 efibootmgr 上写入新的引导入口。

## 专题2 系统调用添加
1. 题目要求以及软硬件配置
   * 在操作系统内核里面添加系统调用
   * 软件：Arch Linux Rolling
   * 硬件：AMD Ryzen 4750U 16 核心 + 16GB 内存
2. 系统调用添加的关键步骤，以及这些步骤的作用
   * kernel/sys.c 下面添加 `SYSCALL_DEFINE1(os_exp, unsigned int, id)`
     这是为了添加系统调用函数，其中 `SYSCALL_DEFINE`后面的数字表示有几个形参，第一个参数是调用名称，第二个是第一个形参的类型，第二个是名称。
   * include/linux/syscalls.h 和 kernel/sys_ni.c 下面注册系统调用
   * include/uapi/asm-generic/unistd.h 下面注册通用系统调用
   * arch/x86/entry/syscalls/syscall_64.tbl 注册 x86 系统调用表   
     上面填写系统调用号的时候，按照这里面的走
3. 给出自己系统调用处理学号的关键代码，并以此代码为例，证明内核编程与应用程序编程的差别。
```C
SYSCALL_DEFINE1(os_exp, unsigned int, id)
{
    long result = 0;
    int end = ((id % 2 == 0) ? 6 : 5);
    int i, j;
    for (i = 0; i < end; i++) {
        int exp = 1;
        for (j = 0; j < i; j++) {
            exp = exp * 10;
        }
        result += exp * (id % 10);
        id /= 10;
    }
    return result;
}
```
差异有：不能在 for 循环里面搞变量声明，因为截止 v5.17 ，内核的语言标准是 C90

## 专题3 内核模块
1.  题目要求以及软硬件配置
	* 编写内核模块，能读取一个进程的信息，然后打印其进程控制块到文件。
	* 软件：Arch Linux Rolling
	* 硬件：AMD Ryzen 4750U 16 核心 + 16GB 内存
	
2. 内核模块编写的关键步骤，以及这些步骤的作用。

   1. 引入两个头文件： `<linux/kernel.h> ` `<linux/module.h>`
   2. 两个宏：`module_init()``module_exit()`，分别是初始化内核模块时候执行的函数和卸载模块释怀运行的函数，要填到这里面。
   3. `static int __init syscall_start(void)` 初始化内核模块函数，`__init`
   4. `static void __exit syscall_end(void)` 卸载内核模块函数，`__exit`

3. 内核模块Makefile和应用程序Makefile之间的区别以及这些区别背后的原因
    区别：模块的 Makefile 需要切换到内核头文件的目录，然后编译
	理由：普通程序需要调用标准 C 库，没有特殊头文件需求，不像内核模块，使用 Linux 内核里面的库

4. 选做题的实现关键步骤，以及这些步骤的作用。
   * 相关函数介绍：
   
     ![](https://raw.githubusercontent.com/BenderBlog/Practise-Programs/main/OS/pcb_get_explation.png)
   
   * 过程分析：打开/新建文件，新建缓冲区。遍历所有的进程，检查进程控制块中里面的 comm 成分，如果和待寻找的相同，读取其信息，写入到缓冲区中。最后将缓冲区写入到文件中。
   
   * 核心代码：
```C
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
```

## 专题4 设备驱动

 1. 题目要求以及软硬件配置

    * 编写内核模块，完善例子中的字符设备程序
    * 软件：Arch Linux Rolling
    * 硬件：AMD Ryzen 4750U 16 核心 + 16GB 内存

 2. 设备驱动中所编写的关键函数（如打开，关闭，读写等）是如何与Linux内核函数进行对接的。

    使用该结构体来实现设备文件：

    ```C
    static struct file_operations rwbuf_fops =
    {
        open : rwbuf_open,				//打开设备
        release : rwbuf_release,		//关闭设备，没有这个将无法卸载模块
        read : rwbuf_read,				//读
        write : rwbuf_write,			//写
        unlocked_ioctl : rwbuf_ioctl	//ioctl 接口
    };
    ```
    里面对这些函数的形参有很多定义，还有两个函数：
    `copy_to_user(buf, rwbuf, count);` `copy_to_user(buf, rwbuf, count);`
    是用来从用户到内核模块里面的数据读写。

 3. 以自己的设备驱动代码为例，说明编写设备驱动应解决的关键问题，及其对应的解决方案。
    * 写入设备的时候，可以注意一下有没有溢出情况，并警告用户
    * 尽量使用宏代替设备端口的物理地址，并且可以使用 #if #define 宏确定版本等信息
    * 注意设备名称要和模块里面给的一样
    * 根据 Linux 设备的文件属性（字符设备文件），我们可以使用 `echo xxx >> /dev/rwbuf`来写入数据

​	

## 个人总结

### 此次实验活动中遇到的哪些关键问题，自己是如何发现并解决的。
   1. 第一次实验：
   * 我们需要使用这个方式添加系统引导。链接在这：https://wiki.archlinux.org/title/EFISTUB
   * 使用 `modprobed-db` 加速内核编译
   * 使用 steam++ 加速代码下载，在`.gitconfig`里特别添加以下代码：  
   ```
   [http]
   	sslVerify = false
   ```
   2. 第二次实验：看得懂这个文章 https://www.kernel.org/doc/html/latest/process/adding-syscalls.html
   3. 第三次实验：查询如何在内核模块中读写文件，Linux 中关于 PCB 结构体的使用。
   4. 第四次实验：保证输出时候的检测，溢出检测。

### 上述问题的发现与解决对自己有哪些启发（从技术层面和学习做事方法两个角度进行说明）
我从这回实验中对 Linux 系统的认识更加深刻，看出来 Linux 内核的严格性与模块性，对之前日常使用 Linux 的时候，对 dkms 之类的东西有了更深的认识。预计可以将其应用于对释放电脑性能(指玩黑山起源)。而对驱动程序的简单编写，也让我对最近英伟达开源驱动到底还是坑有了进一步认识。同时进一步掌握了在互联网上搜索资料的能力。

### 视频两则，本人制作
https://www.bilibili.com/read/cv15236480 提升性能失败尝试
https://www.bilibili.com/video/BV1uL4y1F7MV 内核编译+系统调用
https://www.bilibili.com/video/BV1y54y1d7Ho 内核模块+驱动
