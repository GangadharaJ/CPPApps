#pragma once
#include<iostream>
#include<mutex>
#include<condition_variable>
#include <vector>
#include <queue>
#include<sstream>
#include<thread>
#include<functional>
using namespace std;
class ThreadPool
{

private:
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;
	mutex queueMutex;
	condition_variable condition;
	bool stop;
public:
	template<class F>
	void enque(F&& task)
	{
		unique_lock<mutex> lock(queueMutex);
		tasks.emplace(std::forward<F>(task));
		lock.unlock();
		condition.notify_one();
	}
	ThreadPool(size_t noofthreads)
		:stop(false)
	{
		for (size_t i = 0; i < noofthreads; i++)
		{
			workers.emplace_back
			(
				[this]
				{
					for (;;)
					{
						unique_lock<mutex> lock(queueMutex);
						condition.wait(lock, [this] { return stop || !tasks.empty(); });
						if (stop && tasks.empty())
						{
							return;
						}
						//cout << "Thread Executing" << endl;
						auto task = move(tasks.front());
						tasks.pop();
						lock.unlock();
						task();

					}

				}
				);
		}
	}
	~ThreadPool()
	{
		unique_lock<mutex> lock(queueMutex);
		stop = true;
		lock.unlock();
		condition.notify_all();
		for (thread& worker : workers)
		{
			worker.join();
		}
	}
	
};

std::string get_threadID()
{
	auto id = this_thread::get_id();
	std::stringstream ss;
	ss << id;
	std::string mystr = ss.str();
	return mystr;
}