#include <hello1.h>
// hello1.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Zherdiev Danylo <zerdevdanil430@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct my_data {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

LIST_HEAD(my_list_head);

void print_hello(void)
{
	struct my_data *my_data = kmalloc(sizeof(*my_data), GFP_KERNEL);

	my_data->start_time = ktime_get();
	pr_info("Hello, world!\n");
	my_data->end_time = ktime_get();

	list_add(&my_data->list, &my_list_head);
}
EXPORT_SYMBOL(print_hello);

static int __init hello_init(void)
{
	return 0;
}

static void __exit hello_exit(void)
{
	struct my_data *my_data,  *next;
	list_for_each_entry_safe(my_data, next, &my_list_head, list) {
		pr_info("Start time: %lld nano seconds\n", ktime_to_ns(my_data->start_time));
		pr_info("End time: %lld nano seconds\n", ktime_to_ns(my_data->end_time));
		pr_info("Time elapsed: %lld nano seconds\n", ktime_to_ns(my_data->end_time) - ktime_to_ns(my_data->start_time));

		list_del(&my_data->list);

		kfree(my_data);
	}
}

module_init(hello_init);
module_exit(hello_exit);
