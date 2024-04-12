#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>

#define DEVICE_NAME "pwhrootkit"
#define CLASS_NAME "pwhrootkit"

static int major_num;
static int erro_code;
static struct class *module_class;
static struct device *module_device;

static ssize_t pwh_rootkit_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t pwh_rootkit_write(struct file *, const char __user *, size_t, loff_t *);
static long pwh_rootkit_ioctl(struct file *, unsigned int, unsigned long);


static struct file_operations pwh_rootkit_fops = {
    .owner = THIS_MODULE,   //这里是内核中实现的一个宏,标示出编译阶段生成的与当前内核模块关联的struct module结构体的地址
    .read = pwh_rootkit_read,
    .write = pwh_rootkit_write,
    .unlocked_ioctl = pwh_rootkit_ioctl,
};


static int __init pwh_init(void){
    /* 注册字符设备 */
    printk(KERN_INFO "[peiwithhao rootkit] Start to register ch-device...");
    major_num = register_chrdev(0, DEVICE_NAME, &pwh_rootkit_fops);
    if(major_num < 0){
        printk(KERN_WARNING "[peiwithhao rootkit] register the chrdev failed!");
        erro_code = major_num;
        goto erro_major;
    }

    printk(KERN_INFO "[peiwithhao rootkit] Start to create a class...");
    module_class = class_create(CLASS_NAME);
    if(IS_ERR(module_class)){
        printk(KERN_WARNING "[peiwithhao rootkit] Create the class failed!");
        erro_code = PTR_ERR(module_class);
        goto erro_class;
    }

    printk(KERN_INFO "[peiwithhao rootkit] Start to create a device...");
    module_device = device_create(module_class, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
    if(IS_ERR(module_device)){
        printk(KERN_WARNING "[peiwithhao rootkit] Create the device failed!");
        erro_code = PTR_ERR(module_device);
        goto erro_device;

    }
    printk(KERN_INFO "[peiwithhao rootkit] Register a ch-device successfully...");
    return 0;

erro_device:
    class_destroy(module_class);
erro_class:
    unregister_chrdev(major_num, DEVICE_NAME);
erro_major:
    return erro_code;
}

static void __exit pwh_exit(void){
    printk(KERN_INFO "Peiwithhao's baby rootkit out :(\n");
    device_destroy(module_class, MKDEV(major_num, 0));
    class_destroy(module_class);
    unregister_chrdev(major_num, DEVICE_NAME);
}


static ssize_t pwh_rootkit_read(struct file *file, char __user *buf, size_t count, loff_t *start){
    return 0;
}
static ssize_t pwh_rootkit_write(struct file *file, const char __user *buf, size_t count, loff_t *start){
    return 0;
}
static long pwh_rootkit_ioctl(struct file *file, unsigned int cmd, unsigned long arg){
    return 0;
}



module_init(pwh_init);
module_exit(pwh_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("peiwithhao");
