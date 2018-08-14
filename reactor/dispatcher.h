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

class Initiation_Dispatcher {
	public:
		virtual int register_handler(Event_Handler *eh, Event_Type et) = 0;

		virtual int remove_handler(Event_handler *eh, Event_Type et) = 0;

		virtual int handle_events(Time_Value *timeout = 0) = 0;
}
#endif   /* ----- #ifndef dispatcher_INC  ----- */
