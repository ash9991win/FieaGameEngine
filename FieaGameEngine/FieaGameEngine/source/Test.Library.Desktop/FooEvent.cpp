#include "pch.h"
#include "FooEvent.h"
#include "EventPublisher.h"
#include"Event.h"
FooEvent::FooEvent():
Message(-1)
{
}


FooEvent::~FooEvent()
{
}

void FooEvent::Notify(EventPublisher & p)
{

	Event<int> *ip = p.As<Event<int>>();
	if (ip)
	{
		Message = ip->Message();
	}
	
}
