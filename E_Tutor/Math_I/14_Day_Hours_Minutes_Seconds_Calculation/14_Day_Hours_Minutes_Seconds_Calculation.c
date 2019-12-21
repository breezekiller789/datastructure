#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#define MaxLine 1024

//  https://e-tutor.itsa.org.tw/e-Tutor/mod/programming/view.php?id=6894

int main(int argc, char *argv[]){
    int time, Day, Hours, Minutes, Seconds;
    while(scanf("%d", &time) != EOF){
        Day = time/86400;
        Hours = (time - (Day*86400))/3600;
        Minutes = (time - (Day*86400) - (Hours*3600))/60;
        Seconds = time-(Day*86400)-(Hours*3600)-(Minutes*60);
        printf("%d Days\n", Day);
        printf("%d Hours\n", Hours);
        printf("%d Minutes\n", Minutes);
        printf("%d Seconds\n", Seconds);
    }
    

    return 0;
}
