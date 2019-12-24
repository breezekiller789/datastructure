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
#include <math.h>
#define MaxLine 1024
#define YES 1
#define NO -1
// Number of vertices  
// in the graph 
#define V 9 

//  Q : 有沒有可能一個節點距離其他sample node的距離一樣。

struct hnode{
    int src;
    int dst;
    int cost;
    struct hnode *next;
};
  
// A utility function to find the  
// vertex with minimum distance 
// value, from the set of vertices 
// not yet included in shortest 
// path tree 
int minDistance(int dist[], int sptSet[], int Num_Nodes) 
{ 
      
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < Num_Nodes; v++) 
        if (sptSet[v] == -1 && dist[v] <= min) {
            min = dist[v];
            min_index = v; 
        }
  
    return min_index; 
} 
  
// Function to print shortest 
// path from source to j 
// using parent array 
void printPath(int parent[], int j) 
{ 
      
    // Base Case : If j is source 
    if (parent[j] == -1) 
        return; 
  
    printPath(parent, parent[j]); 
  
    /* printf("%d ", j); */ 
} 
  
// A utility function to print  
// the constructed distance 
// array 
void printSolution(int dist[], int n, int parent[], int src, int *Distance) 
{ 
    static int Distance_cnt=0;
    /* printf("Vertex\t\t Distance\tPath"); */ 
    for (int i = 0; i < n; i++) 
    { 
        Distance[Distance_cnt++] = dist[i];
        /* printf("\n%d -> %d \t\t %d\t\t%d ", */ 
        /*               src, i, dist[i], src); */ 
        printPath(parent, i); 
    } 
    /* printf("\n"); */
} 
  
// Funtion that implements Dijkstra's 
// single source shortest path 
// algorithm for a graph represented 
// using adjacency matrix representation 
void dijkstra(int **graph, int src, int Num_Nodes, int *Distance) 
{ 
      
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
        dist[i] = INT_MAX;
        parent[src] = -1; 
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
        int u = minDistance(dist, sptSet, Num_Nodes); 
  
        // Mark the picked vertex  
        // as processed 
        sptSet[u] = 1; 
  
        // Update dist value of the  
        // adjacent vertices of the 
        // picked vertex. 
        for (int v = 0; v < Num_Nodes; v++) 
  
            // Update dist[v] only if is 
            // not in sptSet, there is 
            // an edge from u to v, and  
            // total weight of path from 
            // src to v through u is smaller 
            // than current value of 
            // dist[v] 
            if (sptSet[v] == -1 && graph[u][v] && 
                dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    } 
  
    // print the constructed 
    // distance array 
    printSolution(dist, Num_Nodes, parent, src, Distance);
} 
void Parse_Input(int ***Logic_Map, int ***Inputs, int *Num_Nodes, int *Num_Edges
        , int *Num_Inputs, int *Prime){
    int Dont_Care;
    scanf("%d %d %d", &(*Num_Nodes), &(*Num_Edges), &(*Prime));
    //  檢查吃進來的Node, Edge數對不對。
    /* printf("Nodes = %d Edges = %d Prime = %d\n", *Num_Nodes, *Num_Edges, *Prime); */
    *Logic_Map = (int **)malloc(sizeof(int *) * (*Num_Edges));

    //  分配記憶體來放邏輯圖
    for(int i=0; i<*Num_Edges; i++){
        *(*Logic_Map+i) = (int *)malloc(sizeof(int) * 5);
    }
    //  把input吃進來放進Logic_Map裡面，記得第一個column的值不要吃，沒意義。
    for(int i=0; i<*Num_Edges; i++){
        for(int j=0; j<=3; j++){
            //  j是0的不要吃，這只是index而已，用不到。
            if(j==0){
                //  我不知道怎麼略過這個，我就直接用變數讓他寫進去，不要用就好
                scanf("%d", &Dont_Care);
                continue;
            }
            else if(j<4 && j>0){
                scanf("%d", &(*(*Logic_Map+i))[j-1]);
                /* printf("%d ", (*(*Logic_Map+i))[j-1]); */
            }
            else
                continue;
        }
        /* printf("\n"); */
    }
    //  把後面的input吃進來。
    scanf("%d", &(*Num_Inputs));
    //  檢查吃進來的Input數對不對。
    /* printf("Num_Inputs = %d\n", *Num_Inputs); */
    *Inputs = (int **)malloc(sizeof(int *) * (*Num_Inputs));
    for(int i=0; i<*Num_Inputs; i++){
        *(*Inputs+i) = (int *)malloc(sizeof(int) * 2);
    }
    for(int i=0; i<*Num_Inputs; i++){
        for(int j=0; j<3; j++){
            if(j==0){
                scanf("%d", &Dont_Care);
            }
            else{
                scanf("%d", &(*(*Inputs+i))[j-1]);
                /* printf("%d ", (*(*Inputs+i))[j-1]); */
            }
        }
        /* printf("\n"); */
    }
}

