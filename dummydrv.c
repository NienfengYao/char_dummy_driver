#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/moduleparam.h>

#define SUCCESS 0
#define DEVICE_NAME "dummydrv"
#define BUF_LEN 64*1024		/* Max length of the message from the device */


static int major_num = 255;	/* major_num number assigned to our device driver */
static int dev_open_count = 0; /* Is device open? Used to prevent multiple */

//static char msg[BUF_LEN];	/* The msg the device will give when asked */
static int total_num = 0;	/* The total count that write in */

static int device_open(struct inode *inode, struct file *file)
{
	if (dev_open_count)
		return -EBUSY;
	
	dev_open_count++;
	printk("%s() call\n", __func__);
	total_num = 0;
	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
	dev_open_count--; /* We're now ready for our next caller */
	printk("%s() call.\n", __func__);
	return 0;
}

static ssize_t device_read(struct file *file, char *buff, size_t len, loff_t *off)
{
/*
	if (len < BUF_LEN) {
		copy_to_user(buff, msg, len);
		return len;
	}
	else {
		copy_to_user(buff, msg, BUF_LEN);
		return BUF_LEN;
	}
*/
	return total_num;
}

static ssize_t device_write(struct file *filp, const char *buff, size_t len,
                            loff_t *off)
{
	if (BUF_LEN >= len){
		total_num += len;
		return len;
	}else {
		printk ("Support maximum length = %d\n", BUF_LEN);
		return -EINVAL;
	}
}

static struct file_operations fops = {
	.read    = device_read, 
	.write   = device_write,
	.open    = device_open,
	.release = device_release
};

static int __init dummydrv_init(void)
{
	int ret = register_chrdev(major_num, DEVICE_NAME, &fops);
	
	if (ret < 0)  {
		printk("Registering the character device failed with %d\n", ret);
		return ret;
	}
	
	printk("'create driver file: mknod /dev/%s c %d 0'.\n", DEVICE_NAME, major_num);
	//memset(msg, 0x0, 80);	
	return 0;
}

static void __exit dummydrv_exit(void)
{
	unregister_chrdev(major_num, DEVICE_NAME);
} 

module_init(dummydrv_init);
module_exit(dummydrv_exit);
