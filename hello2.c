#include "hello1.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("Zherdiev Danylo <zerdevdanil430@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

extern void print_hello(void);

static unsigned int number_of_iterations = 1;
module_param(number_of_iterations, uint, S_IRUGO);
MODULE_PARM_DESC(number_of_iterations, "Number of how many times 'Hello world' will be printed");

static int __init hello_init(void)
{
	if (number_of_iterations == 0) {
		pr_warn("You printed 0 iterations\n");
	} else if (number_of_iterations >= 5 && number_of_iterations <= 10) {
		pr_warn("You printed between 5 and 10\n");
	} else if (number_of_iterations > 10) {
		pr_err("You printed number bigger than 10\n");
		return -EINVAL;
	}

	int counter = 0;
	while (number_of_iterations != counter) {
		print_hello();
		counter++;
	}
	return 0;
}

static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);
