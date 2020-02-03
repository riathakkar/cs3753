# cs3753

Ria Thakkar
ria.thakkar@colorado.edu

Makefile - /home/kernel/linux-hwe-4.15.0/arch/x86/kernel/Makefile

cs3753_add.c - /home/kernel/linux-hwe-4.15.0/arch/x86/kernel/cs3753_add.c

test_add.c - /home/kernel/linux-hwe-4.15.0/cs3753_add_test.c

test_helloworld.c -/home/kernel/linux-hwe-4.15.0/helloworld_test.c

syscall_64.tbl - /home/kernel/linux-hwe-4.15.0/arch/x86/entry/syscalls/syscall_64.tbl

syscalls.h - /home/kernel/linux-hwe-4.15.0/include/linux/syscalls.h

syslog - /var/log/syslog

cs3753_add and helloworld.c have the code for the system calls.
test_add and test_helloworld test the code in those system calls. 
Makefile tells the kernel what to compile
syscall_64.tbl tables all the sys calls.
syscalls.h contains the headers

run test_add.c -> sudo gcc test_add.c
-> ./a.out
-> dmesg
