/**
 * @Author: liuqiuyuewo
 * @Version: v1.0 
 * @Link: https://blog.csdn.net/liuqiuyuewo/article/details/72628905
 * @Date: 2018-04-27 09:31:21 
 * @Brief: 线程安全队列
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-17 11:25:05
 * @Last Modified log: 
 */

#ifndef _S2THREADSAFEQUEUE_HPP_
#define _S2THREADSAFEQUEUE_HPP_
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class SThreadSafeQueue
{
private:
	mutable std::mutex 		        mut;		//锁
	std::queue<T> 			        data_queue;	//队列
	std::condition_variable 	    data_cond;	//条件变量
public:
	//构造函数
	SThreadSafeQueue();
	SThreadSafeQueue &operator=(const SThreadSafeQueue&)=delete;

	//可以多传递一个额外的条件
	bool WaitAndPop(T &value,std::atomic_bool &bl);
	bool TryPop(T &value);
	void Push(T new_value);
	bool Empty() const;

	void NotifyAll()
	{
		data_cond.notify_all();
	}
};
template <class T>
SThreadSafeQueue<T>::SThreadSafeQueue(){}

template <class T>
bool SThreadSafeQueue<T>::Empty() const
{
	std::lock_guard<std::mutex> lock(mut);
	return data_queue.Empty();
}

template <class T>
void SThreadSafeQueue<T>::Push(T new_value)
{
	std::lock_guard<std::mutex> lock(mut);
	data_queue.Push(new_value);
	data_cond.notify_one();
}


template <class T>
bool SThreadSafeQueue<T>::WaitAndPop(T &value,std::atomic_bool &bl)
{
	std::unique_lock<std::mutex> lock(mut);
	
	//避免队列为空时一直等待
	data_cond.wait(lock,[this,&bl](){return (!this->data_queue.Empty())||bl; });

	if(bl&&data_queue.Empty())
		return false;

	value=data_queue.front();
	data_queue.pop();
	return true;
}
template<class T>
bool SThreadSafeQueue<T>::TryPop(T &value)
{
	std::lock_guard<std::mutex> lock(mut);
	if(Empty())
		return false;

	value=data_queue.front();
	data_queue.pop();
	return true;
}
#endif