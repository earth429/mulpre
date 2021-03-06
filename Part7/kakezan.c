#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    //int return_val;
    int x, y;
    int i;

    srandom(time(NULL));

    for (i = 0; i < 10;i++){
        x = (random() % 1000);
        y = (random() % 1000);

        setInt(&a, x);
        setInt(&b, y);

        printf("x = %d\ny = %d\nx * y = %d\n", x, y, x * y);
        dispNumberZeroSuppress(&a);
        puts("");
        dispNumberZeroSuppress(&b);
        puts("");

        multiple(&a, &b, &c);
        setText(&c, x * y);
        checkText();
    }
        

    /*printf("x = %d\ny = %d\nx * y = %d\n", x, y, x * y);

    return_val = multiple(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);*/

    return 0;
}

// c = a * b
int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int i, j, h, e, aj, bi;
    struct NUMBER a_abs, b_abs, d, tmp;

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ // c = a * b
        for (i = 0; i < KETA;i++){
            bi = b->n[i];
            h = 0;
            clearByZero(&d);
            for (j = 0; j < KETA;j++){
                aj = a->n[j];
                e = aj * bi + h; //e = a->n[j] * b->n[i] + h;
                if(j + i < KETA){ // 配列の範囲外をアクセスしないように
                    d.n[j + i] = (e % 10); // 1桁目を取り出す
                    e /= 10;
                    h = e; // 2桁目を取り出す
                }
                
            }
            if(h != 0){ // オーバーフローする
                return -1;
            }
            add(c, &d, &tmp);
            copyNumber(&tmp, c);
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ // c = -a * |b|
        getAbs(b, &b_abs);
        multiple(a, &b_abs, c);
        setSign(c, -1);
    } else if(getSign(a) < 0 && getSign(b) > 0){ // c = -|a| * b
        getAbs(a, &a_abs);
        multiple(&a_abs, b, c);
        setSign(c, -1);
    } else if(getSign(a) < 0 && getSign(b) < 0){ // // c = |a| * |b|
        getAbs(a, &a_abs);
        getAbs(b, &b_abs);
        multiple(&a_abs, &b_abs, c);
    }

    return 0; // 正常終了
}