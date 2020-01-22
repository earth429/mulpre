// 11/27 -2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
int x, y;

    x = 16;
    y = 16;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx * y = %d\n", x, y, x * y);

    return_val = multiple(&a, &b, &c);
    printf("\n");
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}

// c = a * b
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int i, j, h, e, aj, bi;
    struct NUMBER tmp, d;
    //int flag_a = 0; // aが負の値だったとき1に
    //int flag_b = 0; // aが負の値だったとき1に

    clearByZero(c);
    dispNumberZeroSuppress(a);
    dispNumberZeroSuppress(b);

    for (i = 0; i < KETA;i++){
        printf("iはここですよ%d\n", i);
        bi = b->n[i];
        h = 0;
        clearByZero(&d);
        for (j = 0; j < KETA;j++){
            aj = a->n[j];
            printf("aj:%d\nbi%d\n", aj, bi);
            //printf("a:");
            //dispNumberZeroSuppress(a);
            // printf("\nb:");
            // dispNumberZeroSuppress(b);
            // puts("");
            e = aj * bi + h; //e = a->n[j] * b->n[i] + h;
            printf("e:%d\n", e); //
            if(j + i < KETA){
                d.n[j + i] = (e % 10); // 1桁目を取り出す
                printf("dl:");
                dispNumberZeroSuppress(&d);
                puts("");
                e /= 10;
                h = e; // 2桁目を取り出す
            }
        }

        if(h != 0){ // オーバーフローする
            return -1;
        }
        printf("c:");
        dispNumberZeroSuppress(c);
        printf("d:");
        dispNumberZeroSuppress(&d);
        puts("");
        add(c, &d, &tmp);
        copyNumber(&tmp, c);
    }

    /*if(getSign(a) == -1){
        setSign(a, 1);
        flag_a++;
    } else if(getSign(b) == -1){
        setSign(b, 1);
        flag_b++;
    }

    if(numComp(a, b) == -1){
        copyNumber(&tmp, a);
        copyNumber(a, b); // bの値をaにする
        copyNumber(&tmp, b);
    }

    copyNumber(a, c);

    while(1){
        add(a, c, c);
        i++;

        if(i == b){
            break;
        }
    }

    if(flag_a != 0 && flag_b != 0){
        // スルー
    } else if(flag_a != 0){nie
        setSign(c, -1);
    } else if(flag_b != 0){
        setSign(c, -1);
    }*/

    return 0; // 正常終了
}