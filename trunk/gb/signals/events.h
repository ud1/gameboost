#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

namespace gb
{

#define DECLARE_EVENT0(name)          gb::Event0 name;
#define DECLARE_EVENT1(name, argtype) gb::Event1<argtype> name;

	class EventReceiver;

	class Event
	{
	public:
		virtual void receiverDisconnected(EventReceiver* reciver) = 0;
	};

	class EventReceiver
	{
	public:
		virtual ~EventReceiver();

		inline void eventConnected(Event* e) { _events.push_back(e); }
		void eventDisconnected(Event* e);

	private:
		typedef std::vector<Event*> EventList;
		EventList _events;
	};

	class EventConnectionBase
	{
	public:
		virtual EventReceiver* receiver() = 0;
	};

	/*
	* Event 0
	*/

	class Event0ConnectionBase : public EventConnectionBase
	{
	public:
		virtual void emit() = 0;
	};

	template <typename RecevierType>
	class Event0Connection : public Event0ConnectionBase
	{
	public:
		Event0Connection(RecevierType* receiver, void(RecevierType::*func)());

		inline EventReceiver* receiver() { return _receiver; }
		inline void emit() { (_receiver->*_receiverMethod)(); }

	private:
		RecevierType* _receiver;
		void (RecevierType::*_receiverMethod)();
	};

	class Event0 : public Event
	{
	public:
		~Event0();

		template <typename R>
		void connect(R* receiver, void (R::*receiverMethod)());

		template <typename R>
		void disconnect(R* receiver);

		void receiverDisconnected(EventReceiver* r);
		void invoke();

	private:
		typedef std::vector<Event0ConnectionBase*> ConnectionList;
		ConnectionList _connections; 
	};

	/*
	* Event 1
	*/

	template <typename ArgType>
	class Event1ConnectionBase : public EventConnectionBase
	{
	public:
		virtual void emit(ArgType arg) = 0;
	};

	template <typename ReceiverType, typename ArgType>
	class Event1Connection : public Event1ConnectionBase<ArgType>
	{
	public:
		Event1Connection(ReceiverType* receiver, void(ReceiverType::*func)(ArgType));

		inline EventReceiver* receiver() { return _receiver; }
		inline void emit(ArgType arg) { (_receiver->*_receiverMethod)(arg); }

	private:
		ReceiverType* _receiver;
		void (ReceiverType::*_receiverMethod)(ArgType);
	};

	template <typename ArgType>
	class Event1 : public Event
	{
	public:
		~Event1();

		template <typename ReceiverType>
		void connect(ReceiverType* receiver, void (ReceiverType::*receiverMethod)(ArgType));

		template <typename ReceiverType>
		void disconnect(ReceiverType* receiver);

		void receiverDisconnected(EventReceiver* r);
		void invoke(ArgType arg);

	private:
		typedef std::vector<Event1ConnectionBase<ArgType>*> ConnectionList;
		ConnectionList _connections; 
	};

#include "events.inl.h"

}