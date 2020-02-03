
#include <unistd.h>
#include <sys/syscall.h> 
#include <stdio.h>
#include <linux/kernel.h>

int main()
{
printf("Test function! \n");
int res;
int num1=1, num2=2;
syscall(334, num1, num2, &res);
printf("%d + %d = %d\n", num1,num2, res);
return 0;
}
