#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int quickDivide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    double t1 = time(NULL);
    struct NUMBER a, b, c, d;
    //int return_val;
    int x, y;
    

    x = 49585;
    y = 98;


    setInt(&a, x);
    setInt(&b, y);

    printf("x = %d\ny = %d\nx / y = %d\nx %% y = %d\n", x, y, x / y, x % y);

    quickDivide(&a, &b, &c, &d);
    dispNumberZeroSuppress(&c);
    puts("");
    dispNumberZeroSuppress(&d);
    puts("");

    /*srandom(time(NULL));

    int i;

    for (i = 0; i < TRY;i++){
        x = (random() % 100000);
        y = (random() % 100);

        setInt(&a, x);
        setInt(&b, y);

        printf("x = %d\ny = %d\nx / y = %d\n", x, y, x / y);
        dispNumberZeroSuppress(&a);
        puts("");
        dispNumberZeroSuppress(&b);
        puts("");

        quickDivide(&a, &b, &c, &d);
        dispNumberZeroSuppress(&c);
        puts("");
        setText(&c, x / y);
        checkText();
    }*/

    double t2 = time(NULL);
    printf("処理時間:%f\n", t2 - t1);
    // system("curl -X POST https://maker.ifttt.com/trigger/END/with/key/o1MGI2dHX6aKborXX0xlb");
    return 0;
}

// c = a / b，d = a % b(改良版) 499786/98ができない
int quickDivide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d) {
    struct NUMBER tmp1, tmp2, a_tmp, e;

    if(isZero(b) != -1){ // ゼロ除算エラー
        return -1;
    }

    // 負の数への対応
    if(getSign(a) > 0 && getSign(b) < 0){ // bが負
        getAbs(b, &tmp1);
        divide(a, &tmp1, c, d);
        setSign(c, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) > 0){ // aが負
        getAbs(a, &tmp1);
        divide(&tmp1, b, c, d);
        setSign(c, -1);
        setSign(d, -1);
        return 0; 
    } else if(getSign(a) < 0 && getSign(b) < 0) { // a,bが負
        getAbs(a, &tmp1);
        getAbs(b, &tmp2);
        divide(&tmp1, &tmp2, c, d);
        setSign(d, -1);
        return 0; 
    }

    clearByZero(c); // 1
    copyNumber(a, &a_tmp);
    clearByZero(d);

    while(1){
        if(numComp(&a_tmp, b) >= 0){ // 2.a>=b
            copyNumber(b, d); // 3
            setInt(&e, 1); // 4
            while(1){ // a > dになる最大のdを探す
                if(numComp(&a_tmp, d) >= 0){
                    mulBy10(d, &tmp1);
                    copyNumber(&tmp1, d);
                    mulBy10(&e, &tmp2);
                    copyNumber(&tmp2, &e);
                } else { // 5.a > dでなくなったら
                    divBy10(d, &tmp1); // 1つ前の値がa > dなので
                    copyNumber(&tmp1, d);
                    divBy10(&e, &tmp2);
                    copyNumber(&tmp2, &e);
                    break;
                }
            }
            sub(&a_tmp, d, &tmp1); // 7
            copyNumber(&tmp1, &a_tmp);
            add(c, &e, &tmp2); // 8
            copyNumber(&tmp2, c);
            // 9は2に戻る
            printf("c:");
            dispNumberZeroSuppress(c);
            puts("");
            printf("d:");
            dispNumberZeroSuppress(d);
            puts("");
            printf("a_tmp:");
            dispNumberZeroSuppress(&a_tmp);
            puts("");
        } else if(numComp(&a_tmp, b) < 0){ // 終了, 10
            copyNumber(&a_tmp, d);
            break; // 11
        }
    }

    return 0;
}