void Table_Init(struct hnode **Hash_Table, int Table_Size){
    for(int i=0; i<Table_Size; i++){
        Hash_Table[i] = NULL;
    }
}

void Collision_Handler(struct hnode **Hash_Table, int Hash_Value, int Table_Size
        , int src, int dst, int cost){
    struct hnode *node = (struct hnode *)malloc(sizeof(struct hnode));
    node->src = src;
    node->dst = dst;
    node->cost = cost;
    //  Insert At Front!!
    node->next = Hash_Table[Hash_Value];
    Hash_Table[Hash_Value] = node;
    /* printf("Collision() Insert src = %d dst = %d HV = %d cost = %d\n", src, dst, Hash_Value, cost); */
}

int Get_Hash_Value(int src, int dst, int Table_Size, int Prime){
    int Hash_Value = ((src+1) * (dst+1))%Prime%Table_Size;
    return Hash_Value;
}

int Hash_Find(struct hnode **Hash_Table, int Table_Size, int src, int dst, int Prime){
    struct hnode *node;
    int Hash_Value = Get_Hash_Value(src, dst, Table_Size, Prime);
    int Distance_Value;

    node = Hash_Table[Hash_Value];
    while(node != NULL){
        if(node->src == src && node->dst == dst){
            return node->cost;
        }
        else if(node->src == dst && node->dst == src){
            return node->cost;
        }
        else{
            node = node->next;
        }
    }
    //  會走到這邊就是沒有這個組合存在Hash_Table，回傳-1
    return NO;
}

int Insert_Cnt=0;

void Hash_Insert(struct hnode **Hash_Table, int Table_Size, int src, int dst
        , int cost, int Prime){
    int Hash_Value = Get_Hash_Value(src, dst, Table_Size, Prime);
    /* printf("Hash Value = %d src = %d dst = %d cost = %d\n", Hash_Value, src, dst, cost); */

    //  會進來這裡代表有collision
    if(Hash_Table[Hash_Value] != NULL){
        //  Handle Collision
        Collision_Handler(Hash_Table, Hash_Value, Table_Size, src, dst, cost);
    }
    //  做Insert
    else if(Hash_Table[Hash_Value] == NULL){
        //  Do Insert
        struct hnode *node = (struct hnode *)malloc(sizeof(struct hnode));
        node->src = src;
        node->dst = dst;
        node->cost = cost;
        node->next = NULL;
        Hash_Table[Hash_Value] = node;
        /* printf("Insert src = %d dst = %d cost = %d HV = %d\n", src, dst, cost, Hash_Value); */
    }
    else{
        printf("What The Fuck? From Hash_Insert()\n");
    }
    Insert_Cnt++;
}

int Check_If_This_dst_Is_In_Sample_Nodes(int *Sample_Nodes, int src, int dst
        , int Num_Sample_Nodes){
    for(int i=0; i<Num_Sample_Nodes; i++){
        if(Sample_Nodes[i] == dst){
            return YES;
        }
    }
    return NO;
}

