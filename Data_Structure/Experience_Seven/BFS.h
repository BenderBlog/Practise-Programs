/* Breadth First Search formula, using as header file. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

/* Used a array as quene. */

#ifndef _BFS_H
#define _BFS_H

#ifndef _GRAPH_H_
#include "Graph.h"
#endif

#ifndef _STDBOOL_H
#include<stdbool.h>
#endif

/* For memset formula. */
#ifndef _STRING_H
#include<string.h>
#endif

/* Whether the quene array is empty (all element are zero) or not. */
bool queneEmpty(int quene[], int size){
    for (int i = 0; i < size; ++i)
        if (quene[i] != 0)
            return false;
    return true;
}

void BFS(matrix letsGo){
    /* forQuene marks the first element's position in the quene array. */
    int forQuene = 0;
    int quene[letsGo.nodes];
    memset(quene,0,sizeof(quene));
    /* Store whether this node has found or not. */
    bool isStep[letsGo.nodes];
    memset(isStep,false,sizeof(quene));
    /* Start from the first node. */
    int current = 1;
    isStep[current-1] = true;
    printf("%d ",current);
    /* While all elements are not visited. */
    while (isAllVisited(isStep,letsGo.nodes) == false){
        /* Search the nearby, accessible node. */
        for (int i = 0; i < letsGo.nodes; ++i){
            if (letsGo.matrix[current-1][i] == 1 && isStep[i] == false){
                printf("%d ",i+1);
                quene[forQuene] = i;
                forQuene += 1;
                isStep[i] = true;
            }
        }
        /* If quene is not empty, pop the end of the quene to be the next current. */
        if (queneEmpty(quene,sizeof(quene)/sizeof(int)) == false){
            for (int i = 0; i < letsGo.nodes; ++i){
                if (quene[i] != 0){
                    current = quene[i] + 1;
                    quene[i] = 0;
                    break;
                }
            }
        }
        /* Else, we need to seek for the sub graph. */
        else {
            for (int i = 0; i < letsGo.nodes; ++i){
                if (isStep[i] == false){
                    current = i + 1;
                    printf("%d ",current);
                    isStep[i] = true;
                }
            }
        }

    }
    printf("\n");
    return;
}

#endif