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
        int ***Shortest_Path, int *Hops){
    /* int src = 0; */ 
    static int cnt=0;
    static int Hop_Cnt=0;
    /* printf("Vertex\t\t Distance\tPath"); */ 
    for (int i = 0; i < Num_Nodes; i++){
        Shortest_Path_Cnt = 0;
        Hops[Hop_Cnt++] = dist[i];
        /* printf("\ncnt = %d", cnt); */
        /* printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); */ 
        *((*Shortest_Path)+cnt) = (int *)malloc(sizeof(int) * Num_Nodes);
        for(int j=0; j<Num_Nodes; j++){
            (*((*Shortest_Path)+cnt))[j] = -1;
        }
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
void dijkstra(int **graph, int src, int Num_Nodes, int ***Shortest_Path
        , int *Hops){
      
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
    printSolution(dist, Num_Nodes, parent, src, Num_Nodes, Shortest_Path, Hops);
} 

void Parse_Input(int ***Logic_Map, int ***Inputs, int *Num_Nodes, int *Num_Edges, int *Num_Inputs){
    int Dont_Care;
    scanf("%d %d", &(*Num_Nodes), &(*Num_Edges));
    //  檢查吃進來的Node, Edge數對不對。
    printf("Nodes = %d\nEdges = %d\n", *Num_Nodes, *Num_Edges);
    *Logic_Map = (int **)malloc(sizeof(int *) * (*Num_Edges));
    
    //  分配記憶體來放邏輯圖
    for(int i=0; i<*Num_Edges; i++){
        *(*Logic_Map+i) = (int *)malloc(sizeof(int) * 5);
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
            //  第四個column代表weight，第五個column代表現在這個路徑上的load
            if(j==4){
                (*(*Logic_Map+i))[j-1] = 0;
                (*(*Logic_Map+i))[j] = (*(*Logic_Map+i))[2];
                printf("%d %d\n", (*(*Logic_Map+i))[j-1], (*(*Logic_Map+i))[j]);
            }
            else if(j<5 && j>0){
                scanf("%d", &(*(*Logic_Map+i))[j-1]);
                printf("%d ", (*(*Logic_Map+i))[j-1]);
            }
            else
                continue;
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
        **Shortest_Path, *Hops;

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
    Hops = (int *)malloc(sizeof(int) * (Num_Nodes*Num_Nodes));
    for(int i=0; i<Num_Nodes; i++){
        dijkstra(graph, i, Num_Nodes, &Shortest_Path, Hops); 
    }

    //  印出很騷的Shortest Path
    /* printf("Num_Nodes^2 = %d\n", Num_Nodes*Num_Nodes); */
    /* for(int i=0; i<Num_Nodes*Num_Nodes; i++){ */
    /*     for(int j=0; j<Num_Nodes; j++){ */
    /*         printf("%d ", (*(Shortest_Path+i))[j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    //  印出每一條shortest path的hop數。
    /* for(int i=0; i<Num_Nodes*Num_Nodes; i++){ */
    /*     printf("%d ", Hops[i]); */
    /* } */
    /* printf("\n"); */

    //  印出有點小騷的Inputs，檢查用。
    /* for(int i=0; i<Num_Inputs; i++){ */
    /*     printf("%d %d %d\n", (*(Inputs+i))[0], (*(Inputs+i))[1], (*(Inputs+i))[2]); */
    /* } */

    int Two_Segment[Num_Nodes*Num_Inputs][Num_Nodes];
    //  初始化。
    for(int i=0; i<Num_Nodes; i++){
        for(int j=0; j<Num_Nodes; j++){
            Two_Segment[i][j] = 0;
        }
    }

    //  src是input的起點，middle_state是中間要經過的點（2-segment），dst是
    //  input裡面的終點。
    int src, middle_state, dst;     
    int Two_Segment_Row=0, Input=0;
    float Update_Weights[Num_Edges];
    for(int i=0; i<Num_Edges; i++){
        Update_Weights[i] = 0;
    }
    for(int i=0; i<Num_Inputs; i++){
        Input = i;
        //  下面這個for就是在檢查進來的這一條input可不可以吃。
        //  Step 1:
        //          第一步先把shortest path找出來（2-segment routing）。
        //  Step 2:
        //          在這些shortest path當中，算出每一條的weight，如果這一條
        //          shortest path中，有weight數是無限大（INT_MAX），這條路
        //          就不能用了，直接算下一個。
        //  Step 3:
        //          再用一個for迴圈，去檢查這些weight數，有沒有哪些的weight數
        //          是一樣的，如果沒有一樣，那就簡單，直接把這個最小的weight的
        //          shortest path拿去用，若有一樣的weight的話，按照下面步驟。
        //
        //          step 3-1：
        //                    把這些weight一樣的shortest path，去算總共的hop數
        //                    hop數小的，就是他了，如果hop數又他媽一樣，就往下
        //                    一個步驟走。
        //          step 3-2：
        //                    檢查這些hop數一樣的shortest path，從src開始進去
        //                    走，看先遇到index小的節點的，就是這條了，不會再有
        //                    其他情況了。
        //  Step 4：
        //          好，會走到這一步，代表現在已經有找到一條可以走的shortest path
        //          了，到這邊，第一步要先檢查進來的這一條input，他的load數，是
        //          不是我們選到的這條shortest path中每一條路徑的load都可以滿
        //          足，如果有某一條路徑的load會爆掉，這條input就要直接reject
        //          掉，如果每一條路徑的load都滿足了，就可以進到下一步。
        //          
        //  Step 5：
        //          到這裡，現在這一條input就是可以接受的，把這一條input的load
        //          算出每一個路徑的weight數，算完之後存回去Logic_Map中的第四
        //          個column，然後把第五個column的load數，扣掉這條input的load
        //          然後要小心weight數萬一有算出無限大的，就存成INT_MAX，我前
        //          面在檢查weight的時候，就會去看看weight數有沒有是(INT_MAX)
        //          ，有的話，這條shortest path就不能選了，因為weight爆掉。
        //  Step 6：
        //         weight跟load都更新完了之後，就把這一條shortest path擺進一個
        //         Outputs裡面，然後要記得算出總共接受了幾個input，啊然後那個
        //         middle_state不用放進去，第一個column放index，第二個放src，
        //         第三個放dst，第四個放該input的load。


        //  把Two_segment做初始化，不然會有問題。
        for(int i=0; i<Num_Nodes*Num_Inputs; i++){
            for(int j=0; j<Num_Nodes; j++){
                Two_Segment[i][j] = -1;
            }
        }
        for(int j=0; j<Num_Nodes; j++){
            src = (*(Inputs+i))[0];
            middle_state = j;
            dst = (*(Inputs+i))[1];
            printf("src=%d middle=%d dst=%d\n", src, middle_state, dst);
            //  Step 1
            int cnt=0;
            int Two_Segment_Cnt=0;
            while(cnt < 2){
                if(cnt == 0){
                    for(int k=0; k<Num_Nodes*Num_Nodes; k++){
                        if((*(Shortest_Path+k))[0] == src){
                            int m=0;
                            while((*(Shortest_Path+k+middle_state))[m] != -1){
                                Two_Segment[j][Two_Segment_Cnt] = (*(Shortest_Path+k+middle_state))[m];
                                /* printf("%d ", (*(Shortest_Path+k+middle_state))[m]); */
                                /* printf("%d ", Two_Segment[j][Two_Segment_Cnt]); */
                                m++;
                                Two_Segment_Cnt++;
                            }
                            break;
                        }
                    }
                    cnt++;
                }
                else{
                    for(int k=0; k<Num_Nodes*Num_Nodes; k++){
                        if((*(Shortest_Path+k))[0] == middle_state){
                            int m=0;
                            while((*(Shortest_Path+k+dst))[m] != -1){
                                if(m==0){
                                    m++;
                                    continue;
                                }
                                Two_Segment[j][Two_Segment_Cnt] = (*(Shortest_Path+k+dst))[m];
                                /* printf("%d ", Two_Segment[j][Two_Segment_Cnt]); */
                                m++;
                                Two_Segment_Cnt++;
                            }
                            break;
                        }
                    }
                    cnt++;
                }
            }
            /* printf("\n"); */
        }
        //  印出這個input的所有shortest path
        for(int k=0; k<Num_Nodes; k++){
            for(int n=0; n<Num_Nodes; n++){
                printf("%d ", Two_Segment[k][n]);
            }
            printf("\n");
        }
        //  Step 2
        //  Logic Map的排列：
        //  0     1      2           3         4
        //  src   dst    capacity    weight    load
        /* printf("%d\n", Input); */
        /* sleep(5); */
        int Weights[Num_Nodes];
        for(int i=0; i<Num_Nodes; i++)
            Weights[i] = -1;

        int cnt=0;
        for(int row=0; row<Num_Nodes; row++){
            //  要-1，因為有可能剛好從頭走到尾，如果從頭走到尾，可能會越界。
            int Weight=0;
            for(int col=0; col<Num_Nodes-1; col++){
                //  一個路徑一個路徑回去算weight
                if(Two_Segment[row][col+1] != -1){
                    int src, dst, i;
                    for(i=0; i<Num_Edges; i++){
                        src = Two_Segment[row][col];
                        dst = Two_Segment[row][col+1];
                        /* printf("src = %d dst = %d map0 = %d map1 = %d i = %d\n", src, dst, (*(Logic_Map+i))[0], (*(Logic_Map+i))[1], i); */
                        if((*(Logic_Map+i))[0] == src && (*(Logic_Map+i))[1] == dst){
                            //  先檢查這個路徑的weight是不是已經爆了，爆了就不
                            //  用找這條了，直接continue找下一條。
                            if(Update_Weights[i] == INT_MAX){
                                Weight = INT_MAX;
                                break;
                            }
                            else{
                                /* printf("src = %d dst = %d\n", src, dst); */
                                Weight += Update_Weights[i];
                                continue;
                            }
                        }
                        //  不一定會是正向的，有可能會反過來，這樣也要算。
                        else if((*(Logic_Map+i))[0] == dst && (*(Logic_Map+i))[1] == src){
                            if(Update_Weights[i] == INT_MAX){
                                Weight = INT_MAX;
                                break;
                            }
                            else{
                                /* printf("src = %d dst = %d\n", src, dst); */
                                Weight += Update_Weights[i];
                                continue;
                            }
                        }
                        else
                            continue;
                    }
                    if(i == Num_Edges){
                        continue;
                    }
                    //  weight爆了，找下一條。
                    else if(Update_Weights[i] == INT_MAX){
                        break;
                    }
                    else
                        continue;

                    /* Weights[cnt++] = Weight; */
                    /* printf("%d ", Weight); */
                }
                //  走到看見-1，代表走完了，繼續走下一個shortest path
                else
                    break;
            }
                /* printf("\n"); */
            Weights[cnt++] = Weight;
            /* printf("cnt = %d\n", cnt); */
            /* printf("Weight = %d Input = %d cnt = %d\n", Weight, Input, cnt); */
        }
        //  印出擺進來的weight陣列，檢查是不是對的。
        /* for(int z=0; z<cnt; z++){ */
        /*     printf("%d ", Weights[z]); */
        /* } */
        /* printf("\n"); */
        /* sleep(5); */


        //  Step 3
        int Min = Weights[0], Min_Cnt=0, Choosen_Shortest_Path[Num_Nodes];
        for(int i=0; i<cnt; i++){
            if(Weights[i] < Min){
                Min = Weights[i];
                Min_Cnt++;
            }
            else if(Weights[i] == Min && i != 0){
                Min_Cnt++;
            }
            else
                continue;
        }
        //  印出Hops
        /* for(int i=0; i<Num_Nodes*Num_Nodes; i++) */
        /*     printf("%d ", Hops[i]); */
        /* printf("\n"); */
        
        //  Min_Cnt是0代表只有個路徑weight是最小的，再用一個for進去裡面找，看
        //  是哪一條shortest path，把這條shortest path的index記下來，往下繼續
        //  做。
        /* printf("================\n"); */
        /* printf("Min_Cnt = %d\n", Min_Cnt); */
        int Same_Weight_Shortest_Paths[Num_Nodes][Num_Nodes];
        if(Min_Cnt == 0){
            for(int i=0; i<cnt; i++){
                if(Weights[i] == Min){
                    for(int j=0; j<Num_Nodes; j++){
                        Choosen_Shortest_Path[j] = Two_Segment[i][j];
                        printf("%d ", Choosen_Shortest_Path[j]);
                    }
                    printf("\n");
                    break;
                }
            }
        }
        /* printf("================\n"); */
        /* sleep(5); */
        //  Min_Cnt不是0代表有多個weight一樣的shortest path，這樣就必須得先進
        //  去把這些是最小且重複weight的shortest path找出來，先把這些shortest
        //  path放進一個叫做Same_Weight_Shortest_Paths裡面，全部搞完記得把他
        //  清乾淨。
        else{
            //  Same_Weight_Shortest_Paths, Hop_Cnts 初始化
            for(int i=0; i<Num_Nodes; i++){
                for(int j=0; j<Num_Nodes; j++){
                    Same_Weight_Shortest_Paths[i][j] = -1;
                }
            }
            //  Step 3-1
            //  先進去Two_Segment裡面走一次，把這些Weight一樣的找出來。
            int idx=0;  //  來算總共有幾條路徑weight一樣，待會可以用。
            /* printf("==========\n"); */
            for(int i=0; i<Num_Nodes; i++){
                if(Weights[i] == Min){
                    for(int j=0; j<Num_Nodes; j++){
                        Same_Weight_Shortest_Paths[idx][j] = Two_Segment[i][j];
                        /* printf("%d ", Same_Weight_Shortest_Paths[idx][j]); */
                    }
                    /* printf("\n"); */
                    idx++;
                }
            }
            //  然後再把這些挑出來的shortest path，去算出每一個的hop數。
            int Hop_Cnts[idx];
            for(int i=0; i<idx; i++){
                int sum=0;
                for(int j=0; j<Num_Nodes-1; j++){
                    //  碰到-1代表這shortest path走完了。
                    if(Two_Segment[i][j+1] == -1){
                        break;
                    }
                    int src, dst, index;            //  因為我的Hop是用一個一 
                    src = Two_Segment[i][j];        //  元陣列放的，必須要把前
                    dst = Two_Segment[i][j+1];      //  面那個element * 7再加 
                    index = src * Num_Nodes + dst;  //  上後面的才會是剛好那個
                                                    //  路徑的hop值。         
                    sum += Hops[index];
                }
                printf("hop[%d] = %d\n", i, sum);
                Hop_Cnts[i] = sum;
            }
            int Min_Hop = Hop_Cnts[0], Min_Hop_Cnt=0;
            //  找出最小的Hop數
            for(int i=0; i<idx; i++){
                if(Hop_Cnts[i] < Min_Hop){
                    Min_Hop = Hop_Cnts[i];
                }
            }
            //  回去算出有沒有重複的Hop數的。
            for(int i=0; i<idx; i++){
                if(Hop_Cnts[i] == Min_Hop){
                    Min_Hop_Cnt++;
                }
            }
            /* printf("Min_Hop = %d\n", Min_Hop); */
            /* printf("Min_Hop_Cnt = %d\n", Min_Hop_Cnt); */

            //  Min_Hop_Cnt是零，太好了，就進去Same_Weight_Shortest_Paths裡面
            //  把hop數是Min_Hop的那個shortest path，擺進Choosen_Shortest_Path
            int Same_Hop_Shortest_Paths[Min_Hop_Cnt][Num_Nodes];
            if(Min_Hop_Cnt == 0){
                for(int i=0; i<idx; i++){
                    if(Hop_Cnts[i] == Min_Hop){
                        for(int j=0; j<Num_Nodes; j++){
                            Choosen_Shortest_Path[j] = Same_Weight_Shortest_Paths[i][j];
                            /* printf("%d ", Choosen_Shortest_Path[j]); */
                        }
                        /* printf("\n"); */
                    }
                }
            }
            //  Step 3-2
            //  他馬的，這樣就要再進去比index，把這些Hop一樣的Same_Weight_Shortest_Paths
            //  ，把hop數是Min_Hop的這些路徑，擺進Same_Hop_Shortest_Paths裡面。
            //  然後再進去這裡面，從頭開始往後比，只要比到一個最小index的那條
            //  就把這條shortest path放進Choosen_Shortest_Path裡面。
            else{
                int Same_Hop_Cnt = 0;
                for(int i=0; i<idx; i++){
                    if(Hop_Cnts[i] == Min_Hop){
                        for(int j=0; j<Num_Nodes; j++){
                            Same_Hop_Shortest_Paths[Same_Hop_Cnt][j] = Same_Weight_Shortest_Paths[i][j];
                            /* printf("%d ", Same_Hop_Shortest_Paths[Same_Hop_Cnt][j]); */
                        }
                        /* printf("\n"); */
                        Same_Hop_Cnt++;
                    }
                }
                /* printf("Same_Hop_Cnt = %d\n", Same_Hop_Cnt); */
                //  回去找index小的那個，i, j都從一開始是因為自己跟自己比沒有意義。
                int Min_Index = -1, i;
                for(i=1; i<Num_Nodes; i++){
                    int index = Same_Hop_Shortest_Paths[0][i], j;
                    for(j=1; j<Same_Hop_Cnt; j++){
                        if(Same_Hop_Shortest_Paths[j][i] < index){
                            Min_Index = index;
                        }
                    }
                    /* printf("j = %d Same_Hop_Cnt = %d\n", j, Same_Hop_Cnt); */
                    //  Min_Index還是-1的話代表這個column的index都一樣。
                    if(Min_Index == -1){
                        continue;
                    }
                    //  會進這個else就代表已經有開始不一樣了，而且有一個最小的
                    //  再回去這個column裡面找，看是哪一條路，把它放進shortest path
                    else{
                        for(int j=1; j<Same_Hop_Cnt; j++){
                            if(Same_Hop_Shortest_Paths[j][i] == Min_Index){
                                for(int k=0; k<Num_Nodes; k++){
                                    Choosen_Shortest_Path[k] = Same_Hop_Shortest_Paths[j][k];
                                    printf("%d ", Choosen_Shortest_Path[k]);
                                }
                                printf("\n");
                            }
                        }
                        break;
                    }
                }
                //  會進來這個if，代表今天hop一樣的所有路徑，都長得一模一樣，
                //  所以就挑第一條就好。
                if(i == Num_Nodes){
                    for(int k=0; k<Num_Nodes; k++){
                        Choosen_Shortest_Path[k] = Same_Hop_Shortest_Paths[0][k];
                        printf("%d ", Choosen_Shortest_Path[k]);
                    }
                    printf("\n");
                }
            }

            //  Step 4 
            //  Choosen_Shortest_Path中的每一段路徑，都要回去Logic_Map裡面找，
            //  看看有沒有load是沒辦法承受的。
            int load = (*(Inputs+i))[2], reject = -1;
            /* printf("load = %d\n", load); */
            for(int i=0; i<Num_Nodes; i++){
                int j, src, dst;
                src = Choosen_Shortest_Path[i];
                dst = Choosen_Shortest_Path[i+1];
                //  走到-1代表走完了，跳出去。
                if(dst == -1){
                    break;
                }
                for(j=0; j<Num_Edges; j++){
                    /* printf("src = %d dst = %d 0 = %d 1 = %d\n", src, dst, (*(Logic_Map+j))[0], (*(Logic_Map+j))[1]); */
                    //  走到-1代表Choosen_Shortest_Path走完了，這個input可以吃
                    if((*(Logic_Map+j))[0] == src && (*(Logic_Map+j))[1] == dst){
                        //  會進去這裡，就代表這個要直接reject掉。
                        if(load > (*(Logic_Map+j))[4]){
                            reject = 1;
                        }
                        else
                            continue;
                    }
                    else if((*(Logic_Map+j))[0] == dst && (*(Logic_Map+j))[1] == src){
                        //  會進去這裡，就代表這個要直接reject掉。
                        if(load > (*(Logic_Map+j))[4]){
                            reject = 1;
                        }
                        else
                            continue;
                    }
                    else
                        continue;
                }
                if(reject == 1){
                    break;
                }
            }
            printf("reject = %d, load = %d\n", reject, load);
            //  這條要reject，continue，繼續看下一條input
            if(reject == 1){
                continue;
            }

            //  Step 5
            /* printf("load = %d\n", load); */
            for(int i=0; i<Num_Nodes; i++){
                int src, dst;
                src = Choosen_Shortest_Path[i];
                dst = Choosen_Shortest_Path[i+1];
                //  走到-1代表走完了，跳出去。
                if(dst == -1){
                    break;
                }
                for(int j=0; j<Num_Edges; j++){
                    /* printf("src = %d dst = %d 0 = %d 1 = %d\n", src, dst, (*(Logic_Map+j))[0], (*(Logic_Map+j))[1]); */
                    //  走到-1代表Choosen_Shortest_Path走完了，這個input可以吃
                    if((*(Logic_Map+j))[0] == src && (*(Logic_Map+j))[1] == dst){
                        //  weight爆掉。
                        if(((*(Logic_Map+j))[2] - load) == 0){
                            Update_Weights[j] = INT_MAX;
                            continue;
                        }
                        int capacity;
                        float weight=0;
                        capacity = (*(Logic_Map+j))[2] - load;
                        weight = (float)load / ((*(Logic_Map+j))[2] - load);
                        printf("weight = %f\n", weight);
                        Update_Weights[j] += weight;
                    }
                    else if((*(Logic_Map+j))[0] == dst && (*(Logic_Map+j))[1] == src){
                        //  weight爆掉。
                        if(((*(Logic_Map+j))[2] - load) == 0){
                            Update_Weights[j] = INT_MAX;
                            continue;
                        }
                        int capacity;
                        float weight=0;
                        capacity = (*(Logic_Map+j))[2] - load;
                        weight = (float)load / ((*(Logic_Map+j))[2] - load);
                        printf("weight = %f\n", weight);
                        Update_Weights[j] += weight;
                    }
                    else
                        continue;
                }
                //  TODO 更新load數。
            }
            for(int i=0; i<Num_Edges; i++){
                printf("%f ", Update_Weights[i]);
            }
            printf("\n");





            continue;
        }

    }




    return 0; 
} 
