
#include <iostream>

using namespace std;


int main()
{
	int i =10;
	int j =11;

	auto helloWorld = []()
	{
		cout << "hellow" << endl;
	};
	helloWorld();


	auto helloWorldNum = [](int a, int b)
	{
		cout << a+b << endl;
	};
	helloWorldNum(4, 5);

	auto helloWorldPara = [i, j](int a, int b)
	{
		cout << "a+b= "<< a+b << endl;
		cout << "i: " << i << endl; // 10
		cout << "i: " << j << endl; // 11
	};
	helloWorldPara(1, 2);


	auto helloWorldRef = [&i, &j]()
	{
		cout << "i: " << i << endl; // 10
		cout << "i: " << j << endl; // 11

		/* the variable values will be changed*/
		i=100;
		j=101;
	};
	helloWorldRef();

	cout << i << endl;  // 100
	cout << j << endl;  // 101

	return 0;
}







