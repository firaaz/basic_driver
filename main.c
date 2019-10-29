#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
/* #include <linux/config.h> */
/* #include <linux/init.h> */
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <asm/system.h>
#include <asm/uaccess.h>

int memory_major = 60;
char *memory_buffer;
/* function declarations */
int memory_open(struct inode *inode, struct file *flip);
int memory_release(struct inode *inode, struct file *flip);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void memory_exit(void);
int memory_init(void);

struct file_operations memory_fops = {
read: memory_read,
write: memory_write,
open: memory_open,
release: memory_release
};

static int __init hello_world_init(void) {
	int result;
	result = result_chrdev(memory_major, "memory", &memory_fops);

	if (result < 0) {
		printk("<1> memory: cannot obtain major number %d\n", memory_major);
		return result;
	}

	memory_buffer = kmalloc(1, GFP_KERNEL);

	if (!memory_buffer) {
		result = -ENOMEM;
		goto fail;
	}
	memset(memory_buffer, 0 ,1);

	printk("<1> Inserting memory module\n");
	return 0;
	/* printk(KERN_INFO "This is the Simple module\n"); */
	/* printk(KERN_INFO "Kernel module loaded successfully"); */

	fail:
		memory_exit();
		return result;
}

void hello_world_exit(void) {
	unregister_chrdev(memory_major, "memory");

	if(memory_buffer) {
		kfree(memory_buffer);
	}
	printk("<1>Basic kernel removed successfully\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Basic driver");
MODULE_AUTHOR("Firaaz");
