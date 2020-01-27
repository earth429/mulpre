#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mulprec.h"

int curt(struct NUMBER *, struct NUMBER *);

/*int curt2(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER x, ox, tx, px, dx, zero, one, two, three, quotient, sum, rest; // x:現在の平方根の近似値,ox:1つ前のx,tx:2つ前のx
    //clearByZero(b);
    setInt(&zero, 0);
    setInt(&one, 1);
    setInt(&two, 2);
    setInt(&three, 3);

    quickDivide(a, &two, &x, &rest);
    if(isZero(&x) != -1 || numComp(&x, &one) == 0){ // a = 0 or 1なら curt(a) = a
        copyNumber(a, b);
        return 0;
    }
    if (numComp(&x, &zero) == -1){ // a < 0ならエラーで-1を返す
        return -1;
    }

    copyNumber(&x, &ox);

    while(1){
        copyNumber(&ox, &tx); // tx = 2つ前のx
        copyNumber(&x, &ox); // ox = 1つ前のx
        power(&ox, &two, &px); // px = ox^2
        /*printf("a:");
        dispNumberZeroSuppress(a);
        puts("");
        printf("px:");
        dispNumberZeroSuppress(&px);
        puts("");
        quickDivide(a, &px, &quotient, &rest);
        /*printf("a2:");
        dispNumberZeroSuppress(a);
        puts("");
        printf("px2:");
        dispNumberZeroSuppress(&px);
        puts("");
        printf("quotient2:");
        dispNumberZeroSuppress(&quotient);
        puts("");*/

        /*printf("ox:");
        dispNumberZeroSuppress(&ox);
        puts("");*/
        multiple(&ox, &two, &dx); // dx = 2ox
        /*printf("dx:");
        dispNumberZeroSuppress(&dx);
        puts("");

        /*printf("dx:");
        dispNumberZeroSuppress(&dx);
        puts("");
        printf("quo:");
        dispNumberZeroSuppress(&quotient);
        puts("");
        add(&dx, &quotient, &sum);
        printf("sum:");
        dispNumberZeroSuppress(&sum);
        puts("");
        quickDivide(&sum, &three, &x, &rest);

        printf("x:");
        dispNumberZeroSuppress(&x);
        puts("");
        
        if(numComp(&x, &ox) == 0){ // 収束
            puts("収束");
            break;
        }
        if(numComp(&x, &tx) == 0){ // 振動
            puts("振動");
            if(numComp(&ox, &x) == -1){ // 小さい方を取る
                copyNumber(&ox, &x);
            }
            break;
        }
    }

    copyNumber(&x, b);
    return 0;
}*/

int main(int argc, char **argv)
{
    struct NUMBER r1, ans, tmp;
    int j, r;
    //double r2;

    srandom(time(NULL));

    r = 27;
    setInt(&r1, r);
    /*for (j = 0; j < 10;j++){
        mulBy10(&r1, &tmp);
        copyNumber(&tmp, &r1);
    }*/
    curt(&r1, &ans);
    printf("r:%d\nr1:", r);
    dispNumberZeroSuppress(&ans);
    puts("");

    /*for (i = 0; i < 10;i++){
        r = random();
        setInt(&r1, r);
        for (j = 0; j < 10;j++){
            mulBy10(&r1, &tmp);
            copyNumber(&tmp, &r1);
        }
        curt(&r1, &ans);
        printf("r:%d\nr1:", r);
        dispNumberZeroSuppress(&ans);
        puts("");
        r2 = pow((double)r, 1/3);
        printf("r2:%f\n", r2);
    }*/

    return 0;
}

// b = curt(a) 三乗根
int curt(struct NUMBER *a, struct NUMBER *b) {
    struct NUMBER x, ox, tx, px, dx, zero, one, two, three, quotient, sum, rest; // x:現在の平方根の近似値,ox:1つ前のx,tx:2つ前のx
    setInt(&zero, 0);
    setInt(&one, 1);
    setInt(&two, 2);
    setInt(&three, 3);

    quickDivide(a, &two, &x, &rest);
    if(isZero(&x) != -1 || numComp(&x, &one) == 0){ // a = 0 or 1なら curt(a) = a
        copyNumber(a, b);
        return 0;
    }
    if (numComp(&x, &zero) == -1){ // a < 0ならエラーで-1を返す
        return -1;
    }

    copyNumber(&x, &ox);

    while(1){
        copyNumber(&ox, &tx); // tx = 2つ前のx
        copyNumber(&x, &ox); // ox = 1つ前のx
        power(&ox, &two, &px); // px = ox^2
        quickDivide(a, &px, &quotient, &rest);
        multiple(&ox, &two, &dx); // dx = 2ox
        add(&dx, &quotient, &sum);
        quickDivide(&sum, &three, &x, &rest);

        if(numComp(&x, &ox) == 0){ // 収束
            break;
        }
        if(numComp(&x, &tx) == 0){ // 振動
            if(numComp(&ox, &x) == -1){ // 小さい方を取る
                copyNumber(&ox, &x);
            }
            break;
        }
    }

    copyNumber(&x, b);
    return 0;
}