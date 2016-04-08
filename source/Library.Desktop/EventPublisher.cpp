#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)
	EventPublisher::EventPublisher( SList<EventSubscriber*>& list)
		:SubscriberList(&list)
	{
	}
	void EventPublisher::SetTime(const std::chrono::high_resolution_clock::time_point& eTime, const std::chrono::milliseconds delay)
	{
		EnequeTime = eTime;
		DelayTime = delay;
	}

	const std::chrono::high_resolution_clock::time_point & EventPublisher::TimeEnequed()
	{
		return EnequeTime;
	}

	const std::chrono::milliseconds & EventPublisher::Delay() const
	{
		return DelayTime;
	}

	void EventPublisher::Deliver() 
	{
		for (auto& subscriber : (*SubscriberList))
		{
			subscriber->Notify(*this);
		}
	}

	bool EventPublisher::IsExpired(const std::chrono::high_resolution_clock::time_point & currentTime)
	{
		return (currentTime >= EnequeTime + DelayTime);
	}

	EventPublisher::EventPublisher(const EventPublisher && rhs)
		:EventPublisher(rhs)
	{
	}
	EventPublisher& EventPublisher::operator=(const EventPublisher && rhs)
	{
		if (this != &rhs)
		{
			*this = rhs;
		}
		return *this;
	}
}
