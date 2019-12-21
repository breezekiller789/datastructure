#include <stdio.h>

//利用迴圈印出圖形
//     *
//    ***
//   *****
//    ***
//     *
//輸入的值代表最中間那一行的星星數

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=1287

int main(){
    int i;
    int k;
    int m;
    scanf("%d", &k);

    for(i=1; i<=(k+1)/2; ++i){                  //上半部（包含中間行）
        for(m=0; m<(k+1)/2-i; ++m){             //要印的空格數會剛好等於中間行數扣掉該行行數 
            printf(" ");                        //要印的星星數剛好等於該行數兩倍減一 */
        }
        //  前半部
        int j;
        for(j=0; j<(2*i-1)/2; j++){
            printf("%c", '1'+j);   
        }
        //  後半部
        for(int k=j; k>=0; k--){
            printf("%c", '1'+k);
        }
        printf("\n");
    }

    for(i=(k+1)/2-1; i>0; --i){                //下半部
        for(m=0; m<(k+1)/2-i; ++m){            //從中間行的下一行開始印 
            printf(" ");                       //假設k=5，第四行就要比照第二行的方式印，他們是一樣的，上下對稱
        }                                      //只要想辦法把i弄成跟第二行一樣然後慢慢減，上半部是一行一行往下，後面
        //  前半部                             //一行一行往上，這樣反過來做
        int j;                                 
        for(j=0; j<(2*i-1)/2; j++){
            printf("%c", '1'+j);   
        }
        //  後半部
        for(int k=j; k>=0; k--){
            printf("%c", '1'+k);
        }
        if(i!=0)
            printf("\n");
    }


}
