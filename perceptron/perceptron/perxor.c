#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define inputLayerNeurons 2
#define hiddenLayerNeurons 2
#define outputLayerNeurons 1

FILE *fp;

double predicted_output[4][1] = { 0 };
double hidden_layer_output[4][2] = { 0 };
double d_predicted_output[4][1] = { 0 };
double d_hidden_layer[4][2] = { 0 };
double error[4][1] = { 0 };
double error_hidden_layer[4][2] = { 0 };
double hidden_layer_activation[4][2] = { 0 };
double output_layer_activation[4][1] = { 0 };
double sum = 0;
double hsum[2] = { 0 };
double thidden_layer_output[2][4] = { 0 };
int tinputs[2][4] = { 0 };
double tW[1][2] = { 0 };
double c = 0.1;


int inputs[4][2] = //4행 2열
{
	{0,0},
	{1,0},
	{0,1},
	{1,1},
};
int expected_output[4][1] = { {0},{1},{1},{0} };

double hW[inputLayerNeurons][hiddenLayerNeurons] = { 0 };  //22
double hBias[1][hiddenLayerNeurons] = { 0 };  //12
double W[hiddenLayerNeurons][outputLayerNeurons] = { 0 }; //21
double Bias[1][1] = { 0 };  //11
//선언


double sig(double x) {
	return 1 / (1 + exp(-x));
}

double dsig(double x) {
	return sig(x)*(1 - sig(x));
}

void Reset() {
	int i = 0, j = 0;
	srand(time(NULL));

	for (i = 0;i < inputLayerNeurons;i++) {
		for (j = 0;j < hiddenLayerNeurons;j++) {
			hW[i][j] = (double)rand() / (RAND_MAX + 1);
			printf("hW[%d][%d]= %lf\n", i, j, hW[i][j]);
		}
		W[i][0] = (double)rand() / (RAND_MAX + 1);
		printf("W[%d][0]= %lf\n", i, W[i][0]);

		hBias[0][i] = -1; //초기 조정값 = -1
		Bias[0][0] = -1;
	}// 초기 가중치는 랜덤
}

void forward() {
	int i = 0, j = 0, k = 0;

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			for (k = 0;k < 2;k++) {
				hidden_layer_activation[i][j] += inputs[i][k] * hW[k][j];
			}
			//			printf("hidden layer act[%d][%d] = %lf\n", i, j, hidden_layer_activation[i][j]);
		}
	}

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			hidden_layer_activation[i][j] += hBias[0][j];
			//			printf("hidden layer act[%d][%d] = %lf\n", i, j, hidden_layer_activation[i][j]);
		}
	}

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			hidden_layer_output[i][j] = sig(hidden_layer_activation[i][j]);
			//			printf("hidden layer out[%d][%d] = %lf\n", i, j, hidden_layer_output[i][j]);
		}
	}

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			output_layer_activation[i][0] += hidden_layer_activation[i][j] * W[j][0];
			//			printf("out layer act[%d][%d] = %lf\n", i, j, output_layer_activation[i]);
		}
	}

	for (i = 0;i < 4;i++) {
		output_layer_activation[i][0] += Bias[0][0];
		//		printf("out layer act[%d][%d] = %lf\n", i, j, output_layer_activation[i]);
	}

	for (i = 0;i < 4;i++) {
		predicted_output[i][0] = sig(output_layer_activation[i][0]);
		//		printf("predicted ouput[%d] = %lf\n", i, predicted_output[i]);
	}

}

void backpro() {
	//back
	int i = 0, j = 0, k = 0;
	for (i = 0;i < 4;i++) {
		error[i][0] = expected_output[i][0] - predicted_output[i][0];
		//		printf("err[%d] = %lf\n", i, error[i]);
	}

	for (i = 0; i < 4; i++) {
		d_predicted_output[i][0] = error[i][0] * dsig(predicted_output[i][0]);
		//		printf("d_pre_out[%d] = %lf\n", i,predicted_output[i]);

	}

	for (i = 0;i < 2;i++) {
		tW[0][i] = W[i][0];
	}

	for (i = 0; i < 4; i++) {
		for (j = 0;j < 2;j++) {
			error_hidden_layer[i][j] = d_predicted_output[i][0] * tW[0][j];
			//			printf("err_hidden_layer[%d][%d] = %lf\n", i,j, error_hidden_layer[i][j]);
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0;j < 2;j++) {
			d_hidden_layer[i][j] = error_hidden_layer[i][j] * dsig(hidden_layer_output[i][j]);
			//			printf("d_hidden_layer[%d][%d] = %lf\n", i, j, d_hidden_layer[i][j]);
		}
	}
}

void update() {
	int i, j, k;

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			thidden_layer_output[j][i] = hidden_layer_output[i][j];
			//			printf("d_hidden_layer[%d][%d] = %lf\n", j, i, thidden_layer_output[j][i]);
		}
	}

	for (i = 0; i < 2; i++) {
		for (j = 0;j < 4;j++) {
			W[i][0] += thidden_layer_output[i][j] * d_predicted_output[j][0];
		}
		W[i][0] += W[i][0] * c;
		//		printf("W[%d] = %lf\n", i,W[i]);
	}

	for (i = 0;i < 4;i++) {
		sum += d_predicted_output[i][0];
	}
	Bias[0][0] += sum * c;
	//	printf("Bias= %lf\n",Bias);

	for (i = 0;i < 4;i++) {
		for (j = 0;j < 2;j++) {
			tinputs[j][i] = inputs[i][j];
		}
	}

	for (i = 0;i < 2;i++) {
		for (j = 0;j < 2;j++) {
			for (k = 0;k < 4;k++) {
				hW[i][j] += tinputs[i][k] * d_hidden_layer[k][j];
			}
			hW[i][j] += hW[i][j] * c;
			//			printf("hW[%d][%d] = %lf\n", i, j, hW[i][j]);
		}
	}

	for (i = 0;i < 2;i++) {
		for (j = 0;j < 4;j++) {
			hsum[i] += d_hidden_layer[j][i];
		}
		//		printf("hsum[%d] = %lf\n", i, hsum[i]);
	}

	for (i = 0;i < 2;i++) {
		hBias[0][i] += hsum[i] * c;
		//		printf("hBias[%d] = %lf\n", i, hBias[i]);
	}
}

int main() {
	int i = 0, j = 0, k = 0;

	fp = fopen("xor.txt", "w");

	Reset(); //xor에 사용되는 가중치 = 6개

	forward();
	printf("\nBefore Train\n");
	printf("test1: %lf \n", predicted_output[0][0]); //00
	printf("test2: %lf \n", predicted_output[1][0]); //10
	printf("test3: %lf \n", predicted_output[2][0]); //01
	printf("test4: %lf \n", predicted_output[3][0]); //11



	for (i = 0;i < 400;i++) {
		forward();
		backpro();
		update();
	}
	printf("\nAfer Train\n");
	printf("test1: %lf \n", predicted_output[0][0]); //00
	printf("test2: %lf \n", predicted_output[1][0]); //10
	printf("test3: %lf \n", predicted_output[2][0]); //01
	printf("test4: %lf \n", predicted_output[3][0]); //11


	fclose(fp);
}


