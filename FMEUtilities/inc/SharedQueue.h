#ifndef SHAREDQUEUE_H_
#define SHAREDQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

namespace FME
{
	namespace Utilities
	{
		template <typename T>
		class SharedQueue
		{
		public:
			SharedQueue();
			~SharedQueue();

			T& Front();
			void PopFront();

			void PushBack(const T& item);
			void PushBack(T&& item);

			int Size();
			bool Empty();

		private:
			std::deque<T> m_queue;
			std::mutex m_mutex;
			std::condition_variable m_cond;
		};

		template <typename T>
		SharedQueue<T>::SharedQueue() {}

		template <typename T>
		SharedQueue<T>::~SharedQueue() {}

		template <typename T>
		T& SharedQueue<T>::Front()
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			while (m_queue.empty())
			{
				m_cond.wait(mlock);
			}
			return m_queue.front();
		}

		template <typename T>
		void SharedQueue<T>::PopFront()
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			while (m_queue.empty())
			{
				m_cond.wait(mlock);
			}
			m_queue.pop_front();
		}

		template <typename T>
		void SharedQueue<T>::PushBack(const T& item)
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			m_queue.push_back(item);
			mlock.unlock();     // unlock before notificiation to minimize mutex con
			m_cond.notify_one(); // notify one waiting thread

		}

		template <typename T>
		void SharedQueue<T>::PushBack(T&& item)
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			m_queue.push_back(std::move(item));
			mlock.unlock();     // unlock before notificiation to minimize mutex con
			m_cond.notify_one(); // notify one waiting thread

		}

		template <typename T>
		int SharedQueue<T>::Size()
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			int size = m_queue.size();
			mlock.unlock();
			return size;
		}

		template <typename T>
		bool SharedQueue<T>::Empty()
		{
			std::unique_lock<std::mutex> mlock(m_mutex);
			bool isEmpty =  m_queue.empty();
			mlock.unlock();
			return isEmpty;
		}
	}
}

#endif
