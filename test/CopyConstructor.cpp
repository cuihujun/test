


#include <iostream>
#include <thread>


using namespace std;


class Base
{
public:
	Base()
	{
		cout << "Base Constructor" << endl;
	}
	Base(const Base& base)
	{
		cout << "Copy Constructor" << endl;
	}
	virtual ~Base()
	{
		cout << "Base Destructor" << endl;
	}
	virtual void name(){};
};


int main()
{
	Base base1;
	Base base2 = base1;

	

	return 0;
}
