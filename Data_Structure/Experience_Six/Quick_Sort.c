/* Quick Sort Demo for Pintia.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int numbers[], int size){
    for (int i = 0; i < size; ++i){
        printf("%d ",numbers[i]);
    }
    printf("\n");
}

/* QUICK SORT FORMULA
 * numbers: Array with numbers to be sorted.
 * lowMark & highMark: the range to be sorted.
 * Yay, because range may change.
 * size: the size of the array, since C don't have &
 */
void QuickSort(int numbers[], int lowMark, int highMark, int size){
    // For the valid range...
    if (lowMark < highMark){
        // Since range may change while sorting.
        int left = lowMark;
        int right = highMark;
        // As a flag, smaller left, bigger right.
        int flag = numbers[lowMark];
        while (left < right){
            // Find the two invalid number, each on the one side.
            while (left < right && numbers[right] > flag){
                right --;
            }
            while (left < right && numbers[left] <= flag){
                left ++;
            }
            // Then swap it.
            swap(&numbers[left],&numbers[right]);
        }
        // Since left equals to right on the end, it is where we
        // put the flag on.
        swap(&numbers[left],&numbers[lowMark]);
        // Then do the same thing, first on the left, then on the right.
        QuickSort(numbers, lowMark, left-1, size);
        QuickSort(numbers, left+1, highMark, size);
        return;
    } else {
        return;
    }
}

int main(){
    //int numbers[1000] = {0};
    int numbers[] = {49,38,65,97,76,13,27,49}, total = 8;
    //int numbers[] = {4,5,3,2,1};
    //int total = 0;
    //scanf("%d",&total);
    //for (int i = 0; i < total; ++i){
    //    scanf("%d",&numbers[i]);
    //}
    QuickSort(numbers, 0, total - 1, total);
    printArray(numbers, total);
    return 0;
}