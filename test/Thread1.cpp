#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

std::deque<int> q;
std::mutex mu;


// push some data in to queue
// creating the queue
void function_1()
{
	int count = 10;
	while(count >0)
	{
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();

		std::this_thread::sleep_for(chrono::seconds(1));
		count --;
	}
 
}

// check the queue, if not empty will pop the data from queue
// consuming queue data
void function_2()
{
	int data = 0;
	while(data!=1)
	{
		std::unique_lock<std::mutex> locker(mu);
		if(!q.empty())
		{
			data = q.back();
			q.pop_back();
			locker.unlock();

			cout << "t2 got a value from t1: " << data << endl;
		}
		else
		{
			// here will check if queue empty and unlock and check it again
			// here is busy looping !!!
			locker.unlock();
		}
	}
}


int main()
{
	std::thread t1(function_1);
	std::thread t2(function_2);

	if(t1.joinable())
		t1.join();

	if(t2.joinable())
		t2.join();
	
	return 0;
}


