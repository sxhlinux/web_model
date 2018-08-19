/*
 * =============================================================================
 *       Filename:  event_handler.h
 *    Description:  event handle header file
 *
 *        Version:  1.0
 *        Created:  08/14/2018 11:30:17 PM
 *         Author:  sxhlinux@163.com
 * =============================================================================
 */

#ifndef  event_handler_INC
#define  event_handler_INC

#include "dispatcher.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <errno.h>

class Logging_Handler : public Event_Handler {
	public:
		Logging_Handler(int filedes) : sockfd(filedes)
		{
			Sxh_Dispatcher::get_instance()->register_handler(this);
		} 

		virtual void handle_event()
		{
			char buff[1024] = {'\0'};
			ssize_t num = recv(sockfd, buff, sizeof(buff) - 1, 0);
			if (num > 0)
				std::cout << "recv " << buff << " from client " << std::endl;
			else {
				close(sockfd);
			}
		}

		virtual Handle get_handle(void) const
		{
			return sockfd;
		}

	private:
		int sockfd;
};

class Logging_Acceptor : public Event_Handler {
	public:
		Logging_Acceptor(const struct sockaddr_in &addr)
		{
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd == -1) {
				std::cerr << "###ERR: create socket failed: " << strerror(errno) << std::endl;
				return;
			}

			if (bind(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1) {
				std::cerr << "###ERR: bind socket failed: " << strerror(errno) << std::endl;
				return;
			}

			listen(sockfd, 10);

			Sxh_Dispatcher::get_instance()->register_handler(this);
		}

		virtual void handle_event()
		{
			struct sockaddr_in peer_addr;
			socklen_t addrlen;
			int conn_sock = accept(sockfd, (struct sockaddr *)&peer_addr, &addrlen);

			new Logging_Handler(conn_sock);
		}

		virtual Handle get_handle(void) const
		{
			return sockfd;
		}

	private:
		int sockfd;
};


#endif   /* ----- #ifndef event_handler_INC  ----- */
