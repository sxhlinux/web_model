/*
 * =============================================================================
 *       Filename:  thread_pool.h
 *    Description:  thread pool
 *
 *        Version:  1.0
 *        Created:  Wed Sep 12 2018 19:52:34 CST
 *         Author:  shenxiaohuan@meituan.com
 * =============================================================================
 */


#ifndef  thread_pool_INC
#define  thread_pool_INC

#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <deque>

#include <cstring>
#include <cerrno>
#include <cstdio>

class Thread_Pool {
	public:
		static pthread_mutex_t mtx;

		static Thread_Pool* get_instance(void)
		{
			if (instance == nullptr) {
				pthread_mutex_lock(&mtx);
				instance = new Thread_Pool();
				pthread_mutex_unlock(&mtx);
			}

			return instance;
		}

		pthread_t get_waiter(void)
		{
			pthread_t thread_fd;
			if (waiters.size() == 0) {
				if (pthread_create(&thread_fd, NULL, &thread_func, nullptr)) {
					std::cerr << "new thread failed: " << strerror(errno) << std::endl;
					throw "pthread_create failed";
				}
			}
			else {
				thread_fd = waiters.front();
				waiters.pop_front();
			}
			workers.push_back(thread_fd);
			return thread_fd;
		}

	protected:
		Thread_Pool()
		{
			pthread_mutex_init(&mtx, nullptr);
		}

	private:
		static Thread_Pool *instance;
		std::deque<pthread_t> workers;
		std::deque<pthread_t> waiters;

		void thread_func(void)
		{
			while (true) {
			/* TODO do some work */
			}
		}
}

#endif   /* ----- #ifndef thread_pool_INC  ----- */
