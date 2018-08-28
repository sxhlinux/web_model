/*
 * =============================================================================
 *       Filename:  client.cpp
 *    Description:  client to test server model
 *
 *        Version:  1.0
 *        Created:  08/26/2018 11:36:09 PM
 *         Author:  sxhlinux@163.com
 * =============================================================================
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include <iostream>


int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in target;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cerr << "create socket failed: " << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}

	target.sin_family = AF_INET;
	target.sin_port = 6000;
	target.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sockfd, (struct sockaddr *)&target, sizeof(struct sockaddr)) == 1) {
		std::cerr << "connect to target failed: " << strerror(errno) << std::endl;
		return EXIT_FAILURE;
	}

	char buf[1024] = {'\0'};
	struct iovec iov;
	iov.iov_base = buf;
	iov.iov_len = 1024;
	struct msghdr msg;
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iovlen = 1;
	msg.msg_iov = &iov;
	msg.msg_control = 0;
	msg.msg_controllen = 0;

	strcpy(buf, "hello reactor");
	int retval = sendmsg(sockfd, &msg, 0);
	if (retval == -1) 
		std::cerr << "sendmsg failed " << strerror(errno) << std::endl;
	else
		std::cout << "sendmsg 'hello reactor' successfully" << std::endl;

	close(sockfd);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
