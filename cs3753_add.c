#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>

asmlinkage long sys_cs3753_add(int num1, int num2, int* result)
{
printk(KERN_ALERT "%d", num1);
printk(KERN_ALERT "%d", num2);
int kern_result = num1+num2;
copy_to_user(result, &kern_result, 4);
printk(KERN_ALERT "%d", kern_result);
return 0;
}