int *Get_Sample_Nodes(int *Sample_Nodes, int Num_Sample_Nodes, int **Rearrange_Distance
        , struct hnode **Hash_Table, int Table_Size, int Prime, int Num_Nodes
        ,int *Distance_Record_On_The_Node){
    int Round_Cnt=0, Max_Distance=0, Next_Sample_Node;
    int Min_Distance_In_Distance_Records;
    static int Sample_Node_Cnt=0;
    while(Round_Cnt < Num_Sample_Nodes){
        Max_Distance = INT_MIN;Min_Distance_In_Distance_Records=INT_MAX;
        //  一開始都是從零出發。
        if(Round_Cnt == 0){
            int src = 0, dst;
            //  要小心，自己跟自己不用insert
            //  也要避開dst是sample node的情況。
            for(int i=0; i<Num_Nodes; i++){
                dst = i;
                if(src == dst){
                    Distance_Record_On_The_Node[i] = 0;
                    continue;
                }

                Hash_Insert(Hash_Table, Table_Size, src, dst
                        , Rearrange_Distance[src][dst], Prime);

                Distance_Record_On_The_Node[i] = Rearrange_Distance[src][dst];

                if(Max_Distance < Rearrange_Distance[src][dst]){
                    Max_Distance = Rearrange_Distance[src][dst];
                    Next_Sample_Node = dst;
                }
            }
            //  Insert Sample Node
            Sample_Nodes[Sample_Node_Cnt++] = src;
            /* printf("Max_Distance = %d Next_Sample_Node = %d\n", Max_Distance, Next_Sample_Node); */
        }
        else{
            int src = Next_Sample_Node, dst;
            for(int i=0; i<Num_Nodes; i++){
                dst = i;
                if(src == dst){
                    Distance_Record_On_The_Node[i] = 0;
                    continue;
                }
                //  進去sample node裡面檢查有沒有在裡面，有的話要避開。
                if(Check_If_This_dst_Is_In_Sample_Nodes(Sample_Nodes,
                        src, dst, Num_Sample_Nodes) == YES){
                    //  Ignore This dst
                    continue;
                }
                else{
                    //  Hash_Insert();
                    Hash_Insert(Hash_Table, Table_Size, src, dst
                            , Rearrange_Distance[src][dst], Prime);
                }
                //  每個node都會有自己的distance紀錄，我就只記最小的就好。
                if(Rearrange_Distance[src][dst] < Distance_Record_On_The_Node[i]){
                    Distance_Record_On_The_Node[i] = Rearrange_Distance[src][dst];
                }
                //  每個node的distance記錄當中，挑一個最大的。
                if(Max_Distance < Distance_Record_On_The_Node[i]){
                    Max_Distance = Distance_Record_On_The_Node[i];
                    Next_Sample_Node = dst;
                }
                /* if(Max_Distance < Rearrange_Distance[src][dst]){ */
                /*     Max_Distance = Rearrange_Distance[src][dst]; */
                /*     Next_Sample_Node = dst; */
                /* } */
            }
            Sample_Nodes[Sample_Node_Cnt++] = src;
            /* printf("Next_Sample_Node = %d\n", Next_Sample_Node); */
        }
        Round_Cnt++;
    }
    return Distance_Record_On_The_Node;
}

int Check_If_Sample_Node(int *Sample_Nodes, int Num_Sample_Nodes, int src, int dst){
    for(int i=0; i<Num_Sample_Nodes; i++){
        if(Sample_Nodes[i] == src || Sample_Nodes[i] == dst){
            return YES;
        }
    }
    return NO;
}

int Get_Total_Distance(int *Sample_Nodes, int Num_Sample_Nodes, struct hnode **Hash_Table
        , int Table_Size, int src_from_input, int dst_from_input, int Distance_In_Between
        , int **Rearrange_Distance, int Num_Nodes, int Prime){
    int Round_Cnt=0;
    //  這邊在做的事情是在看哪一個sample node是這個節點的鄰近的。
    while(Round_Cnt < Num_Sample_Nodes){
        int sample_node = Sample_Nodes[Round_Cnt];
        int Distance = Hash_Find(Hash_Table, Table_Size, sample_node, src_from_input, Prime);
        /* printf("Distance = %d In_Between = %d\n", Distance, Distance_In_Between); */
        if(Distance != Distance_In_Between){
            Round_Cnt++;
        }
        //  找到了，就是這個sample node，可以開始算距離了。
        else{
            int Value1 = Hash_Find(Hash_Table, Table_Size, sample_node, dst_from_input, Prime);
            int Value2 = Hash_Find(Hash_Table, Table_Size, sample_node, src_from_input, Prime);
            return Value1+Value2;
        }
    }
    //  會走到這裡就有問題。
    return NO;
}

