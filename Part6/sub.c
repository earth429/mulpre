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
