# ECEC_353_Final

#intercept_syscalls

 * Compile as follows: gcc -o intercept_syscalls intercept_syscalls.c -std=c99 -Wall 
 * Execute as follows: ./intercept_syscalls ./hello_world
Description-program uses ptrace to intercept the write() system call and modify the contents of the buffer to be all caps when printed by the child


#sandbox.c

 * Compile as follows: gcc -o sandbox sandbox.c -std=c99 -Wall 
 * Execute as follows: ./sandbox ./guest_program 
Description-Program intercepts ptrace system calls and inspect them so that only open() syscalls flagged as O_RDONLY or that create files in the tmp directly can be executed

#counting_sort.c
 * Compile as follows: gcc -o counting_sort counting_sort.c -std=c99 -Wall -O3 -lpthread -lm -D_GNU_SOURCE 
 * Execute as follows: ./counting_sort num_elements num_threads 
Description-Program generates an num_element array of random numbers between 0 and 1023 and sorts them in a serial and parallel fashion.
