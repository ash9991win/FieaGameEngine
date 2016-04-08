#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"Factory.h"
#include"AttributedFoo.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(FactoryTest)
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
		TEST_METHOD(Factory_Find)
		{
		
			CONCRETEFACTORY(AttributedFoo, Attributed)
				AttributedFooFactory Foofactory;
			const Factory<Attributed>* AttrFactory = Factory<Attributed>::Find("AttributedFoo");
			Assert::IsTrue(AttrFactory != nullptr);
			const Factory<RTTI>* RttiFactory = Factory<RTTI>::Find("RTTIFoo");
			Assert::IsTrue(RttiFactory == nullptr);

		}
		TEST_METHOD(Factory_Create)
		{
			CONCRETEFACTORY(AttributedFoo,Attributed)
				AttributedFooFactory Foofactory;
			Attributed* attribute = Factory<Attributed>::Create("AttributedNull");
			Assert::IsTrue(attribute == nullptr);
			attribute = Factory<Attributed>::Create("AttributedFoo");
			Assert::IsTrue(attribute != nullptr);
			delete attribute;
		}
		TEST_METHOD(Factory_Iterator)
		{
			Assert::IsTrue(Factory<Attributed>::Begin() == Factory<Attributed>::End());
			CONCRETEFACTORY(AttributedFoo, Attributed)
				AttributedFooFactory Foofactory;
			Assert::IsTrue(Factory<Attributed>::Size() == 1U);

		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState FactoryTest::sStartMemState;
#endif
}