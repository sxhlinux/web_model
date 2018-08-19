/*
 * =============================================================================
 *       Filename:  dispatcher.h
 *    Description:  event dispatcher header file
 *
 *        Version:  1.0
 *        Created:  08/14/2018 11:36:37 PM
 *         Author:  sxhlinux@163.com
 * =============================================================================
 */


#ifndef  dispatcher_INC
#define  dispatcher_INC

#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <errno.h>

#include <sys/epoll.h>
#include <pthread.h>

using Handle = int;

class Event_Handler {
	public:
		virtual void handle_event() = 0;
		virtual Handle get_handle(void) const = 0;
};

class Initiation_Dispatcher {
	public:
		virtual int register_handler(Event_Handler *eh) = 0;

		virtual int remove_handler(Event_Handler *eh) = 0;

		virtual int handle_events(int timeout = 0) = 0;
};

#define	MAX_EVENTS 10			/*  */
class Sxh_Dispatcher : public Initiation_Dispatcher {
	public:
		static Sxh_Dispatcher* get_instance(void)
		{
			if (instance == nullptr) {
				pthread_mutex_lock(&mtx);
				instance = new Sxh_Dispatcher();
				pthread_mutex_unlock(&mtx);
			}

			return instance;
		}

		virtual int register_handler(Event_Handler *eh)
		{
			struct epoll_event evt;
			evt.events = EPOLLIN | EPOLLET;
			evt.data.ptr = eh;

			if (epoll_ctl(epollfd, EPOLL_CTL_ADD, eh->get_handle(), &evt) == 0) {
				std::cerr << "epoll_ctl add event failed: " << strerror(errno) << std::endl;
				return EXIT_FAILURE;
			}

			return EXIT_SUCCESS;
		}

		virtual int remove_handler(Event_Handler *eh)
		{
			if (epoll_ctl(epollfd, EPOLL_CTL_DEL, eh->get_handle(), nullptr) == -1) {
				std::cerr << "epoll_ctl del event failed: " << strerror(errno) << std::endl;
				return EXIT_FAILURE;
			}

			return EXIT_SUCCESS;
		}

		virtual int handle_events(int timeout = -1)
		{
			int nfds = -1;
			sigset_t sigmask;
			struct epoll_event events[MAX_EVENTS];
			while (true) {
				nfds = epoll_pwait(epollfd, events, MAX_EVENTS, timeout, &sigmask);
				if (nfds == -1) {
					std::cerr << "epoll_pwait failed: " << strerror(errno) << std::endl;
					break;
				}

				for (int i = 0; i < nfds; i++) {
					Event_Handler *eh = (Event_Handler *)events[i].data.ptr;
					eh->handle_event();
				}
			}

			return EXIT_FAILURE;
		}

	private:
		Sxh_Dispatcher()
		{
			epollfd = epoll_create(MAX_EVENTS);
			if (epollfd == -1) {
				std::cerr << "epoll_create failed: " << strerror(errno) << std::endl;
				return;
			}
		}

		static Sxh_Dispatcher *instance;
		static pthread_mutex_t mtx;

		int epollfd;
};
#endif   /* ----- #ifndef dispatcher_INC  ----- */
