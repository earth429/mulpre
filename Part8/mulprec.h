// #defineとstructとプロトタイプ宣言を書く
#ifndef MULPREC_H // インクルードガード
#define MULPREC_H

#define KETA 15
#define TRY 10 // 自動チェック用

struct NUMBER{
    int n[KETA]; // 各桁の値
    int sign; // 符号変数
};

void clearByZero(struct NUMBER *);
void dispNumber(struct NUMBER *);
void dispNumberZeroSuppress(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
int divBy10(struct NUMBER *, struct NUMBER *);
int setInt(struct NUMBER *, int);
void setText(struct NUMBER *, int);
void checkText();
int setSign(struct NUMBER *, int);
int getSign(struct NUMBER *);
int numComp(struct NUMBER *, struct NUMBER *);
int add(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int sub(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int increment(struct NUMBER *, struct NUMBER *);
int decrement(struct NUMBER *, struct NUMBER *);
int multiple(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int divide(struct NUMBER *, struct NUMBER *, struct NUMBER *, struct NUMBER *);
int gcd(struct NUMBER *, struct NUMBER *, struct NUMBER *);

#endif