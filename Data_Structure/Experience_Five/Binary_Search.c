/* Binary Search Demo.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stdlib.h>

// This formula is used in the qsort formula.
// enter two elements, then return a flag.
int cmp(const void *a,const void *b)
{
    /* If the flag is smaller than 0, a is at the front of b.
     * If the flag is bigger than 0,  a is at the back of b.
     * Else a is equal to b.
     */
    return *(int *)a-*(int *)b;
}

// Binary Search Formula
int search(int toFind, int *array, int size, int low, int high){
    if (low <= high){
        int middle = (low + high)/2;
        int a = array[middle];
        if (array[middle] == toFind){
            return 0;
        } else if (array[middle] > toFind){
            search(toFind, array, size, low, middle - 1);
        } else {
            search(toFind, array, size, middle + 1, high);
        }
    } else {
        return 1;
    }
}

int main(){
    /* 'rndtable' from DOOM Source Code m_random.c.
     * Refrence:
     *      https://github.com/id-Software/DOOM/blob/master/linuxdoom-1.10/m_random.c
     *      https://github.com/chocolate-doom/chocolate-doom/blob/master/src/doom/m_random.c
     * Note that DOOM Source Code are licensed under GPLv2+
     * Cyberdemon is the creature of me, Bender. Bite my shiny metal ass!
     */
    int rndtable[256] = {
    0,   8, 109, 220, 222, 241, 149, 107,  75, 248, 254, 140,  16,  66 ,
    74,  21, 211,  47,  80, 242, 154,  27, 205, 128, 161,  89,  77,  36 ,
    95, 110,  85,  48, 212, 140, 211, 249,  22,  79, 200,  50,  28, 188 ,
    52, 140, 202, 120,  68, 145,  62,  70, 184, 190,  91, 197, 152, 224 ,
    149, 104,  25, 178, 252, 182, 202, 182, 141, 197,   4,  81, 181, 242 ,
    145,  42,  39, 227, 156, 198, 225, 193, 219,  93, 122, 175, 249,   0 ,
    175, 143,  70, 239,  46, 246, 163,  53, 163, 109, 168, 135,   2, 235 ,
    25,  92,  20, 145, 138,  77,  69, 166,  78, 176, 173, 212, 166, 113 ,
    94, 161,  41,  50, 239,  49, 111, 164,  70,  60,   2,  37, 171,  75 ,
    136, 156,  11,  56,  42, 146, 138, 229,  73, 146,  77,  61,  98, 196 ,
    135, 106,  63, 197, 195,  86,  96, 203, 113, 101, 170, 247, 181, 113 ,
    80, 250, 108,   7, 255, 237, 129, 226,  79, 107, 112, 166, 103, 241 ,
    24, 223, 239, 120, 198,  58,  60,  82, 128,   3, 184,  66, 143, 224 ,
    145, 224,  81, 206, 163,  45,  63,  90, 168, 114,  59,  33, 159,  95 ,
    28, 139, 123,  98, 125, 196,  15,  70, 194, 253,  54,  14, 109, 226 ,
    71,  17, 161,  93, 186,  87, 244, 138,  20,  52, 123, 251,  26,  36 ,
    17,  46,  52, 231, 232,  76,  31, 221,  84,  37, 216, 165, 212, 106 ,
    197, 242,  98,  43,  39, 175, 254, 145, 190,  84, 118, 222, 187, 136 ,
    120, 163, 236, 249
    };
    /* Qsort formula from "stdlib.h" since C90.
     * Usage:
     *   qsort(point to the array with data,           // const void *data
     *         how many elements in the array,         // int numbers
     *         the size of the elements in the array,  // int size
     *         formula to evaluate compare);           // const void *formula
     */
    qsort(rndtable,sizeof(rndtable)/sizeof(int),sizeof(int),cmp);
    // Binary Search for not found numbers between 0 and 256.
    for (int i = 0; i < sizeof(rndtable)/sizeof(int); ++i)
        if (search(i,rndtable,sizeof(rndtable)/sizeof(int),0,sizeof(rndtable)/sizeof(int)) == 1)
            printf("Not Found %d!\n", i);
    return 0;
}
