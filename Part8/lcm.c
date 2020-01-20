// 2020/01/17 -2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int lcm(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
    int x, y;

    x = 98765;
    y = 43210;

    setInt(&a, x);
    setInt(&b, y);

    return_val = lcm(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}

// c = aとbの最小公倍数 (lcm(a,b) = (a/gcd(a,b))*b)
int lcm(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER tmp, tmp2;
    gcd(a, b, c);

    if(isZero(c) != -1){ // 0除算になるので
        return 0;
    }

    divide(a, c, &tmp, &tmp2);
    dispNumberZeroSuppress(&tmp);
    dispNumberZeroSuppress(b);
    multiple(&tmp, b, c);

    return 0;
}