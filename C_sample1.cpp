#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define X_SIZE 256
#define Y_SIZE 256

#define NUM 79

unsigned char Rin[Y_SIZE][X_SIZE];
unsigned char Gin[Y_SIZE][X_SIZE];
unsigned char Bin[Y_SIZE][X_SIZE];
unsigned char Rout[Y_SIZE][X_SIZE];
unsigned char Gout[Y_SIZE][X_SIZE];
unsigned char Bout[Y_SIZE][X_SIZE];

int main(void){
	extern unsigned char Rin[Y_SIZE][X_SIZE];
	extern unsigned char Gin[Y_SIZE][X_SIZE];
	extern unsigned char Bin[Y_SIZE][X_SIZE];
	extern unsigned char Rout[Y_SIZE][X_SIZE];
	extern unsigned char Gout[Y_SIZE][X_SIZE];
	extern unsigned char Bout[Y_SIZE][X_SIZE];

	int i, j,k;
	int avg;
	int x;
	int n;

	FILE *fp1, *fp2;
	char header[54];

	//入力画像ファイルオープン
	if ((fp1 = fopen("4.1.07.bmp", "rb")) == NULL){
		printf("ファイルをオープンできません。\n");
		return (-1);
	}

	fread(header, 54, 1, fp1);

	//読み込み
	for (i = 0; i < Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			fread(&Bin[i][j], 1, 1, fp1); //Bin[i][j]に1バイトfp1から読み込み
			fread(&Gin[i][j], 1, 1, fp1);
			fread(&Rin[i][j], 1, 1, fp1);
		}
	}

	//ファイルクローズ
	fclose(fp1);


	//画像処理
	for (i = 0; i<Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			avg = (Bin[i][j] + Gin[i][j] + Rin[i][j]) / 3; //モノクロ化
			n = pow((double)2, 2);//色数
			for (k = 0; k < n; k++){
				if (avg >= k * 255 / n && avg < (k + 1) * 255 / n){
					x = 255 * k / (n - 1);
				}
			}

			Bout[i][j] = x;
			Gout[i][j] = x;
			Rout[i][j] = x;
		}
	}

	//出力yuv画像ファイルオープン
	if ((fp2 = fopen("4.1.07processed_2bit.bmp", "wb")) == NULL){
		printf("ファイルをオープンできません。\n");
		return(1);
	}

	//出力画像書き出し
	fwrite(header, sizeof(header), 1, fp2);
	for (i = 0; i < Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			fwrite(&Bout[i][j], 1, 1, fp2);
			fwrite(&Gout[i][j], 1, 1, fp2);
			fwrite(&Rout[i][j], 1, 1, fp2);
		}
	}

	//ファイルクローズ
	fclose(fp2);
}
