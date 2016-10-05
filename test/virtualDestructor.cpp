


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
	virtual ~Base()
	{
		cout << "Base Destructor" << endl;
	}
	virtual void name(){};
};

class Child : public Base
{
public:
	Child()
	{
		cout << "Child Constructor" << endl;
	}
	~Child()
	{
		cout << "Child Destructor" << endl;
	}
	void name()
	{
		cout << "my name is child" << endl;
	}
};


int main()
{

	Child* child;
	Base* base;

	child = new Child();

	base = child;


	delete child;

	return 0;
}