void Insert_Reachable_Nodes_Into_Hash_Table(struct hnode **Hash_Table, int Table_Size
        , int *Sample_Nodes, int Num_Sample_Nodes, int *Distance_Record_On_The_Node
        , int Num_Nodes, int Prime, int **Rearrange_Distance);

void Circle_Binding(struct hnode **Hash_Table, int Table_Size, int src, int dst
        , int Prime, int Distance_In_Between);

int See_If_Already_Exists_In_Hash_Table(struct hnode **Hash_Table, int Table_Size
        , int src, int dst, int Prime);

int main() 
{ 
    //  Let us create the example 
    // graph discussed above 
    /* int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0}, */ 
    /*                    {4, 0, 8, 0, 0, 0, 0, 11, 0}, */ 
    /*                     {0, 8, 0, 7, 0, 4, 0, 0, 2}, */ 
    /*                     {0, 0, 7, 0, 9, 14, 0, 0, 0}, */ 
    /*                     {0, 0, 0, 9, 0, 10, 0, 0, 0}, */ 
    /*                     {0, 0, 4, 0, 10, 0, 2, 0, 0}, */ 
    /*                     {0, 0, 0, 14, 0, 2, 0, 1, 6}, */ 
    /*                     {8, 11, 0, 0, 0, 0, 1, 0, 7}, */ 
    /*                     {0, 0, 2, 0, 0, 0, 6, 7, 0} */ 
    /*                 }; */ 

    int **Logic_Map, **Inputs, Num_Nodes, Num_Edges, Prime, Num_Inputs;

    Parse_Input(&Logic_Map, &Inputs, &Num_Nodes, &Num_Edges, &Num_Inputs, &Prime);

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
    //  path的時候，會用這個graph去兜，參考上面的那個，那是一個demo
    for(int i=0; i<Num_Edges; i++){
        /* printf("%d %d\n", (*(Logic_Map+i))[0], (*(Logic_Map+i))[1]); */
        graph[(*(Logic_Map+i))[0]][(*(Logic_Map+i))[1]] = (*(Logic_Map+i))[2];
        graph[(*(Logic_Map+i))[1]][(*(Logic_Map+i))[0]] = (*(Logic_Map+i))[2];
    }

    //  印出graph，看是不是正確
    /* printf("===================\n"); */
    /* for(int i=0; i<Num_Nodes; i++){ */
    /*     for(int j=0; j<Num_Nodes; j++){ */
    /*         printf("%d ", graph[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    /* printf("===================\n"); */

    int Distance[Num_Nodes*Num_Nodes];
    for(int i=0; i<Num_Nodes*Num_Nodes; i++){
        Distance[i]=0;
    }
  
    //  Do Dijkstra
    for(int i=0; i<Num_Nodes; i++){
        dijkstra(graph, i, Num_Nodes, Distance); 
    }

    //  算出有幾個sample node
    int Num_Sample_Nodes = (int)ceil(sqrt(Num_Nodes));
    int Sample_Nodes[Num_Sample_Nodes];
    /* printf("sample node = %d\n", Num_Sample_Nodes); */
    for(int i=0; i<Num_Sample_Nodes; i++){
        Sample_Nodes[i] = INT_MIN;
    }

    //  把Distance轉成二維的陣列，這樣方便我後面辦事情。
    int **Rearrange_Distance;
    Rearrange_Distance = (int **)malloc(sizeof(int *) * Num_Nodes);
    for(int i=0; i<Num_Nodes; i++){
        *(Rearrange_Distance+i) = (int *)malloc(sizeof(int) * Num_Nodes);
        static int cnt=0;
        for(int j=0; j<Num_Nodes; j++){
            Rearrange_Distance[i][j] = Distance[cnt++];
            //  印出調整過後的Distance
            /* printf("%d ", Rearrange_Distance[i][j]); */
            /* if(j==Num_Nodes-1) */
            /*     printf("\n"); */
        }
    }

    //  印Distance
    /* for(int i=0; i<Num_Nodes*Num_Nodes; i++){ */
    /*     printf("%d ", Distance[i]); */
    /* } */
    /* printf("\n"); */

    //  算Hash Table Size (Num_Nodes^1.5)取ceiling
    int Table_Size = ceil(pow(Num_Nodes, 1.5));
    /* printf("Table_Size = %d\n", Table_Size); */
    struct hnode *Hash_Table[Table_Size];
    
    //  把Table 初始化
    Table_Init(Hash_Table, Table_Size);

    //  去確認hash function要怎麼實作，取餘數那個規則
    //  回傳每個節點上的路徑紀錄。
    int Distance_Record_On_The_Node[Num_Nodes];
    Get_Sample_Nodes(Sample_Nodes, Num_Sample_Nodes, Rearrange_Distance
        , Hash_Table, Table_Size, Prime, Num_Nodes, Distance_Record_On_The_Node);

    //  Print Each Node's Distance Record
    /* for(int i=0; i<Num_Nodes; i++){ */
    /*     printf("Node_Distance %d\n", Distance_Record_On_The_Node[i]); */
    /* } */

    //  Print Sample Nodes
    /* for(int i=0; i<Num_Sample_Nodes; i++) */
    /*     printf("Sample Node = %d\n", Sample_Nodes[i]); */

    int Output_Array[Num_Inputs][4];
    int Round_Cnt=0;
    while(Round_Cnt < Num_Inputs){
        int src, dst;
        src = (*(Inputs+Round_Cnt))[0];
        dst = (*(Inputs+Round_Cnt))[1];
        /* printf("src=%d dst=%d Round_Cnt=%d", src, dst, Round_Cnt); */
        //  先檢查這條input，有沒有src或者dst是sample node
        if(Check_If_Sample_Node(Sample_Nodes, Num_Sample_Nodes, src, dst) == YES){
            //  直接去Hash Table做mapping
            int Distance_Value = Hash_Find(Hash_Table, Table_Size, src, dst, Prime);
            Output_Array[Round_Cnt][0] = Round_Cnt;
            Output_Array[Round_Cnt][1] = src;
            Output_Array[Round_Cnt][2] = dst;
            Output_Array[Round_Cnt][3] = Distance_Value;
            /* printf("%d %d %d %d\n", Round_Cnt, src, dst, Distance_Value); */
        }
        else{
            //  畫圈圈
            /* printf("%d %d %d Not done yet\n", Round_Cnt, src, dst); */
            //  先算出這兩點之間的距離，待會要看這個距離他們畫圈有沒有辦法畫到。
            int Distance_In_Between = Rearrange_Distance[src][dst];
            int Radius1 = Distance_Record_On_The_Node[src];
            int Radius2 = Distance_Record_On_The_Node[dst];
            //  框的到對方
            if(Radius1 >= Distance_In_Between || Radius2 >= Distance_In_Between){
                /* Hash_Insert(Hash_Table, Table_Size, src, dst, Distance_In_Between */
                /*         , Prime); */
                Output_Array[Round_Cnt][0] = Round_Cnt;
                Output_Array[Round_Cnt][1] = src;
                Output_Array[Round_Cnt][2] = dst;
                Output_Array[Round_Cnt][3] = Distance_In_Between;
                /* printf("%d %d %d %d\n", Round_Cnt, src, dst, Distance_In_Between); */
            }
            //  框不到對方
            else{
                int Distance_Forward, Distance_Backwards;

                Distance_In_Between = Distance_Record_On_The_Node[src];

                Distance_Forward = Get_Total_Distance(Sample_Nodes, Num_Sample_Nodes, Hash_Table
                                        , Table_Size, src, dst, Distance_In_Between
                                        , Rearrange_Distance, Num_Nodes, Prime);

                Distance_In_Between = Distance_Record_On_The_Node[dst];

                Distance_Backwards = Get_Total_Distance(Sample_Nodes, Num_Sample_Nodes, Hash_Table
                                        , Table_Size, dst, src, Distance_In_Between
                                        , Rearrange_Distance, Num_Nodes, Prime);
                /* printf("Forward = %d Backward = %d\n", Distance_Forward, Distance_Backwards); */
                if(Distance_Forward < Distance_Backwards){
                    Output_Array[Round_Cnt][0] = Round_Cnt;
                    Output_Array[Round_Cnt][1] = src;
                    Output_Array[Round_Cnt][2] = dst;
                    Output_Array[Round_Cnt][3] = Distance_Forward;
                    /* printf("%d %d %d %d\n", Round_Cnt, src, dst, Distance_Forward); */
                }
                else{
                    Output_Array[Round_Cnt][0] = Round_Cnt;
                    Output_Array[Round_Cnt][1] = src;
                    Output_Array[Round_Cnt][2] = dst;
                    Output_Array[Round_Cnt][3] = Distance_Backwards;
                    /* printf("%d %d %d %d\n", Round_Cnt, src, dst, Distance_Backwards); */
                }
            }
            


        }
        Round_Cnt++;
        

    }
    
    //  算出除了sample node之外，彼此之間可以到達彼此（也就是畫圈可以畫到的）
    //  要把他們Insert進去Hash Table
    Insert_Reachable_Nodes_Into_Hash_Table(Hash_Table, Table_Size, Sample_Nodes
            , Num_Sample_Nodes, Distance_Record_On_The_Node, Num_Nodes, Prime
            , Rearrange_Distance);

    printf("%d\n", Insert_Cnt);
    for(int i=0; i<Num_Inputs; i++){
        for(int j=0; j<4; j++){
            printf("%d", Output_Array[i][j]);
            if(j!=3){
                printf(" ");
            }
            else
                printf("\n");
        }
    }

    
    return 0; 
}

