#include "pch.h"
#include "EventQueue.h"
#include"EventPublisher.h"
#include<algorithm>

void Library::EventQueue::Enequeue(std::shared_ptr<EventPublisher>& publisher, const GameTime & time, std::chrono::milliseconds delay)
{
	if (!ActiveEvents.IsFound(publisher))
	{
		publisher->SetTime(time.CurrentTime(), delay);
		ActiveEvents.PushBack(publisher);
	}
}
void Library::EventQueue::Update(const GameTime & time)
{
	for (auto& events : ActiveEvents)
	{
		EventPublisher& currentPublisher = (*events);
		if (currentPublisher.IsExpired(time.CurrentTime()))
		{
			currentPublisher.Deliver();
			ExpiredEvents.PushBack(events);
		}
	}
	for (auto& expiredEvents : ExpiredEvents)
	{
		ActiveEvents.Remove(expiredEvents);
	}
	ExpiredEvents.Clear();
}

void Library::EventQueue::Clear(const GameTime& time)
{
	Update(time);
	ActiveEvents.Clear();
	ExpiredEvents.Clear();
}

bool Library::EventQueue::IsEmpty()
{
	return (ActiveEvents.IsEmpty());
}

std::uint32_t Library::EventQueue::Size()
{
	return ActiveEvents.GetSize();
}

