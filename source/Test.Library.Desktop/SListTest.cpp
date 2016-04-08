#include "pch.h"
#include "CppUnitTest.h"
#include"SList.h"
#include"Foo.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Library;
using namespace FooC;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:
#if defined(DEBUG) | defined(_DEBUG)
		TEST_METHOD_INITIALIZE(LIST_CLEAR)
		{	
			intList.Clear();
			auto functionException_int = [&] {intList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_int);
			Assert::AreEqual(intList.Size(), 0U);

			intPointerList.Clear();
			auto functionException_pointer = [&] {intPointerList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_pointer);
			Assert::AreEqual(intPointerList.Size(), 0U);

			fooList.Clear();
			auto functionException_Foo = [&] {fooList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_Foo);
			Assert::AreEqual(fooList.Size(), 0U);

			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			intList.Clear();
			auto functionException_int = [&] {intList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_int);
			Assert::AreEqual(intList.Size(), 0U);

			intPointerList.Clear();
			auto functionException_pointer = [&] {intPointerList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_pointer);
			Assert::AreEqual(intPointerList.Size(), 0U);

			fooList.Clear();
			auto functionException_Foo = [&] {fooList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_Foo);
			Assert::AreEqual(fooList.Size(), 0U);

			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}

		}
#endif
		TEST_METHOD(LIST_COPYCONSTRUCTOR)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			intList.PushBack(1);
			intList.PushFront(2);
			SList<int> testIntList(intList);
			Assert::AreEqual(intList.Front(), testIntList.Front());
			Assert::AreEqual(intList.Back(), intList.Back());
			intList.PushBack(2);
			Assert::AreNotEqual(intList.Size(), testIntList.Size());

			intPointerList.PushBack(testPtr);
			SList<int*> testIntPointerList(intPointerList);
			Assert::AreEqual(intPointerList.Front(), testIntPointerList.Front());
			Assert::AreEqual(intPointerList.Back(), testIntPointerList.Back());
			intPointerList.PopFront();
			Assert::AreNotEqual(intPointerList.Size(), testIntPointerList.Size());

			fooList.PushBack(testFoo);
			SList<Foo>  testFooList(fooList);
			Assert::IsTrue(fooList.Front() == testFooList.Front());
			fooList.PushBack(testFoo);
			Assert::AreNotEqual(fooList.Size(), testFooList.Size());
		}
		TEST_METHOD(LIST_PUSHFRONT)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			Assert::AreEqual(intList.Size(),0U);
			Assert::AreEqual(intPointerList.Size(), 0U);
			Assert::AreEqual(fooList.Size(), 0U);

			intList.PushFront(testInt);
			Assert::AreEqual(intList.Size(), 1U);
			Assert::AreEqual(intList.Front(), testInt);
			Assert::AreEqual(intList.Front(), intList.Back());
			intList.PushFront(testInt2);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Front(), testInt2);
			Assert::AreEqual(intList.Back(), testInt);

			intPointerList.PushFront(testPtr);
			Assert::AreEqual(intPointerList.Size(), 1U);
			Assert::AreEqual(intPointerList.Front(), testPtr);
			Assert::AreEqual(intPointerList.Front(), intPointerList.Back());
			intPointerList.PushFront(testPtr2);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Front(), testPtr2);
			Assert::AreEqual(intPointerList.Back(),testPtr);

			fooList.PushFront(testFoo);
			Assert::AreEqual(fooList.Size(), 1U);
			Assert::IsTrue(fooList.Front() == testFoo);
			Assert::IsTrue(fooList.Front() == fooList.Back());
			fooList.PushFront(testFoo2);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Front() == testFoo2);
			Assert::IsTrue(testFoo == fooList.Back());
		}
		TEST_METHOD(LIST_POPFRONT)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			auto functionException_int = [&] {intList.PopFront(); };
			auto functionException_pointer = [&] {intPointerList.PopFront(); };
			auto functionException_Foo = [&] {fooList.PopFront(); };

			Assert::ExpectException<out_of_range>(functionException_int);
			Assert::ExpectException<out_of_range>(functionException_pointer);
			Assert::ExpectException<out_of_range>(functionException_Foo);

			intList.PushFront(testInt);
			intList.PopFront();
			Assert::AreEqual(intList.Size(), 0U);
			intList.PushFront(testInt);
			intList.PushFront(testInt2);
			Assert::AreEqual(intList.Size(), 2U);
			intList.PopFront();
			Assert::AreEqual(intList.Size(), 1U);
			Assert::AreEqual(intList.Front(), testInt);
			Assert::AreEqual(intList.Back(), testInt);


			intPointerList.PushFront(testPtr);
			intPointerList.PopFront();
			Assert::AreEqual(intPointerList.Size(), 0U);
			intPointerList.PushFront(testPtr);
			intPointerList.PushFront(testPtr2);
			Assert::AreEqual(intPointerList.Size(), 2U);
			intPointerList.PopFront();
			Assert::AreEqual(intPointerList.Size(), 1U);
			Assert::AreEqual(intPointerList.Front(), testPtr);
			Assert::AreEqual(intPointerList.Back(), testPtr);

			fooList.PushFront(testFoo);
			fooList.PopFront();
			Assert::AreEqual(fooList.Size(), 0U);
			fooList.PushFront(testFoo);
			fooList.PushFront(testFoo2);
			fooList.PopFront();
			Assert::AreEqual(fooList.Size(), 1U);
			Assert::IsTrue(fooList.Front() == testFoo);
			Assert::IsTrue(fooList.Front() == fooList.Back());
		}
		TEST_METHOD(LIST_PUSHBACK)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			Assert::AreEqual(intList.Size(), 0U);
			Assert::AreEqual(intPointerList.Size(), 0U);
			Assert::AreEqual(fooList.Size(), 0U);
			

			intList.PushBack(testInt);
			Assert::AreEqual(intList.Size(), 1U);
			Assert::AreEqual(intList.Front(), testInt);
			Assert::AreEqual(intList.Front(), intList.Back());
			intList.PushBack(testInt2);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Front(), testInt);
			Assert::AreEqual(intList.Back(), testInt2);


			intPointerList.PushBack(testPtr);
			Assert::AreEqual(intPointerList.Size(), 1U);
			Assert::AreEqual(intPointerList.Front(), testPtr);
			Assert::AreEqual(intPointerList.Front(), intPointerList.Back());
			intPointerList.PushBack(testPtr2);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Front(), testPtr);
			Assert::AreEqual(intPointerList.Back(), testPtr2);

			fooList.PushBack(testFoo);
			Assert::AreEqual(fooList.Size(), 1U);
			Assert::IsTrue(fooList.Front() == testFoo);
			Assert::IsTrue(fooList.Front() == fooList.Back());
			fooList.PushBack(testFoo2);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Front() == testFoo);
			Assert::IsTrue(testFoo2 == fooList.Back());
		
		}
		TEST_METHOD(LIST_FRONT)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			auto functionException_int = [&] {intList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_int);
			intList.PushBack(1);
			intList.PushBack(2);
			Assert::AreEqual(intList.Front(), 1);

			auto functionException_pointer = [&] {intPointerList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_pointer);
			intPointerList.PushBack(testPtr);
			Assert::AreEqual(intPointerList.Front(), testPtr);


			auto functionException_Foo = [&] {fooList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_Foo);
			fooList.PushBack(testFoo);
			Assert::IsTrue(fooList.Front() == testFoo);	
		}
		TEST_METHOD(LIST_BACK)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			auto functionException_int = [&] {intList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_int);
			intList.PushBack(1);
			intList.PushBack(2);
			Assert::AreEqual(intList.Back(), 2);

			auto functionException_pointer = [&] {intPointerList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_pointer);
			intPointerList.PushBack(testPtr);
			Assert::AreEqual(intPointerList.Back(), testPtr);

			auto functionException_Foo = [&] {fooList.Front(); };
			Assert::ExpectException<out_of_range>(functionException_Foo);
			fooList.PushBack(testFoo);
			Assert::IsTrue(fooList.Back() == testFoo);
		}
		TEST_METHOD(LIST_OPERATORS)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);
			SList<int> testIntList;
			SList<int*> testIntPointerList;
			SList<Foo> testFooList;

			Assert::AreEqual(intList.Size(), 0U);
			Assert::AreEqual(intPointerList.Size(),0U);
			Assert::AreEqual(fooList.Size(), 0U);

			intList.PushBack(testInt);
			intList.PushBack(testInt2);
			testIntList = intList;
			Assert::AreEqual(intList.Size(), testIntList.Size());
			Assert::AreEqual(intList.Front(), testIntList.Front());
			testIntList = testIntList;
			Assert::AreEqual(testIntList.Size(), 2U);

			intPointerList.PushBack(testPtr);
			intPointerList.PushBack(testPtr2);
			testIntPointerList = intPointerList;
			Assert::AreEqual(intPointerList.Size(), testIntPointerList.Size());
			Assert::AreEqual(intPointerList.Front(), testIntPointerList.Front());
			testIntPointerList = testIntPointerList;
			Assert::AreEqual(testIntPointerList.Size(), 2U);

			fooList.PushBack(testFoo);
			fooList.PushBack(testFoo2);
			testFooList = fooList;
			Assert::AreEqual(fooList.Size(), testFooList.Size());
			Assert::IsTrue(fooList.Front() == testFooList.Front());
			testFooList = testFooList;
			Assert::AreEqual(testFooList.Size(), 2U);
		}
		TEST_METHOD(LIST_ISEMPTY)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			intList.Clear();
			Assert::AreEqual(intList.IsEmpty(), true);
			intList.PushBack(1);
			Assert::AreEqual(intList.IsEmpty(), false);

			intPointerList.Clear();
			Assert::AreEqual(intPointerList.IsEmpty(), true);
			intPointerList.PushBack(testPtr);
			Assert::AreEqual(intPointerList.IsEmpty(), false);

			fooList.Clear();
			Assert::AreEqual(fooList.IsEmpty(), true);
			fooList.PushBack(testFoo);
			Assert::AreEqual(fooList.IsEmpty(), false);
		}
		TEST_METHOD(LIST_SIZE)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			Assert::AreEqual(intList.Size(), 0U);
			intList.PushBack(testInt);
			intList.PushBack(testInt2);
			Assert::AreEqual(intList.Size(), 2U);
			intList.PopFront();
			Assert::AreEqual(intList.Size(), 1U);

			Assert::AreEqual(intPointerList.Size(),0U);
			intPointerList.PushBack(testPtr);
			intPointerList.PushBack(testPtr2);
			Assert::AreEqual(intPointerList.Size(),2U);
			intPointerList.PopFront();
			Assert::AreEqual(intPointerList.Size(), 1U);

			Assert::AreEqual(fooList.Size(), 0U);
			fooList.PushBack(testFoo);
			fooList.PushBack(testFoo2);
			Assert::AreEqual(fooList.Size(), 2U);
			fooList.PopFront();
			Assert::AreEqual(fooList.Size(), 1U);
		}
		TEST_METHOD(LIST_FIND)
		{
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			intList.PushBack(testInt);
			intList.PushBack(testInt2);
			intIterator = intList.begin();
			SList<int>::Iterator findIntIterator = intList.Find(testInt);
			Assert::IsTrue(intIterator == findIntIterator);
			findIntIterator = intList.Find(15);
			Assert::IsTrue(findIntIterator == intList.end());

			intPointerList.PushBack(testPtr);
			intPointerList.PushBack(testPtr2);
			intPointerIterator = intPointerList.begin();
			SList<int*>::Iterator findIntPointerIterator = intPointerList.Find(testPtr);
			Assert::IsTrue(intPointerIterator == findIntPointerIterator);
			intPointerList.PopFront();
			findIntPointerIterator = intPointerList.Find(testPtr);
			Assert::IsTrue(findIntPointerIterator == intPointerList.end());

			fooList.PushBack(testFoo);
			fooList.PushBack(testFoo2);
			fooIterator = fooList.begin();
			SList<Foo>::Iterator findFooIterator = fooList.Find(testFoo);
			Assert::IsTrue(fooIterator == findFooIterator);
			fooList.PopFront();
			findFooIterator = fooList.Find(testFoo);
			Assert::IsTrue(findFooIterator == fooList.end());
		}
		TEST_METHOD(LIST_REMOVE)
		{
			int testInt = 5;
			int testInt2 = 10;
			int testInt3 = 15;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			int *testPtr3 = &testInt3;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);
			Foo testFoo3;
			testFoo3.setData(4);
			testFoo3.setPointerData(5);

			auto functionException_int = [&] {intList.Remove(testInt); };
			Assert::ExpectException<exception>(functionException_int);
			intList.PushBack(testInt);
			intList.PushBack(testInt2);
			intList.PushBack(testInt3);
			Assert::AreEqual(intList.Size(), 3U);
			intList.Remove(testInt);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Front(), testInt2);
			intList.PushFront(testInt);
			intList.Remove(testInt3);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Back(), testInt2);
			intList.PushBack(testInt3);
			intList.Remove(testInt2);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Front(), testInt);

			auto functionException_intPointer = [&] {intPointerList.Remove(testPtr); };
			Assert::ExpectException<exception>(functionException_intPointer);
			intPointerList.PushBack(testPtr);
			intPointerList.PushBack(testPtr2);
			intPointerList.PushBack(testPtr3);
			Assert::AreEqual(intPointerList.Size(), 3U);
			intPointerList.Remove(testPtr);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Front(), testPtr2);
			intPointerList.PushFront(testPtr);
			intPointerList.Remove(testPtr3);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Back(), testPtr2);
			intPointerList.PushBack(testPtr3);
			intPointerList.Remove(testPtr2);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Front(), testPtr);

			auto functionException_Foo = [&] {fooList.Remove(testFoo); };
			Assert::ExpectException<exception>(functionException_Foo);
			fooList.PushBack(testFoo);
			fooList.PushBack(testFoo2);
			fooList.PushBack(testFoo3);
			Assert::AreEqual(fooList.Size(), 3U);
			fooList.Remove(testFoo);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Front() == testFoo2);
			fooList.PushFront(testFoo);
			fooList.Remove(testFoo3);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Back() == testFoo2);
			fooList.PushBack(testFoo3);
			fooList.Remove(testFoo2);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Front() == testFoo);
		}
		TEST_METHOD(LIST_INSERTAFTER)
		{
			int testInt = 5;
			int testInt2 = 10;
			int testInt3 = 15;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			int *testPtr3 = &testInt3;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);
			Foo testFoo3;
			testFoo3.setData(4);
			testFoo3.setPointerData(5);

			SList<int> testList;
			testList.PushBack(1);
			SList<int>::Iterator testIntIterator = testList.begin();
			auto functionException_int = [&] {intList.InsertAfter(testIntIterator, testInt); };
			Assert::ExpectException<exception>(functionException_int);
			intList.PushBack(testInt);
			Assert::AreEqual(intList.Size(), 1U);
			intIterator = intList.end();
			intList.InsertAfter(intIterator, testInt3);
			Assert::AreEqual(intList.Size(), 2U);
			Assert::AreEqual(intList.Back(), testInt3);
			intIterator = intList.Find(testInt);
			intList.InsertAfter(intIterator, testInt2);
			Assert::AreEqual(intList.Size(), 3U);
			Assert::IsTrue(intList.Find(testInt2) != intList.end());

			SList<int*> testPointerList;
			testPointerList.PushBack(testPtr);
			SList<int*>::Iterator testIntPointerIter = testPointerList.begin();
			auto functionException_intPointer = [&] {intPointerList.InsertAfter(testIntPointerIter, testPtr); };
			Assert::ExpectException<exception>(functionException_intPointer);
			intPointerList.PushBack(testPtr);
			Assert::AreEqual(intPointerList.Size(), 1U);
			intPointerIterator = intPointerList.end();
			intPointerList.InsertAfter(intPointerIterator, testPtr3);
			Assert::AreEqual(intPointerList.Size(), 2U);
			Assert::AreEqual(intPointerList.Back(), testPtr3);
			intPointerIterator = intPointerList.Find(testPtr);
			intPointerList.InsertAfter(intPointerIterator, testPtr2);
			Assert::AreEqual(intPointerList.Size(), 3U);
			Assert::IsTrue(intPointerList.Find(testPtr2) != intPointerList.end());
			
			SList<Foo> testFooList;
			testFooList.PushBack(testFoo);
			SList<Foo>::Iterator testFooIter = testFooList.begin();
			auto functionException_Foo = [&] {fooList.InsertAfter(testFooIter, testFoo); };
			Assert::ExpectException<exception>(functionException_Foo);
			fooList.PushBack(testFoo);
			Assert::AreEqual(fooList.Size(), 1U);
			fooIterator = fooList.end();
			fooList.InsertAfter(fooIterator, testFoo3);
			Assert::AreEqual(fooList.Size(), 2U);
			Assert::IsTrue(fooList.Back() == testFoo3);
			fooIterator = fooList.Find(testFoo);
			fooList.InsertAfter(fooIterator, testFoo2);
			Assert::AreEqual(fooList.Size(), 3U);
			Assert::IsTrue(fooList.Find(testFoo2) != fooList.end());

			
		}
		TEST_METHOD(LIST_BEGIN)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			intList.PushBack(testInt);
			intIterator = intList.begin();
			Assert::AreEqual(*intIterator, testInt);
           
			intPointerList.PushBack(testPtr);
			intPointerIterator = intPointerList.begin();
			Assert::AreEqual(*intPointerIterator, testPtr);

			fooList.PushBack(testFoo);
			fooIterator = fooList.begin();
			Assert::IsTrue((*fooIterator) == testFoo);
		}
		TEST_METHOD(LIST_END)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			intList.PushBack(testInt);
			intIterator = intList.end();
			auto functionException_int = [&] {intIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_int);

			intPointerList.PushBack(testPtr);
			intPointerIterator = intPointerList.end();
			auto functionException_intPointer = [&] {intPointerIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_intPointer);


			fooList.PushBack(testFoo);
			fooIterator = fooList.end();
			auto functionException_Foo = [&] {fooIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_Foo);
		}
		TEST_METHOD(ITER_COPYCONSTRUCTOR)
		{
			int testInt = 5;
			int *testPtr = &testInt;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);

			intList.PushBack(testInt);
			intIterator = intList.begin();
			SList<int>::Iterator testIntIter(intIterator);
			Assert::IsTrue(intIterator == testIntIter);

			intPointerList.PushBack(testPtr);
			intPointerIterator = intPointerList.begin();
			SList<int*>::Iterator testIntPointerIter(intPointerIterator);
			Assert::IsTrue(intPointerIterator == testIntPointerIter);

			fooList.PushBack(testFoo);
			fooIterator = fooList.begin();
			SList<Foo>::Iterator testFooIter(fooIterator);
			Assert::IsTrue(testFooIter == fooIterator);
		}
		TEST_METHOD(ITER_OPERATORS)
		{
			//Dereference 
			int testInt = 5;
			int testInt2 = 10;
			int *testPtr = &testInt;
			int *testPtr2 = &testInt2;
			Foo testFoo;
			testFoo.setData(1);
			testFoo.setPointerData(2);
			Foo testFoo2;
			testFoo2.setData(2);
			testFoo2.setPointerData(3);

			auto functionException_int = [&] {intIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_int);
			auto functionException_intIncrement_Pre = [&] {intIterator.operator++(); };
			Assert::ExpectException<exception>(functionException_intIncrement_Pre);
			auto functionException_intIncrement_Post = [&] {intIterator.operator++(0); };
			Assert::ExpectException<exception>(functionException_intIncrement_Post);
			intList.PushBack(testInt);
			intIterator = intList.begin();
			Assert::IsTrue((*intIterator) == testInt);
			SList<int>::Iterator testIntIter(intIterator);
			Assert::IsTrue(intIterator == testIntIter);
			testIntIter = intList.end();
			Assert::IsTrue(intIterator != testIntIter);
			intList.PushBack(testInt2);
			intIterator = intList.begin();
			++intIterator;
			Assert::IsTrue((*intIterator) == testInt2);
			intIterator++;
			Assert::IsTrue(intIterator == intList.end());

			auto functionException_IntPointer = [&] {intPointerIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_IntPointer);
			auto functionException_intPointerIncrement_Pre = [&] {intPointerIterator.operator++(); };
			Assert::ExpectException<exception>(functionException_intPointerIncrement_Pre);
			auto functionException_intPointerIncrement_Post = [&] {intPointerIterator.operator++(0); };
			Assert::ExpectException<exception>(functionException_intPointerIncrement_Post);
			intPointerList.PushBack(testPtr);
			intPointerIterator = intPointerList.begin();
			Assert::IsTrue((*intPointerIterator) == testPtr);
			SList<int*>::Iterator testIntPointerIter(intPointerIterator);
			Assert::IsTrue(intPointerIterator == testIntPointerIter);
			testIntPointerIter = intPointerList.end();
			Assert::IsTrue(intPointerIterator != testIntPointerIter);
			intPointerList.PushBack(testPtr2);
			intPointerIterator = intPointerList.begin();
			++intPointerIterator;
			Assert::IsTrue((*intPointerIterator) == testPtr2);
			intPointerIterator++;
			Assert::IsTrue(intPointerIterator == intPointerList.end());

			auto functionException_Foo = [&] {fooIterator.operator*(); };
			Assert::ExpectException<exception>(functionException_Foo);
			auto functionException_Foot_Pre = [&] {fooIterator.operator++(); };
			Assert::ExpectException<exception>(functionException_Foot_Pre);
			auto functionException_Foo_Post = [&] {fooIterator.operator++(0); };
			Assert::ExpectException<exception>(functionException_Foo_Post);
			fooList.PushBack(testFoo);
			fooIterator = fooList.begin();
			Assert::IsTrue((*fooIterator) == testFoo);
			SList<Foo>::Iterator testFooIter(fooIterator);
			Assert::IsTrue(fooIterator == testFooIter);
			testFooIter = fooList.end();
			Assert::IsTrue(fooIterator != testFooIter);
			fooList.PushBack(testFoo2);
			fooIterator = fooList.begin();
			++fooIterator;
			Assert::IsTrue((*fooIterator) == testFoo2);
			fooIterator++;
			Assert::IsTrue(fooIterator == fooList.end());


		}
		 SList<int> intList;
		 SList<int*> intPointerList;
		 SList<Foo>  fooList;
		 SList<int>::Iterator intIterator;
		 SList<int*>::Iterator intPointerIterator;
		 SList<Foo>::Iterator fooIterator;
#if defined(DEBUG) | defined(_DEBUG)
		 static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	 _CrtMemState SListTest::sStartMemState;
#endif


}