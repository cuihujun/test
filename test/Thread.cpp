#include <thread>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

std::mutex mu;

/*
 * Problem 1: it use mutex lock to protect the std::cout, 
 *            but if std::cout throw error, the mutex will be locked forever. 
 */
// void shared_print(string msg, int id)
// {
// 	mu.lock();
// 	cout << msg << id << endl;
// 	mu.unlock();
// }

/*
 * Problem 2: the guard goes out of the scope the std::cout will be unlocked. 
 *            but here std::cout is not completely protected, because std::cout is global function
 *            it still being used by other thread.
 */
// void shared_print(string msg, int id)
// {
// 	std::lock_guard<std::mutex> guard(mu);
// 	cout << msg << id << endl;
// }


/*
 * Best solution: BUT NEVER return/pass to others. it need to be at the inside of shared_print function.
 */

class LogFile
{
private: 
	std::mutex mu;
	ofstream fstream;
public: 
	LogFile()
	{
		fstream.open("log.txt");
	}
	~LogFile()
	{
		fstream.close();
	}
	void shared_print(string msg, int index)
	{
		std::lock_guard<std::mutex> guard(mu);
		fstream << msg << index << endl;
	}
};

void function_1(LogFile& log)
{
	for(int i=0; i<100; ++i)
	{
		log.shared_print("From t1 ", i);
	}
}

int main()
{
	LogFile logFile;
	std:: thread t1(function_1, std::ref(logFile));
	
	for(int i=0; i<100; ++i)
	{
		logFile.shared_print("From main: ", i);
	}

	t1.join();

	return 0;
}