// 12/20 -2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int power(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;
    int x, y;

    x = 2;
    y = 5;

    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx^y = %f\n", x, y, pow(x, y));

    return_val = power(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}

// c = a^b
int power(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER i, tmp1, tmp2, tmp3;
    clearByZero(&i);
    clearByZero(c);
    clearByZero(&i);
    clearByZero(b);

    while(1){
        if(numComp(&i, b) != -1){ // i < bが満たされなくなったら
            clearByZero(&i);
            clearByZero(b);
            puts("neko");
            break;
        }

        multiple(a, a, &tmp1);
        add(&tmp1, c, &tmp2);
        copyNumber(&tmp2, c);

        increment(&i, &tmp3);
        copyNumber(&tmp3, &i);
    }

    return 0;
}