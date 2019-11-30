// C program for Dijkstra's single  
// source shortest path algorithm. 
// The program is for adjacency matrix 
// representation of the graph. 
#include <stdio.h> 
#include <limits.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024
// Number of vertices  
// in the graph 
#define V 9 
  
// A utility function to find the  
// vertex with minimum distance 
// value, from the set of vertices 
// not yet included in shortest 
// path tree 
int minDistance(int dist[],  
                int sptSet[]) 
{ 
      
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++){
        if (sptSet[v] == -1 && dist[v] <= min) 
            min = dist[v];
            /* min = dist[v], min_index = v; */ 
    }
    for (int v = 0; v<V; v++){
        if(sptSet[v] == -1 && dist[v] == min)
            /* min_index = v; */
            return v;
            /* return min_index; */
    }
    return min_index; 
} 
  
int Shortest_Path_Cnt=0;
// Function to print shortest 
// path from source to j 
// using parent array 
void printPath(int parent[], int j, int ***Shortest_Path, int cnt){
    // Base Case : If j is source 
    if (parent[j] == - 1) 
        return; 
  
    printPath(parent, parent[j], Shortest_Path, cnt); 
  
    (*((*Shortest_Path)+cnt))[Shortest_Path_Cnt] = j;
    /* printf("%d ", (*((*Shortest_Path)+cnt))[Shortest_Path_Cnt]); */
    Shortest_Path_Cnt++;
    /* printf("%d ", j); */ 
} 
  
// A utility function to print  
// the constructed distance 
// array 
void printSolution(int dist[], int n, int parent[], int src, int Num_Nodes,
        int ***Shortest_Path){
    /* int src = 0; */ 
    static int cnt=0;
    /* printf("Vertex\t\t Distance\tPath"); */ 
    for (int i = 0; i < Num_Nodes; i++){
        Shortest_Path_Cnt = 0;
        /* printf("\ncnt = %d", cnt); */
        /* printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); */ 
        *((*Shortest_Path)+cnt) = (int *)malloc(sizeof(int) * Num_Nodes);
        (*((*Shortest_Path)+cnt))[Shortest_Path_Cnt++] = src;
        printPath(parent, i, Shortest_Path, cnt); 
        cnt++;
    } 
    /* printf("\n"); */
} 
  