void Insert_Reachable_Nodes_Into_Hash_Table(struct hnode **Hash_Table, int Table_Size
        , int *Sample_Nodes, int Num_Sample_Nodes, int *Distance_Record_On_The_Node
        , int Num_Nodes, int Prime, int **Rearrange_Distance){
    int src, dst, Round_Cnt=0;
    while(Round_Cnt < Num_Nodes){
        src = Round_Cnt;
        //  src是sample node不用做，直接continue
        if(Check_If_Sample_Node(Sample_Nodes, Num_Sample_Nodes, src, INT_MIN) == YES){
            Round_Cnt++;
            continue;
        }
        for(int i=0; i<Num_Nodes; i++){
            dst = i;
            //  dst若是sample node就直接continue
            if(Check_If_Sample_Node(Sample_Nodes, Num_Sample_Nodes, src, dst) == YES){
                continue;
            }
            //  自己跟自己不用做。
            if(src == dst){
                continue;
            }
            //  到這邊就可以確認現在src跟dst肯定都不是sample node，這樣就可以
            //  繼續下一步。
            int Distance_In_Between = Rearrange_Distance[src][dst];
            int Distance_Value_1 = Distance_Record_On_The_Node[src];
            //  兩點之間的距離，小於那個點上的值，就要進去insert hash table
            if(Distance_In_Between <= Distance_Value_1){
                //  這兩個點畫圈圈可以被框住。
                Circle_Binding(Hash_Table, Table_Size, src, dst, Prime
                        , Distance_In_Between);
            }
            else{
                continue;
            }
            /* printf("src = %d dst = %d In_Between = %d\n", src, dst, Distance_In_Between); */
        }
        Round_Cnt++;
    }
}

