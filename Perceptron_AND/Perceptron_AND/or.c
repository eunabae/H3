//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#pragma warning(disable : 4996) //scanf ���� ����
//
//#define N 2 //N=2�� ����
//
//float theta; //theta���� ������ 0 ũ�� 1
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
//int or(float w1, float w2) {
//	float n = 0;
//	int count = 4;
//	n = sum(0, 0, w1, w2); //00 �� ��
//	if (func(n) == 0) count--;
//	//printf("X[0]W[0] : %f , X[1]W[1] : %f  net = %f\n", X[0] * W[0], X[1] * W[1], n);
//
//	n = sum(0, 1, w1, w2); //01
//	if (func(n) == 1) count--;
//	//printf("X[0]W[0] : %f , X[1]W[1] : %f  net = %f\n", X[0] * W[0], X[1] * W[1], n);
//
//	n = sum(1, 0, w1, w2);
//	if (func(n) == 1) count--;
//	//printf("X[0]W[0] : %f , X[1]W[1] : %f  net = %f\n", X[0] * W[0], X[1] * W[1], n);
//
//	n = sum(1, 1, w1, w2);
//	if (func(n) == 1) count--;
//	//printf("X[0]W[0] : %f , X[1]W[1] : %f  net = %f\n", X[0] * W[0], X[1] * W[1], n);
//
//	printf("Wrong count = %d\n", count);
//	return count;
//}
//
//int main() {
//	//��������
//	float X[N];
//	float W[N];
//	float n = 0;
//	int count = 4; //out Ʋ������ ī��Ʈ
//	int i = 0;
//
//	srand(time(NULL));
//
//	for (i = 0;i < N;i++) {
//		W[i] = rand() % 10;
//	}
//
//	theta = (rand() % 10);
//	if (theta == 0) theta++; //theta =0�̸� ��� �Ұ�
//	// ���� ���� ���� = 1~9
//	//printf("Theta: %f\n", theta);
//
//	while (1) //or
//	{
//		count = or (W[0], W[1]);
//		if (count == 0) break;
//		else {
//			while (1) {
//				printf("Enter W[N]: ");
//				scanf("%f %f", &W[0], &W[1]);
//				count = or (W[0], W[1]);
//				if (count == 0) break;
//			}
//			break;
//		}
//	}
//}
