#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <future>

using namespace std;
 
std::mutex mu; 


// pass value from child thread to main thread
int factorial(int N)
{
	int res = 1;
	for(int i=N; i>1; --i)
	{
		res*=i;
	}

	cout << "Result is : " << res << endl;
	return res;
}

// pass value from main thread to child thread
int factorial_1(std::future<int>& future)
{
	int res = 1;
	int N = future.get();

	for(int i=N; i>1; --i)
	{
		res*=i;
	}

	cout << "Result is : " << res << endl;
	return res;
}

int main()
{
	int x;

	/* pass value from child thread to main thread */
	//std::future<int> future= std::async(std::launch::deferred | std::launch::async, factorial, 4); // default value
	//std::future<int> future= std::async(factorial, 4); // depends on the condition will section one 
	//std::future<int> future= std::async(std::launch::deferred, factorial, 4); // NOT create another thread
	std::future<int> future_0= std::async(std::launch::async, factorial, 4);  // create another thread
	x = future_0.get(); // get return value from future_0
	cout << x << endl;


	/*pass value from main thread to child thread */
	std::promise<int> promise;
	std::future<int> future_1 = promise.get_future(); // will pass value through promise
	std::future<int> future_2= std::async(std::launch::async, factorial_1, std::ref(future_1)); 
	//do some thing else 
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	promise.set_value(5);
	x = future_2.get(); // get return value from future_2 
	cout << x << endl;

	return 0;
}


