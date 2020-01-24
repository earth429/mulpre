// 11/22 -1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"


int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
    int x, y;

    srandom(time(NULL));

    clearByZero(&a);
    clearByZero(&b);

    x = random() % 201 - 100; // -100から100  % 201 - 100
    y = random() % 201 - 100; // -100から100  % 201 - 100

    printf("x = %d\ny = %d\nx - y = %d\n", x, y, x - y);

    setInt(&a, x);
    setInt(&b, y);
    dispNumberZeroSuppress(&a);
    printf("\n");
    dispNumberZeroSuppress(&b);
    printf("\n");

    return_val = sub(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}

int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int h = 0;
    int i;
    int return_val;
    int x, y; // 計算時一時的にaとbの値を入れておく
    struct NUMBER a_abs, b_abs; // aとbの絶対値を格納

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ // c = a - b
        return_val = numComp(a, b); // aとbの大小比較

        switch (return_val)
        {
        case 1: // a>b
            for (i = 0; i < KETA;i++){
                x = a->n[i] - h;
                y = b->n[i];
                if(a->n[i] < b->n[i]){
                    c->n[i] = 10 + x - y;
                    h = 1; // 桁借りをした
                } else if(a->n[i] >= b->n[i]){
                    c->n[i] = x - y;
                    h = 0; // 桁借りをしていない
                }
            }
            if(h != 0){ // オーバーフローする(基本起こらないけど)
                return -1;
            }
            return 0; // 正常に計算できた
        case -1: // a<b
            sub(b, a, c);
            setSign(c, -1);
            return 0;
        case 0: // a==b
            return 0;
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ // c = a + |b|
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; // 正常に計算できた
    } else if(getSign(a) < 0 && getSign(b) > 0){ // c = -(|a| + b)
        getAbs(a, &a_abs);
        add(&a_abs, b, c);
        setSign(c, -1);
        return 0; // 正常に計算できた
    } else if(getSign(a) < 0 && getSign(b) < 0){ // // c = |b| - |a| = a + |b|
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
        return 0; // 正常に計算できた
    }

    return 100; // それ以外
}