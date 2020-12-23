#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable : 4996) //scanf 에러 방지

#define N 2 //N=2로 고정

float theta; 
float W[N];

float xW[4];  //Xor에서 사용될 가중치

int func(float n) { //theta보다 작으면 0 크면 1
	if (n < theta) return 0;
	else return 1;
}

int nandfunc(float n) { //nand = and 가중치의 음수, 세타도 음수
	if (n < -theta) return 0; //임계값의 음수 = nand의 임계값 > 임계값보다 크면 1
	else return 1;
}

int sum(int x1, int x2, float w1, float w2) {
	return x1 * w1 + x2 * w2;  //net계산
}

float add(int x1, int x2, int t, int out) { //가중치 조절
	float learn = 0.5;
	W[0] = W[0] + (learn*x1)*(t - out);  //t = 희망 값 , out = 실제 값
	W[1] = W[1] + (learn*x2)*(t - out);
}

float nand_add(int x1, int x2, int t, int out) { //nand 가중치 조절
	float learn = 0.5;
	xW[0] = xW[0] + (learn*x1)*(t - out);
	xW[1] = xW[1] + (learn*x2)*(t - out);
}

float or_add(int x1, int x2, int t, int out) { //or 가중치 조절
	float learn = 0.5;
	xW[2] = xW[2] + (learn*x1)*(t - out);
	xW[3] = xW[3] + (learn*x2)*(t - out);
}


int and() {
	float n = 0;
	int out;
	int count = 4;
	n = sum(0, 0, W[0],W[1]); //00 일 때
	out = func(n);
	if (out == 0) count--;
	else add(0, 0, 0, out);

	n = sum(0, 1, W[0],W[1]); //01일때
	out = func(n);
	if (out == 0) count--;
	else add(0, 1, 0, out);

	n = sum(1, 0, W[0],W[1]); //10일때
	out = func(n);
	if (out == 0) count--;
	else add(1, 0, 0, out);

	n = sum(1, 1, W[0],W[1]); //11일때
	out = func(n);
	if (out == 1) count--;
	else add(1, 1, 1, out);
	
	return count;
}

int or() {
	float n = 0;
	int out;
	int count = 4;
	n = sum(0, 0, W[0], W[1]); //00 일 때
	out = func(n);
	if (out == 0) count--;
	else add(0, 0, 0, out);

	n = sum(0, 1, W[0], W[1]); //01일때
	out = func(n);
	if (out == 1) count--;
	else add(0, 1, 1, out);

	n = sum(1, 0, W[0], W[1]); //10일때
	out = func(n);
	if (out == 1) count--;
	else add(1, 0, 1, out);

	n = sum(1, 1, W[0], W[1]); //11일때
	out = func(n);
	if (out == 1) count--;
	else add(1, 1, 1, out);

	return count;
}

int x_or() { //xor에 사용할 or 계산
	float n = 0;
	int out;
	int count = 4;
	n = sum(0, 0, xW[2], xW[3]); //00 일 때
	out = func(n);
	if (out == 0) count--;
	else or_add(0, 0, 0, out);

	n = sum(0, 1, xW[2], xW[3]);//01일때
	out = func(n);
	if (out == 1) count--;
	else or_add(0, 1, 1, out);

	n = sum(1, 0, xW[2], xW[3]);//10일때
	out = func(n);
	if (out == 1) count--;
	else or_add(1, 0, 1, out);

	n = sum(1, 1, xW[2], xW[3]);//11일때
	out = func(n);
	if (out == 1) count--;
	else or_add(1, 1, 1, out);

	return count;
}

int x_nand() { //xor에 사용할 nand 계산
	float n = 0;
	int out;
	int xout;
	int count = 4;
	n = sum(0, 0, xW[0],xW[1]); //00 일 때
	out = func(n);
	if (out == 0) count--;
	else nand_add(0, 0, 0, out);


	n = sum(0, 1, xW[0], xW[1]); //01일때
	out = func(n);
	if (out == 0) count--;
	else nand_add(0, 1, 0, out);

	n = sum(1, 0, xW[0], xW[1]); //10일때
	out = func(n);
	if (out == 0) count--;
	else nand_add(1, 0, 0, out);

	n = sum(1, 1, xW[0], xW[1]); //11일때
	out = func(n);
	if (out == 1) count--;
	else nand_add(1, 1, 1, out);

	return count;

	//nand는 and 성립시키는 임계값, 가중치의 음수
}

