#include "pch.h"
#include "CppUnitTest.h"
#include"Event.h"
#include "FooEvent.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include "GameTime.h"
#include<string>
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(EventTest)
	{
	public:
#if defined(DEBUG) || defined(_DEBUG)

		TEST_METHOD_INITIALIZE(HASHMAP_INIT)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}
		TEST_METHOD_CLEANUP(HASH_CLEANUP)
		{
			_CrtMemState endMemState, diffMemState;

			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
#endif
		
		TEST_METHOD(EventTests)
		{
			Event<int> intEvent(3);
			Assert::IsTrue(intEvent.Message() == 3);
			Event<int> intEventCopy(2);
			intEvent = intEventCopy;
			Assert::IsTrue(intEvent.Message() == 2);
			intEvent = std::move(intEventCopy);
			Assert::IsTrue(intEvent.Message() == 2);
			Event<int> intEventCopyCtor(intEvent);
			Assert::IsTrue(intEventCopyCtor.Message() == 2);
			Event<int> intEventMoveCtor = std::move(intEventCopyCtor);
			Assert::IsTrue(intEventMoveCtor.Message() == 2);

			FooEvent f;
			intEvent.Subscribe(f);
			FooEvent f2;
			intEvent.Subscribe(f2);
			intEvent.Unsubscribe(f2);
			intEvent.UnsubscribeAll();
		}
		TEST_METHOD(EventQueueTests)
		{
			GameTime time;
			EventQueue queue;
			Event<int> intEvent(3);
			FooEvent fooEvent;
			intEvent.Subscribe(fooEvent);
			std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<int>>(intEvent);
			queue.Enequeue(eventPublisher, time);
			queue.Update(time);
			queue.Clear(time);
			Assert::IsTrue(queue.IsEmpty());
			Assert::IsTrue(queue.Size() == 0U);
			Assert::IsTrue(fooEvent.Message == intEvent.Message());
			intEvent.UnsubscribeAll();
		}
		TEST_METHOD(EventPublisherTest)
		{
			GameTime time;
			EventQueue queue;
			Event<int> intEvent(3);
			FooEvent fooEvent;
			intEvent.Subscribe(fooEvent);
			EventPublisher& intPublisher = *(intEvent.As<EventPublisher>());
			EventPublisher intPublisherCopy = intPublisher;
			intPublisher.TimeEnequed();
			intPublisher.Delay();
			EventPublisher intPublishMove = std::move(intPublisherCopy);
			intEvent.UnsubscribeAll();
		}
		TEST_METHOD(EventRTTI)
		{
			Event<int> testEvent(1);
			RTTI* testRTTI = &testEvent;
			uint64_t staticID = Event<int>::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			std::string name = Event<int>::TypeName();
			name;
			Assert::IsTrue(Event<int>::TypeName() == "Event");
			Assert::IsTrue(testEvent.Is(staticID));
			Assert::IsFalse(testEvent.Is(0));
			Assert::IsTrue(testEvent.Is("Event"));
			Assert::IsFalse(testEvent.Is("TEST"));
			Assert::IsTrue(testEvent.QueryInterface(0) == nullptr);
			Assert::IsTrue(testEvent.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testEvent.ToString() != "");
			Assert::IsTrue(testEvent.Equals(testRTTI));
		}
		TEST_METHOD(EventPublisherRTTI)
		{
			Event<int> testEvent(1);
			EventPublisher& publisher = *(testEvent.As<EventPublisher>());
			RTTI* testRTTI = &publisher;
			uint64_t staticID = EventPublisher::TypeIdClass();
			Assert::IsFalse(testRTTI->TypeIdInstance() == staticID);
			std::string name = EventPublisher::TypeName();
			name;
			Assert::IsTrue(EventPublisher::TypeName() == "EventPublisher");
			Assert::IsTrue(publisher.Is(staticID));
			Assert::IsFalse(publisher.Is(0));
			Assert::IsTrue(publisher.Is("EventPublisher"));
			Assert::IsFalse(publisher.Is("TEST"));
			Assert::IsTrue(publisher.QueryInterface(0) == nullptr);
			Assert::IsTrue(publisher.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(publisher.ToString() != "");
			Assert::IsTrue(publisher.Equals(testRTTI));
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EventTest::sStartMemState;
#endif

}