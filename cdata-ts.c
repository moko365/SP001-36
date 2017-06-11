#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <asm/io.h>
#include <asm/uaccess.h>

struct cdata_ts {
	struct input_dev *ts_input;
	int x;
	int y;
};

static int ts_input_open(struct input_dev *dev)
{	
}

static int ts_input_close(struct input_dev *dev)
{
}

static int cdata_ts_open(struct inode *inode, struct file *filp)
{
	struct cdata_ts *cdata;

	cdata = kmalloc(sizeof(struct cdata_ts), GFP_KERNEL);

	/** handling input device ***/
        cdata->ts_input = input_allocate_device();

	cdata->ts_input->name = "cdata-ts";
	cdata->ts_input->open = ts_input_open;
	cdata->ts_input->close = ts_input_close;

    	// Set events
    	cdata->ts_input->evbit[0] = BIT(EV_ABS);
    	// Set types
	cdata->ts_input->absbit[0] = BIT(ABS_X) | BIT(ABS_Y);

	input_set_drvdata(cdata->ts_input, cdata);

	input_register_device(cdata->ts_input);

	cdata->x = 0;
	cdata->y = 0;

	filp->private_data = (void *)cdata;

	return 0;
}

static ssize_t cdata_ts_read(struct file *filp, char *buf, size_t size, loff_t *off)
{
	return 0;
}

static ssize_t cdata_ts_write(struct file *filp, const char *buf, size_t size, 
			loff_t *off)
{
	return 0;
}

static int cdata_ts_close(struct inode *inode, struct file *filp)
{
	return 0;
}

static struct file_operations cdata_ts_fops = {	
	owner:		THIS_MODULE,
	open:		cdata_ts_open,
	release:	cdata_ts_close,
	read:		cdata_ts_read,
	write:		cdata_ts_write
};

static struct miscdevice cdata_ts_misc = {
	minor:		78,
	name:		"cdata-ts",
	fops:		&cdata_ts_fops,
};

int cdata_ts_init_module(void)
{
	if (misc_register(&cdata_ts_misc) < 0) {
	    printk(KERN_INFO "CDATA-TS: can't register driver\n");
	    return -1;
	}
	printk(KERN_INFO "CDATA-TS: cdata_ts_init_module\n");
	return 0;
}

void cdata_ts_cleanup_module(void)
{
	misc_register(&cdata_ts_misc);
}

module_init(cdata_ts_init_module);
module_exit(cdata_ts_cleanup_module);

MODULE_LICENSE("GPL");

