/*
* EventReceiver
*/

inline EventReceiver::~EventReceiver() 
{
	for (EventList::iterator i = _events.begin(), e = _events.end(); i != e; ++i)
		(*i)->receiverDisconnected(this);
}

inline void EventReceiver::eventDisconnected(Event* e)
{
	EventList::iterator i = std::find(_events.begin(), _events.end(), e);

	if (i != _events.end())
		_events.erase(i);
}

/*
* Event0Connection
*/

template <typename T>
inline Event0Connection<T>::Event0Connection(T* receiver, void(T::*func)()) :  
_receiver(receiver), _receiverMethod(func)
{
}

/*
* Event0
*/

inline Event0::~Event0()
{
	for (ConnectionList::iterator i = _connections.begin(), e = _connections.end(); i != e; ++i)
	{
		(*i)->receiver()->eventDisconnected(this);
		delete (*i);
	}
	_connections.clear();
}

template <typename R>
inline void Event0::connect(R* receiver, void (R::*receiverMethod)())
{
	_connections.push_back( new Event0Connection<R>(receiver, receiverMethod) );
	receiver->eventConnected(this);
}

template <typename R>
inline void Event0::disconnect(R* receiver)
{
	receiverDisconnected(receiver);
}

inline void Event0::receiverDisconnected(EventReceiver* r)
{ 
	ConnectionList::iterator i = _connections.begin();
	while (i != _connections.end())
	{
		if (r == (*i)->receiver())
		{
			delete (*i);
			i = _connections.erase(i);
		}
		else
		{
			++i;
		}
	}
}

inline void Event0::invoke()
{
	for (ConnectionList::iterator i = _connections.begin(), e = _connections.end(); i != e; ++i)
	{
		(*i)->emit();
	}
}

/*
* Event1Connection
*/

template <typename ReceiverType, typename ArgType>
inline Event1Connection<ReceiverType, ArgType>::Event1Connection(ReceiverType* receiver, void(ReceiverType::*func)(ArgType)) :  
_receiver(receiver), _receiverMethod(func)
{
}

/*
* Event1
*/
template <typename ArgType>
inline Event1<ArgType>::~Event1()
{
	for (typename ConnectionList::iterator i = _connections.begin(), e = _connections.end(); i != e; ++i)
	{
		(*i)->receiver()->eventDisconnected(this);
		delete (*i);
	}
	_connections.clear();
}

template <typename ArgType>
template <typename ReceiverType>
inline void Event1<ArgType>::connect(ReceiverType* receiver, void (ReceiverType::*receiverMethod)(ArgType))
{
	_connections.push_back( new Event1Connection<ReceiverType, ArgType>(receiver, receiverMethod) );
	receiver->eventConnected(this);
}

template <typename ArgType>
template <typename ReceiverType>
inline void Event1<ArgType>::disconnect(ReceiverType* receiver)
{
	receiverDisconnected(receiver);
}

template <typename ArgType>
inline void Event1<ArgType>::receiverDisconnected(EventReceiver* r)
{ 
	typename ConnectionList::iterator i = _connections.begin();
	while (i != _connections.end())
	{
		if (r == (*i)->receiver())
		{
			delete (*i);
			i = _connections.erase(i);
		}
		else
		{
			++i;
		}
	}
}

template <typename ArgType>
inline void Event1<ArgType>::invoke(ArgType arg)
{
	for (typename ConnectionList::iterator i = _connections.begin(), e = _connections.end(); i != e; ++i)
	{
		(*i)->emit(arg);
	}
}