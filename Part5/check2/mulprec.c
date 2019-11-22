#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

// 多倍長変数の値をゼロクリアし、符号をプラスにセットする
void clearByZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        a->n[i] = 0;
    }

    setSign(a, 1);
}

// aを表示する
void dispNumber(struct NUMBER *a){
    int i;

    if(getSign(a) == 1){
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0;i--){
        printf("%2d", a->n[i]);
    }
}

// aを表示する(ゼロサプレス機能付き)
void dispNumberZeroSuppress(struct NUMBER *a){
    int i;

    if(getSign(a) == 1) {
        printf("+");
    } else {
        printf("-");
    }

    for (i = KETA - 1; i >= 0; i--) {
        if(a->n[i] != 0){
            break;
        }

        if(i == 0){
            printf("%2d", a->n[i]);
        }
    }
    for (; i >= 0;i--) {
        printf("%2d", a->n[i]);
    } 
}

// aの下位k桁に乱数値をセットする
void setRnd(struct NUMBER *a, int k){
    int i;
    int judge;

    clearByZero(a);

    for (i = 0; i < k;i++){
        a->n[i] = random() % 10; // random()%(B-A+1)+A
    }

    judge = random() % 2; // 符号をランダムに決める:1は+,0は-

    switch (judge) {
        case 1:
            setSign(a, 1);
            break;
        case 0:
            setSign(a, -1);
            break;
    }
}

// aをbにコピーする
void copyNumber(struct NUMBER *a, struct NUMBER *b){
    int i;

    clearByZero(b);

    setSign(b, getSign(a));

    for (i = 0; i < KETA;i++){
        b->n[i] = a->n[i];
    }
}

// aの絶対値をbに返す
void getAbs(struct NUMBER *a, struct NUMBER *b){
    copyNumber(a, b);
    setSign(b, 1); // 符号を正に
}

// aがゼロか判別する 0でなかったら戻り値-1 (符号は見ていない)
int isZero(struct NUMBER *a){
    int i;

    for (i = 0; i < KETA;i++){
        if(a->n[i] != 0){
            return -1;
        }
    }

    return 0;
}

// aを10倍にしてbに返す
int mulBy10(struct NUMBER *a, struct NUMBER *b){
    int i;

    clearByZero(b);

    setSign(b, getSign(a)); // 符号の共通化

    // オーバーフローする
    if(a->n[KETA - 1] != 0){
        return -1;
    }

    for (i = KETA - 2; i >= 0;i--){
        b->n[i + 1] = a->n[i];
    }

    b->n[0] = 0;

    return 0;
}

// aを1/10倍にしてbに返す 戻り値:aを10で割った余り
int divBy10(struct NUMBER *a, struct NUMBER *b){
    int i;
    int remainder; // 余りを格納

    clearByZero(b);

    setSign(b, getSign(a)); // 符号の共通化

    remainder = getSign(a) * a->n[0]; // 余りに符号をつける

    for (i = 1; i <= KETA - 2;i++){
        b->n[i - 1] = a->n[i];
    }

    b->n[KETA - 1] = 0;

    return remainder;
}

// 多倍長整数aにint型変数xの値を設定する 戻り値-1:xの値がaに設定しきれなかった
int setInt(struct NUMBER *a, int x) {
    int i;
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

    setSign(a, xsign);

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
            if(getSign(a) != 0){
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

            if(int_num != mul_num){
                printf("値が違います\nint = %d\nmul = %d", int_num, mul_num);
            }
        }
        fclose(fp);
    }
    
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

