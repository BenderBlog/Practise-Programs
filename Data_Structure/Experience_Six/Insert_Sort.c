/* Insert Sort Demo.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>

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

int main(){
    //int arr[]={49,38,65,97,76,13,27,49};
    int arr[]={3,1,2,8,7,5,9,4,6,0};
    PrintArray(arr,sizeof(arr)/sizeof(int));
    // Make the first and second ordered, as ordered range.
    if (arr[0]>arr[1]){
        int temp = arr[0];
        arr[0] = arr[1];
        arr[1] = temp;
    }
    // For the chaos range, look for the first element.
    // Then find a perfect place for it, in the ordered range.
    for (int i = 2; i < sizeof(arr)/sizeof(int); ++i){
        int stand = i;
        int temp = arr[i];
        for (int j = stand - 1; j >= 0; --j){
            if (j != 0 && arr[j-1] <= temp  && arr[j] >= temp){
                stand = j;
                break;
            } else if (j == 0 && arr[j] >= temp){
                stand = j;
                break;
            }
        }
        if (stand != i){
            for (int j = i; j >= stand; --j){
                arr[j] = arr[j-1];
            }
            arr[stand] = temp;
        }
        // That's all folks!
        PrintArray(arr,sizeof(arr)/sizeof(int));
    }
}