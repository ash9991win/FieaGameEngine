#pragma once
#include "RTTI.h"
#include "SList.h"
#include "GameTime.h"
#include<memory>
namespace Library
{
	class EventSubscriber;
	/*!
	\class EventPublisher
	\brief The publisher class 
	*/
	class EventPublisher :
		public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher,RTTI)
	
	public:
		/*!
		\fn EventPublisher(SList<EventSubscriber>)
		\brief The event publisher ctor
		\param The list of subscribers 
		*/
		EventPublisher( SList<EventSubscriber*>& list);
		EventPublisher(const EventPublisher& rhs) = default;
		EventPublisher& operator=(const EventPublisher& rhs) = default;
		/*!
		\fn EventPublisher(EventPublisher&&)
		\brief The move constructor 
		\param The RValue reference to move from
		*/
		EventPublisher(const EventPublisher&& rhs);
		/*!
		\fn EventPublisher(EventPublisher&&)
		\brief The move assignment operator
		\param The RValue reference to move from
		*/
		EventPublisher& operator=(const EventPublisher&& rhs);
		/*!
		\fn SetTime(EnequeTime,DelayTime)
		\brief Sets the starting time and the delay time of the event
		\param The time at which the event was enequeud
		\param The delay time after which the event is dequeud
		*/
		void SetTime(const std::chrono::high_resolution_clock::time_point& eTime, const std::chrono::milliseconds delay = std::chrono::milliseconds(0));
		/*!
		\fn TimeEnequed()
		\brief The time at which the event was enequed
		\return The time at which the event was enequed
		*/
		const std::chrono::high_resolution_clock::time_point& TimeEnequed();
		/*!
		\fn Delay()
		\brief Returns the delay time of the event
		\return Returns the delay time
		*/
		const std::chrono::milliseconds& Delay() const;
		/*!
		\fn Deliver()
		\brief Delivers the message to all the subscribers
		*/
		void Deliver() ;
		/*!
		\fn IsExpired(CurrentTime)
		\brief Checks if at the given time the event has expired or not
		\param The current time
		*/
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime);
		~EventPublisher() = default;
	protected:
		/*
		\var SubscriberList
		\brief The list of subscribers for this publisher
		*/
		SList<EventSubscriber*> *SubscriberList;
		/*!
		\var DelayTime
		\brief The delay time
		*/
		std::chrono::milliseconds DelayTime;
		/*!
		\fn EnequeTime
		\brief The time at which at the event was enequed
		*/
		std::chrono::high_resolution_clock::time_point EnequeTime;
	};
}
