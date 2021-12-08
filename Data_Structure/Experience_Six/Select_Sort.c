/* Select Sort Demo for Pintia.
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

void PrintArray(int numbers[], int size){
    for (int i = 0; i < size; ++i){
        printf("%d",numbers[i]);
        if (i != size - 1){
            printf(" ");
        }
    }
    printf("\n");
    return;
}

// Get the address of the smallest element from the range of the array.
int GetMinimal(int arr[], int begin, int size){
    int minimal = begin;
    for (int i = begin + 1; i < size; ++i){
        if (arr[i] < arr[minimal]){
            minimal = i;
        }
    }
    return minimal;
}

// Divided into two parts: ordered and chaos.
// For the chaos, swap the first element with the smallest element.
void SelectSort(int arr[], int size){
    for (int i = 0; i < size - 1; ++i){
        int minimal = GetMinimal(arr, i, size);
        swap(&arr[i],&arr[minimal]);
        PrintArray(arr,size);
    }
    return; 
}

// That's all! What you're expecting?
int main(){
    int numbers[10]={0}, total = 0;
    scanf("%d",&total);
    for (int i = 0; i < total; ++i){
        scanf("%d ",&numbers[i]);
    }
    // Why I have to eval 1 to get a perfect answer?
    if (total == 1){
        printf("%d",numbers[0]);
    } else {
        SelectSort(numbers,total);
    }
}