// 追加

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 15

struct NUMBER{
    int n[KETA]; // 各桁の値
    int sign; // 符号変数
};

void dispNumberZeroSuppress(struct NUMBER *);
// aを表示する
void dispNumber(struct NUMBER *a){
    int i;

    if(a->sign == 1){
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0;i--){
        printf("%2d", a->n[i]);
    }
}

// 多倍長変数の値をゼロクリアし、符号をプラスにセットする
void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    a->sign = 1;
}

// aの下位k桁に乱数値をセットする
void setRnd(struct NUMBER *a, int k){
    int i;
    int judge;

    clearByZero(a);

    for (i = 0; i < k;i++){
        a->n[i] = random() % 10; // random()%(B-A+1)+A
    }

    judge = random() % 2; // 符号をランダムに決める:1は+,0は-

    switch (judge) {
        case 1:
            a->sign = 1;
            break;
        case 0:
            a->sign = -1;
            break;
    }
}

int main(int argc, char **argv)
{
    srandom(time(NULL));
    struct NUMBER a;

    setRnd(&a, 10);

    printf("a = "); // 0が表示されるか
    dispNumberZeroSuppress(&a);
    printf("\n");

    printf("aあり = "); // 0が表示されるか
    dispNumber(&a);
    printf("\n");

}

// aを表示する(ゼロサプレス機能付き)
void dispNumberZeroSuppress(struct NUMBER *a){
    int i;

    if(a->sign == 1) {
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0; i--) {
        if(a->n[i] != 0){
            //printf("あい%d", i);
            break;
        }

        if(i == 0){
            //printf("あい%d", i);
            printf("%2d", a->n[i]);
        }
    }
    for (; i >= 0;i--) {
        //printf("あい%d", i);
        printf("%2d", a->n[i]);
    } 
}