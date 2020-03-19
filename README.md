# ECEC_353_Final

#intercept_syscalls

 * Compile as follows: gcc -o intercept_syscalls intercept_syscalls.c -std=c99 -Wall 
 * Execute as follows: ./intercept_syscalls ./hello_world
Description-program uses ptrace to intercept the write() system call and modify the contents of the buffer to be all caps when printed by the child


#sandbox.c

 * Compile as follows: gcc -o sandbox sandbox.c -std=c99 -Wall 
 * Execute as follows: ./sandbox ./guest_program 
Description-Program intercepts ptrace system calls and inspect them so that only open() syscalls flagged as O_RDONLY or that create files in the tmp directly can be executed