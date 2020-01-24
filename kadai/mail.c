#include <stdio.h>
#include <stdlib.h>

void WrightMail() //メールの本文作成関数
{
	FILE *outputfile;         // 出力ストリーム
  
	outputfile = fopen("MailBody.txt", "w");  // ファイルを書き込み用にオープン(開く)
	if (outputfile == NULL) {          // オープンに失敗した場合
		printf("cannot open\n");         // エラーメッセージを出して
		exit(1);                         // 異常終了
	}

	fprintf(outputfile, "自動送信メール\n"); // ファイルに書く
	fprintf(outputfile, "プログラムが終了しました\n");
	fclose(outputfile);          // ファイルをクローズ(閉じる)
}

void SendMail(char Title[], char BodyText[], char Address[]) //メール送信関数
{
	int ret=0;//結果収納
	char buf[256];

	printf("メール送信処理開始!\n");
	sprintf(buf,"C:\\smail\\smail-v4.21\\smail.exe  -s%s -F%s %s",Title,BodyText,Address);
	printf("\n%s\n",buf);

	ret = system(buf);

	if (ret == 0) printf("送信成功\n");
	else printf("送信失敗\n");
}  	

int main()
{
	 WrightMail();	//メール本文の作成
	 SendMail("test","MailBody.txt","17429@g.nagano-nct.ac.jp"); 
			//タイトル・本文ファイル(.txt)・宛先
	return 0;
}