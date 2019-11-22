// 11/21 -3 + 11/22 -2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    int return_val;

    srandom(time(NULL));

    clearByZero(&a);
    clearByZero(&b);

    setInt(&a, -98);
    setInt(&b, -3);

    return_val = add(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);

    return 0;
}