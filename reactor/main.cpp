/*
 * =============================================================================
 *       Filename:  main.cpp
 *    Description:  main function of reactor model
 *
 *        Version:  1.0
 *        Created:  08/14/2018 11:28:19 PM
 *         Author:  sxhlinux@163.com
 * =============================================================================
 */

#include <iostream>
#include "dispatcher.h"
#include "event_handler.h"

int main(int argc, char *argv[])
{
	std::cout << "Hello! I'm the reactor model server " << std::endl;
	new Logging_Acceptor(6000);
	Sxh_Dispatcher *dispatcher = Sxh_Dispatcher::get_instance();
	dispatcher->handle_events();

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
