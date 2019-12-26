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

	//���͉摜�t�@�C���I�[�v��
	if ((fp1 = fopen("4.1.07.bmp", "rb")) == NULL){
		printf("�t�@�C�����I�[�v���ł��܂���B\n");
		return (-1);
	}

	fread(header, 54, 1, fp1);

	//�ǂݍ���
	for (i = 0; i < Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			fread(&Bin[i][j], 1, 1, fp1); //Bin[i][j]��1�o�C�gfp1����ǂݍ���
			fread(&Gin[i][j], 1, 1, fp1);
			fread(&Rin[i][j], 1, 1, fp1);
		}
	}

	//�t�@�C���N���[�Y
	fclose(fp1);


	//�摜����
	for (i = 0; i<Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			avg = (Bin[i][j] + Gin[i][j] + Rin[i][j]) / 3; //���m�N����
			n = pow((double)2, 2);//�F��
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

	//�o��yuv�摜�t�@�C���I�[�v��
	if ((fp2 = fopen("4.1.07processed_2bit.bmp", "wb")) == NULL){
		printf("�t�@�C�����I�[�v���ł��܂���B\n");
		return(1);
	}

	//�o�͉摜�����o��
	fwrite(header, sizeof(header), 1, fp2);
	for (i = 0; i < Y_SIZE; i++){
		for (j = 0; j < X_SIZE; j++){
			fwrite(&Bout[i][j], 1, 1, fp2);
			fwrite(&Gout[i][j], 1, 1, fp2);
			fwrite(&Rout[i][j], 1, 1, fp2);
		}
	}

	//�t�@�C���N���[�Y
	fclose(fp2);
}