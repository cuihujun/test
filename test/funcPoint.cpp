

#include <iostream>

using namespace std;

void PrintHello()
{
	cout<<"hello"<<endl;
}


int Add(int a, int b)
{
	return a+b;
}

int main()
{

	void (*HelloPtr)(void);
	int (*AddPtr)(int,int);

	AddPtr = Add;
	cout << AddPtr(1,2) << endl;

	HelloPtr = PrintHello;
	HelloPtr();
	return 0;
}






