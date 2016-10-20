#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <fstream>

using namespace std;

std::once_flag flag;
ofstream f;
std::mutex mu;

void shared_print(string msg, int index)
{
	std::call_once(flag, [&](){
		f.open("log.txt");
	});

	std::unique_lock<std::mutex> locker(mu, std::defer_lock);

	locker.lock();
	f << "shared_print: "<< msg << index << endl;
	locker.unlock();
}

void testFunc()
{
	for(int i=0; i<100; ++i)
	{
		shared_print("From t1 ", i);
	}
}

int main()
{ 
	std:: thread t1(testFunc);

	for(int i=0; i<100; ++i)
	{
		shared_print("From main: ", i);
	}

	t1.join();

	//std::async(std::launch::async, testFunc);
	
	return 0;
}