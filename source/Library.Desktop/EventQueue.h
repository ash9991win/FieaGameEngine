#pragma once
#include"Vector.h"
#include"GameTime.h"
#include<memory>
namespace Library
{
	
	class EventPublisher;
	/*!
	\class EventQueue
	\brief The event queue class
	*/
	class EventQueue final
	{
	public:
		EventQueue() = default;
		~EventQueue() = default;
		/*!
		\fn Eneque(publisher,GameTime, DelayTime)
		\brief The function adds the given publisher to the queue
		\param The publisher to be added to the queue
		\param The gametime reference to set as the eneque time of the publisher
		\param The delay time of the publisher
		*/
		void Enequeue(std::shared_ptr<EventPublisher>& publisher,const  GameTime& time, std::chrono::milliseconds delay = std::chrono::milliseconds( 0));
		/*!
		\fn Update(gameTime&)
		\brief The function calls delivers the events of all the active events in the queue
		*/
		void Update(const GameTime& time);
		/*!
		\fn Clear(Time)
		\brief Clears the queue. Note that this does send out all the active events
		\param The game time 
		*/
		void Clear(const GameTime& time);
		/*!
		\fn IsEmpty()
		\brief Checks if the queue is empty
		\return Returns true if the queue is empty
		*/
		bool IsEmpty();
		/*!
		\fn Size()
		\brief Returns the size of the queue
		\return Returns the size of the queue
		*/
		std::uint32_t Size();
		EventQueue& operator=(const EventQueue&) = delete;
		EventQueue(const EventQueue&) = delete;
	private:
		/*!
		\var ActiveEvents
		\brief The list of all the active events
		*/
		Vector<std::shared_ptr<EventPublisher>> ActiveEvents;
		/*!
		\var ExpiredEvents
		\brief The list of all the Expired events
		*/
		Vector<std::shared_ptr<EventPublisher>> ExpiredEvents;
	};

}