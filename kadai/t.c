// time:7703.000000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int neipia(struct NUMBER *, struct NUMBER *);

int main(int argc, char **argv)
{
    //system("curl -X POST https://maker.ifttt.com/trigger/START/with/key/o1MGI2dHX6aKborXX0xlb");
    //puts("");
    double t1 = time(NULL);

    struct NUMBER a, b, c, d, one, two, three, a_tmp;
    int val;

    setInt(&one ,1);
    setInt(&two, 2);
    setInt(&three, 3);

    setInt(&b, 500); //

    printf("ネイピア数計算開始\n");
    neipia(&a, &b);
    dispNumber(&a);
    //setTextForCheck(&a);
    //checkTextForCheck();
    val = getDigit(&a);
    printf("\nval1:%d\n", val);
    compareNumber(&a, "neipia.txt", val);
    //exit(1);
    
    double t3 = time(NULL);
    printf("\n途中時間:%f\n", t3 - t1);
    printf("\n平方根計算開始\n");
    divBy10(&a, &a_tmp);
    copyNumber(&a_tmp, &a);
    sqrt_newton(&a, &c);
    dispNumberZeroSuppress(&c);
    val = getDigit(&c);
    printf("\nval2:%d\n", val);
    compareNumber(&c, "sqrtE.txt", val);
    t3 = time(NULL);
    printf("\n途中時間:%f\n", t3 - t1);
    printf("\n三乗根計算開始\n");
    //divBy10(&a, &a_tmp);
    //copyNumber(&a_tmp, &a);
    //divBy10(&a, &a_tmp);
    //copyNumber(&a_tmp, &a);


    /*quickDivide(&a, &three, &b, &rest);
    if(numComp(&rest, &one) == 0){
        mulBy10(&a, &a_tmp);
        copyNumber(&a_tmp, &a);
        mulBy10(&a, &a_tmp);
        copyNumber(&a_tmp, &a);
    } else if(numComp(&rest, &two)){
        mulBy10(&a, &a_tmp);
        copyNumber(&a_tmp, &a);
    }*/

    mulBy10(&a, &a_tmp);
    copyNumber(&a_tmp, &a);
    curt(&a, &d);
    dispNumberZeroSuppress(&d);
    val = getDigit(&d);
    printf("\nval3:%d\n", val);
    compareNumber(&d, "curtE.txt", val);
    //setText(&a, 7);
    //setText(&c, 8);
    //setText(&d, 9);

    //setTextForCheck(&a);
    //setTextForCheck(&c);
    //setTextForCheck(&d);
    //checkTextForCheck();

    double t2 = time(NULL);
    printf("\n処理時間:%f\n", t2 - t1);
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

    divided.n[KETA-1] = 1;
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