#include <thread>
#include <iostream> 
#include <string> 
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
int factorial_f(std::future<int>& future)
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

// multiple thread will get the value via std::shared_future
// the parameter not have to be a reference.
int factorial_sf(std::shared_future<int> future)
{
	int res = 1;
	int N = future.get();

	for(int i=N; i>1; --i)
	{
		res*=i;
	}

	// it just a simple print out, if the std::cout throw error, this will be locked forever.
	mu.lock();
	cout << "Result is : " << res << endl;
	mu.unlock();
	return res;
}

int main()
{
	int x;

	/* Example 1: pass value from child thread to main thread */

	//std::future<int> future= std::async(std::launch::deferred | std::launch::async, factorial, 4); // default value
	//std::future<int> future= std::async(factorial, 4); // depends on the condition will section one 
	//std::future<int> future= std::async(std::launch::deferred, factorial, 4); // NOT create another thread
	std::future<int> future_0= std::async(std::launch::async, factorial, 4);  // create another thread
	x = future_0.get(); // get return value from future_0
	cout << x << endl;


	/* Example 2: pass value from main thread to child thread */

	std::promise<int> promise;
	std::future<int> future_1 = promise.get_future(); // will pass value through promise
	std::future<int> future_2= std::async(std::launch::async, factorial_f, std::ref(future_1)); 
	//do some thing else 
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	promise.set_value(5);
	x = future_2.get(); // get return value from future_2 
	cout << x << endl;


	/* Example 3: multiple thread get the value via std::shared_future */
	std::promise<int> promise11;
	std::future<int> future_11 = promise11.get_future(); // will pass value through promise
	std::shared_future<int> sf = future_11.share(); // unlike std::future, the std::shared_future can be copied.

	std::future<int> future_12 = std::async(std::launch::async, factorial_sf, sf); // send std::shared_future copy
	std::future<int> future_13 = std::async(std::launch::async, factorial_sf, sf); // send std::shared_future copy
	std::future<int> future_14 = std::async(std::launch::async, factorial_sf, sf); // send std::shared_future copy
	std::future<int> future_15 = std::async(std::launch::async, factorial_sf, sf); // send std::shared_future copy

	promise11.set_value(6);
	// x = future_12.get(); // get return value from future_2 
	// cout << x << endl;


	return 0;
}


