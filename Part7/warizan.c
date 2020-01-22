#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int divide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a, b, c, d;
    // int return_val;
    int x, y;
    int i;

    srandom(time(NULL));

    for (i = 0; i < 10;i++){
        x = (random() % 1000);
        y = (random() % 100);

        setInt(&a, x);
        setInt(&b, y);

        printf("x = %d\ny = %d\nx / y = %d\n", x, y, x / y);
        dispNumberZeroSuppress(&a);
        puts("");
        dispNumberZeroSuppress(&b);
        puts("");

        divide(&a, &b, &c, &d);
        setText(&c, x / y);
        checkText();
    }


    return 0;
}

// c = a / b，d = a % b
int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER m, n, p, q;

    // 負の数への対応
    if(getSign(a) > 0 && getSign(b) < 0){ // bが負
        getAbs(b, &p);
        divide(a, &p, c, d);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ // aが負
        getAbs(a, &p);
        divide(&p, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0) { // a,bが負
        getAbs(a, &p);
        getAbs(b, &q);
        divide(&p, &q, c, d);
        setSign(d, -1);
        return 0; 
    }

    clearByZero(c);
    clearByZero(d);

    if(isZero(b) != -1){ // ゼロ除算エラー
        return -1;
    }

    copyNumber(a, &n);

    while(1){
        if(numComp(&n, b) != -1){ // n>=b
            increment(c, &m);
            copyNumber(&m, c);
            sub(&n, b, &m);
            copyNumber(&m, &n);
        } else { // 終了
            copyNumber(&n, d);
            break;
        }
    }

    return 0;
}