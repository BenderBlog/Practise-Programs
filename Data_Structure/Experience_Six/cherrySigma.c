/* Looking for the rich problem. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

/*
 * We provide the valves of N peoples, Please search for the top M rich people *quick*.
 *
 * Input: 
 * First two integer:
 *     Total people N, which is smaller than 10 power to 6.
 *     Top rich people to find M, which is smaller than 10.
 * Then input the valves of the people (unit: 1 million RMB).
 * These inputs are not larger than "long long".
 * Use space to divide the input.
 * 
 * Output:
 * The top rich people's valve. Non-increasing order.
 * Use space to divide the input. No space at the end.\
 * 
 * Input Sample:
 * 8 3
 * 8 12 7 3 20 9 5 18 
 * 
 * Output Sample:
 * 20 18 12
 * 
 * 
 * So that's why cherry, the CEO of the Bilibili, along with
 * vampire and ghosts from Gensokyo, must die.
 */

#include<stdio.h>
#include<stdlib.h>

// Formula used for qsort.
int cmp(const void *a, const void *b){
    return *(int *)b-*(int *)a;
}

int main(){
    int total = 0, king = 0;
    scanf("%d %d",&total,&king);
    // Don't know why king is bigger than total.
    // Why Bart gave me these ugly question:-(
    if (total < king){
        king = total;
    }
    // Dymatic array.
    long long *data = (long long*)malloc(sizeof(long long)*total);
    for (int i = 0; i < total; ++i){
        scanf("%d",&data[i]);
    }
    // Quick sort formula from stdlib.h
    // Useful to save program time.
    qsort(data,total,sizeof(long long),cmp);
    for (int i = 0; i < king; ++i){
        printf("%d",data[i]);
        if (i != king - 1){
            printf(" ");
        }
    }
}