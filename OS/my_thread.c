/*
 * 2022 SuperBart, Released under
 * SuperBart Public Domain Software License.
 * You want a process, and here it is!
 * Since process is just a running program.
 */

#include<stdlib.h>  // For random number.
#include<stdio.h>   // For printf.
#include<time.h>    // Used to get seed.
#include<unistd.h>  // For sleep.

// fortune-telling thread
int main()
{
    const char *pool[] = {
        "WEALTH",
        "HAPPINESS",
        "REPUTATION",
        "JUST4LIVING",
        "FORTUNE",
        "MADNESS",
        "YUYUKO",
        "CLAPTON"
    };
    for(;;)
    {
        printf("What is the meaning of the life?\n");
        srand((unsigned)time(NULL));
        printf("%s\n",pool[rand() % 8]);
        sleep(1);
    }
}
