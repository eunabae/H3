//#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//
//#define inputsize 9 
//#define layernode 2
//#define layer 1
//
//FILE *fp;
//
////모멘텀 사용을 위해 이전의 가중치, 바이어스들을 저장할 배열
//float tmpw[2] = { 0 };
//float tmphw[2][2] = { 0 };
//float tmpbias = 0;
//float tmphbias[2] = { 0 };
//float w[layernode] = { 0 };
//float bias;
//
//float hw[2][layernode] = { 0 };
//float hbias[layernode] = { 0 };
//
//float hout[inputsize][layernode] = { 0 };
//float hnet[inputsize][layernode] = { 0 };
//float outnet[inputsize] = { 0 };
//
//float out[inputsize] = {0,0,0,0,0,0,0,0,1} ;
//
////활성 함수 - 시그모이드 사용
//float sig(float x) {
//	return 1 / (1 + exp(-x));
//}
//
//float dsig(float x) {
//	return sig(x)*(1 - sig(x));
//}
//
////활성함수에 사용할 net 계산
//float compute(float x[][layernode], int row) {
//	int i = 0;
//	float wx = 0.0;
//	for (i = 0; i < layernode;i++) {
//		wx += x[row][i] * w[i];
//		//	printf("wx +=  %lf * %lf = %lf      \n ",x[row][i], w[i], wx);
//	}
//	outnet[i] = wx + bias;
//	//	printf("net = %lf \n", outnet[i]);
//	return sig(bias + wx);
//	//out 계산
//}
//
//float hcompute(float x[][layernode], int row, int node) {
//	int i = 0;
//	float wx = 0.0;
//	for (i = 0; i < layernode;i++) {
//		wx += x[row][i] * hw[i][node];
//	}
//	hnet[row][node] = wx + hbias[node];
//
//	return sig(hbias[node] + wx);
//	//out 계산
//}
//
//
////학습 - 가중치 업데이트
//void train(float c, float x[][layernode]) {
//	int i = 0, j = 0, k = 0, l = 0;
//	float delta = 0, delta1 = 0, delta2 = 0;
//	float deltabar = 0, deltabar1 = 0, deltabar2 = 0;
//	float t = 0, o = 0;
//	float error = 0;
//	float u = 0.5;
//
//	for (j = 0; j < inputsize; j++) { //각 입력에 대해서
//		for (l = 0; l < layer;l++) { //레이어 수만큼
//			for (i = 0;i < 2;i++) { // 노드 수만큼
//				hout[j][i] = hcompute(x, j, i);
//			}
//		}
//		o = compute(hout, j);
//		t = out[j];
//		error += pow((t - o), 2.0);
//		//forward - out계산
//
//		deltabar = -(t - o); //델타 바 계산
//		delta = deltabar * dsig(outnet[j]); //델타바를 이용해 델타 계산
//
//		if (fabs(t - o) > 0.01) { //목표값과의 차이가 0.01보다 크면 학습
//			for (i = 0;i < layernode;i++) {
//				w[i] -= c * delta*hout[j][i] + u * tmpw[i]; //모멘텀사용
//				tmpw[i] = -c * delta*hout[j][i]; // 가중치 변화량을 저장
//			}
//			bias -= c * delta + u * tmpbias;
//			tmpbias = -c * delta;
//
//
//// 위와 동일 방식으로 히든레이어의 가중치 업데이트
//// 델타바 업데이트에 이전의 델타 사용
//
//			for (l = 0; l < layer; l++) {
//				for (i = 0;i < 2;i++) {
//					deltabar1 = delta * w[i];
//					delta1 = deltabar1 * dsig(hnet[j][i]);
//					for (k = 0; k < layernode;k++) {
//						hw[k][i] -= c * delta1* x[j][k] + u * tmphw[k][i];
//						tmphw[k][i] = -c * delta1* x[j][k];
//					}
//					hbias[i] -= c * delta1 * u*tmphbias[i];
//					tmphbias[i] = -c * delta1;
//				}
//			}
//		}
//	}
////각 입력에 대한 학습이 끝나면  파일에 문자열 저장 - 학습 진행 여부와 상관 없이 가중치 업데이트
//	fprintf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
//		hw[0][0], hw[1][0], hw[0][1], hw[1][1], hbias[0], hbias[1], w[0], w[1], bias, error/2);
//
//}
//
//void reset() {
//	int i = 0, j = 0;
//	srand(time(NULL));
//
//	for (i = 0;i < layernode;i++) {
//		for (j = 0;j < 2; j++) {
//			hw[i][j] = (float)rand() / (RAND_MAX + 1);
//			printf("hw[%d][%d]= %lf\n", i, j, hw[i][j]);
//			//printf("hw1[%d]= %lf  hw2[%d]= %lf \n", i, hw1[i], i, hw2[i]);
//		}
//		w[i] = (float)rand() / (RAND_MAX + 1);
//		hbias[i] = -1;
//		printf("w[%d]= %lf\n", i, w[i]);
//	} // 초기 가중치는 랜덤
//	bias = -1; //초기 조정값 = -1
//}
//
//int main() {
//	int i = 0, j = 0;
//	float input[inputsize][2] = { 
//	 {0.0,0.0},
//	 {0.0,1.0},
//	 {1.0,0.0},
//	 {1.0,1.0},
//	 {0.5,1.0},
//	 {1.0,0.5},
//	 {0.0,0.5},
//	 {0.5,0.0},
//	 {0.5,0.5} };
//
//	fp = fopen("doughnut.txt", "w");
//
//	reset(); //초기화
//
//	for (i = 0;i < 7000;i++)
//		train(1.0, input);
//
//	for (i = 0; i < 2; i++) {
//		hcompute(input, 0, i);
//		hcompute(input, 1, i);
//		hcompute(input, 2, i);
//		hcompute(input, 3, i);
//		hcompute(input, 4, i);
//		hcompute(input, 5, i);
//		hcompute(input, 6, i);
//		hcompute(input, 7, i);
//		hcompute(input, 8, i);
//	}
//
//	printf("\n after train\n");
//	printf("test1: %lf \n\n", compute(hout, 0)); 
//	printf("test2: %lf \n\n", compute(hout, 1)); 
//	printf("test3: %lf \n\n", compute(hout, 2)); 
//	printf("test4: %lf \n\n", compute(hout, 3)); 
//	printf("test5: %lf \n\n", compute(hout, 4));
//	printf("test6: %lf \n\n", compute(hout, 5));
//	printf("test7: %lf \n\n", compute(hout, 6));
//	printf("test8: %lf \n\n", compute(hout, 7));
//	printf("test9: %lf \n\n", compute(hout, 8));
//
//	fclose(fp);
//}
