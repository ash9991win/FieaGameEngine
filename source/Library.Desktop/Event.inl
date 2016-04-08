#include"Event.h"
namespace Library
{
#pragma warning(disable : 4592)
	template<typename T>
	SList<EventSubscriber*> Event<T>::EventSubscriberList;
#pragma warning(default : 4592)
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)
	

	template<typename T>
	 Event<T>::Event(const T & message)
		 : MessageData(message), EventPublisher(EventSubscriberList)
	{
	}
	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber & subscriber)
	{
		EventSubscriberList.PushBack(&subscriber);
	}
	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber & subscriber)
	{
			EventSubscriberList.Remove(&subscriber);
	}
	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
			EventSubscriberList.Clear();
	}
	template<typename T>
	inline const T & Event<T>::Message() const
	{
		return MessageData;
	}
	template<typename T>
	 Event<T>::Event(const Event && rhs)
		 :Event(rhs)
	{
	}
	 template<typename T>
	 Event<T>& Event<T>::operator=(const Event && rhs)
	 {
		 if (this != &rhs)
		 {
			 *this = rhs;
			 MessageData = std::move(rhs.MessageData);
		 }
		 return *this;
	 }
}