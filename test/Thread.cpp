#include <thread>
#include <iostream>

using namespace std;

std::mutex mu;


void shared_print(string msg, int id)
{
	mu.lock();
	cout << msg << id << endl;
	mu.unlock();
}

void function_1()
{
	for(int i=0; i<100; ++i)
	{
		shared_print("From t1 ", i);
	}
}

int main()
{

	std:: thread t1(function_1);

	for(int i=0; i<100; ++i)
	{
		shared_print("From main: ", i);
	}

	t1.join();

	return 0;
}