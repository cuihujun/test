

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
/*
	char * const p;		 //常量指针，p的值不可以修改
	
	int * const a; 		  //第四个意思a 是一个指向整型数的常指针（也就是说，指针指向的整型数是可以修改的，但指针是不可修改的）

	char const * p；		//指向常量的指针，指向的常量值不可以改
	const char * p；   	 //和char const *p

	const int *a;             //第三个意味着a 是一个指向常整型数的指针（也就是，整型数是不可修改的，但指针可以）
*/
	char str1[] = "abc";
	char str2[] = "abc";
	
	const char str3[] = "abc";
	const char str4[] = "abc";

	const char *str5 = "abc";
	const char *str6 = "abc";

	char *str7 = "abc";
	char *str8 = "abc";

	cout << ( str1 == str2 ) << endl;		//output 0
	cout << ( str3 == str4 ) << endl;		//output 0
	cout << ( str5 == str6 ) << endl;		//output 1
	cout << ( str7 == str8 ) << endl;		//output 1

	//str1,str2,str3,str4是数组变量，它们有各自的内存空间； 而str5,str6,str7,str8是指针，它们指向相同的常量区域

	return 0;

}
