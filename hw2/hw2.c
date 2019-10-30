#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024


//  做初始化，並把總共的節點數找出來
void Initialize(FILE *fp, int **Origin, int **Final, int *Number_Of_Nodes
        , int **Output_Array){
    fscanf(fp, "%d", Number_Of_Nodes);
    /* printf("%d\n", *Number_Of_Nodes); */
    *Origin = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    *Final = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    *Output_Array = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    for(int i=0; i<*Number_Of_Nodes; i++){
        (*Output_Array)[i] = 0;
    }
}

//  把input吃進來放進陣列
void Get_Input(int *Origin, int *Final, int Number_Of_Nodes, FILE *fp){

    int idx=0;
    while(idx < 2){
        for(int i=0; i< Number_Of_Nodes; i++){
            if(idx == 0){
                fscanf(fp, "%d", Origin+i);
                /* printf("%d ", *(Origin+i)); */
            }
            else{
                fscanf(fp, "%d", Final+i);
                /* printf("%d ", *(Final+i)); */
            }
        }
        /* printf("\n"); */
        idx++;
    }
}

//  input吃進來之後，還要把更新前更新後的路徑做重新調整，我希望把所有的路徑
//  都弄成一直線往下指，不然還要在那邊走來走去，很麻煩，先做調整演算法會簡單
//  一些
void Adjust_Input(int **Adjust_Origin, int **Adjust_Final, int *Origin, int *Final
        , int Number_Of_Nodes, int *Number_Of_Origins, int *Number_Of_Finals){

    int cnt, idx;
    //  分配兩塊整數陣列，大小是原本吃進來多大就分配多大
    *Adjust_Origin = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    *Adjust_Final = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    for(int i=0; i<Number_Of_Nodes; i++){
        (*Adjust_Origin)[i] = -1;
        (*Adjust_Final)[i] = -1;
    }

    //  這段在把原本"更新前"的table做一連串的指向，原本要一直用index裡面的
    //  sequence來做操作，這邊直接先一次做好。
    cnt=0;
    idx=0;
    while(cnt < Number_Of_Nodes){
        if(cnt == 0){
            (*Adjust_Origin)[cnt] = 0;
            printf("%d ", (*Adjust_Origin)[cnt]);
            cnt++;
            continue;
        }
        (*Adjust_Origin)[cnt] = Origin[idx];
        idx = Origin[idx];
        if((*Adjust_Origin)[cnt] == -1)
            break;
        printf("%d ", (*Adjust_Origin)[cnt]);
        cnt++;
    }
    *Number_Of_Origins = cnt;
    /* printf("cnt = %d", cnt); */
    printf("\n");

    //  這段在做一樣的事情，只是是把"更新後"的table放進新的陣列
    cnt=0;
    idx=0;
    while(cnt < Number_Of_Nodes){
        //  多這段if是因為我希望有source在最前面，這樣我演算法比較好做。
        if(cnt == 0){
            (*Adjust_Final)[cnt] = 0;
            printf("%d ", (*Adjust_Final)[cnt]);
            cnt++;
            continue;
        }
        (*Adjust_Final)[cnt] = Final[idx];
        idx = Final[idx];
        if((*Adjust_Final)[cnt] == -1)
            break;
        printf("%d ", (*Adjust_Final)[cnt]);
        cnt++;
    }
    *Number_Of_Finals = cnt;
    /* printf("cnt = %d", cnt); */
    printf("\n");

}

