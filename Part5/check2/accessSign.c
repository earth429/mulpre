// 11/21 -1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int setSign(struct NUMBER *, int);
int getSign(struct NUMBER *);

int main(int argc, char **argv)
{
    struct NUMBER a;
    clearByZero(&a);
    dispNumberZeroSuppress(&a);
    setSign(&a, -1);
    dispNumberZeroSuppress(&a);

    return 0;
}

// 多倍長変数aの符号をs = 1なら正に、s = -1なら負に設定して0を返す(それ以外は-1を返す)
int setSign(struct NUMBER *a, int s) {
    if(s == 1){
        a->sign = 1;
    } else if(s == -1){
        a->sign = -1;
    } else {
        return -1;
    }

    return 0;
}

// aの符号が正なら1を、負なら-1を返す
int getSign(struct NUMBER *a) {
    if(a->sign == 1){ // 正の時
        return 1;
    }
    
    return -1;
}