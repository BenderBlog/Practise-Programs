/* Depth First Search formula, using as header file. 
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

#ifndef _DFS_H
#define _DFS_H

/* For memset formula. */
#ifndef _STRING_H
#include<string.h>
#endif

#ifndef _GRAPH_H_
#include "Graph.h"
#endif

/* Use stack for fallback. */
#ifndef _STACK_H_
#include "Stack.h"
#endif

void DFS(matrix letsGo){
    /* Store whether this node has found or not. */
    bool welcomeList[letsGo.nodes];
    memset(welcomeList,false,sizeof(welcomeList));
    /* Stack for fallback. */
    stack fallback = initStack(letsGo.nodes);
    /* Start from the first node. */
    int current = 1;
    welcomeList[0] = true;
    fallback = push(fallback,current);
    printf("%d ", current);
    /* Maybe could be changed to eval if all visited or not. */
    while(1){
        /* To see whether to see the whole information in the line or not. */
        bool allchecked = false;
        for (int i = 0; i < letsGo.nodes; ++i){
            /* Seek for the 1 element, which means have road to it. */
            if (letsGo.matrix[current-1][i]==1 && welcomeList[i]==0){
                current = i + 1;
                printf("%d ", current);
                welcomeList[i] = true;
                fallback = push(fallback,current);
                break;
            } else if (i == letsGo.nodes - 1){
                allchecked = true;
            } else {
                continue;
            }
        }
        /* If the whole line has gone... */
        if (allchecked == true){
            /* If all node has found, finish. */
            if (isAllVisited(welcomeList,letsGo.nodes) == true){
                printf("\n");
                break;
            }
            /* Else, if the stack is empty, we may need to look for another sub graph. */
            else if (isEmpty(fallback) == true) {
                for (int i = 0; i < letsGo.nodes; ++i){
                    if (welcomeList[i] == false){
                        current = i + 1;
                        fallback = push(fallback,current);
                        printf("%d ", current);
                        welcomeList[i] = true;
                        continue;
                    }
                }
            }
            /* Else, we need to fallback. */
            else {
                current = gettop(fallback);
                fallback = pop(fallback);
                continue;
            }
        } else continue;
    }
    return;
}

#endif