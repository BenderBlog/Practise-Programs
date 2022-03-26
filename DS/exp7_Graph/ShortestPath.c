//Written by Chen Songze <superbart_chen@qq.com>
//Under the Unlicense
//Function: Demo of the Shortest Path Algorithm called Dijkstra.
//OK with gcc-11, Arch Linux.
#include<stdio.h>
#define INFINATE -1     //将不可达设置为-1，该算法无法处理负权值
#define MAX_ROUTE 10    //最多处理10个路径，可以改的

struct {
    int from;   //开始节点
    int length; //节点长度
    int to;     //结束节点
}route[MAX_ROUTE];

void print(int routes, int begin, int notes){
    //生产邻接矩阵
    int graph[notes][notes];
    for (int i = 0; i < notes; ++i){
        for (int j = 0; j < notes; ++j){
            if (i == j){
                graph[i][j] = 0;
            } else {
                graph[i][j] = INFINATE;
            }
        }
    }
    for (int i = 0; i < routes; ++i){
        graph[route[i].from - 1][route[i].to - 1] = route[i].length;
        graph[route[i].to - 1][route[i].from - 1] = route[i].length;
    }
    //进行最短路径查询
    int present[notes];
    present[0] = begin - 1;
    for (int i = 0; i < notes - 1; ++i){
        
        int temp = 0;
        int toAdd = -1;
        //从开始的节点所在行开始寻找最短距离的路径
        for (int j = i; j < notes; ++j){
            if ( ( graph[present[i]][j] < toAdd || toAdd == -1 ) 
                 && graph[present[i]][j] != 0 && graph[present[i]][j] != -1 ){
                toAdd = graph[present[i]][j];
                temp = j;
            }
        }
        //经由最短路径跳转到对应点，将其对应点上的路径全部加上来时路径的长度
        present[i+1] = temp;
        for (int j = 0; j < notes; ++j){
            if ( graph[present[i+1]][j] != -1 && graph[present[i+1]][j] != 0 ) {
                graph[present[i+1]][j] += toAdd;
                //注意，如果加完发现比上回最短的还长，就还是最短的吧
                //所以这就是为啥我不想搞显示路径功能了，对于我这样录入节点的程序，很明显需要实现一个矩阵来表示
                //可是我没有时间写了，而且网上的代码都是需要写一个节点的结构体来储存路径的
                if (graph[present[i+1]][j] >= graph[present[i]][j]
                     && graph[present[i]][j] != -1){
                    graph[present[i+1]][j] = graph[present[i]][j];
                }
            }
        }
        //用过的节点一律清除，也就是把节点删了
        for (int j = 0; j <= i; ++j){
            graph[present[i+1]][present[j]] = 0;
        }
    }
    //输出，路径输出功能被我砍掉了，因为需要另一个矩阵，我没时间复习了:-(
    for (int i = 0; i < notes; ++i){
        if (i == begin - 1){
            continue;
        } else {
            int smallest = -1;
            for (int j = 0; j < notes; ++j){
                if ( ( graph[j][i] < smallest || smallest == -1 ) 
                    && graph[j][i] != 0 && graph[j][i] != -1 ){
                    smallest = graph[j][i];
                }
            }
            printf("%d -> %d Length = %d\n", begin, i+1, smallest);
        }
    }
}
//查询到有多少个节点
int getNotes(int * a, int routes){
    int non_note = 0;
    for (int i = 0; i < routes*2; ++i){
        for (int j = i + 1; j < routes*2; ++j){
            if (a[j] == a[i]){
                a[j] = 0;
            }
        }
    }
    for (int i = 0; i < routes*2; ++i){
        if (a[i] == 0){
            non_note++;
        }
    }
    return routes * 2 - non_note;
}

int main(){
    
    int routes;
    //输入路径
    printf("How many route: ");
    scanf("%d",&routes);
    int notes_appears[routes*2];
    if ( routes > MAX_ROUTE ){
        printf("Too much note, I can't handle it!\n");
        return 1;
    } else {
        for (int i = 0; i < routes; ++i){
            
            printf("====THE %d note====\n", i+1);
            
            printf("The start note is: ");
            scanf("%d",&route[i].from);
            notes_appears[i*2] = route[i].from;
            
            printf("The end note is: ");
            scanf("%d",&route[i].to);
            notes_appears[i*2+1] = route[i].to;

            printf("The length of the path is: ");
            scanf("%d",&route[i].length);
        
        }
    }
    //选择开始节点
    int begin;
    printf("Which note should be the start? ");
    scanf("%d",&begin);
    //主要代码的Link
    print(routes, begin, getNotes(notes_appears, routes));
}
