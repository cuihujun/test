

#include <iostream>

using namespace std;

#pragma pack(8)
//使用伪指令#pragma pack (n)，编译器将按照n 个字节对齐
//如果#pragma pack (n)中指定的n 大于结构体中最大成员的size，则其不起作用，结构体仍然按照size 最大的成员进行对界

struct example1 //여기서 제일큰 변수의 크기가 4이기때문에 4로 对齐한다 그리하여 이 struct 의 크기는 8이다.
{
	short a;    	   	//sizeof(short)=2
	long b;    			//sizeof(long)=4
};
struct example2 
//이 struct중에 example1이라는 구조가있는데 이는 4로 对齐했으면 이는 example 중에서도 제일 크다
//하여 이구조도 4로 对齐한다. 그리하여 이 struct 의 크기는 16이다.
{
	char c;		         // sizeof(char)=1
	example1 struct1;  // sizeof(example1)=8  인데 example1이라는 구조는 4로 对齐 했다
	short e;				//sizeof(short)=2
};

#pragma pack()
//使用伪指令#pragma pack ()，取消自定义字节对齐方式

int main(int argc, char* argv[])
{
	example2 struct2;
	cout << sizeof(example1) << endl;  //output 8
	cout << sizeof(example2) << endl;  //output 16
	//cout << (unsigned int)(&struct2.struct1) - (unsigned int)(&struct2) << endl;  //output 4
//由于struct example2 中的成员以4 为单位对界，故其char 变量c 后应补充3 个空，其后才是
//成员struct1 的内存空间，所以输出结果为4
	return 0;
}
