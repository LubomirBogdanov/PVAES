/*  absgradientout.c - The simplest kernel module.

* Copyright (C) 2013-2022 Xilinx, Inc
* Copyright (c) 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along
*   with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/interrupt.h>

#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>

#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include <linux/delay.h>

struct file_operations absgradientout_fops;
static dev_t major; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class

struct absgradientout_local *lp = NULL; //Contains the remapped ABSGRADIENTOUT value

typedef struct {
	int32_t grad_0;
	int32_t grad_1;
	int32_t grad_2;
	int32_t grad_3;
	int32_t grad_4;
	int32_t grad_5;
	int32_t grad_out;

	int32_t abs_in0;
	int32_t abs_in1;
	int32_t abs_div;
	uint32_t abs_out;

	uint32_t abs_interrupt;
	uint32_t gpio_out;
}abs_gradient_out_t;

volatile abs_gradient_out_t *ABSGRADOUT0;


/* Standard module information, edit as appropriate */
MODULE_LICENSE("GPL");
MODULE_AUTHOR
    ("Lubomir Bogdanov, TU-Sofia");
MODULE_DESCRIPTION
    ("absgradientout - loadable module template generated by petalinux-create -t modules and modified to support /dev/ file");

#define DRIVER_NAME "absgradientout"

/* Simple example of how to receive command line parameters to your module.
   Delete if you don't need them */
unsigned myint = 0xdeadbeef;
char *mystr = "default";

module_param(myint, int, S_IRUGO);
module_param(mystr, charp, S_IRUGO);

struct absgradientout_local {
	int irq;
	unsigned long mem_start;
	unsigned long mem_end;
	void __iomem *base_addr;
};

static irqreturn_t absgradientout_irq(int irq, void *lp)
{
	printk("absgradientout interrupt\n");
	return IRQ_HANDLED;
}

static int absgradientout_open(struct inode *inode, struct file *file){
	printk(KERN_INFO "absgradientout_open\n");
	return 0;
}

static int absgradientout_close(struct inode *i, struct file *f){
  printk(KERN_INFO "absgradientout_close\n");
  return 0;
}

static ssize_t absgradientout_read(struct file *file, char __user *buf, size_t count, loff_t *ptr){
	printk(KERN_INFO "absgradientout_read\n");

	return count;
}

static ssize_t absgradientout_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos){
	int cmd_int;
	char cmd_str[64];	
	
	if(copy_from_user(cmd_str, buf, count)) {
        	printk("Unable to read buffer from user\n");
        	return -EFAULT;
    	}   
	
	printk(KERN_INFO "absgradientout_write %s\n", cmd_str);

	kstrtoint(cmd_str, 10, &cmd_int); // == atoi		
	
	switch(cmd_int){
	case 0:
		printk(KERN_INFO "Setting ARM Cortex-A9_0 interrupt ...\n");
		ABSGRADOUT0->abs_interrupt |= 0x01;
		udelay(1);
		ABSGRADOUT0->abs_interrupt &= ~0x01;
	break;
	case 1:
		printk(KERN_INFO "Setting MicroBlaze interrupt ...\n");
		ABSGRADOUT0->abs_interrupt |= 0x02;
		udelay(1);
		ABSGRADOUT0->abs_interrupt &= ~0x02;
	break;
	case 2:
		ABSGRADOUT0->gpio_out |= 0x03;
	break;
	case 3:
		ABSGRADOUT0->gpio_out &= ~0x03;
	break;
	}

	return count;
}

static long absgradientout_ioctl(struct file *infile, unsigned int cmd, unsigned long arg){
	printk("firstmod_ioctl: cmd=%d, arg=%ld\n", cmd, arg);

	return 0;
}

