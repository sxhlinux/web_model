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

#include <iostream>

enum Event_Type {
	ACCEPT_EVENT = 01,
	READ_EVENT = 02,
	WRITE_EVENT = 04,
	TIMEOUT_EVENT = 010,
	SIGNAL_EVENT = 020,
	CLOSE_EVENT = 040
};

class Event_Handler {
	public:
		virtual void handle_event(Event_Type evt) = 0;
		virtual Handler get_handler() const = 0;
}

class Logging_Acceptor : public Event_Handler {
	public:
		Logging_Acceptor(const INET_addr & addr);

		virtual void handle_event(Event_Type et);

		virtual Handler get_handler() const
		{
			return acceptor.get_handler();
		}

	private:
		SOCK_Acceptor acceptor;
}

class Logging_Handler : public Event_Handler {
	public:
		Logging_Handler(SOCK_Stream &cs);

		virtual void handle_event(Event_Type et);

		virtual Handler get_handler() const
		{
			return peer_stream.get_handler();
		}

	private:
		SOCK_Stream peer_stream;
}

#endif   /* ----- #ifndef event_handler_INC  ----- */
