#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Firaaz");
MODULE_DESCRIPTOIN("A Sample driver");
MODULE_VERSION("0:0.1");

static int __init hello_world_init(void) {
	printk(KERN_INFO "This is the Simple module\n");
	printk(KERN_INFO "Kernel module loaded successfully");
	return 0;
}

void __exit hello_world_exit(void) {
	printk(KERN_INFO "Basic kernel removed successfully");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