// Funtion that implements Dijkstra's 
// single source shortest path 
// algorithm for a graph represented 
// using adjacency matrix representation 
void dijkstra(int **graph, int src, int Num_Nodes, int ***Shortest_Path){
      
    // The output array. dist[i] 
    // will hold the shortest 
    // distance from src to i 
    int dist[Num_Nodes];  
  
    // sptSet[i] will 1 if vertex 
    // i is included / in shortest 
    // path tree or shortest distance  
    // from src to i is finalized 
    int sptSet[Num_Nodes]; 
  
    // Parent array to store 
    // shortest path tree 
    int parent[Num_Nodes]; 
  
    // Initialize all distances as  
    // INFINITE and stpSet[] as -1 
    for (int i = 0; i < Num_Nodes; i++) 
    { 
        parent[src] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = -1; 
    } 
  
    // Distance of source vertex  
    // from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path 
    // for all vertices 
    for (int count = 0; count < Num_Nodes - 1; count++) 
    { 
        // Pick the minimum distance 
        // vertex from the set of 
        // vertices not yet processed.  
        // u is always equal to src 
        // in first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex  
        // as processed 
        sptSet[u] = 1; 
  
        // Update dist value of the  
        // adjacent vertices of the 
        // picked vertex. 
        for (int v = 0; v < Num_Nodes; v++) {
  
        /* if(src == 8 && count == 3) */
        /*     printf("U = %d\n", u); */
            // Update dist[v] only if is 
            // not in sptSet, there is 
            // an edge from u to v, and  
            // total weight of path from 
            // src to v through u is smaller 
            // than current value of 
            // dist[v] 
            /* if (!sptSet[v] && graph[u][v] && */ 
            if (sptSet[v] == -1 && graph[u][v] && 
                dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
        }
    } 
  
    // print the constructed 
    // distance array 
    printSolution(dist, Num_Nodes, parent, src, Num_Nodes, Shortest_Path);
} 

void Parse_Input(int ***Logic_Map, int ***Inputs, int *Num_Nodes, int *Num_Edges, int *Num_Inputs){
    int Dont_Care;
    scanf("%d %d", &(*Num_Nodes), &(*Num_Edges));
    //  檢查吃進來的Node, Edge數對不對。
    printf("Nodes = %d\nEdges = %d\n", *Num_Nodes, *Num_Edges);
    *Logic_Map = (int **)malloc(sizeof(int *) * (*Num_Edges));
    
    //  分配記憶體來放邏輯圖
    for(int i=0; i<*Num_Edges; i++){
        *(*Logic_Map+i) = (int *)malloc(sizeof(int) * 4);
    }
    //  把input吃進來放進Logic_Map裡面，記得第一個column的值不要吃，沒意義。
    for(int i=0; i<*Num_Edges; i++){
        for(int j=0; j<=4; j++){
            //  j是0的不要吃，這只是index而已，用不到。
            if(j==0){
                //  我不知道怎麼略過這個，我就直接用變數讓他寫進去，不要用就好
                scanf("%d", &Dont_Care);
                continue;
            }
            //  第四個column代表weight
            if(j==4){
                (*(*Logic_Map+i))[j] = 0;
                printf("%d\n", (*(*Logic_Map+i))[j]);
            }
            else{
                scanf("%d", &(*(*Logic_Map+i))[j-1]);
                printf("%d ", (*(*Logic_Map+i))[j-1]);
            }
        }
        /* printf("\n"); */
    }
    //  把後面的input吃進來。
    scanf("%d", &(*Num_Inputs));
    //  檢查吃進來的Input數對不對。
    printf("Num_Inputs = %d\n", *Num_Inputs);
    *Inputs = (int **)malloc(sizeof(int *) * (*Num_Inputs));
    for(int i=0; i<*Num_Inputs; i++){
        *(*Inputs+i) = (int *)malloc(sizeof(int) * 3);
    }
    for(int i=0; i<*Num_Inputs; i++){
        for(int j=0; j<4; j++){
            if(j==0){
                scanf("%d", &Dont_Care);
            }
            else{
                scanf("%d", &(*(*Inputs+i))[j-1]);
                printf("%d ", (*(*Inputs+i))[j-1]);
            }
        }
        printf("\n");
    }

}
  
// https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
// Driver Code 
int main() 
{ 
    int **Logic_Map, **Inputs, Num_Nodes, Num_Edges, Num_Inputs,
        **Shortest_Path;

    Parse_Input(&Logic_Map, &Inputs, &Num_Nodes, &Num_Edges, &Num_Inputs);

    /* int graph[Num_Nodes][Num_Nodes]; */
    int **graph;
    graph = (int **)malloc(sizeof(int *) * Num_Nodes);
    //  把graph做初始化
    for(int i=0; i<Num_Nodes; i++){
        *(graph+i) = (int *)malloc(sizeof(int) * Num_Nodes);
        for(int j=0; j<Num_Nodes; j++){
            (*(graph+i))[j] = 0;
        }
    }

    //  建立graph：
    //  這裡有點小嗨，Logic_Map裡面的第一個element是Src，第二個是Dst，意思是說
    //  這兩個節點之間有鏈結，長度就直接給1，會這樣做是因為我後面在兜shortest
    //  path的時候，會用這個graph去兜，參考下面的那個，那是一個demo
    for(int i=0; i<Num_Edges; i++){
        /* printf("%d %d\n", (*(Logic_Map+i))[0], (*(Logic_Map+i))[1]); */
        graph[(*(Logic_Map+i))[0]][(*(Logic_Map+i))[1]] = 1;
        graph[(*(Logic_Map+i))[1]][(*(Logic_Map+i))[0]] = 1;
    }

    //  印出graph，看是不是正確
    printf("===================\n");
    for(int i=0; i<Num_Nodes; i++){
        for(int j=0; j<Num_Nodes; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("===================\n");
    //  Let us create the example 
    // graph discussed above 
    /* int graph[V][V] = {{0, 1, 0, 0, 0, 0, 0, 1, 0}, */ 
    /*                    {1, 0, 1, 0, 0, 0, 0, 1, 0}, */ 
    /*                     {0, 1, 0, 1, 0, 1, 0, 0, 1}, */ 
    /*                     {0, 0, 1, 0, 1, 1, 0, 0, 0}, */ 
    /*                     {0, 0, 0, 1, 0, 1, 0, 0, 0}, */ 
    /*                     {0, 0, 1, 0, 1, 0, 1, 0, 0}, */ 
    /*                     {0, 0, 0, 1, 0, 1, 0, 1, 1}, */ 
    /*                     {1, 1, 0, 0, 0, 0, 1, 0, 1}, */ 
    /*                     {0, 0, 1, 0, 0, 0, 1, 1, 0} */ 
    /*                 }; */ 
  
    //  找Shortest Path~~~~傳graph進去，最後會完成Shortest_Path
    Shortest_Path = (int **)malloc(sizeof(int *) * (Num_Nodes*Num_Nodes));
    for(int i=0; i<Num_Nodes; i++){
        dijkstra(graph, i, Num_Nodes, &Shortest_Path); 
    }

    //  印出很騷的Shortest Path
    printf("Num_Nodes^2 = %d\n", Num_Nodes*Num_Nodes);
    for(int i=0; i<Num_Nodes*Num_Nodes; i++){
        for(int j=0; j<Num_Nodes; j++){
            printf("%d ", (*(Shortest_Path+i))[j]);
        }
        printf("\n");
    }
    return 0; 
} 
