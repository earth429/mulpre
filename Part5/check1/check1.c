// 11/15 -1

// ここまでのチェックプログラムその１

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int main(int argc, char **argv)
{
    struct NUMBER a, b, c, d, e;
    int r;     

    srandom(time(NULL)); // 乱数シードの初期化

    clearByZero(&a); // aを0に
    printf("a = "); // 0が表示されるか
    dispNumberZeroSuppress(&a);
    printf("\n");

    setRnd(&b, 10); // bに10桁の乱数(bの初期化はSetRnd内で)
    printf("b = "); // bを表示
    dispNumberZeroSuppress(&b);
    printf("\n");

    copyNumber(&b, &c); // cをbに
    printf("c = "); // cを表示
    dispNumberZeroSuppress(&c);
    printf("\n");

    r = mulBy10(&b, &d); // dをbの10倍に
    printf("b * 10 = "); // dを表示
    dispNumberZeroSuppress(&d);
    printf(", r = %d\n", r);

    r = divBy10(&c, &e); // eをcの1/10に
    printf("c / 10 = "); // eを表示
    dispNumberZeroSuppress(&e);
    printf(", r = %d\n", r);

    printf("a == 0? --> %d\n", isZero(&a)); // isZero()の結果を表示
    printf("b == 0? --> %d\n", isZero(&b));
    printf("c == 0? --> %d\n", isZero(&c));
    printf("d == 0? --> %d\n", isZero(&d));
    printf("e == 0? --> %d\n", isZero(&e));

    return (0);
}