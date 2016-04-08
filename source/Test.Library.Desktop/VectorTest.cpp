#include "pch.h"
#include "CppUnitTest.h"
#include"Vector.h"
#include"TestFunctor.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
using namespace FooC;
namespace TestLibraryDesktop
{		
	TEST_CLASS(VectorTest)
	{
	public:
#if defined(DEBUG) | defined(_DEBUG)
		TEST_METHOD_INITIALIZE(Initialize)
		{
			IntList.Clear();
			Assert::AreEqual(IntList.GetSize(), 0U);
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntPtrList.Clear();
			Assert::AreEqual(IntPtrList.GetSize(), 0U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			FooList.Clear();
			Assert::AreEqual(FooList.GetSize(), 0U);
			Assert::AreEqual(FooList.GetCapacity(), 0U);

			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			IntList.Clear();
			Assert::AreEqual(IntList.GetSize(), 0U);
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntPtrList.Clear();
			Assert::AreEqual(IntPtrList.GetSize(), 0U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			FooList.Clear();
			Assert::AreEqual(FooList.GetSize(), 0U);
			Assert::AreEqual(FooList.GetCapacity(), 0U);
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}

		}
#else 
		TEST_METHOD_INITIALIZE(Initialize)
		{
			IntList.Clear();
			Assert::AreEqual(IntList.GetSize(), 0U);
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntPtrList.Clear();
			Assert::AreEqual(IntPtrList.GetSize(), 0U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			FooList.Clear();
			Assert::AreEqual(FooList.GetSize(), 0U);
			Assert::AreEqual(FooList.GetCapacity(), 0U);

		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			IntList.Clear();
			Assert::AreEqual(IntList.GetSize(), 0U);
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntPtrList.Clear();
			Assert::AreEqual(IntPtrList.GetSize(), 0U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			FooList.Clear();
			Assert::AreEqual(FooList.GetSize(), 0U);
			Assert::AreEqual(FooList.GetCapacity(), 0U);
		}
#endif

		TEST_METHOD(VECTOR_TESTFUNCTOR)
		{
			Vector<int, TestFunctor> TestIntVector;
			Assert::AreEqual(TestIntVector.GetCapacity(), 3U);
			TestIntVector.PushBack(TestInt1);
			TestIntVector.PushBack(TestInt2);
			TestIntVector.PushBack(TestInt3);
			Assert::AreEqual(TestIntVector.GetCapacity(), 3U);
			TestIntVector.PushBack(TestInt1);
			Assert::AreEqual(TestIntVector.GetCapacity(), 4U);

			Vector<int*, TestFunctor> TestPtrVector;
			Assert::AreEqual(TestPtrVector.GetCapacity(), 3U);
			TestPtrVector.PushBack(TestPtr1);
			TestPtrVector.PushBack(TestPtr2);
			TestPtrVector.PushBack(TestPtr3);
			Assert::AreEqual(TestPtrVector.GetCapacity(), 3U);
			TestPtrVector.PushBack(TestPtr1);
			Assert::AreEqual(TestPtrVector.GetCapacity(), 4U);

			Vector<Foo, TestFunctor> TestFooVector;
			Assert::AreEqual(TestFooVector.GetCapacity(), 3U);
			TestFooVector.PushBack(TestFoo1);
			TestFooVector.PushBack(TestFoo2);
			TestFooVector.PushBack(TestFoo3);
			Assert::AreEqual(TestFooVector.GetCapacity(), 3U);
			TestFooVector.PushBack(TestFoo1);
			Assert::AreEqual(TestFooVector.GetCapacity(), 4U);
		}
		TEST_METHOD(VECTOR_COPYCONSTRUCTOR)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Vector<int> TestIntCopy = IntList;
			Assert::AreEqual(IntList.GetSize(), TestIntCopy.GetSize());
			Assert::AreEqual(IntList.GetCapacity(), TestIntCopy.GetCapacity());
			IntList.PushBack(TestInt3);
			Assert::AreNotEqual(IntList.GetSize(), TestIntCopy.GetSize());
			Assert::AreEqual(IntList.GetCapacity(), TestIntCopy.GetCapacity());

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Vector<int*> TestIntPtrCopy = IntPtrList;
			Assert::AreEqual(IntPtrList.GetSize(), TestIntPtrCopy.GetSize());
			Assert::AreEqual(IntPtrList.GetCapacity(), TestIntPtrCopy.GetCapacity());
			IntPtrList.PushBack(TestPtr3);
			Assert::AreNotEqual(IntPtrList.GetSize(), TestIntPtrCopy.GetSize());
			Assert::AreEqual(IntPtrList.GetCapacity(), TestIntPtrCopy.GetCapacity());

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Vector<Foo> TestFooCopy = FooList;
			Assert::AreEqual(FooList.GetSize(), TestFooCopy.GetSize());
			Assert::AreEqual(FooList.GetCapacity(), TestFooCopy.GetCapacity());
			FooList.PushBack(TestInt3);
			Assert::AreNotEqual(FooList.GetSize(), TestFooCopy.GetSize());
			Assert::AreEqual(FooList.GetCapacity(), TestFooCopy.GetCapacity());	
		}
		TEST_METHOD(VECTOR_MOVECONSTRUCTOR)
		{
			
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			Vector<int> TestIntCopy = std::move(IntList);
			Assert::AreEqual(TestIntCopy.GetCapacity(), 3U);
			Assert::AreEqual(TestIntCopy.GetSize(), 3U);

			Vector<int*> TestIntPtrCopy;
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList = std::move(TestIntPtrCopy);
			Assert::AreEqual(IntPtrList.GetCapacity(), 3U);
			Assert::AreEqual(TestIntPtrCopy.GetSize(), 0U);

			Vector<Foo> TestFooCopy;
			TestFooCopy.PushBack(TestFoo1);
			TestFooCopy.PushBack(TestFoo1);
			TestFooCopy.PushBack(TestFoo1);
			FooList = std::move(TestFooCopy);
			Assert::AreEqual(FooList.GetCapacity(), 3U);
			Assert::AreEqual(TestFooCopy.GetSize(), 0U);
		}
		TEST_METHOD(VECTOR_POPBACK)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			Assert::IsTrue(IntList.Back() == TestInt3);
			Assert::AreEqual(IntList.GetSize(), 3U);
			IntList.PopBack();
			Assert::IsTrue(IntList.Back() == TestInt2);
			Assert::AreEqual(IntList.GetSize(), 2U);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			Assert::IsTrue(IntPtrList.Back() == TestPtr3);
			Assert::AreEqual(IntPtrList.GetSize(), 3U);
			IntPtrList.PopBack();
			Assert::IsTrue(IntPtrList.Back() == TestPtr2);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			Assert::IsTrue(FooList.Back() == TestFoo3);
			Assert::AreEqual(FooList.GetSize(), 3U);
			FooList.PopBack();
			Assert::IsTrue(FooList.Back() == TestFoo2);
			Assert::AreEqual(FooList.GetSize(), 2U);

		}
		TEST_METHOD(VECTOR_ISEMPTY)
		{
			Assert::IsTrue(IntList.IsEmpty());
			IntList.PushBack(TestInt1);
			Assert::IsFalse(IntList.IsEmpty());

			Assert::IsTrue(IntPtrList.IsEmpty());
			IntPtrList.PushBack(TestPtr1);
			Assert::IsFalse(IntPtrList.IsEmpty());

			Assert::IsTrue(FooList.IsEmpty());
			FooList.PushBack(TestFoo1);
			Assert::IsFalse(FooList.IsEmpty());
		}
		TEST_METHOD(VECTOR_FRONT)
		{
			auto functionException_int = [&] {IntList.Front(); };
			Assert::ExpectException<std::exception>(functionException_int);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Assert::IsTrue(IntList.Front() == TestInt1);
			IntList.Front() = TestInt3;
			Assert::IsTrue(IntList.Front() == TestInt3);
			const Vector<int> ConstIntList = IntList;
			Assert::AreEqual(ConstIntList.Front(), TestInt3);

			auto functionException_Ptr = [&] {IntPtrList.Front(); };
			Assert::ExpectException<std::exception>(functionException_Ptr);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Assert::IsTrue(IntPtrList.Front() == TestPtr1);
			IntPtrList.Front() = TestPtr3;
			Assert::IsTrue(IntList.Front() == TestInt3);
			const Vector<int*> ConstIntPtrList = IntPtrList;
			Assert::AreEqual(ConstIntPtrList.Front(), TestPtr3);

			auto functionException_Foo = [&] {FooList.Front(); };
			Assert::ExpectException<std::exception>(functionException_Foo);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Assert::IsTrue(FooList.Front() == TestFoo1);
			FooList.Front() = TestFoo3;
			Assert::IsTrue(FooList.Front() == TestFoo3);
			const Vector<Foo> ConstFooList = FooList;
			Assert::IsTrue(ConstFooList.Front() ==  TestFoo3);
		}
		TEST_METHOD(VECTOR_BACK)
		{
			auto functionException_int = [&] {IntList.Back(); };
			Assert::ExpectException<std::exception>(functionException_int);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Assert::IsTrue(IntList.Back() == TestInt2);
			IntList.Back() = TestInt3;
			Assert::IsTrue(IntList.Back() == TestInt3);
			const Vector<int> ConstIntList = IntList;
			Assert::AreEqual(ConstIntList.Back(), TestInt3);

			auto functionException_Ptr = [&] {IntPtrList.Back(); };
			Assert::ExpectException<std::exception>(functionException_Ptr);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Assert::IsTrue(IntPtrList.Back() == TestPtr2);
			IntPtrList.Back() = TestPtr3;
			Assert::IsTrue(IntList.Back() == TestInt3);
			const Vector<int*> ConstIntPtrList = IntPtrList;
			Assert::AreEqual(ConstIntPtrList.Back(), TestPtr3);

			auto functionException_Foo = [&] {FooList.Back(); };
			Assert::ExpectException<std::exception>(functionException_Foo);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Assert::IsTrue(FooList.Back() == TestFoo2);
			FooList.Back() = TestFoo3;
			Assert::IsTrue(FooList.Back() == TestFoo3);
			const Vector<Foo> ConstFooList = FooList;
			Assert::IsTrue(ConstFooList.Back() == TestFoo3);
		}
		TEST_METHOD(VECTOR_GETSIZE)
		{
			Assert::AreEqual(IntList.GetSize(), 0U);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Assert::AreEqual(IntList.GetSize(), 2U);
			IntList.PopBack();
			Assert::AreEqual(IntList.GetSize(), 1U);

			Assert::AreEqual(IntPtrList.GetSize(), 0U);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);
			IntPtrList.PopBack();
			Assert::AreEqual(IntPtrList.GetSize(), 1U);

			Assert::AreEqual(FooList.GetSize(), 0U);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Assert::AreEqual(FooList.GetSize(), 2U);
			FooList.PopBack();
			Assert::AreEqual(FooList.GetSize(), 1U);
		}
		TEST_METHOD(VECTOR_GETCAPACITY)
		{
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Assert::AreEqual(IntList.GetCapacity(), 3U);
			IntList.Reserve(10);
			Assert::AreEqual(IntList.GetCapacity(), 10U);

			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Assert::AreEqual(IntPtrList.GetCapacity(), 3U);
			IntPtrList.Reserve(10);
			Assert::AreEqual(IntPtrList.GetCapacity(), 10U);

			Assert::AreEqual(FooList.GetCapacity(), 0U);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo1);
			Assert::AreEqual(FooList.GetCapacity(), 3U);
			FooList.Reserve(10);
			Assert::AreEqual(FooList.GetCapacity(), 10U);
			Assert::IsTrue(FooList.Front() == TestFoo1);
		}
		TEST_METHOD(VECTOR_BEGIN_END)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Vector<int>::Iterator IntIter = IntList.begin();
			Assert::AreEqual(*IntIter , TestInt1);
			IntIter = IntList.end();
			auto functionException_it = [&] {IntIter.operator*(); };
			Assert::ExpectException<std::exception>(functionException_it);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Vector<int*>::Iterator IntIterPtr = IntPtrList.begin();
			Assert::AreEqual(*IntIterPtr, TestPtr1);
			IntIterPtr = IntPtrList.end();
			auto functionException_ptr = [&] {IntIterPtr.operator*(); };
			Assert::ExpectException<std::exception>(functionException_ptr);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Vector<Foo>::Iterator IntIterFoo = FooList.begin();
			Assert::IsTrue(*IntIterFoo == TestFoo1);
			IntIterFoo = FooList.end();
			auto functionException_foo = [&] {IntIterFoo.operator*(); };
			Assert::ExpectException<std::exception>(functionException_foo);
		}
		TEST_METHOD(VECTOR_PUSHBACK)
		{
			IntList.PushBack(TestInt1);
			Assert::AreEqual(IntList.GetSize(), 1U);
			Assert::IsTrue(IntList[0] == TestInt1);

			IntPtrList.PushBack(TestPtr1);
			Assert::AreEqual(IntPtrList.GetSize(), 1U);
			Assert::IsTrue(IntPtrList[0] == TestPtr1);

			FooList.PushBack(TestFoo1);
			Assert::AreEqual(FooList.GetSize(), 1U);
			Assert::IsTrue(FooList[0] == TestFoo1);

		}
		TEST_METHOD(VECTOR_PUSHBACKWITHITERATOR)
		{
			Vector<int>::Iterator PushIterator = IntList.PushBackWithIterator(TestInt1);
			Assert::AreEqual(*PushIterator, TestInt1);
			*PushIterator = TestInt2;
			Assert::AreEqual(IntList.Back(), TestInt2);
		}
		TEST_METHOD(VECTOR_AT)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			Assert::IsTrue(IntList.At(0) == TestInt1);
			IntList.At(0) = TestInt2;
			Assert::IsTrue(IntList[0] == TestInt2);
			const Vector<int> ConstIntList = IntList;
			Assert::IsTrue(ConstIntList.At(0) == TestInt2);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			Assert::IsTrue(IntPtrList.At(0) == TestPtr1);
			IntPtrList.At(0) = TestPtr2;
			Assert::IsTrue(IntPtrList[0] == TestPtr2);
			const Vector<int*> ConstIntPtrList = IntPtrList;
			Assert::IsTrue(ConstIntPtrList.At(0) == TestPtr2);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			Assert::IsTrue(FooList.At(0) == TestFoo1);
			FooList.At(0) = TestFoo2;
			Assert::IsTrue(FooList[0] == TestFoo2);
			const Vector<Foo> ConstFooList = FooList;
			Assert::IsTrue(ConstFooList.At(0) == TestFoo2);
		}
		TEST_METHOD(VECTOR_RESERVE)
		{
			IntList.Reserve(10U);
			Assert::AreEqual(IntList.GetCapacity(), 10U);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.Reserve(11U);
			Assert::AreEqual(IntList.GetCapacity(), 11U);
			Assert::IsTrue(IntList[0] == TestInt1);

			IntPtrList.Reserve(10U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 10U);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.Reserve(11U);
			Assert::AreEqual(IntPtrList.GetCapacity(), 11U);
			Assert::IsTrue(IntPtrList[0] == TestPtr1);

			FooList.Reserve(10U);
			Assert::AreEqual(FooList.GetCapacity(), 10U);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.Reserve(11U);
			Assert::AreEqual(FooList.GetCapacity(), 11U);
			Assert::IsTrue(FooList[0] == TestFoo1);
		}
		TEST_METHOD(VECTOR_FIND)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			Vector<int>::Iterator FindIter = IntList.Find(TestInt2);
			Assert::IsTrue(*FindIter == TestInt2);
			IntList.PopBack();
			FindIter = IntList.Find(TestInt3);
			Assert::IsTrue(FindIter == IntList.end());

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			Vector<int*>::Iterator FindIterPtr = IntPtrList.Find(TestPtr2);
			Assert::IsTrue(*FindIterPtr == TestPtr2);
			IntPtrList.PopBack();
			FindIterPtr = IntPtrList.Find(TestPtr3);
			Assert::IsTrue(FindIterPtr == IntPtrList.end());

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			Vector<Foo>::Iterator FindIterFoo = FooList.Find(TestFoo2);
			Assert::IsTrue(*FindIterFoo == TestFoo2);
			FooList.PopBack();
			FindIterFoo = FooList.Find(TestInt3);
			Assert::IsTrue(FindIterFoo == FooList.end());
		}
		TEST_METHOD(VECTOR_CLEAR)
		{
			Assert::AreEqual(IntList.GetCapacity(), 0U);
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.Clear();
			Assert::AreEqual(IntList.GetCapacity(), 0U);

			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.Clear();
			Assert::AreEqual(IntPtrList.GetCapacity(), 0U);

			Assert::AreEqual(FooList.GetCapacity(), 0U);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.Clear();
			Assert::AreEqual(FooList.GetCapacity(), 0U);
		}
		TEST_METHOD(VECTOR_ERASE)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			IntList.Erase(4);
			IntList.Erase(2);
			Assert::AreEqual(IntList.GetSize(), 2U);
			IntList.PushBack(TestInt3);
			IntList.Erase(1);
			Assert::AreEqual(IntList.GetSize(), 2U);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			IntPtrList.Erase(4);
			IntPtrList.Erase(2);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);
			IntPtrList.PushBack(TestPtr3);
			IntPtrList.Erase(1);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			FooList.Erase(4);
			FooList.Erase(2);
			Assert::AreEqual(FooList.GetSize(), 2U);
			FooList.PushBack(TestFoo3);
			FooList.Erase(1);
			Assert::AreEqual(FooList.GetSize(), 2U);
		}
		TEST_METHOD(VECTOR_REMOVE)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			IntList.Remove(TestInt3);
			Assert::AreEqual(IntList.GetSize(), 2U);
			IntList.PushBack(TestInt3);
			Vector<int> TestIntList = IntList;
			Vector<int>::Iterator TestIntIterator1 = IntList.Find(TestInt2);
			Vector<int>::Iterator TestIntIterator2 = TestIntList.Find(TestInt2);
			auto functionException_Int = [&] {IntList.Remove(TestIntIterator1, TestIntIterator2); };
			Assert::ExpectException<std::exception>(functionException_Int);
			TestIntIterator2 = IntList.Find(TestInt1);
			auto functionException_Int2 = [&] {IntList.Remove(TestIntIterator1, TestIntIterator2); };
			Assert::ExpectException<std::exception>(functionException_Int2);
			IntList.Clear();
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			TestIntIterator1 = IntList.Find(TestInt1);
			TestIntIterator2 = IntList.Find(TestInt2);
			IntList.Remove(TestIntIterator1, TestIntIterator2);
			Assert::AreEqual(IntList.GetSize(), 2U);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			IntPtrList.Remove(TestPtr3);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);
			IntPtrList.PushBack(TestPtr3);
			Vector<int*> TestPtrPtrList = IntPtrList;
			Vector<int*>::Iterator TestPtrIterator1 = IntPtrList.Find(TestPtr2);
			Vector<int*>::Iterator TestPtrIterator2 = TestPtrPtrList.Find(TestPtr2);
			auto functionException_IntPtr = [&] {IntPtrList.Remove(TestPtrIterator1, TestPtrIterator2); };
			Assert::ExpectException<std::exception>(functionException_IntPtr);
			TestPtrIterator2 = IntPtrList.Find(TestPtr1);
			auto functionException_IntPtr2 = [&] {IntPtrList.Remove(TestPtrIterator1, TestPtrIterator2); };
			Assert::ExpectException<std::exception>(functionException_IntPtr2);
			IntPtrList.Clear();
			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			TestPtrIterator1 = IntPtrList.Find(TestPtr1);
			TestPtrIterator2 = IntPtrList.Find(TestPtr2);
			IntPtrList.Remove(TestPtrIterator1, TestPtrIterator2);
			Assert::AreEqual(IntPtrList.GetSize(), 2U);
			TestFoo1.setData(1);
			TestFoo2.setData(2);
			TestFoo3.setData(3);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			FooList.Remove(TestFoo3);
			Assert::AreEqual(FooList.GetSize(), 2U);
			FooList.PushBack(TestFoo3);
			Vector<Foo> TestFooList = FooList;
			Vector<Foo>::Iterator TestFooIterator1 = FooList.Find(TestFoo2);
			Vector<Foo>::Iterator TestFooIterator2 = TestFooList.Find(TestFoo2);
			auto functionException_Foo = [&] {FooList.Remove(TestFooIterator1, TestFooIterator2); };
			Assert::ExpectException<std::exception>(functionException_Foo);
			TestFooIterator2 = FooList.Find(TestFoo1);
			auto functionException_Foo2 = [&] {FooList.Remove(TestFooIterator1, TestFooIterator2); };
			Assert::ExpectException<std::exception>(functionException_Foo2);
			FooList.Clear();
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			TestFooIterator1 = FooList.Find(TestFoo1);
			TestFooIterator2 = FooList.Find(TestFoo2);
			FooList.Remove(TestFooIterator1, TestFooIterator2);
			Assert::AreEqual(FooList.GetSize(), 2U);
		}
		TEST_METHOD(VECTOR_ITERATOR_COPYCONSTRUCTOR)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			IntIterator = IntList.begin();
			Vector<int>::Iterator TestIntIter = IntIterator;
			Assert::IsTrue(*TestIntIter == *IntIterator);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			IntPtrIterator = IntPtrList.begin();
			Vector<int*>::Iterator TestPtrIter = IntPtrIterator;
			Assert::IsTrue(*TestPtrIter == *IntPtrIterator);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			FooIterator = FooList.begin();
			Vector<Foo>::Iterator TestFooIter = FooIterator;
			Assert::IsTrue(*TestFooIter == *FooIterator);
		}
		TEST_METHOD(VECTOR_ITERATOR_MOVECONSTRUCTOR)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntList.PushBack(TestInt3);
			IntIterator = IntList.begin();
			Vector<int>::Iterator TestIntIter = std::move(IntIterator);
			auto functionException_Int = [&] {IntIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Int);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrList.PushBack(TestPtr3);
			IntPtrIterator = IntPtrList.begin();
			Vector<int*>::Iterator TestPtrIter = std::move(IntPtrIterator);
			auto functionException_IntPtr = [&] {IntIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_IntPtr);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooList.PushBack(TestFoo3);
			FooIterator = FooList.begin();
			Vector<Foo>::Iterator TestFooIter = std::move(FooIterator);
			auto functionException_Foo = [&] {IntIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Foo);
		}
		TEST_METHOD(VECTOR_OPERATORS)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			Vector<int> TestList = IntList;
			Assert::AreEqual(TestList.GetSize(), IntList.GetSize());
			IntList = std::move(TestList);
			Assert::AreEqual(TestList.GetSize(), 0U);
			Assert::IsTrue(IntList[0] == TestInt1);
			const Vector<int> ConstIntList = IntList;
			Assert::IsTrue(ConstIntList[0] == TestInt1);
			auto functionException_Int = [&] {ConstIntList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_Int);
			auto functionException_Int1 = [&] {IntList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_Int1);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			Vector<int*> TestPtrList = IntPtrList;
			Assert::AreEqual(TestPtrList.GetSize(), IntPtrList.GetSize());
			IntPtrList = std::move(TestPtrList);
			Assert::AreEqual(TestPtrList.GetSize(), 0U);
			Assert::IsTrue(IntPtrList[0] == TestPtr1);
			const Vector<int*> ConstIntPtrList = IntPtrList;
			Assert::IsTrue(ConstIntPtrList[0] == TestPtr1);
			auto functionException_IntPtr = [&] {ConstIntPtrList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_IntPtr);
			auto functionException_Int1Ptr = [&] {IntPtrList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_Int1Ptr);

			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			Vector<Foo> TestFooList = FooList;
			Assert::AreEqual(TestFooList.GetSize(), FooList.GetSize());
			FooList = std::move(TestFooList);
			Assert::AreEqual(TestFooList.GetSize(), 0U);
			Assert::IsTrue(FooList[0] == TestFoo1);
			const Vector<Foo> ConstFooList = FooList;
			Assert::IsTrue(ConstFooList[0] == TestFoo1);
			auto functionException_Foo = [&] {ConstFooList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_Foo);
			auto functionException_Foo1 = [&] {FooList.operator[](10); };
			Assert::ExpectException<std::exception>(functionException_Foo1);
		}
		TEST_METHOD(VECTOR_ITERATOR_OPERATORS)
		{
			IntList.PushBack(TestInt1);
			IntList.PushBack(TestInt2);
			IntIterator = IntList.begin();
			Assert::IsTrue(*IntIterator == TestInt1);
			Vector<int>::Iterator TestIntIterator = IntList.begin();
			Assert::IsTrue(*TestIntIterator == TestInt1);
			IntIterator = std::move(TestIntIterator);
			auto functionException_Int = [&] {TestIntIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Int);
			Assert::IsTrue(IntIterator != TestIntIterator);
			IntList.PushBack(TestInt3);
			TestIntIterator = IntList.Find(TestInt3);
			IntList.PopBack();
			Assert::ExpectException<std::exception>(functionException_Int);
			IntList.PushBack(TestInt3);
			IntIterator = IntList.begin();
			IntIterator++;
			Assert::IsTrue(*IntIterator == TestInt2);
			++IntIterator;
			Assert::IsTrue(*IntIterator == TestInt3);
			++IntIterator;
			auto functionException_Int2 = [&] {IntIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Int2);

			IntPtrList.PushBack(TestPtr1);
			IntPtrList.PushBack(TestPtr2);
			IntPtrIterator = IntPtrList.begin();
			Assert::IsTrue(*IntPtrIterator == TestPtr1);
			Vector<int*>::Iterator TestPtrIterator = IntPtrList.begin();
			Assert::IsTrue(*TestPtrIterator == TestPtr1);
			IntPtrIterator = std::move(TestPtrIterator);
			auto functionException_IntPtr = [&] {TestPtrIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_IntPtr);
			Assert::IsTrue(IntPtrIterator != TestPtrIterator);
			IntPtrList.PushBack(TestPtr3);
			TestPtrIterator = IntPtrList.Find(TestPtr3);
			IntPtrList.PopBack();
			Assert::ExpectException<std::exception>(functionException_IntPtr);
			IntPtrList.PushBack(TestPtr3);
			IntPtrIterator = IntPtrList.begin();
			IntPtrIterator++;
			Assert::IsTrue(*IntPtrIterator == TestPtr2);
			++IntPtrIterator;
			Assert::IsTrue(*IntPtrIterator == TestPtr3);
			++IntPtrIterator;
			auto functionException_IntPtr2 = [&] {IntPtrIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_IntPtr2);

			TestFoo1.setData(1);
			TestFoo2.setData(2);
			TestFoo3.setData(3);
			FooList.PushBack(TestFoo1);
			FooList.PushBack(TestFoo2);
			FooIterator = FooList.begin();
			Assert::IsTrue(*FooIterator == TestFoo1);
			Vector<Foo>::Iterator TestFooIterator = FooList.begin();
			Assert::IsTrue(*TestFooIterator == TestFoo1);
			FooIterator = std::move(TestFooIterator);
			auto functionException_Foo = [&] {TestFooIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Foo);
			Assert::IsTrue(FooIterator != TestFooIterator);
			FooList.PushBack(TestFoo3);
			TestFooIterator = FooList.Find(TestFoo3);
			FooList.PopBack();
			Assert::ExpectException<std::exception>(functionException_Foo);
			FooList.PushBack(TestFoo3);
			FooIterator = FooList.begin();
			FooIterator++;
			Assert::IsTrue(*FooIterator == TestFoo2);
			++FooIterator;
			Assert::IsTrue(*FooIterator == TestFoo3);
			++FooIterator;
			auto functionException_Foo2 = [&] {FooIterator.operator*(); };
			Assert::ExpectException<std::exception>(functionException_Foo2);

		}
	private:
		static Vector<int> IntList;
		static Vector<int>::Iterator IntIterator;
		static Vector<Foo> FooList;
		static Vector<Foo>::Iterator FooIterator;
		static Vector<int*> IntPtrList;
		static Vector<int*>::Iterator IntPtrIterator;
		int TestInt1 = 1;
		int TestInt2 = 2;
		int TestInt3 = 3;
		int *TestPtr1 = &TestInt1;
		int *TestPtr2 = &TestInt2;
		int *TestPtr3 = &TestInt3;
		Foo TestFoo1;
		Foo TestFoo2;
		Foo TestFoo3;
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState VectorTest::sStartMemState;
#endif
	 Vector<int> VectorTest::IntList;
	 Vector<int>::Iterator VectorTest::IntIterator;
	 Vector<Foo> VectorTest::FooList;
	 Vector<Foo>::Iterator VectorTest::FooIterator;
	 Vector<int*> VectorTest::IntPtrList;
	 Vector<int*>::Iterator VectorTest::IntPtrIterator;
};