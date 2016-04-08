#include "pch.h"
#include "CppUnitTest.h"
#include "Attributed.h"
#include"AttributedFoo.h"
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
	TEST_CLASS(AttributedTest)
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
		TEST_METHOD(ATTRIBUTED_COPY)
		{
			AttributedFoo f;
			AttributedFoo f2(f);
			Assert::IsTrue(f.Size() == f2.Size());
			Assert::IsTrue(f["Scope"] == f2["Scope"]);
			AttributedFoo f3;
			f3 = f2;
			Assert::IsTrue(f3.Size() == f2.Size());
			Assert::IsTrue(f3["Scope"] == f2["Scope"]);
		}
		TEST_METHOD(ATTRIBUTED_MOVE)
		{
			AttributedFoo f;
			AttributedFoo f2 = std::move(f);
			Assert::IsTrue(f.Size() == 0U);
			Assert::AreEqual(f2.Size(), 14U);
			Assert::IsTrue(f2.Find("Scope") != nullptr);
		}
		TEST_METHOD(ATTRIBUTED_ISPRESCRIBED)
		{
			AttributedFoo f;
			f["Auxilliary"] = "Auxilliary";
			Assert::IsTrue(f.IsPrescribedAttribute("i"));
			Assert::IsFalse(f.IsPrescribedAttribute("Auxilliary"));
		}
		TEST_METHOD(ATTRIBUTED_ISATTRIBUTE)
		{
			AttributedFoo f;
			f["Auxilliary"] = "Auxilliary";
			Assert::IsTrue(f.IsAttribute("i"));
			Assert::IsTrue(f.IsAttribute("Auxilliary"));
		}
		TEST_METHOD(ATTRIBUTED_ISAUXILLIARY)
		{
			AttributedFoo f;
			f["Auxilliary"] = "Auxilliary";
			Assert::IsFalse(f.IsAuxilliaryAttribute("i"));
			Assert::IsTrue(f.IsAuxilliaryAttribute("Auxilliary"));
		}
		TEST_METHOD(ATTRIBURED_APPENDAUXILLIARY)
		{
			AttributedFoo f;
			f.AppendAuxilliaryAttribute("Auxilliary") = 5;
			Assert::IsTrue(f.IsAuxilliaryAttribute("Auxilliary"));
			Assert::IsTrue(f.Find("Auxilliary") != nullptr);
			Assert::ExpectException<std::exception>([&] {f.AppendAuxilliaryAttribute("i"); });
		}
		TEST_METHOD(ATTRIBUTED_AUXILLIARYBEGIN)
		{
			AttributedFoo f;
			AttributedBar b;
			Assert::AreEqual(f.AuxilliaryBegin(), 15U);
			Assert::AreEqual(b.AuxilliaryBegin() , 17U);
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState AttributedTest::sStartMemState;
#endif
}