void Circle_Binding(struct hnode **Hash_Table, int Table_Size, int src, int dst
        , int Prime, int Distance_In_Between){
    //  會進這個if代表這個組合已經在Hash Table裡面了，這就不用做，回傳就好。
    if(See_If_Already_Exists_In_Hash_Table(Hash_Table, Table_Size, src, dst
                , Prime) == YES){
        return;
    }
    //  會在這裡代表這個組合沒有在Hash_Table裡面，去Insert
    Hash_Insert(Hash_Table, Table_Size, src, dst, Distance_In_Between, Prime);
    return;
}
/* int Hash_Find(struct hnode **Hash_Table, int Table_Size, int src, int dst, int Prime){ */

int See_If_Already_Exists_In_Hash_Table(struct hnode **Hash_Table, int Table_Size
        , int src, int dst, int Prime){
    struct hnode *node = NULL;
    int Hash_Value = Get_Hash_Value(src, dst, Table_Size, Prime);
    //  Hash_Find如果有找到的話，會回傳這個組合的cost，如果沒有找到，我會回傳-1
    int Return_Value = Hash_Find(Hash_Table, Table_Size, src, dst, Prime);
    if(Return_Value == -1){
        //  回傳NO，代表沒有這個組合存在Hash_Table
        return NO;
    }
    else{
        return YES;
    }
}


