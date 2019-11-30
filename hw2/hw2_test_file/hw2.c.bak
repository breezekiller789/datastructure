#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define MaxLine 1024

int Rounds=0;

//  做初始化，並把總共的節點數找出來
void Initialize(FILE *Input_File, int **Origin, int **Final, int *Number_Of_Nodes
        , int **Output_Array){
    fscanf(Input_File, "%d", Number_Of_Nodes);
    /* printf("%d\n", *Number_Of_Nodes); */
    *Origin = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    *Final = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    *Output_Array = (int *)malloc(sizeof(int) * *Number_Of_Nodes);
    for(int i=0; i<*Number_Of_Nodes; i++){
        (*Output_Array)[i] = 0;
    }
}

//  把input吃進來放進陣列
void Get_Input(int *Origin, int *Final, int Number_Of_Nodes, FILE *Input_File){

    int idx=0;
    while(idx < 2){
        for(int i=0; i< Number_Of_Nodes; i++){
            if(idx == 0){
                fscanf(Input_File, "%d", Origin+i);
                /* printf("%d ", *(Origin+i)); */
            }
            else{
                fscanf(Input_File, "%d", Final+i);
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
            /* printf("%d ", (*Adjust_Origin)[cnt]); */
            cnt++;
            continue;
        }
        (*Adjust_Origin)[cnt] = Origin[idx];
        idx = Origin[idx];
        if((*Adjust_Origin)[cnt] == -1)
            break;
        /* printf("%d ", (*Adjust_Origin)[cnt]); */
        cnt++;
    }
    /* printf("\n"); */
    *Number_Of_Origins = cnt;
    /* printf("cnt = %d", cnt); */

    //  這段在做一樣的事情，只是是把"更新後"的table放進新的陣列
    cnt=0;
    idx=0;
    while(cnt < Number_Of_Nodes){
        //  多這段if是因為我希望有source在最前面，這樣我演算法比較好做。
        if(cnt == 0){
            (*Adjust_Final)[cnt] = 0;
            /* printf("%d ", (*Adjust_Final)[cnt]); */
            cnt++;
            continue;
        }
        (*Adjust_Final)[cnt] = Final[idx];
        idx = Final[idx];
        if((*Adjust_Final)[cnt] == -1)
            break;
        /* printf("%d ", (*Adjust_Final)[cnt]); */
        cnt++;
    }
    *Number_Of_Finals = cnt;
    /* printf("cnt = %d", cnt); */
    /* printf("\n"); */

}

int main(int argc, char *argv[]){

    FILE *Input_File, *Output_File;
    char *line;
    int *Origin, *Final, Number_Of_Nodes = 0;
    int Number_Of_Origins, Number_Of_Finals;    //  算出調整後的長度分別多少
    int *Adjust_Origin, *Adjust_Final;  //  事後把讀進來的做順序調整
    int cnt, idx;   //  迴圈控制用的變數
    int *Output_Array, **Update_Rules, **Outputs;
    int *Last_Print;
    Last_Print = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    /* Input_File = fopen("input1.txt", "r"); */
    /* Input_File = fopen("input2.txt", "r"); */
    /* Input_File = fopen("input3.txt", "r"); */
    Input_File = fopen("./hw2_test_file/input.txt", "r");
    Output_File = fopen("Output.txt", "r");
    Outputs = (int **)malloc(sizeof(int *) * 20);

    //  做初始化
    Initialize(Input_File, &Origin, &Final, &Number_Of_Nodes, &Output_Array);

    //  把input吃進來然後擺進陣列
    Get_Input(Origin, Final, Number_Of_Nodes, Input_File);

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

    *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    for(cnt=0; cnt<Number_Of_Nodes; cnt++){
        (*(Outputs+Rounds))[cnt] = Origin[cnt];
        /* printf("%d ", Origin[cnt]); */
    }
    /* printf("\n"); */
    ++Rounds;
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
                    Length *= -1;
                }
                else{
                    Length = end - start - 1;
                }

                //  Step 2
                *(Update_Rules + Rules_Cnt) = (int *)malloc(sizeof(int) * 4);
                (*(Update_Rules + Rules_Cnt))[0] = Src;
                (*(Update_Rules + Rules_Cnt))[1] = Dst;
                (*(Update_Rules + Rules_Cnt))[2] = Length;
                //  這個for loop是把我現在所有更新的路徑都印出來
                //  (x, y, z) ->三個欄位，第一個欄位是開始的節點，第二個是結束
                //  的節點，第三個是這兩個節點中，距離是多少
                /* for(int j=0; j<3; j++){ */
                /*     printf("%d ", (*(Update_Rules + Rules_Cnt))[j]); */
                /* } */
                /* printf("\n"); */
                Rules_Cnt++;

                //  印出我爬出來的長度是不是對的
                /* printf("end = %d, start = %d\n", end, start); */
                /* printf("Length = %d\n", Length); */

                //  Step 3
                end = start = -1;   //  這兩個要設回去初始值
                Src = Dst;          // Dst給Src，然後Dst變成Src下一個繼續跑
                Dst = Adjust_Final[++idx];
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
        //  路徑上沒有這個節點，可以直接去把Output_Array做更新。
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
        if(cnt == Number_Of_Finals+1){
            //  把這個原本路徑上沒有的節點，回去更新，方法簡單講，就是把這個節
            //  點的值，例如是5的話，就回去原本路徑中第五個位置的那個節點的值
            //  改成第5個節點的下一個，這真的要想一下。
            *(Output_Array+Adjust_Final[idx]) = Adjust_Final[idx+1];
            Dst = Adjust_Final[++idx];
            /* printf("idx = %d\n", idx); */
        }
        else
            continue;


    }
    //  印出0th round的結果
    /* printf("0th Round\n"); */
    *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    for(int k=0; k<Number_Of_Nodes; k++){
        (*(Outputs+Rounds))[k] = *(Output_Array+k);
        /* printf("%d ", *(Output_Array+k)); */
    }
    /* printf("\n"); */
    ++Rounds;

    //  奇數回合，先用一層for把最大值掃出來，拿到最大值之後，再用一層for，再進
    //  去爬一次，把那些最大值的Rule擺進一個新的陣列，之後再進去這些都是最長路
    //  徑的Rule裡面，找出source是最小的，這一個Rule是肯定要在這一round更新的，
    //  沒有例外，完成之後就回去Update_Rules裡面爬，把剛剛選出來要更新的那個路
    //  徑，去origin裡面走一次，走一個節點就回去檢查Update_Rules裡面有沒有相同
    //  的Source節點（注意，如果長度是負的，直接跳過不看，因為他是往回走的），
    //  如果有遇到一樣的Source節點，代表有overlab!!，這條Update_Rule就要在偶數
    //  回合更新，建立一個Even_Round，來擺放偶數回合要更新的，然後一直爬一直爬
    //  ，爬到最後，如果Update_Rules還有剩下，代表這些剩下的也可以和原本肯定要
    //  更新的一起做更新。
    //  Step 1:
    //          for loop進去爬，找出最大路徑，要先檢查這個Update_Rule是不是NULL
    //          是NULL就continue
    //  Step 2:
    //          再一個for loop回去爬，路徑長度是最大路徑的，把它放進一個array
    //          MAX_PATH，然後把MAX_Cnt+1，因為有可能會有多個。
    //  Step 3:
    //          再一個for loop進去這個新的array裡面爬，爬出一個Src（第一個欄位）
    //          最小的，這個路徑肯定要更新，把這條路徑，擺進Odd_Round_Update，
    //          然後把這在Update_Rule中Free掉，然後用一個變數Odd_Round_Cnt，
    //          把他+1
    //  Step 4:
    //          要略過Odd_Round_Update那個路徑，檢查Src是不是一樣，一樣的要略過。
    //          從Update_Rules開始一個一個Rule，回去Adjust_Origin裡面找，要先檢查這個
    //          Rule的長度，若是負的代表他往回走，直接continue，檢查是正的之後
    //          就拿這個Update_Rule的Src跟Dst進去Adjust_Origin爬，看有沒有一樣的節點
    //          ，不管是Src還是Dst有一樣，就把這個Update_Rule擺進Even_Round_Update
    //          ，同時把他再Update_Rule裡面的位置Free掉，然後把Even_Round_Cnt
    //          加一，代表他要在偶數回合更新，如果該Update_Rule的Src跟Dst，都
    //          沒有出現在Origin裡面，代表這個Update_Rule也可以同時更新，直接
    //          擺進Odd_Round_Update，再把Odd_Round_Cnt+1然後再把她在Update_Rule
    //          中的位置Free掉。
    //  Step 5:
    //          去Output_Array裡面，Odd_Round_Update把要更新的更新進去，例如
    //          Odd_Round_Update要更新的是 (0, 3)，代表後來是從0走到3，就去
    //          Adjust_Final裡面找，找到0這個節點，然後把這個節點的下一個節點
    //          的值更新回去Output_Array[0]，再舉個例子，假如是(2, 14)，就是
    //          Adjust_Final裡面，找值是2這個節點，找到之後，把他的下一個節點
    //          ，拿去Output_Array[2]更新。
    //  Step 6:
    //          印出Output_Array
    
    //
    //          
    //  偶數回合，把剛剛弄好的Even_Round_Update，拿去更新，然後把後續的清理程序
    //  做好，首先，先把Odd_Round_Update, Even_Round_Update, MAX_PATH, 都清掉，
    //  下一個奇數回合才可以正常使用。
    //  Step 1:
    //          把Even_Round_Update裡面的路徑一個個抓出來更新，先從第一個路徑
    //          開始，假設是(1, 4)就去Adjust_Final裡面找看看1這個節點，找到之後
    //          把他的下一個節點，拿去Output_Array[1]更新。
    //  Step 2:
    //          更新完之後檢查看看，Update_Rules裡面是不是還有往後跳的，如果還
    //          有往後跳的，就可以繼續做下一步，如果已經沒有往前跳的，都只剩下
    //          往回跳，代表已經做到最後一步，就把Update_Rules裡面的通通拿去
    //          更新。
    //  Step 3:
    //          把Odd_Round_Update, Even_Round_Update, MAX_PATH清掉，記得用
    //          Odd_Round_Cnt, Even_Round_Cnt, MAX_Cnt來清，不然會seg fault，
    //          然後清完之後，要把Odd_Round_Cnt, Even_Round_Cnt, MAX_Cnt設為0
    //  Step 4:
    //          把Update_Rules整理，因為剛剛會有一些是被Free的，把我在第零個
    //          round的算出來的Rules_Cnt拿來用，迴圈控制就用Rules_Cnt來跳出回圈
    //
    //  Step 5:
    //          印出Output_Array
    //
    int MAX = (*Update_Rules)[2];
    int **MAX_PATH, **Odd_Round_Update, **Even_Round_Update, MAX_Cnt = 0;
    int Odd_Round_Cnt=0, Even_Round_Cnt=0, Round_Cnt=1;
    MAX_PATH = (int **)malloc(sizeof(int *) * Rules_Cnt);
    Odd_Round_Update = (int **)malloc(sizeof(int *) * Rules_Cnt);
    Even_Round_Update = (int **)malloc(sizeof(int *) * Rules_Cnt);
    /* printf("%d\n", MAX); */

    while(Rules_Cnt != 0){
        /* printf("Round_Cnt = %d\n", Round_Cnt); */
        
        //  Odd_Round :
        if(Round_Cnt % 2 == 1){
        //  Step 1
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if(*(Update_Rules+cnt) == NULL){
                    continue;
                }
                if((*(Update_Rules+cnt))[2] > MAX){
                    MAX = (*(Update_Rules+cnt))[2];
                }
                else
                    continue;
            }
            /* printf("MAX = %d\n", MAX); */
            //  Step 2
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if((*(Update_Rules+cnt))[2] == MAX){
                    *(MAX_PATH+MAX_Cnt) = (int *)malloc(sizeof(int) * 3);
                    memcpy(*(MAX_PATH+MAX_Cnt), *(Update_Rules+cnt), sizeof(int) * 3);
                    MAX_Cnt++;
                }
            }
                /* printf("MAX_Cnt = %d\n", MAX_Cnt); */
            //  Step 3
            int MIN = *Update_Rules[0];
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if((*(Update_Rules+cnt))[0] < MIN){
                    MIN = (*(Update_Rules+cnt))[0];
                }
            }
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if((*(Update_Rules+cnt))[0] == MIN){
                    *(Odd_Round_Update+Odd_Round_Cnt) = (int *)malloc(sizeof(int) * 3);
                    memcpy(*(Odd_Round_Update+Odd_Round_Cnt), *(Update_Rules+cnt), sizeof(int) * 3);
                    Odd_Round_Cnt++;
                    *(Update_Rules+cnt) = NULL;
                }
            }
            /* for(int j=0; j<3; j++) */
            /*     printf("%d ", (*Odd_Round_Update)[j]); */
            /* printf("\n"); */
            //  Step 4
            int Length;
            for(int j=0; j<Number_Of_Origins; j++){
                if(Adjust_Origin[j] == (*Odd_Round_Update)[0]){
                    for(cnt=0; cnt<Rules_Cnt; cnt++){
                        //  如果是Odd_Round_Update，就continue
                        if(*(Update_Rules+cnt) == NULL){
                            continue;
                        }
                        //  長度是負的，代表往回走，也是continue
                        else if((*(Update_Rules+cnt))[2] < 0){
                            continue;
                        }
                        else{
                            /* sleep(3); */
                            Src = (*(Update_Rules+cnt))[0];
                            Dst = (*(Update_Rules+cnt))[1];
                            /* printf("Src = %d, Dst = %d\n", Src, Dst); */
                            Length = (*Odd_Round_Update)[2];
                            for(idx=0; idx<Length; idx++){
                                if(Adjust_Origin[idx] == Src){
                                    *(Even_Round_Update+Even_Round_Cnt) = (int *)malloc(sizeof(int) * 3);
                                    memcpy(*(Even_Round_Update+Even_Round_Cnt), *(Update_Rules+cnt), sizeof(int) * 3);
                                    Even_Round_Cnt++;
                                    *(Update_Rules+cnt) = NULL;
                                    break;
                                }
                            }
                            //  如果有人走到最後了，代表這個路徑沒有overlab，可以
                            //  一起更新。
                            /* printf("Length = %d, idx = %d, cnt = %d\n", Length, idx, cnt); */
                            /* printf("%d\n", (*(Update_Rules+cnt))[0]); */
                            if(idx == Length){
                                *(Odd_Round_Update+Odd_Round_Cnt) = (int *)malloc(sizeof(int) * 3);
                                memcpy(*(Odd_Round_Update+Odd_Round_Cnt), *(Update_Rules+cnt), sizeof(int) * 3);
                                Odd_Round_Cnt++;
                                *(Update_Rules+cnt) = NULL;
                            }
                        }

                    }
                }
            }
            //  Step 5
            for(cnt=0; cnt<Odd_Round_Cnt; cnt++){
                Src = (*(Odd_Round_Update+cnt))[0];
                /* printf("Src = %d, cnt = %d\n", Src, cnt); */
                for(idx=0; idx<Number_Of_Finals; idx++){
                    if(Adjust_Final[idx] == Src){
                        Output_Array[Src] = Adjust_Final[idx+1];
                    }
                }
            }
            //  Step 6
            memcpy(Last_Print, Output_Array, sizeof(int) * Number_Of_Nodes);
            /* printf("Odd_Round Step 6 print\n"); */
            *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
            for(cnt=0; cnt<Number_Of_Nodes; cnt++){
                (*(Outputs+Rounds))[cnt] = Output_Array[cnt];
                /* printf("%d ", Output_Array[cnt]); */
            }
            /* printf("\n"); */
            ++Rounds;
            Round_Cnt++;
            continue;
        }
        
        //  Even Round
        else{
            //  Step 1
            for(cnt=0; cnt<Even_Round_Cnt; cnt++){
                Src = (*(Even_Round_Update+cnt))[0]; 
                for(idx=0; idx<Number_Of_Finals; idx++){
                    if(Adjust_Final[idx] == Src){
                        Output_Array[Src] = Adjust_Final[idx+1];
                    }
                }
            }
            for(idx=0;idx<Number_Of_Nodes; idx++){
                if(Last_Print[idx] != Output_Array[idx]){
                    /* printf("Even_Round Step 1\n"); */
                    *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
                    for(cnt=0; cnt<Number_Of_Nodes; cnt++){
                        (*(Outputs+Rounds))[cnt] = Output_Array[cnt];
                        /* printf("%d ", Output_Array[cnt]); */
                    }
                    /* printf("\n"); */ 
                    ++Rounds;
                    memcpy(Last_Print, Output_Array, sizeof(int) * Number_Of_Nodes);
                }
            }
            //  Step 2
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if(*(Update_Rules+cnt) == NULL){
                    continue;
                }
                if((*(Update_Rules+cnt))[2] > 0){
                    break;
                }
            }
            if(cnt == Rules_Cnt){
                //  進這個if，代表已經沒有往後跳的，全都往回跳，直接把Update_Rules
                //  都更新掉。
                for(int i=0; i<Rules_Cnt; i++){
                    if(*(Update_Rules+i) == NULL){
                        //  要跳過空的，不然會seg fault
                        continue;
                    }
                    Src = (*(Update_Rules+i))[0];
                    for(int j=0; j<Number_Of_Nodes; j++){
                        if(Adjust_Final[j] == Src){
                            /* printf("Adjust_Final[j+1] = %d, Src = %d\n", Adjust_Final[j+1], Src); */
                            Output_Array[Src] = Adjust_Final[j+1];
                        }
                    }
                    *(Update_Rules+i) = NULL;
                }
                for(idx=0;idx<Number_Of_Nodes; idx++){
                    if(Last_Print[idx] != Output_Array[idx]){
                        /* printf("Even_Round Step 2\n"); */
                        *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
                        for(cnt=0; cnt<Number_Of_Nodes; cnt++){
                            (*(Outputs+Rounds))[cnt] = Output_Array[cnt];
                            /* printf("%d ", Output_Array[cnt]); */
                        }
                        /* printf("\n"); */
                        ++Rounds;
                        memcpy(Last_Print, Output_Array, sizeof(int) * Number_Of_Nodes);
                        break;
                    }
                }
                break;
            }
            else{
                Round_Cnt++;
                continue;
            }
            //  Step 3
            //  重設Odd_Round_Update
            for(cnt=0; cnt<Odd_Round_Cnt; cnt++){
                free(*(Odd_Round_Update+cnt));
            }
            //  重設Even_Round_Update
            for(cnt=0; cnt<Even_Round_Cnt; cnt++){
                free(*(Even_Round_Update+cnt));
            }
            //  重設MAX_PATH
            for(cnt=0; cnt<MAX_Cnt; cnt++){
                free(*(MAX_PATH+cnt));
            }
            //  Step 4
            //  重設Update_Rules
            int Rules_Cnt_After = 0, **Tmp;
            Tmp = (int **)malloc(sizeof(int *) * Rules_Cnt);
            for(cnt=0; cnt<Rules_Cnt; cnt++){
                if(*(Update_Rules+cnt) == NULL){
                    continue;
                }
                else{
                    *(Tmp+Rules_Cnt_After) = (int *)malloc(sizeof(int) * 3);
                    Rules_Cnt_After++;
                }
            }
            Rules_Cnt = Rules_Cnt_After;
            /* printf("Rules_Cnt_After = %d\n", Rules_Cnt_After); */
            Odd_Round_Cnt = Even_Round_Cnt = MAX_Cnt = 0;
            if(Rules_Cnt_After == 0)
                break;


            //  Step 5
            *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
            for(cnt=0; cnt<Number_Of_Nodes; cnt++){
                (*(Outputs+Rounds))[cnt] = Output_Array[cnt];
                /* printf("%d ", Output_Array[cnt]); */
            }
            /* printf("\n"); */ 
            ++Rounds;
            Round_Cnt++;
        }
    }
    /* printf("Last\n"); */
    *(Outputs+Rounds) = (int *)malloc(sizeof(int) * Number_Of_Nodes);
    for(cnt=0; cnt<Number_Of_Nodes; cnt++){
        (*(Outputs+Rounds))[cnt] = Final[cnt];
        /* printf("%d ", Final[cnt]); */
    }
    /* printf("\n"); */
    ++Rounds;
    printf("%d\n", Rounds);
    for(cnt=0; cnt<Rounds; cnt++){
        for(idx=0; idx<Number_Of_Nodes; idx++){
            printf("%d ", (*(Outputs+cnt))[idx]);
        }
        printf("\n");
    }
    /* printf("Even_Round_Cnt = %d\n", Even_Round_Cnt); */
    /* for(int k=0; k<Even_Round_Cnt; k++){ */
    /*     for(int j=0; j<3; j++) */
    /*         printf("%d ", (*(Even_Round_Update+k))[j]); */
    /*     printf("\n"); */
    /* } */




    return 0;
}