static int absgradientout_probe(struct platform_device *pdev)
{
	struct resource *r_irq; /* Interrupt resources */
	struct resource *r_mem; /* IO mem resources */
	struct device *dev = &pdev->dev;
	uint32_t reg_pointer;

	int rc = 0;
	printk(KERN_INFO "Device Tree Probing\n");
	/* Get iospace for the device */
	r_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!r_mem) {
		printk(KERN_INFO "invalid address\n");
		return -ENODEV;
	}
	lp = (struct absgradientout_local *) kmalloc(sizeof(struct absgradientout_local), GFP_KERNEL);
	if (!lp) {
		printk(KERN_INFO "Cound not allocate absgradientout device\n");
		return -ENOMEM;
	}
	dev_set_drvdata(dev, lp);
	lp->mem_start = r_mem->start;
	lp->mem_end = r_mem->end;

	if (!request_mem_region(lp->mem_start,
				lp->mem_end - lp->mem_start + 1,
				DRIVER_NAME)) {
		printk(KERN_INFO "Couldn't lock memory region at %p\n",
			(void *)lp->mem_start);
		rc = -EBUSY;
		goto error1;
	}

	lp->base_addr = ioremap(lp->mem_start, lp->mem_end - lp->mem_start + 1);
	if (!lp->base_addr) {
		printk(KERN_INFO "absgradientout: Could not allocate iomem\n");
		rc = -EIO;
		goto error2;
	}
	

	reg_pointer = lp->base_addr;
	ABSGRADOUT0 = (volatile abs_gradient_out_t *)reg_pointer;

	/* Get IRQ for the device */
	r_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!r_irq) {
		printk(KERN_INFO "no IRQ found\n");
		printk(KERN_INFO "absgradientout at 0x%08x mapped to 0x%08x\n",
			(unsigned int __force)lp->mem_start,
			(unsigned int __force)lp->base_addr);
		return 0;
	}
	lp->irq = r_irq->start;
	rc = request_irq(lp->irq, &absgradientout_irq, 0, DRIVER_NAME, lp);
	if (rc) {
		printk(KERN_INFO "testmodule: Could not allocate interrupt %d.\n",
			lp->irq);
		goto error3;
	}

	printk(KERN_INFO "absgradientout at 0x%08x mapped to 0x%08x, irq=%d\n",
		(unsigned int __force)lp->mem_start,
		(unsigned int __force)lp->base_addr,
		lp->irq);	
		
	return 0;
error3:
	free_irq(lp->irq, lp);
error2:
	release_mem_region(lp->mem_start, lp->mem_end - lp->mem_start + 1);
error1:
	kfree(lp);
	dev_set_drvdata(dev, NULL);
	return rc;
}

static int absgradientout_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct absgradientout_local *lp = dev_get_drvdata(dev);
	free_irq(lp->irq, lp);
	iounmap(lp->base_addr);
	release_mem_region(lp->mem_start, lp->mem_end - lp->mem_start + 1);
	kfree(lp);
	dev_set_drvdata(dev, NULL);
	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id absgradientout_of_match[] = {
	{ .compatible = "xlnx,abs-gradient-out-1.0", },
	{ /* end of list */ },
};
MODULE_DEVICE_TABLE(of, absgradientout_of_match);
#else
# define absgradientout_of_match
#endif

struct file_operations absgradientout_fops = {
	.owner = THIS_MODULE,
	.read = absgradientout_read,
	.write = absgradientout_write,
	.open = absgradientout_open,
	.release = absgradientout_close,
	.unlocked_ioctl = absgradientout_ioctl
};


static struct platform_driver absgradientout_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table	= absgradientout_of_match,
	},
	.probe		= absgradientout_probe,
	.remove		= absgradientout_remove,
};

static int __init absgradientout_init(void)
{
	int result;
	
	printk(KERN_INFO "Platform driver init\n");
	result = platform_driver_register(&absgradientout_driver);

	if (alloc_chrdev_region(&major, 0, 1, "absgradientout") < 0){
		printk("Error registering char device numbers!\n");
    		return -1;
  	}

    	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL){
		printk("Error creating device class!\n");
    		unregister_chrdev_region(major, 1);
    		return -1;
  	}

    	if (device_create(cl, NULL, major, NULL, "absgradientout") == NULL){
		printk("Error creating device!\n");
		class_destroy(cl);
    		unregister_chrdev_region(major, 1);
    		return -1;
  	}

    	cdev_init(&c_dev, &absgradientout_fops);
    	
	if (cdev_add(&c_dev, major, 1) == -1){
		printk("Error adding a char device to the system!\n");
    		device_destroy(cl, major);
    		class_destroy(cl);
    		unregister_chrdev_region(major, 1);
    		return -1;
  	}

	printk("Device file registered successfully in /dev!\n");

	return result;
}


static void __exit absgradientout_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cl, major);
	class_destroy(cl);
	unregister_chrdev_region(major, 1);
	
	platform_driver_unregister(&absgradientout_driver);
	printk(KERN_ALERT "Goodbye module world.\n");
}

module_init(absgradientout_init);
module_exit(absgradientout_exit);
