// 12/20 -2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int power(struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c;
    //int return_val;
    int x, y;
    int i;

    srandom(time(NULL));

    for (i = 0; i < TRY;i++){
        x = (random() % 10);
        y = (random() % 10);

        setInt(&a, x);
        setInt(&b, y);

        power(&a, &b, &c);
        /*printf("ここからスタート\nx = %d\ny = %d\nx^y = %f\n", x, y, pow(x, y));
        printf("c = ");
        dispNumberZeroSuppress(&c);
        puts("");*/

        setText(&c, pow(x, y));
        checkText();
    }

    /*printf("x = %d\ny = %d\nx^y = %f\n", x, y, pow(x, y));
    return_val = power(&a, &b, &c);
    dispNumberZeroSuppress(&c);
    printf("\n戻り値 = %d", return_val);*/

    return 0;
}

// c = a^b
int power(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    struct NUMBER i, tmp, i_tmp;
    setInt(&i, 1);
    clearByZero(c);

    if(isZero(b) != -1){ // 0乗のとき
        setInt(c, 1);
        return 0;
    } else if(numComp(b, &i) == 0){ // 1乗のとき
        copyNumber(a, c);
        return 0;
    }

    copyNumber(a, &tmp);

    while(1){
        /*printf("c:");
        dispNumberZeroSuppress(c);
        puts("");
        printf("i:");
        dispNumberZeroSuppress(&i);
        puts("");
        printf("numComp = %d\n", numComp(&i, b));*/
        if(numComp(&i, b) != -1){ // i < bが満たされなくなったら
            break;
        }
        multiple(a, &tmp, c);
        copyNumber(c, &tmp);

        increment(&i, &i_tmp);
        copyNumber(&i_tmp, &i);
    }

    return 0;
}