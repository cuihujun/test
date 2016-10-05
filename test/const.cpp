#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{

#if 1
	char * const pConstchar = "aaa"; //指针指向的整型数是可以修改的，但指针是不可修改的
	char * str= pConstchar;
	
	//pConstchar = "bbb";		//error 'pConstchar': you cannot assign to a variable that is const

	cout<< pConstchar <<endl;
	cout<< str <<endl;
	
#else
	char const * pConstchar;	//值是不可修改的，但指针可以

	char * str="bbb";
	char const *Cstr;
	
	pConstchar = "aaa";
	cout<< "pConstchar: "<< pConstchar <<endl;
	cout<<"-------------------------------"<<endl;

	pConstchar = str;
	cout<< "pConstchar: "<< pConstchar <<endl;
	cout<<"-------------------------------"<<endl;

	//str= pConstchar;			//error cannot convert from 'const char *' to 'char *
	Cstr = pConstchar;
	cout<< "Cstr: "<< Cstr <<endl;
#endif
	return 0;
}