int main(int argc, char *argv[]){

    FILE *fp;
    char *line;
    int *Origin, *Final, Number_Of_Nodes = 0;
    int Number_Of_Origins, Number_Of_Finals;    //  算出調整後的長度分別多少
    int *Adjust_Origin, *Adjust_Final;  //  事後把讀進來的做順序調整
    int cnt, idx;   //  迴圈控制用的變數
    int *Output_Array, **Update_Rules;
    /* fp = fopen("input1.txt", "r"); */
    fp = fopen("./hw2_test_file/input.txt", "r");

    //  做初始化
    Initialize(fp, &Origin, &Final, &Number_Of_Nodes, &Output_Array);

    //  把input吃進來然後擺進陣列
    Get_Input(Origin, Final, Number_Of_Nodes, fp);

    //  把input吃進來之後，把他拿去把順序重新調整，讓他變成一條線指到底
    //  ，這樣會讓程式變簡單
    Adjust_Input(&Adjust_Origin, &Adjust_Final, Origin, Final, Number_Of_Nodes
            , &Number_Of_Origins, &Number_Of_Finals);

    //  檢查經過重新調整順序後的節點數量正不正確
    /* printf("origin = %d, final = %d\n", Number_Of_Origins, Number_Of_Finals); */


    //  Description For This While Loop :   Round 0th
    //  這個while loop主要在做的事情就是在做第0個round，就是依照更新後的路徑，
    //  回去更新前的路徑爬來爬去，看哪些節點是更新前更新後就存在，共同的節點中
    //  間，他所經過的路徑有多長，這個就必須得回去更新前的table爬過一次才知道，
    //  然後爬完之後，把這些資訊用一個integer array存起來，最終目的就是拿到這
    //  個array，然後把第1 round的路徑都先更新好。

    //  最初始情況就是從更新完的Source出發，所以先設為零開始
    int Src=0, Dst=0, offset=0, start=-1, end=-1, i, Rules_Cnt=0;
    idx = 0;    cnt = 0;
    Src = Adjust_Final[idx++];  //  加一是因為我第0個故意把他放0，下一個才算
    Dst = Adjust_Final[idx];

    //  下面這行是為了我要把我爬出來的路徑，擺進去，裡面放的是更新前更新後有
    //  交集的點，然後下一個放這兩個點之間原本的路徑長。
    Update_Rules = (int **)malloc(sizeof(int *) * 100);
    
    Output_Array = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    memcpy(Output_Array, Origin, Number_Of_Nodes * sizeof(int));

    /* for(int k=0; k<Number_Of_Nodes; k++) */
    /*     printf("%d ", Output_Array[k]); */
    /* printf("\n"); */
    while(1){
        //  會走到-1代表走完了，直接跳出來
        if(Dst == -1){
            break;
        }
        //  Debug
        /* printf("=======================================\n"); */
        /* printf("Src = %d, Dst = %d\n", Src, Dst); */
        for(cnt=0; cnt<=Number_Of_Finals; cnt++){
            /* printf("Adjust_Origin[cnt] = %d\n", Adjust_Origin[cnt]); */
            //  Description :
            //              有找到一樣的，代表更新前跟更新後都有這個節點，
            //              這種case就是把Src跟Dst擺進一個叫做Update_Rules
            //              的陣列，方便往後選取更新順序使用
            //
            //  如果進這個if :
            //  Step 1 :
            //          一進去，就再用一個for loop下去走，看從source走到這
            //          裡總共有幾個節點（不包含自己，也不包含source）
            //  Step 2 :
            //          把現在的Src, Dst, 剛剛算出來的節點數，擺進
            //          Update_Rules，記得要malloc
            //  Step 3 :
            //          把Src, Dst做更新，把現在的Dst assign給Src，然後
            //          Dst變成Src的下一個，然後break出去回上一層迴圈，
            //          換下一個Dst繼續跑這個迴圈
            if(Dst == Adjust_Origin[cnt]){
                //  Step 1
                for(i=0; i<Number_Of_Origins; i++){
                    if(start != -1 && end != -1){
                        break;
                    }
                    /* printf("Dst = %d, Src = %d\n", Dst, Src); */
                    //  找到一樣的，有兩種case，有可能是先遇到Dst，或者先
                    //  遇到Src，如果先遇到Dst就代表他是往回走，先遇到Src
                    //  就是往後走。
                    if(Src == Adjust_Origin[i]){
                        start = i;
                        /* printf("Src = %d, Adj_Origin[i] = %d, start = %d\n", Src, Adjust_Origin[i], start); */
                    }
                    else if(Dst == Adjust_Origin[i]){
                        end = i;
                        /* printf("Dst = %d, Adj_Origin[i] = %d, end = %d\n", Dst, Adjust_Origin[i], end); */
                    }
                    else
                        continue;
                }
                //  這邊在算爬完之後的長度
                //  如果Length是負的，代表他是往回走的，這樣要反過來扣
                int Length = end - start;
                if(Length <= 0){
                    Length = start - end - 1;
                }
                else{
                    Length = end - start - 1;
                }

                //  Step 2
                *(Update_Rules + Rules_Cnt) = (int *)malloc(sizeof(int) * 4);
                (*(Update_Rules + Rules_Cnt))[0] = Src;
                (*(Update_Rules + Rules_Cnt))[1] = Dst;
                (*(Update_Rules + Rules_Cnt))[2] = Length;
                for(int j=0; j<3; j++)
                    printf("%d ", (*(Update_Rules + Rules_Cnt))[j]);
                printf("\n");
                Rules_Cnt++;

                //  印出我爬出來的長度是不是對的
                /* printf("end = %d, start = %d\n", end, start); */
                /* printf("Length = %d\n", Length); */

                //  Step 3
                end = start = -1;   //  這兩個要設回去初始值
                Src = Dst;          // Dst給Src，然後Dst變成Src下一個繼續跑
                idx++;
                Dst = Adjust_Final[idx];
                break;
            }
            //  不然就是繼續往更新前的table繼續往下走，看有沒有一樣的。
            else{
                continue;
            }
        }
        //  Debug用的
        /* printf("cnt = %d, Number_Of_Finals = %d\n", cnt, Number_Of_Finals); */
        /* sleep(1); */
        //  會進來這個if，就代表這個Dst已經走到最後面了，走到最後面就是更新前的
        //  路徑上沒有這個節點，可以直接去把Output_Array做更新
        if(cnt == Number_Of_Finals+1){
            //  TODO : 先把Origin複製給Output_Array，然後再用現在這個Dst的值
            //  ，回去Origin的這個值的位置的值，把它改成Dst的下一個路徑
            idx++;
            Dst = Adjust_Final[idx];
            /* printf("idx = %d\n", idx); */
        }
        else
            continue;
        //  這層迴圈走完之後到這裡，檢查一下Dst有沒有走到最後，如果有走到最
        //  後，代表這個Dst，在更新前是不存在的，如果是這個case。
        //  Step 1 :
        //          去把Output_Array裡面，這個Dst所顯示的值，去Origin的
        //          index裡面，把那個-1改成Dst所指到的下一個
        //          例如：Dst = 4，就去Origin[4]裡面，把那個-1改成Dst下一個
        //          node，Origin那個位置的value一定會是-1，不然他不可能會
        //          原本不存在。
        //  Step 2 :
        //          把Dst變成Adjust_Final的下一個節點繼續走
        //
        //  其他case直接continue，因為會中間就跳出來，肯定是更新前跟更新後
        //  都有同樣的節點，這個case我在前面for loop裡面就有handle，所以直
        //  接continue
        //          


    }



    return 0;
}