// 2つの多倍長整数a,bの大小を比較する(戻り値0:a==b,1:a>b,-1:a<b)
int numComp(struct NUMBER *a, struct NUMBER *b) {
    int sa = getSign(a);
    int sb = getSign(b);
    int i;

    if(sa > sb){ // aが正、bが負の時
        return 1;
    }

    if(sa < sb){ // aが負、bが正の時
        return -1;
    }

    if(sa == 1 && sb == 1){ // aが正、bが負の時
        for (i = KETA - 1; i >= 0;i--){
            if(a->n[i] > b->n[i]){ // aに大きい値があった
                return 1;
            } else if(a->n[i] < b->n[i]){
                return -1;
            }
        }

        return 0; // a==b
    }

    if(sa == -1 && sb == -1){ // aが負、bが負の時
        for (i = KETA - 1; i >= 0;i--){
            if(a->n[i] > b->n[i]){ // aに大きい値があった=a<b
                return -1;
            } else if(a->n[i] < b->n[i]){
                return 1;
            }
        }

        return 0; // a==b
    }

    // それ以外
    return 100;
}

// c = a + b (オーバーフローが起きた場合戻り値-1)
int add(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int d; // 作業用変数
    int e = 0; // 繰り上がりの値
    int i;
    struct NUMBER a_abs, b_abs; // aとbの絶対値を格納

    clearByZero(c);

    printf("あどどど");

    if(getSign(a) > 0 && getSign(b) > 0){ // c = a + b
    dispNumberZeroSuppress(a);
    dispNumberZeroSuppress(b);
        for (i = 0; i < KETA;i++){
            d = a->n[i] + b->n[i] + e;
            c->n[i] = d % 10;
            e = (d - c->n[i]) / 10; // eはdの10の位の値
            dispNumberZeroSuppress(c);
            printf("\n");
        }

        if(e != 0){ // オーバーフロー
            return -1;
        }

    } else if(getSign(a) > 0 && getSign(b) < 0){ // c = a - |b|
        getAbs(b, &b_abs);
        sub(a, &b_abs, c);
        puts("addinu");
    } else if(getSign(a) < 0 && getSign(b) > 0){ // c = b - |a|
        getAbs(a, &a_abs);
        sub(b, &a_abs, c);
        puts("addneko");
    } else if(getSign(a) < 0 && getSign(b) < 0){ // // c = -(|a| + |b|)
        getAbs(a, &a_abs);
        getAbs(b, &b_abs);
        add(&a_abs, &b_abs, c);
        setSign(c, -1);
        puts("addsita");
    }

    return 0;
}

// c = a - b (オーバーフローが起きた場合戻り値-1)
int sub(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c) {
    int h = 0;
    int i;
    int return_val;
    int x, y; // 計算時一時的にaとbの値を入れておく
    struct NUMBER a_abs, b_abs; // aとbの絶対値を格納

    clearByZero(c);

    if(getSign(a) > 0 && getSign(b) > 0){ // c = a - b
        return_val = numComp(a, b); // aとbの大小比較

        switch (return_val)
        {
        case 1: // a>b
            for (i = 0; i < KETA;i++){
                x = a->n[i] - h;
                y = b->n[i];
                if(a->n[i] < b->n[i]){
                    c->n[i] = 10 + x - y;
                    h = 1; // 桁借りをした
                } else if(a->n[i] >= b->n[i]){
                    c->n[i] = x - y;
                    h = 0; // 桁借りをしていない
                }
            }

            if(h != 0){ // オーバーフローする(基本起こらないけど)
                return -1;
            }
            return 0; // 正常に計算できた
        case -1: // a<b
            sub(b, a, c);
            setSign(c, -1);
            return 0;
        case 0: // a==b
            return 0;
        }
    } else if(getSign(a) > 0 && getSign(b) < 0){ // c = a + |b|
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
    } else if(getSign(a) < 0 && getSign(b) > 0){ // c = -(|a| + b)
        getAbs(a, &a_abs);
        add(&a_abs, b, c);
        setSign(c, -1);
    } else if(getSign(a) < 0 && getSign(b) < 0){ // // c = |b| - |a| = a + |b|
        getAbs(b, &b_abs);
        add(a, &b_abs, c);
    }

    return 100; // それ以外
}