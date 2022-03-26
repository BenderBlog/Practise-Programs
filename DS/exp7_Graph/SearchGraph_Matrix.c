/* Script to show the usage of these header files, using as demo.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
int main(){
    int nodes,roads;
    printf("Input nodes and roads numbers at follow:\n");
    scanf("%d%d",&nodes,&roads);
    printf("Input the roads, two numbers, from and to\n");
    matrix graph = initMatrix(graph,nodes,roads);
    printf("Matrix of the Graph:\n");
    outputMatrix(graph);
    printf("Depth First Search Result:\n");
    DFS(graph);
    printf("Breadth First Search Result:\n");
    BFS(graph);
    return 0;
}