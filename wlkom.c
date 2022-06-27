#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/random.h>
#include <linux/slab.h>

#define DEVICE_NAME "wlkom"

static int major_num;
static char *alphabet = "wlkom";

module_param(alphabet, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(alphabet, "Alphabet");

static int wlkom_open(struct inode *inode, struct file *file)
{
    pr_info("wlkom: Device open\n");
    return 0;
}

static int wlkom_release(struct inode *inode, struct file *file)
{
    pr_info("wlkom: Device close\n");
    return 0;
}

static ssize_t wlkom_read(struct file *file, char *buffer, size_t len, loff_t * offset)
{
    char c;
    int rand;
    int i = 0;
    char *result = kmalloc(len, GFP_KERNEL);
    for (; i < len; i++)
    {
        get_random_bytes(&c, 1);
        rand = c % strlen(alphabet);
        result[i] = alphabet[rand];
    }
    if (copy_to_user(buffer, result, len)) {
        return -EFAULT;
    }
    kfree(result);
    return len;
}

static struct file_operations file_ops = 
{
    .open = wlkom_open,
    .release = wlkom_release,
    .read = wlkom_read
};

static int __init wlkom_init(void)
{
    major_num = register_chrdev(0, "wlkom", &file_ops);
    if (major_num < 0)
    {
        pr_alert("wlkom : Could not register device: %d\n", major_num);
        return major_num;
    }
    else
    {
        pr_info("wlkom: Device registered with major %d\n", major_num);
        return 0;
    }
}

static void __exit wlkom_exit(void)
{
    unregister_chrdev(major_num, DEVICE_NAME);
    pr_info("wlkom: Device unregistered\n");
}

module_init(wlkom_init);
module_exit(wlkom_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malsius");
MODULE_DESCRIPTION("WLKOM");