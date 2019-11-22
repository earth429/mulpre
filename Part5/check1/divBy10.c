// 11/06 -6
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KETA 10

struct NUMBER{
    int n[KETA]; // 各桁の値
    int sign; // 符号変数
};

void clearByZero(struct NUMBER *);
void dispNumber(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
int divBy10(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a;
    struct NUMBER b, c, d;

    srandom(time(NULL));

    clearByZero(&a);
    clearByZero(&b);
    clearByZero(&c);
    clearByZero(&d);

    printf("a = ");
    dispNumber(&a);
    printf("\n");
    printf("b = ");
    dispNumber(&b);
    printf("\n");
    printf("c = ");
    dispNumber(&c);
    printf("\n");
    printf("d = ");
    dispNumber(&d);
    printf("\n");

    setRnd(&a, 3);

    printf("a = ");
    dispNumber(&a);
    printf("\n");


    printf("あまり=%d\n", divBy10(&a, &b));

    printf("b = ");
    dispNumber(&b);
    printf("\n");

    printf("あまり=%d\n", divBy10(&b, &c));

    printf("c = ");
    dispNumber(&c);
    printf("\n");

    printf("あまり=%d\n", divBy10(&c, &d));

    printf("d = ");
    dispNumber(&d);
    printf("\n");

    return 0;
}

// 多倍長変数の値をゼロクリアし、符号をプラスにセットする
void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    a->sign = 1;
}

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

// aの下位k桁に乱数値をセットする
void setRnd(struct NUMBER *a, int k){
    int i;
    int judge;

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

// aをbにコピーする
void copyNumber(struct NUMBER *a, struct NUMBER *b){
    int i;

    b->sign = a->sign;

    for (i = 0; i < KETA;i++){
        b->n[i] = a->n[i];
    }
}

// aの絶対値をbに返す
void getAbs(struct NUMBER *a, struct NUMBER *b){
    copyNumber(a, b);
    b->sign = 1;
}

// aがゼロか判別する 0でなかったら戻り値-1 (符号は見ていない)
int isZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        if(a->n[i] != 0){
            return -1;
        }
    }

    return 0;
}

// aを10倍にしてbに返す
int mulBy10(struct NUMBER *a, struct NUMBER *b){
    int i;

    // オーバーフローする
    if(a->n[KETA - 1] != 0){
        return -1;
    }

    for (i = KETA - 2; i >= 0;i--){
        b->n[i + 1] = a->n[i];
    }

    b->n[0] = 0;

    return 0;
}

// aを1/10倍にしてbに返す 戻り値:aを10で割った余り
int divBy10(struct NUMBER *a, struct NUMBER *b){
    int i;
    int remainder; // 余りを格納

    b->sign = a->sign; // 符号の共通化

    remainder = a->sign * a->n[0]; // 余りに符号をつける

    for (i = 1; i <= KETA - 2;i++){
        b->n[i - 1] = a->n[i];
    }

    b->n[KETA -1] = 0;

    return remainder;
}