/* Heap Sort or Insert Sort Eval from Pintia. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>


/* Suggestions I found from the Internet:
 *      1. Similar to Sample 1.
 *      2. Similar to Sample 2.
 *      3. First step of the Insert Order.
 *      4. First step of the Heap Order.
 *      5. Last step of the Insert Order.
 *      6. Last step of the Heap Order.
 * Refrence: https://blog.csdn.net/FlawlessZhiZhen/article/details/107663603
 */

/* Sample 1:
 *  10
 *  3 1 2 8 7 5 9 4 6 0
 *  1 2 3 7 8 5 9 4 6 0
 *  Insertion Sort
 *  1 2 3 5 7 8 9 4 6 0
 *
 * Sample 2：
 *  10
 *  3 1 2 8 7 5 9 4 6 0
 *  6 4 5 1 0 3 2 7 8 9
 *  Heap Sort
 *  5 4 3 1 0 2 6 7 8 9
 * 
 * Sample 3 (I wrote this)：
 *  10
 *  3 1 2 8 7 5 9 4 6 0
 *  9 8 5 6 7 3 2 4 1 0
 *  Heap Sort
 *  8 7 5 6 0 3 2 4 1 9
 */
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

int* HeapAdjust(int arr[], int begin, int total){
    int father = begin;
    int son = father * 2 + 1;
    // Since we may adjust the sub heap. 
    while (son < total){
        // Basically, we found the biggest/smallest element between the father and sons. 
        int smallest = arr[father] >= arr[son] ? father : son;
        if ( son + 1 < total ){
            smallest = arr[smallest] >= arr[son + 1] ? smallest : son + 1;
        }
        if (smallest != father){
            swap(&arr[father],&arr[smallest]);
            // Maybe the sub heap need adjust, too.
            father = smallest;
            son = father * 2 + 1;
        } else {
            break;
        }
    }
    return arr;
}


void InSort(int arr[], int size, int flag){
        int stand = flag;
        int temp = arr[flag];
        for (int j = stand - 1; j >= 0; --j){
            if (j != 0 && arr[j-1] <= temp  && arr[j] >= temp){
                stand = j;
                break;
            } else if (j == 0 && arr[j] >= temp){
                stand = j;
                break;
            }
        }
        if (stand != flag){
            for (int j = flag; j >= stand; --j){
                arr[j] = arr[j-1];
            }
            arr[stand] = temp;
        }

        PrintArray(arr,size);
}

void HeapSort(int arr[], int size, int flag){
    int toSwap = 0;
    for (int i = size - 1; i > flag; --i){
        if (arr[i] < arr[0]){
            toSwap = i;
            break;
        }
    }
    swap(&arr[0],&arr[toSwap]);
    //PrintArray(arr,size);
    arr = HeapAdjust(arr,0,toSwap);
    PrintArray(arr,size);
}

int main(){
    int total = 0;
    scanf("%d", &total);
    int a[100]={0}, b[100]={0};
    for (int i = 0; i < total; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < total; i++)
    {
        scanf("%d", &b[i]);
    }
    // Eval: find the ordered range.
    // If A lot, means insert sort, else heap sort.
    // Since heap sort have ordered range at the bottom.
    int flag = 0;
    for (flag; flag < total - 1; ++flag){
        if (b[flag] > b[flag+1]){
            flag++;
            break;
        }
    }
    printf("flag = %d\n",flag);
    if (flag != 1){
        printf("Insertion Sort\n");
        InSort(b,total,flag);
    } else {
        printf("Heap Sort\n");
        HeapSort(b,total,flag);
    }
    return 0;
}