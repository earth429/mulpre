// time:7703.000000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int neipia(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    double t1 = time(NULL);

    struct NUMBER a, b, c, d, a_tmp;
    //int return_val;

    setInt(&b, 300); // 

    printf("ネイピア数計算開始\n");
    neipia(&a, &b);
    copyNumber(&a, &a_tmp);
    dispNumberZeroSuppress(&a);
    printf("\n平方根計算開始\n");
    sqrt_newton(&a, &c);
    dispNumberZeroSuppress(&c);
    printf("\n三乗根計算開始\n");
    curt(&a_tmp, &d);
    dispNumberZeroSuppress(&d);
    puts("");
    setText(&a, 9696);
    setText(&c, 2626);
    setText(&d, 7676);

    double t2 = time(NULL);
    printf("処理時間:%f\n", t2 - t1);
    //system("curl -X POST https://maker.ifttt.com/trigger/END/with/key/o1MGI2dHX6aKborXX0xlb");
    return 0;
}

// a = e,b = n
int neipia(struct NUMBER *a, struct NUMBER *b)
{
    struct NUMBER  n, one, divid, divided, quotient, rest;
    //clearByZero(&n);
    //clearByZero(&one);
    //clearByZero(&divid);
    clearByZero(&divided);
    //clearByZero(&quotient);
    clearByZero(a);

    divided.n[KETA-2] = 1;
    setInt(&n,2);
    setInt(&divid,2);
    if(numComp(&n,b) == 1){
        return -1;
    }
    setInt(&one,1);//足していくための1
    multiple(&n,&divided,a);//2*1000000... = a
    //int i = 0;
    while(1){
        quickDivide(&divided,&divid,&quotient,&rest);
        add(a,&quotient,&rest);
        copyNumber(&rest, a);
        /*printf("divided:");
        dispNumberZeroSuppress(&divided);
        puts("");
        printf("divid:");
        dispNumberZeroSuppress(&divid);
        puts("");
        printf("quo:");
        dispNumberZeroSuppress(&quotient);
        puts("");
        printf("a:");
        dispNumberZeroSuppress(a);
        puts("");
        add(a,&quotient,&rest);
        copyNumber(&rest, a);
        puts("inu");*/
        if(numComp(b,&n) == 0){
            break;
        }
        add(&n,&one,&rest);
        copyNumber(&rest, &n);
        multiple(&divid,&n,&rest);
        copyNumber(&rest, &divid);

        /*i++;
        if(i==10){
            puts("10ループ");
            i = 0;
        }*/
    }

    return 0;
}