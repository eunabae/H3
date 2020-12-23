//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#pragma warning(disable : 4996) //scanf 에러 방지
//
//#define N 2 //N=2로 고정
//
//float theta; //theta보다 작으면 0 크면 1
//
//
//int func(float n) {
//	if (n > theta) return 1;
//	else return 0;
//}
//
//int sum(int x1, int x2, float w1, float w2) {
//	return x1 * w1 + x2 * w2;
//}
//
//int and(int x1, int x2) {
//	if (x1 == 1 && x2 == 1) return 1;
//	else return 0;
//}
//
//int or (int x1, int x2) {
//	if (x1 == 0 && x2 == 0) return 0;
//	else return 1;
//}
//
//int nand (int x1, int x2) {
//	if (x1 == 1 && x2 == 1) return 0;
//	else return 1;
//}
//
//int xor (int x1, int x2) {
//	float s1, s2, s3;
//	s1 = nand(x1, x2);
//	s2 = or (x1, x2);
//	s3 = and (s1, s2);
//	return s3;
//}
//
//int main() {
//	//변수선언
//	float X[N];
//	float W[N];
//	float n = 0;
//	int out[4];
//	int count = 4; //out 틀린갯수 카운트
//	int i = 0;
//
//	srand(time(NULL));
//
//	for (i = 0;i < N;i++) {
//		W[i] = rand() % 10;
//	}
//
//	theta = (rand() % 10);
//	if (theta == 0) theta++; //theta =0이면 모두 불가
//	// 랜덤 설정 범위 = 1~9
//	//printf("Theta: %f\n", theta);
//
//	out[0]=xor (0, 0);
//	out[1] = xor (1, 0);
//	out[2] = xor (0, 1);
//	out[3] = xor (1, 1);
//
//	for (i = 0; i < 4;i++) {
//		printf("%d ",out[i]);
//	}
//
//}
