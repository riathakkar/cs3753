#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
	
int main(){
 int num = syscall(333);
         printf("System call return value: %d\n", num);
         return 0;
}
