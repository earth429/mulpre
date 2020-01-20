// 12/17 -2

#include <stdio.h>
#include <math.h>

double newton(double);
double f(double);
double fdash(double);

int main(int argc, char *argv)
{
    double x;
    double x0;
    int i;

    for (i = -5; i <= 5;i++){
        x0 = (double)i;
        x = newton(x0);
        printf("x0 = %10.6lf, x = %10.6lf\n", x0, x); // 初期値x0と解x
        printf("f(x) = %10.6lf\n", f(x));
    }

    return 0;
}

// Newton-Raphson法で f(x) = 0 を解く (x0 = 初期値)
double newton(double x0) {
    double x; // 現在の近似値
    double b; // 一つ前のx
    double e; // 収束判定用

    e = 1.e-7;
    x = x0;
    b = x0;

    while(1){
        b = x; // 一つ前のx
        x = b - (f(b) / fdash(b));
        printf("now x = %10.6lf\n", x);

        if(fabs(x - b) < e){ // 収束
            break;
        }
    }

    return x;
}

// f(x)
double f(double x) {
    return (x * x + 4 * x + 5);
}

// f'(x)
double fdash(double x) {
    return (2 * x + 4);
}