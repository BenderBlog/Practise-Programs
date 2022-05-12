// Could be used in 5.17 version of the kernel.
// Syscall numbers may vary!

#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("%06ld\n",syscall(451,1234567890));
    printf("%06ld\n",syscall(451,1234567891));
    return 0;
}
