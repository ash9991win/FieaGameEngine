#include "pch.h"
#include "CppUnitTest.h"
#include"Scope.h"
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
	TEST_CLASS(ScopeTest)
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
		TEST_METHOD(SCOPE_COPYANDASSIGNMENT)
		{
			Scope s1;
			s1.Append("A");
			s1["A"] = 5;
			Scope s2;
			s2 = s1;
			s1.Append("B");
			Assert::IsTrue(s2.Find("B") == nullptr);
			s1.AppendScope("C");
			s1.AppendScope("C");
			s1.AppendScope("B");
			Scope s3 = s1;
			s2 = s1;
			Assert::IsTrue(*(s2.Find("B")) == *(s1.Find("B")));
			Assert::IsTrue(s2 == s1);
			Assert::IsFalse(s2 != s1);
		}
		TEST_METHOD(SCOPE_MOVESEMANTICS)
		{
			Scope TestScope1;
			Scope TestScope2;
			TestScope1.Append("A");
			TestScope1.AppendScope("Scope");
			TestScope1.AppendScope("Scope");
			Scope* childScope = new Scope();
			Scope* childScopeNew = new Scope();
			childScope->Adopt(*childScopeNew, "subchild");
			TestScope1.Adopt(*childScope, "CHild");
			Scope* childScope2 = new Scope();
			TestScope1.Adopt(*childScope2, "CHild");
			TestScope2 = std::move(TestScope1);
			Assert::IsTrue(TestScope2.Size() == 3U);
			Assert::IsTrue(TestScope1.Size() == 0U);
			Scope TestScope3 = std::move(TestScope2);
			Assert::IsTrue(TestScope3.Size() == 3U);
			Assert::IsTrue(TestScope2.Size() == 0U);
		}
		TEST_METHOD(SCOPE_FIND)
		{
			Scope TestScope1;
			TestScope1.Append("A");
			TestScope1.Append("B");
			TestScope1.AppendScope("SCOPE");
			Assert::IsTrue(TestScope1.Find("C") == nullptr);
			Assert::IsTrue(TestScope1.Find("A") != nullptr);
			Assert::IsTrue(TestScope1.Find("SCOPE") != nullptr);
			Assert::ExpectException<std::exception>([&] {TestScope1.Find(""); });
		}
		TEST_METHOD(SCOPE_SEARCH)
		{
			Scope a;
			Scope *b = new Scope();
			Scope *c = new Scope();
			Scope *d = new Scope();
			d->AppendScope("D");
			c->AppendScope("C");
			b->AppendScope("B");
			a.AppendScope("A");

			c->Adopt(*d, "CD");
			b->Adopt(*c, "BC");
			a.Adopt(*b, "AB");
			const Scope *testPtr = nullptr;
			Datum *found = d->Search("A", &testPtr);
			Assert::IsTrue(testPtr != nullptr);
			Assert::IsTrue(found != nullptr);
			Assert::IsTrue(a.Find("A") == found);
			Assert::IsTrue(*testPtr == a);
		}
		TEST_METHOD(SCOPE_APPEND)
		{
			Scope TestScope1;
			TestScope1.Append("A");
			TestScope1.Append("B");
			Assert::IsTrue(TestScope1.Size() == 2U);
			TestScope1.Append("A");
			Assert::IsTrue(TestScope1.Size() == 2U);
		}
		TEST_METHOD(SCOPE_APPENDSCOPE)
		{
			Scope TestScope1;
			TestScope1.Append("A").SetType(Datum::DatumType::INTEGER);
			Assert::ExpectException<std::exception>([&] {TestScope1.AppendScope("A"); });
			TestScope1.AppendScope("New Scope");
			TestScope1.AppendScope("New Scope");
			Assert::IsTrue(TestScope1.Size() == 2U);
		}
		TEST_METHOD(SCOPE_ADOPT)
		{
			Scope a;
			Scope *b = new Scope();
			Scope *c = new Scope();
			Scope *d = new Scope();
			Scope *e = new Scope();
			d->Adopt(*e, "DE");
			c->Adopt(*d, "CD");
			Assert::ExpectException<std::exception>([&] {c->Adopt(*c, "CD"); });
			a.Adopt(*b, "AB");
			a.Adopt(*c, "AB");
			Assert::IsTrue(a.Size() == 1U);
		}
		TEST_METHOD(SCOPE_GETPARENT)
		{
			Scope a;
			Assert::IsTrue(a.GetParent() == nullptr);
			Scope *b = new Scope();
			a.Adopt(*b, "Adopt");
			Assert::IsTrue((*(b->GetParent())) == a);
		}
		TEST_METHOD(SCOPE_OPERATORS)
		{
			Scope a;
			a.Append("HI");
			a["Hi"] = 5;
			a.AppendScope("ASASA");
			a.AppendScope("ASASA");
			a.AppendScope("Scope 2");
			a.AppendScope("Scope 2");
			Assert::IsTrue(a["Hi"].Type() == Datum::DatumType::INTEGER);
			Assert::IsTrue(a[0].Type() == Datum::DatumType::UNASSIGNED);
			Assert::ExpectException<std::exception>([&] {a.operator[](7U); });

			Scope a1;
			a1.Append("A");
			a1.AppendScope("Scope");
			a1.AppendScope("Scope");
			Scope *b = new Scope();
			b->AppendScope("Scope 1");
			b->AppendScope("Scope 1");
			b->AppendScope("Scope 2");
			b->AppendScope("Scope 3");
			a1 = *b;
			Assert::IsTrue(a1 == *b);
			Assert::IsTrue(!(a1 != *b));
			delete b;
		}
		TEST_METHOD(SCOPE_FINDNAME)
		{
			Scope a;
			a.AppendScope("HI");
			Scope *b = new Scope();
			b->AppendScope("Test");
			a.Adopt(*b, "Adopted");
			Assert::IsTrue(a.FindName(b) == "Adopted");
		}
		TEST_METHOD(SCOPE_CLEAR)
		{
			Scope a;
			a.Append("Integer");
			a["Integer"] = 1;
			a.Append("Float");
			a["Float"] = 3.14f;
			a.Append("String");
			a["String"] = "Test";
			Scope *b = new Scope();
			Scope *c = new Scope();
			c->Append("C");
			b->Adopt(*c, "BC");
			a.Adopt(*b, "AB");
			a.AppendScope("AB");
			a.Clear();
			Assert::IsTrue(a.Size() == 0U);
			Scope scope;
			Datum& findDatum = scope.Append("HI");
			Scope *newScope = new Scope();
			findDatum.PushBack(*newScope);
			scope.Clear();
		}
		TEST_METHOD(SCOPE_ORPHAN)
		{
			Scope a;
			a.Append("Integer");
			a.Orphan();
			Scope *b = new Scope();
			Scope *c = new Scope();
			c->Append("C");
			b->Adopt(*c, "BC");
			a.Adopt(*b, "AB");

			Assert::IsTrue((*(b->GetParent())) == a);
			b->Orphan();
			Assert::IsTrue(b->GetParent() == nullptr);
			delete b;
		}
		TEST_METHOD(SCOPE_RTTI)
		{
			Scope s;
			s.Append("S1");
			s.AppendScope("Scope");
			s.AppendScope("Scope");
			Scope s2 = s;
			Assert::IsTrue(s2.Equals(&s));
			RTTI* testRTTI = &s;
			std::uint64_t staticID = Scope::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(Scope::TypeName() == "Scope");
			Assert::IsTrue(s.Is(staticID));
			Assert::IsTrue(s.Is("Scope"));
			class TestClass : public Scope
			{

			};
			TestClass testClass;
			Assert::IsTrue(testClass.Is("Scope"));
			Assert::IsTrue(testClass.Is(staticID));
			RTTI* rttiQuery = s.QueryInterface(staticID);
			Assert::IsTrue(rttiQuery->Is("Scope"));
			rttiQuery = s.QueryInterface(0);
			Assert::IsTrue(rttiQuery == nullptr);
			std::string scopeString = s.ToString();
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ScopeTest::sStartMemState;
#endif
}