int xor() { //xor = (nand)and(or)
	int out, out1, out2, xout;
	int count = 4;
	float n = 0;
	float s1, s2;

	//00 일 때
	s1 = sum(0, 0, -xW[0], -xW[1]); //and 가중치의 음수로 계산
	out1 = nandfunc(s1);  //음수 가중치로 계산
	s2 = sum(0, 0, xW[2], xW[3]);
	out2 = func(s2);

	n = sum(out1, out2, W[0], W[1]);
	out = func(n);
	if (out == 0) count--;
	//else add(out1, out2, 0, out);
	printf("0 0 => %d %d => %d\n", out1, out2, out);


	//01일때
	s1 = sum(0, 1, -xW[0], -xW[1]);
	out1 = nandfunc(s1);
	s2 = sum(0, 1, xW[2], xW[3]);
	out2 = func(s2);
	
	n = sum(out1, out2, W[0], W[1]);
	out = func(n);
	if (out == 1) count--;
	//else add(out1, out2, 1, out);
	printf("0 1 => %d %d => %d\n", out1, out2, out);

	//10일때
	s1 = sum(1, 0, -xW[0], -xW[1]);
	out1 = nandfunc(s1);
	s2 = sum(1, 0, xW[2], xW[3]);
	out2 = func(s2);
	
	n = sum(out1, out2, W[0], W[1]);
	out = func(n);
	if (out == 1) count--;
	//else add(out1, out2, 1, out);
	printf("1 0 => %d %d => %d\n", out1, out2, out);
	
	//11일때
	s1 = sum(1, 1, -xW[0], -xW[1]);
	if (s1 == -theta) s1 = s1 - 0.1; //값이 같은 경우 문제 발생->해결

	out1 = nandfunc(s1);
	s2 = sum(1, 1, xW[2], xW[3]);
	out2 = func(s2);
	
	n = sum(out1, out2, W[0], W[1]);
	out = func(n);
	if (out == 0) count--;
	//else add(out1, out2, 0, out);
	printf("1 1 => %d %d => %d\n", out1, out2, out);

	return count;
}

int main (){
	//변수선언
	float n=0;
	int count = 4; //out 틀린갯수 카운트
	int i = 0;

	srand(time(NULL));

	for (i = 0;i < N;i++) {
		W[i] = rand()%10;
	} //랜덤 생성

	theta = (rand()%5)+1; 
	// 랜덤 설정 범위 = 1~5
	printf("Theta: %f\n", theta);

	printf("\n\nAnd\n\n");
	printf("초기 %f %f \n", W[0], W[1]);
	while (1) //and
	{
		count = and ();
		printf("%f %f \n", W[0], W[1]);
		if (count == 0) break;
		else {
			while (1)
			{
				count = and ();
				printf("%f %f \n", W[0], W[1]);
				if (count == 0) break;
			}
		}
	}
	printf("최종 %f %f \n", W[0], W[1]);
	
	for (i = 0;i < N;i++) {
		W[i] = rand() % 10;
	}

	printf("\n\nOR\n\n");	
	printf("초기 %f %f \n", W[0], W[1]);
	while (1) //or
	{
		count = or();
		printf("%f %f \n", W[0], W[1]);
		if (count == 0) break;
		else {
			while (1)
			{
				count = or ();
				printf("%f %f \n", W[0], W[1]);
				if (count == 0) break;
			}
		}
	}
	printf("최종 %f %f \n", W[0], W[1]);

	for (i = 0;i < 4;i++) {
		xW[i] = rand() % 10;
	}
	for (i = 0;i < N;i++) {
		W[i] = rand() % 10;
	}

	printf("\n1.Xor NAND\n\n");
	while (1) //nand
	{
		count = x_nand();
		printf("%f %f \n", xW[0], xW[1]);
		if (count == 0) break;
		else {
			while (1)
			{
				count = x_nand ();
				printf("%f %f \n", xW[0], xW[1]);
				if (count == 0) break;
			}
		}
	}

	if ((xW[0] + xW[1]) == theta) {
		if (xW[0] > xW[1]) xW[0] = xW[0] + 0.1;
		else xW[1] = xW[1] + 0.1;
		printf("\n nand의 theta = %f, W1 = %f, W2 = %f\n", -theta, -xW[0], -xW[1]);
	}
	else printf("\n nand의 theta = %f, W1 = %f, W2 = %f\n", -theta, -xW[0], -xW[1]);

	printf("\n2.XOR OR\n\n");
	while (1) //or
	{
		printf("%f %f \n", xW[2], xW[3]);
		count = x_or();
		if (count == 0) break;
	}
	printf("최종 %f %f \n", xW[2], xW[3]);

	printf("\n\n3. XOR And\n\n");
	W[0] = xW[0]; W[1] = xW[1];
	printf("%f %f \n", W[0], W[1]);
	printf("\n\nXOR\n\n");
	//while (1) //xor
	{
		count = xor ();
		printf("Wrong count = %d\n", count);
		//if (count == 0) break;
	}
	printf("\n\nxor_nand의 theta = %f, W1 = %f, W2 = %f\n", -theta, -xW[0], -xW[1]);
	printf("xor_or의 theta = %f, W1 = %f, W2 = %f\n", theta, xW[2], xW[3]);
	printf("xor_and의 theta = %f, W1 = %f, W2 = %f\n", theta, W[0], W[1]);
}
