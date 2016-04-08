#include "pch.h"
#include "CppUnitTest.h"
#include"Stack.h"
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
	TEST_CLASS(STACK_TEST)
	{
	public:
		TEST_METHOD_INITIALIZE(STACK_INITIALIZE)
		{
			IntStack.Clear();
			Assert::AreEqual(IntStack.Size(), 0U);
			IntPtrStack.Clear();
			Assert::AreEqual(IntPtrStack.Size(), 0U);
			FooStack.Clear();
			Assert::AreEqual(FooStack.Size(), 0U);
#if defined(DEBUG) | defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}
		TEST_METHOD_CLEANUP(STACK_MEM)
		{
			IntStack.Clear();
			Assert::AreEqual(IntStack.Size(), 0U);
			IntPtrStack.Clear();
			Assert::AreEqual(IntPtrStack.Size(), 0U);
			FooStack.Clear();
			Assert::AreEqual(FooStack.Size(), 0U);
#if defined(DEBUG) | defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(STACK_COPYCONSTRUCTOR)
		{
		
			IntStack.Push(TestInt1);
			IntStack.Push(TestInt2);
			Stack<int> TestIntStack = IntStack;
			Assert::IsTrue(TestIntStack.Size() == IntStack.Size());
			Assert::IsTrue(TestIntStack.Top() == IntStack.Top());

			IntPtrStack.Push(TestPtr1);
			IntPtrStack.Push(TestPtr2);
			Stack<int*> TestIntPtrStack = IntPtrStack;
			Assert::IsTrue(TestIntPtrStack.Size() == IntPtrStack.Size());
			Assert::IsTrue(TestIntPtrStack.Top() == IntPtrStack.Top());

			FooStack.Push(TestFoo1);
			FooStack.Push(TestFoo2);
			Stack<Foo> TestFooStack = FooStack;
			Assert::IsTrue(TestFooStack.Size() == FooStack.Size());
			Assert::IsTrue(TestFooStack.Top() == FooStack.Top());
		
		}
		TEST_METHOD(STACK_MOVECONSTRUCTOR)
		{
			IntStack.Push(TestInt1);
			IntStack.Push(TestInt1);
			Stack<int> TestIntStack = std::move(IntStack);
			Assert::AreEqual(TestIntStack.Size(), 2U);
			Assert::AreEqual(IntStack.Size(), 0U);
			TestIntStack.Clear();
			IntStack.Push(TestInt1);
			IntStack.Push(TestInt1);
			TestIntStack =std::move( IntStack);
			Assert::AreEqual(TestIntStack.Size(), 2U);
			Assert::AreEqual(IntStack.Size(), 0U);

			IntPtrStack.Push(TestPtr1);
			IntPtrStack.Push(TestPtr1);
			Stack<int*> TestPtrStack = std::move(IntPtrStack);
			Assert::AreEqual(TestPtrStack.Size(), 2U);
			Assert::AreEqual(IntPtrStack.Size(), 0U);
			TestPtrStack.Clear();
			IntPtrStack.Push(TestPtr1);
			IntPtrStack.Push(TestPtr2);
			TestPtrStack = std::move(IntPtrStack);
			Assert::AreEqual(TestPtrStack.Size(), 2U);
			Assert::AreEqual(IntPtrStack.Size(), 0U);

			FooStack.Push(TestFoo1);
			FooStack.Push(TestFoo1);
			Stack<Foo> TestFooStack = std::move(FooStack);
			Assert::AreEqual(TestFooStack.Size(), 2U);
			Assert::AreEqual(FooStack.Size(), 0U);
			TestFooStack.Clear();
			FooStack.Push(TestFoo1);
			FooStack.Push(TestFoo2);
			TestFooStack = std::move(FooStack);
			Assert::AreEqual(TestFooStack.Size(), 2U);
			Assert::AreEqual(FooStack.Size(), 0U);
		}
		TEST_METHOD(STACK_PUSH)
		{
			IntStack.Push(TestInt1);
			Assert::AreEqual(IntStack.Size(), 1U);
			Assert::IsTrue(IntStack.Top() == TestInt1);

			IntPtrStack.Push(TestPtr1);
			Assert::AreEqual(IntPtrStack.Size(), 1U);
			Assert::IsTrue(IntPtrStack.Top() == TestPtr1);

			FooStack.Push(TestFoo1);
			Assert::AreEqual(FooStack.Size(), 1U);
			Assert::IsTrue(FooStack.Top() == TestFoo1);
		}
		TEST_METHOD(STACK_POP)
		{
			IntStack.Push(TestInt1);
			IntStack.Push(TestInt2);
			IntStack.Pop();
			Assert::AreEqual(IntStack.Size(), 1U);
			Assert::IsTrue(IntStack.Top() == TestInt1);

			IntPtrStack.Push(TestPtr1);
			IntPtrStack.Push(TestPtr2);
			IntPtrStack.Pop();
			Assert::AreEqual(IntPtrStack.Size(), 1U);
			Assert::IsTrue(IntPtrStack.Top() == TestPtr1);

			FooStack.Push(TestFoo1);
			FooStack.Push(TestFoo2);
			FooStack.Pop();
			Assert::AreEqual(FooStack.Size(), 1U);
			Assert::IsTrue(FooStack.Top() == TestFoo1);
		}
		TEST_METHOD(STACK_TOP)
		{
			IntStack.Push(TestInt1);
			IntStack.Push(TestInt2);
			Assert::IsTrue(IntStack.Top() == TestInt2);
			IntStack.Top() = TestInt3;
			Assert::IsTrue(IntStack.Top() == TestInt3);
			const Stack<int> TestStack = IntStack;
			Assert::IsTrue(TestStack.Top() == TestInt3);

			IntPtrStack.Push(TestPtr1);
			IntPtrStack.Push(TestPtr2);
			Assert::IsTrue(IntPtrStack.Top() == TestPtr2);
			IntPtrStack.Top() = TestPtr3;
			Assert::IsTrue(IntPtrStack.Top() == TestPtr3);
			const Stack<int*> TestPtrStack = IntPtrStack;
			Assert::IsTrue(TestPtrStack.Top() == TestPtr3);

			FooStack.Push(TestFoo1);
			FooStack.Push(TestFoo2);
			Assert::IsTrue(FooStack.Top() == TestFoo2);
			FooStack.Top() = TestFoo3;
			Assert::IsTrue(FooStack.Top() == TestFoo3);
			const Stack<Foo> TestFooStack = FooStack;
			Assert::IsTrue(TestFooStack.Top() == TestFoo3);
		}
		TEST_METHOD(STACK_SIZE)
		{
			IntStack.Push(TestInt1);
			Assert::AreEqual(IntStack.Size(), 1U);
			IntStack.Push(TestInt2);
			Assert::AreEqual(IntStack.Size(), 2U);

			IntPtrStack.Push(TestPtr1);
			Assert::AreEqual(IntPtrStack.Size(), 1U);
			IntPtrStack.Push(TestPtr2);
			Assert::AreEqual(IntPtrStack.Size(), 2U);

			FooStack.Push(TestFoo1);
			Assert::AreEqual(FooStack.Size(), 1U);
			FooStack.Push(TestFoo2);
			Assert::AreEqual(FooStack.Size(), 2U);
		}
		TEST_METHOD(STACK_ISEMPTY)
		{
			Assert::IsTrue(IntStack.IsEmpty());
			IntStack.Push(TestInt1);
			Assert::IsFalse(IntStack.IsEmpty());

			Assert::IsTrue(IntPtrStack.IsEmpty());
			IntPtrStack.Push(TestPtr1);
			Assert::IsFalse(IntPtrStack.IsEmpty());

			Assert::IsTrue(FooStack.IsEmpty());
			FooStack.Push(TestFoo1);
			Assert::IsFalse(FooStack.IsEmpty());
		}
	private:
		Stack<int> IntStack;
		Stack<int*> IntPtrStack;
		Stack<Foo> FooStack;
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
	_CrtMemState STACK_TEST::sStartMemState;
#endif
};