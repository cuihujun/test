



#include <iostream>

using namespace std;

int main(void)
{ 

#if 1
	int A[]={10,20,30,40,50,60,70};
 
 	double *dp = (double *)A;

 	(*dp)++;
 
 	printf("%d \n",*dp);

 
#else

 	int A[] = {10,20,30,40,50,60,70};
	double *dp= (double*) A;
	
	//(*dp)++;
	//(*(int *)dp)++;
	*dp++;
	
	std::cout<< (*(int *)dp);
#endif

 	return 0;
}

/*
1) 답을 11이 되도록 바꾸는 것이 었는데
 
dp 는 더블형 포인터 입니다. 그렇기에 *dp 는 더블형으로 접근한 값을 1을 증가해 줘야 하는데
접근 한 값은 정수기 때문에 데이터 형에 맞지 않게 1이 증가됩니다. 즉 정리하자면 정수형으로 1을
증가해야 하는데 , 실수형으로 1을 증가시킨다는 이야기입니다. 그러므로 포인터로 접근하는 형 변환이
이루어 져야 하기 때문에, *dp 는	* ( int *) dp	이와같이 코드가 고쳐져야 하며 여기에 ++ 연산자를
넣어줍니다.
그래서 정답은 아래와 같습니다. (*(int *)dp)++; 해설 : 더블형 포인터인 dp를 정수형으로 주소값에 접근한 뒤 1을 더한다.

2) *dp++ 이와 같이 연산을 했을 시 어떠한 결과값이 나올까요?

* 보다 ++ 가 연산 순위가 낮기 때문에 후위 연산으로 dp 에 1을 더하고 dp 의 주소값으로 접근이 됩니다.
그러므로 *dp 는 아무 의미가 없어지고 dp 의 다음 주소값으로 이동되는 연산밖에 없지만,
dp 가 더블형 포인터이고 정수형 배열에 연결 되어 있기 때문에 10을 가르키던 dp 는 30을 가르키게 됩니다.
int 는 4byte , double 는 8 byte 형이기 때문에 더블형 포인터인 dp 는 정수형 배열에서 8byte씩 다음 주소로 이동되기 때문이죠.

3)
포스팅을 하면서 대수롭지 않게 생각했던 부분중의 하나가
printf("%d \n",*dp);
실제값을 접근하는 부분이었습니다. dp가 더블형 포인터이기 때문에 형변환을 시켜 주소값으로 접근해야 했지만,
형변환을 지켜주지 않아도 정수값을 접근하는데는 "32비트 운영체제"에서는 문제가 없습니다.
 
32비트 운영체제를 제외한 다른 운영체제(64비트또는16비트)에서는 전혀 다른 값이 나오죠..
그래서 정확하게 정수형으로 접근을 하는 아래 코드를 세심하게 신경써줘야 합니다.
printf("%d \n",*(int *)dp);
*/



