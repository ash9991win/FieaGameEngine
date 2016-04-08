#pragma once
#include "EventPublisher.h"
namespace Library
{
	class EventSubscriber;
	/*!
	\class Event
	\brief The event class of type T which holds a subscriber list
	*/
	template<typename T>
	class Event final :
		public EventPublisher
	{
		RTTI_DECLARATIONS(Event,EventPublisher)
	public:
		/*!
		\fn Event(message)
		\brief The parametrized ctor which accepts a message as a parameter
		\param The message to be stored
		*/
		explicit Event(const T& message);
		Event(const Event& rhs) = default;
		Event& operator=(const Event& rhs) = default;
		/*!
		\fn Event(Event&&)
		\brief The move constructor 
		\param The Rvalue reference 
		*/
		Event(const Event&& rhs);
		/*!
		\fn Event(Event&&)
		\brief The move assignment operator
		\param The Rvalue reference
		*/
		Event& operator=(const Event&& rhs);
		/*!
		\fn Subscribe(EventSubscriber)
		\brief The Subscribe method which adds a subscriber to this event's list
		\param The Subscriber to add
		*/
		static void Subscribe(EventSubscriber& subscriber);
		/*!
		\fn Unsubscribe(EventSubscriber)
		\param The subscriber to remove from the list
		*/
		static void Unsubscribe(EventSubscriber& subscriber);
		/*!
		\fn UnsubscribeAll()
		\param Remove all subscribers
		*/
		static void UnsubscribeAll();
		/*!
		\fn Message()
		\brief return the message assosciated with the message
		\return Returns the message
		*/
		const T& Message() const;
		~Event() = default;

	private:
		/*!
		\var EventSubscriberList
		\brief The list of subscribers
		*/
		static SList<EventSubscriber*> EventSubscriberList;
		T MessageData;
	};
}
#include"Event.inl"