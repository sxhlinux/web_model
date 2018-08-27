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

	close(sockfd);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
