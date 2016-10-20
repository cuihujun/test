#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <fstream>
#include <sstream>

using namespace std;

std::once_flag flag;
ofstream ofs;
std::mutex mu;

void shared_print(string msg, int index)
{
	std::call_once(flag, [&](){
		ofs.open("log.txt");
	});

	//std::unique_lock<std::mutex> locker(mu, std::defer_lock);
 	std::lock_guard<std::mutex> locker(mu);
	ofs << "shared_print: "<< msg <<" : "<< index << endl;

	std::call_once(flag, [&](){
		
		if(ofs.is_open())
		{
			ofs.close();
		} 
	});
}

void testFunc(string msg)
{
	for(int i=0; i<100; ++i)
	{
		shared_print(msg, i);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
		
}
int main()
{
	std::thread t1(testFunc, "t1"); 
 
	for(int i=0; i<100; ++i)
	{
		shared_print("From Main", i);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
	t1.join();

	return 0;
}