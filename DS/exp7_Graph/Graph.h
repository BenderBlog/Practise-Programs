/* Adjacency matrix of the graph, using as header file. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#ifndef _STDIO_H
#include<stdio.h>
#endif

#ifndef _STDLIB.H
#include<stdlib.h>
#endif

#ifndef _STDBOOL_H
#include<stdbool.h>
#endif

/* For memset formula. */
#ifndef _STRING_H
#include<string.h>
#endif

/* Brief introduction of the things in this header file. */
typedef struct Graph_Matrix matrix;
matrix initMatrix(matrix toInit, int size, int roads);
void outputMatrix(matrix toDeal);
bool isAllVisited(bool list[],int size);

/* Matrix is a dymatic two dimension (dyadic) array, no length of the road here. */
typedef struct Graph_Matrix{
    int nodes;
    int roads;
    int **matrix;
}matrix;

/* Generate a new matrix to toInit, 
 * provide the number of the nodes as size, number of the roads as roads. */
matrix initMatrix(matrix toInit, int size, int roads){
    toInit.nodes = size;
    toInit.roads = roads;
    /* Generate a dymatic two dimension array. 
     * calloc formula is used to make sure the new array is filled with zero.*/
    toInit.matrix = (int **)calloc(sizeof(int*),toInit.nodes);
    for (int i = 0; i < toInit.nodes; ++i){
        toInit.matrix[i] = (int *)calloc(sizeof(int),toInit.nodes);
    }
    /* Translate the road data into adjacency array. */
    for (int i = 0; i < toInit.roads; ++i){
        while (1){
            int from = 0, to = 0;
            scanf("%d%d",&from,&to);
            /* Same road shall not input twice. */
            if (from != to && from <= toInit.nodes && to <= toInit.nodes &&
                (toInit.matrix[from-1][to-1]==0 )){
                toInit.matrix[from-1][to-1]=1;
                break;
            } else {
                printf("Invalid! Please input again.");
                continue;
            }
        }
    }
    return toInit;
}

/* Output the adjacency matrix. */
void outputMatrix(matrix toDeal){
    for (int i = 0; i < toDeal.nodes; ++i){
        for (int j = 0; j < toDeal.nodes; ++j){
            printf("%d ",toDeal.matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

/* Eval the all element in the list, to know whether all visited or not. */
bool isAllVisited(bool list[],int sizeOfList){
    for (int i = 0; i < sizeOfList; ++i)
        if (list[i] == false)
            return false;
    return true;
}

#endif
