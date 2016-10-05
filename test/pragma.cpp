
#include <iostream>

using namespace std;

#pragma pack(8)
//使用伪指令#pragma pack (n)，编译器将按照n 个字节对齐
//如果#pragma pack (n)中指定的n 大于结构体中最大成员的size，则其不起作用，结构体仍然按照size 最大的成员进行对界

struct example1 //여기서 제일큰 변수의 크기가 2이기때문에 2로 对齐한다 그리하여 이 struct 의 크기는 4이다.
{
    short a;               //sizeof(short)=2
    short b;               //sizeof(short)=2
};
struct example2
//이 struct중에 제일큰 변수가 int=4이다 그리고 example1은 2로 对齐했다
//하여 이구조는 4로 对齐한다. 그리하여 이 struct 의 크기는 12이다.
{
    char c;                 // sizeof(char)=1
    example1 struct1;  // sizeof(example1)=4  인데 example1이라는 구조는 2로 对齐 했다
    int e;                   //sizeof(int)=4
};

#pragma pack()
//使用伪指令#pragma pack ()，取消自定义字节对齐方式

int main(int argc, char* argv[])
{
    example2 struct2;
    cout << sizeof(example1) << endl;  //output 4
    cout << sizeof(example2) << endl;  //output 12
    //cout << (unsigned int)(&struct2.struct1) - (unsigned int)(&struct2) << endl;  //output 2

    return 0;
}