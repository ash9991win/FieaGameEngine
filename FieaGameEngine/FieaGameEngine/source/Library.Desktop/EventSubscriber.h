#pragma once
namespace Library
{
	/*!
	\class EventSubscriber
	\brief The event subscriber class
	*/
	class EventSubscriber
	{
	public :
		EventSubscriber() = default;
		virtual ~EventSubscriber() = default;
		/*!
		\fn Notify(EventPublisher)
		\brief The function which notifies the subscriber
		\param The publisher which notified the subscriber
		*/
		virtual void Notify(class EventPublisher&) = 0;
	};
}