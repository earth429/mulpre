// 11/15 -2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mulprec.h"

int setInt(struct NUMBER *, int);
void setText(struct NUMBER *, int);
void checkText();
void dispNumberNormal(struct NUMBER *);

int main(int argc, char **argv)
{
    int i;
    srandom(time(NULL));
    struct NUMBER a;
    setInt(&a, -101);
    dispNumberZeroSuppress(&a);
    for (i = 0; i < TRY;i++){
        
        //int x = random();
        // int return_val;

        // return_val = setInt(&a, x);

        // printf("intの値=%d\n多倍長の値=", x);
        // dispNumberNormal(&a);
        // printf("\n戻り値 = %d\n", return_val);
        //setText(&a, x);
    }
    //checkText();
        

    return 0;
}

// 多倍長整数aにint型変数xの値を設定する 戻り値-1:xの値がaに設定しきれなかった
int setInt(struct NUMBER *a, int x) {
    int i;

    clearByZero(a);

    for (i = 0; i < KETA;i++){
        a->n[i] = x % 10;
        x = x / 10;
    }

    if(x > 0){
        setSign(a, 1);
    } else {
        setSign(a, -1);
    }

        /*int i;
    int digit = 1; // xの桁数を調べる
    int remainder; // 余りを格納
    int xsign; //xの符号を格納
    int loop = 10; // ループ回数,10はintの最大数の桁数

    clearByZero(a);

    
    for (int i = x; i >= 10; i /= 10) {
        digit++;
        if(digit > KETA) {
            return -1;
        }
    }

    if(x > 0){
        xsign = 1;
    } else {
        xsign = -1;
    }

    if(loop > KETA){
        loop = KETA;
    }

    for (i = 0; i < loop;i++){
        remainder = x % 10;
        if(remainder < 0){
            remainder = abs(remainder); // xの値が負の値であったときにaには正の値
        }
        a->n[i] = remainder;
        x -= remainder;
        x /= 10;
    }

    a->sign = xsign;
*/
        return 0;
}

// intの値と多倍長の値をtextに書き込む
void setText(struct NUMBER *a, int x) {
    FILE *fp;
    int i;

    if ((fp = fopen("check.txt", "a")) == NULL) {
		printf("ファイルをオープンできません。\n");
	} else {
        // int型変数の書き込み
        fprintf(fp, "%d\t", x);
        // 多倍長変数の書き込み
        for (i = KETA - 1; i >= 0; i--) {
            if(a->n[i] != 0){
                break;
            }

            if(i == 0){
                fprintf(fp, "%d", a->n[i]);
            }
        }
        for (; i >= 0;i--) {
            fprintf(fp, "%d", a->n[i]);
        }
        fprintf(fp, "\n");

        fclose(fp);
    }
}

// setTextで書き込んだ値を比較して正しいかを調べる
void checkText() {
    FILE *fp;
    int i;
    int int_num;
    int mul_num;

    if ((fp = fopen("check.txt", "r")) == NULL) {
		printf("ファイルをオープンできません。\n");
	} else {
        for (i = 0; i < TRY;i++){
            // int型変数の読み込み
            fscanf(fp, "%d", &int_num);
            // 多倍長変数の読み込み
            fscanf(fp, "%d\n", &mul_num);

            printf("int = %d\nmul = %d\n\n", int_num, mul_num);
        }

        fclose(fp);
    }
    
}

// 多倍長変数を通常の表示で表示する
void dispNumberNormal(struct NUMBER *a){
    int i;

    /*if(a->sign == 1){
        printf("+");
    } else {
        printf("-");
    }*/
    for (i = KETA - 1; i >= 0; i--) {
        if(a->n[i] != 0){
            break;
        }

        if(i == 0){
            printf("%d", a->n[i]);
        }
    }
    for (; i >= 0;i--) {
        printf("%d", a->n[i]);
    } 
}

/*void checkNum(struct NUMBER *a, int x) {
    int i, j;
    int mul = 0; // 多倍長変数の値を代入する変数
    int max;

    for (i = 1; i <= KETA;i++){
        max *= 10;
    }

        // 多倍長変数の0からxに足していく,次の桁になるときはかける10した値
        for (i = 1; i < max; i *= 10)
        {
            for (j = 0; j < KETA; j++)
            {
                mul += a->n[j] * i;
            }
        }

    printf("mul=%d\n", mul);
}*/