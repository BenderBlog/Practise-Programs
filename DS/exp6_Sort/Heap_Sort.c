/* Heap Sort Demo. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE_OF_INT sizeof(int)
//#include <sys/stat.h> could use stat formula, avoid for goddamn Windows.

int compare_time = 0;
int swap_time = 0;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
    swap_time++;
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

// Max Heap use >=
// Min Heap use <=
int* HeapAdjust(int arr[], int begin, int total){
    /* Find the father and his son, use complete Binary Tree Knowledge as follow:
     *    For the nodes in the Complete Binary Tree, mark 0 to n.
     *    Use the mark i to point the node in the tree.
     *    If the node isn't the root node, its parents is the node i/2.
     *    If 2i>n, this node do not have Left Child, else, its Left Child shall be 2i.
     *    If 2i+1>n, this node do not have Right Child, else, its Right Child shall be 2i+1
     * Check Text Book P124  
     */
    int father = begin;
    int son = father * 2 + 1;
    // Since we may adjust the sub heap. 
    while (son < total){
        // Basically, we found the biggest/smallest element between the father and sons. 
        compare_time++;
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

void HeapSort(int arr[], int total){
    // Adjust the array into heap, max heap here.
    for(int i = total/2 - 1; i >= 0; --i){
        arr=HeapAdjust(arr,i,total);
    }
    //PrintArray(arr,total);
    // We use the Max Heap here, which means the first element of the heap is the biggest.
    // Put the biggest to the end of the array, the rest shall become a new heap.
    for(int i = total - 1; i > 0; --i){
        swap(&arr[0],&arr[i]);
        arr = HeapAdjust(arr,0,i);
        //PrintArray(arr,total);
    }
}

int main(){
    //int numbers[]={49,38,65,97,76,13,27,49};
    //int numbers[]={3,1,2,8,7,5,9,4,6,0};

    // Linux command to generate random numbers.
    // I don't know how to generate random numbers in the Windows CMD:-P
    for (int total = 1000000; total <= 1100000; total += 1000){
        
        char command[256] = {'\0'};
        sprintf(command,"dd if=/dev/random bs=%d count=%d of=random.dat 2> /dev/null",SIZE_OF_INT,total);
        system(command);
        FILE *data = fopen("random.dat","rb");
        if (data == NULL){
            perror("[ERROR] File Not Found: ");
            return 0;
        }
        
        int *numbers = (int*)malloc(SIZE_OF_INT*total);
        fread(numbers,SIZE_OF_INT*total,1,data);
        fclose(data);
        /*
        FILE *toSave = fopen("input.txt","w");
        for (int i = 0; i < total; ++i){
            fprintf(toSave,"%d\n",numbers[i]);
        }
        fclose(toSave);
        */
        int start = clock();
        HeapSort(numbers,total);
        //PrintArray(numbers,sizeof(numbers)/sizeof(int));
        int end = clock();
        /*
        FILE *solution = fopen("output.txt","w");
        for (int i = 0; i < total; ++i){
            fprintf(solution,"%d\n",numbers[i]);
        }
        fclose(solution);
        */
        printf("total = %d\t Compare time %d\t Swap time %d\t total CPU time %d\n",total,compare_time,swap_time,(end-start));
    }
}
