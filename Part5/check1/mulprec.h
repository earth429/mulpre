// #defineとstructとプロトタイプ宣言を書く

#define KETA 15

struct NUMBER{
    int n[KETA]; // 各桁の値
    int sign; // 符号変数
};

void clearByZero(struct NUMBER *);
void dispNumberZeroSuppress(struct NUMBER *);
void dispNumber(struct NUMBER *);
void setRnd(struct NUMBER *, int);
void copyNumber(struct NUMBER *, struct NUMBER *);
void getAbs(struct NUMBER *, struct NUMBER *);
int isZero(struct NUMBER *);
int mulBy10(struct NUMBER *, struct NUMBER *);
int divBy10(struct NUMBER *, struct NUMBER *);