//
// Created by jsz on 2021/3/20.
//

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

/*
 * chrdevbase.c
 * chrdevbase 驱动
 */

#define CHRDEVBASE_MAJOR 200			// 主设备号
#define CHRDEVBASE_NAME "chrdevbase"	// 设备名

static char readbuf[100];	// 读缓冲区
static char writebuf[100];  // 写缓冲区

static char kerneldata[] = {"[[[[kernel data!]]]]"};

/*
 * 打开设备
 * @param inode: 传递给驱动的INODE
 * @param filp:  设备文件
 */
static int chrdevbase_open(struct inode *inode, struct file *filp)
{
	return 0;
}

/*
 * 从设备读数据
 * @param filp	: 要打开的设备文件
 * @param buf	： 返回给用户空间的数据
 * @param cnt	: 要读取的数据长度
 * @param offt	: 相对于文件首地址的偏移
 * @return		: 读取的字节数，负值表示读取失败
 */
static ssize_t chrdevbase_read(struct file *filp,
								char __user *buf,
								size_t cnt,
								loff_t *offt)
{
	int retvalue = 0;

	memcpy(readbuf, kerneldata, sizeof(kerneldata));
	retvalue = copy_to_user(buf, readbuf, cnt);
	if (retvalue == 0) {
		printk("kernel senddata ok!\n");
	}
	else {
		printk("kernel senddata failed!\n");
	}
	return 0;
}

/*
 * 向设备写数据
 * @param filp	: 要打开的设备文件
 * @param buf	： 待写入设备的数据
 * @param cnt	: 要写入的数据长度
 * @param offt	: 相对于文件首地址的偏移
 * @return		: 写入的字节数，负值表示写入失败
 */

static ssize_t chrdevbase_write(struct file *filp,
								const char __user *buf,
								size_t cnt,
								loff_t *off)
{
	int retvalue = 0;
	retvalue = copy_from_user(writebuf, buf, cnt);
	if (retvalue == 0) {
		printk("kernel recvdata: %s\n", writebuf);
	}
	else {
		printk("kernel recvdata failed!\n");
	}

	return 0;
}

/*
 * 关闭设备
 * @param filp	:  要关闭的设备文件
 * @return		: 0 成功；其他 失败
 */
static int chrdevbase_release(struct inode *inode,
								struct file *filp)
{
	return 0;
}


/*
 * 设备操作函数结构体
 */
static struct file_operations chrdevbase_fops = {
		.owner = THIS_MODULE,
		.open = chrdevbase_open,
		.read = chrdevbase_read,
		.write = chrdevbase_write,
		.release = chrdevbase_release,
};

/*
 * 驱动入口
 */
static int __init chrdevbase_init(void)
{
	int retvalue = 0;

	retvalue = register_chrdev(CHRDEVBASE_MAJOR,
								CHRDEVBASE_NAME,
								&chrdevbase_fops);
	if (retvalue < 0) {
		printk("chrdevbase driver register failed\n");
	}
	printk("chrdevbase_init()\n");
	return 0;
}

/*
 * 驱动出口
 */
static void __exit chrdevbase_exit(void)
{
	unregister_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME);
	printk("chrdevbase_exit()\n");
}


/*
 * 注册驱动入口和出口
 */
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);


/*
 * LICENSE和作者
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("alientek");
