#define _CRT_SECURE_NO_WARNINGS    // fopen ���� ���� ���� ������ ���� ����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define inputsize 4 //�� �Է�Ƚ�� - 4 (00 / 10 / 01 /11)
#define layernode 2 //���� ���̾��� ����
#define layer 1 //���� ���̾� ��

FILE *fp; //���� ����

//����� ����� ���� ������ ����ġ, ���̾���� ������ �迭
float tmpw[2] = { 0 };
float tmphw[2][2] = { 0 };
float tmpbias = 0;
float tmphbias[2] = { 0 };


float w[layernode] = { 0 };
float bias;

float hw[2][layernode] = { 0 };
float hbias[layernode] = { 0 };

float hout[inputsize][layernode] = { 0 };
float hnet[inputsize][layernode] = { 0 };
float outnet[inputsize] = { 0 };

float out[inputsize] = { 0,1,1,0 };

//Ȱ�� �Լ� - �ñ׸��̵� ���
float sig(float x) {
	return 1 / (1 + exp(-x));
}

float dsig(float x) {
	return sig(x)*(1 - sig(x));
}


//Ȱ���Լ��� ����� net ���
float compute(float x[][layernode], int row) {
	int i = 0;
	float wx = 0.0;
	for (i = 0; i < layernode;i++) {
		wx += x[row][i] * w[i];
	//	printf("wx +=  %lf * %lf = %lf      \n ",x[row][i], w[i], wx);
	}
	outnet[i] = wx + bias;
	//	printf("net = %lf \n", outnet[i]);
	return sig(bias + wx);
	//out ���
}

float hcompute(float x[][layernode], int row, int node) {
	int i = 0;
	float wx = 0.0;
	for (i = 0; i < layernode;i++) {
		wx += x[row][i] * hw[i][node];
	}
	hnet[row][node] = wx + hbias[node];

	return sig(hbias[node] + wx);
	//out ���
}


//�н� - ����ġ ������Ʈ

void train(float c, float x[][layernode]) {
	int i = 0, j = 0, k=0, l=0;
	float delta = 0, delta1 = 0;
	float deltabar = 0, deltabar1 = 0;
	float beforeW[2];
	float t = 0, o = 0;
	float error = 0;
	float u = 0.5;

	for (j = 0; j < inputsize; j++) { //�� �Է¿� ���ؼ�
		for (l = 0; l < layer;l++) { //���̾� ����ŭ
			for (i = 0;i < 2;i++) { // ��� ����ŭ
				hout[j][i] = hcompute(x, j, i);
			}
		}
		o = compute(hout, j);
		t = out[j];
		error += pow((t - o), 2.0);
		//forward - out���

		beforeW[0] = w[0]; //forward�� ���� ������ ���� - ������Ʈ ���� ����ġ
		beforeW[1] = w[1];

		deltabar = -(t - o); //��Ÿ�� ���
		delta = deltabar * dsig(outnet[j]); //��Ÿ�ٸ� �̿��� ��Ÿ ���

		if(fabs(t-o)>0.01){ //��ǥ������ ���̰� 0.01���� ũ�� ����ġ �н�
		for (i = 0;i < layernode;i++) {
			w[i] -= c * delta*hout[j][i]+u*tmpw[i]; // ����һ��
			tmpw[i] = -c * delta*hout[j][i]; //����ġ ��ȭ���� ����
		}
		bias -= c * delta + u*tmpbias;
		tmpbias = -c * delta;

// ���� ���� ������� ���緹�̾��� ����ġ ������Ʈ
// ��Ÿ�� ������Ʈ�� ������ ��Ÿ ���


		for (l = 0; l < layer; l++) {
			for (i = 0;i < 2;i++) {
				deltabar1 = delta * beforeW[i];
				delta1 = deltabar1 * dsig(hnet[j][i]);
				for (k = 0; k < layernode;k++) {
					hw[k][i] -= c * delta1* x[j][k] + u * tmphw[k][i];
					tmphw[k][i] = -c * delta1* x[j][k];
				}
				hbias[i] -= c * delta1 * u*tmphbias[i];
				tmphbias[i] = -c * delta1;
			}
		}
		}
	}
//�� �Է¿� ���� �н��� ������  ���Ͽ� ���ڿ� ���� - �н� ���� ���ο� ��� ���� ����ġ ���
	fprintf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
		hw[0][0], hw[1][0], hw[0][1], hw[1][1], hbias[0], hbias[1], w[0], w[1], bias, error/2);

}

void reset() {
	int i = 0, j = 0;
	srand(time(NULL));

	for (i = 0;i < layernode;i++) {
		for (j = 0;j < 2; j++) {
			hw[i][j] = (float)rand() / (RAND_MAX + 1);
			printf("hw[%d][%d]= %lf\n", i,j, hw[i][j]);
			//printf("hw1[%d]= %lf  hw2[%d]= %lf \n", i, hw1[i], i, hw2[i]);
		}
		w[i] = (float)rand() / (RAND_MAX + 1);
		hbias[i] = -1;
		printf("w[%d]= %lf\n", i, w[i]);
	} // �ʱ� ����ġ�� ����
	bias = -1; //�ʱ� ������ = -1
}

int main() {
	int i = 0, j = 0;
	float input[inputsize][2] = //4�� 2��
	{
		{0,0},
		{1,0},
		{0,1},
		{1,1},
	};
	fp = fopen("xor.txt", "w");

	reset(); //�ʱ�ȭ

	for (i = 0;i < 7000;i++)
		train(1.0, input);
	
	for (i = 0; i < 2; i++) {
		hcompute(input, 0, i);
		hcompute(input, 1, i);
		hcompute(input, 2, i);
		hcompute(input, 3, i);
	}

	printf("\n after train\n");
	printf("test1: %lf \n\n", compute(hout, 0)); //00
	printf("test2: %lf \n\n", compute(hout, 1)); //10
	printf("test3: %lf \n\n", compute(hout, 2)); //01
	printf("test4: %lf \n\n", compute(hout, 3)); //11

	fclose(fp);
}
