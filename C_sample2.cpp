#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define X_SIZE 256
#define Y_SIZE 256

#define NUM 79

unsigned char Rin[Y_SIZE][X_SIZE];
unsigned char Gin[Y_SIZE][X_SIZE];
unsigned char Bin[Y_SIZE][X_SIZE];
unsigned char Yout[Y_SIZE][X_SIZE];
unsigned char Uout[Y_SIZE][X_SIZE];
unsigned char Vout[Y_SIZE][X_SIZE];

int main(void){
	extern unsigned char Rin[Y_SIZE][X_SIZE];
	extern unsigned char Gin[Y_SIZE][X_SIZE];
	extern unsigned char Bin[Y_SIZE][X_SIZE];
	extern unsigned char Yout[Y_SIZE][X_SIZE];
	extern unsigned char Uout[Y_SIZE][X_SIZE];
	extern unsigned char Vout[Y_SIZE][X_SIZE];

	int i, j;
	double Y, Pb, Pr;

	FILE *fp1, *fp2;
	errno_t error;

	char header[54];

	//入力画像ファイルオープン
	if ((error = fopen_s(&fp1, "4.1.07.bmp", "rb")) != 0){
		printf("ファイルをオープンできません。\n");
		return (-1);
	}

	fread(header, sizeof(header), 1, fp1);

	//読み込み
	for (i = Y_SIZE - 1; i > -1; i--){
		for (j = 0; j < X_SIZE; j++){
			Bin[i][j] = fgetc(fp1);
			Gin[i][j] = fgetc(fp1);
			Rin[i][j] = fgetc(fp1);
		}
	}

	//ファイルクローズ
	fclose(fp1);


	//画像処理
	for (i = 0; i<Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			Y = 0.2126*(double)Rin[i][j] + 0.7152*(double)Gin[i][j] + 0.0722*(double)Bin[i][j]; 
			if (Y > 255) Yout[i][j] = 255;			//～255白とび
			else if (Y <0) Yout[i][j] = 0;			//～0黒とび
			else Yout[i][j] = (unsigned char)Y;		//代入

			Pb = 0.5389*((double)Bin[i][j] - (double)Yout[i][j]) + 128; 
			if (Pb> 255) Uout[i][j] = 255;			//255～白とび
			else if (Pb <0) Uout[i][j] = 0;			//～0黒とび
			else Uout[i][j] = (unsigned char)Pb;	//代入

			Pr = 0.6250*((double)Rin[i][j] - (double)Yout[i][j]) + 128;	//-128～127から0～255に
			if (Pr> 255) Vout[i][j] = 255;			//255～白とび
			else if (Pr <0) Vout[i][j] = 0;			//～0黒とび
			else Vout[i][j] = (unsigned char)Pr;	//代入
		}
	}

	//出力yuv画像ファイルオープン
	if ((error = fopen_s(&fp2, "4.1.07processed_YUV444.bmp", "wb")) != 0){
		printf("ファイルをオープンできません。\n");
		return(1);
	}

	//出力画像書き出し
	fwrite(header, sizeof(header), 1, fp2);
	for (i = 0; i < Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			fputc(Yout[i][j], fp2);
			fputc(Uout[i][j], fp2);
			fputc(Vout[i][j], fp2);
		}
	}

	//ファイルクローズ
	fclose(fp2);
	return 0;
}
