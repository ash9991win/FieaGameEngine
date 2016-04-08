#include "pch.h"
#include "CppUnitTest.h"
#include"Hashmap.h"
#include<string>
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
	class FooHash
	{
	public:
		std::uint32_t operator()(const Foo& key)
		{
			const char* Bytes = reinterpret_cast<const char*>(&key);
			std::uint32_t Hash = 0;
			for (int i = 0; i < sizeof(key); i++)
			{
				Hash ^= Bytes[i];
			}
			return Hash ;
		}
	};
	TEST_CLASS(HashTest)
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
		TEST_METHOD(HASHMAP_MOVECONSTRUCTOR)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			TestIntMap1.Insert(TestInt3);
			Hashmap<int, int> TestIntMap2 = std::move(TestIntMap1);
			Assert::AreEqual(TestIntMap1.Count(), 0U);
			Assert::AreEqual(TestIntMap2.Count(), 3U);

			Hashmap<int*, int> TestIntPtrMap1;
			TestIntPtrMap1.Insert(TestPtr1);
			TestIntPtrMap1.Insert(TestPtr2);
			TestIntPtrMap1.Insert(TestPtr3);
			Hashmap<int*, int> TestIntPtrMap2 = std::move(TestIntPtrMap1);
			Assert::AreEqual(TestIntPtrMap1.Count(), 0U);
			Assert::AreEqual(TestIntPtrMap2.Count(), 3U);

			Hashmap<char*, int> TestCharPtrMap1;
			TestCharPtrMap1.Insert(TestChar1);
			TestCharPtrMap1.Insert(TestChar2);
			TestCharPtrMap1.Insert(TestChar3);
			Hashmap<char*, int> TestCharPtrMap2 = std::move(TestCharPtrMap1);
			Assert::AreEqual(TestIntPtrMap1.Count(), 0U);
			Assert::AreEqual(TestIntPtrMap2.Count(), 3U);


			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			TestStringMap1.Insert(TestString3);
			Hashmap<std::string,int> TestStringMap2 = std::move(TestStringMap1);
			Assert::AreEqual(TestIntPtrMap1.Count(), 0U);
			Assert::AreEqual(TestIntPtrMap2.Count(), 3U);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			TestFooMap1.Insert(TestFoo3);
			Hashmap<Foo, int,FooHash> TestFooMap2 = std::move(TestFooMap1);
			Assert::AreEqual(TestIntPtrMap1.Count(), 0U);
			Assert::AreEqual(TestIntPtrMap2.Count(), 3U);
		}
		TEST_METHOD(HASHMAP_FIND)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a,a);
			Foo bFoo(b,b);
			Foo cFoo(c,c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			Hashmap<int, int>::Iterator TestIntIter = TestIntMap1.Find(TestInt2.first);
			Assert::IsTrue(TestIntIter->first == TestInt2.first);
			TestIntIter = TestIntMap1.Find(TestInt3.first);
			Assert::IsTrue(TestIntIter == TestIntMap1.end());

			Hashmap<int*, int> TestIntPtrMap1;
			TestIntPtrMap1.Insert(TestPtr1);
			TestIntPtrMap1.Insert(TestPtr2);
			Hashmap<int*, int>::Iterator TestPtrIter = TestIntPtrMap1.Find(TestPtr2.first);
			Assert::IsTrue(TestPtrIter->first == TestPtr2.first);
			TestPtrIter = TestIntPtrMap1.Find(TestPtr3.first);
			Assert::IsTrue(TestPtrIter == TestIntPtrMap1.end());

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			Hashmap<char*, int>::Iterator TestCharIter = TestCharMap1.Find(TestChar2.first);
			Assert::IsTrue(TestCharIter->first == TestChar2.first);
			TestCharIter = TestCharMap1.Find(TestChar3.first);
			Assert::IsTrue(TestCharIter == TestCharMap1.end());

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			Hashmap<std::string,int>::Iterator TestStringIter = TestStringMap1.Find(TestString2.first);
			Assert::IsTrue(TestStringIter->first == TestString2.first);
			TestStringIter = TestStringMap1.Find(TestString3.first);
			Assert::IsTrue(TestStringIter == TestStringMap1.end());

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			Assert::IsTrue(TestFooMap1.ContainsKey(TestFoo1.first));
			Assert::IsFalse(TestFooMap1.ContainsKey(TestFoo3.first));
		}
		TEST_METHOD(HASHMAP_INSERT)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a,a);
			Foo bFoo(b,b);
			Foo cFoo(c,c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			Hashmap<int, int>::Iterator TestIntIter = TestIntMap1.Find(TestInt2.first);
			Assert::IsTrue(TestIntIter->first == TestInt2.first);
			TestIntIter = TestIntMap1.Insert(TestInt1);
			Assert::IsTrue(TestIntIter->second == TestInt1.second);

			Hashmap<int*, int> TestIntPtrMap1;
			TestIntPtrMap1.Insert(TestPtr1);
			TestIntPtrMap1.Insert(TestPtr2);
			Hashmap<int*, int>::Iterator TestPtrIter = TestIntPtrMap1.Find(TestPtr2.first);
			Assert::IsTrue(TestPtrIter->first == TestPtr2.first);
			TestPtrIter = TestIntPtrMap1.Insert(TestPtr1);
			Assert::IsTrue(TestPtrIter->second == TestPtr1.second);

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			Hashmap<char*, int>::Iterator TestCharIter = TestCharMap1.Find(TestChar2.first);
			Assert::IsTrue(TestCharIter->first == TestChar2.first);
			TestCharIter = TestCharMap1.Insert(TestChar1);
			Assert::IsTrue(TestCharIter->second == TestChar1.second);

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			Hashmap<std::string,int>::Iterator TestStringIter = TestStringMap1.Find(TestString2.first);
			Assert::IsTrue(TestStringIter->first == TestString2.first);
			TestStringIter = TestStringMap1.Insert(TestString1);
			Assert::IsTrue(TestStringIter->second == TestString1.second);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			Hashmap<Foo, int,FooHash>::Iterator TestFooIter = TestFooMap1.Find(TestFoo2.first);
			Assert::IsTrue(TestFooIter->first == TestFoo2.first);
			TestFooIter = TestFooMap1.Insert(TestFoo1);
			Assert::IsTrue(TestFooIter->second == TestFoo1.second);
		}
		TEST_METHOD(HASHMAP_REMOVE)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			TestIntMap1.Insert(TestInt3);
			TestIntMap1.Remove(TestInt2.first);
			Assert::IsTrue(TestIntMap1.Find(TestInt2.first) == TestIntMap1.end());

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			TestPtrMap1.Insert(TestPtr2);
			TestPtrMap1.Insert(TestPtr3);
			TestPtrMap1.Remove(TestPtr2.first);
			Assert::IsTrue(TestPtrMap1.Find(TestPtr2.first) == TestPtrMap1.end());

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			TestCharMap1.Insert(TestChar3);
			TestCharMap1.Remove(TestChar2.first);
			Assert::IsTrue(TestCharMap1.Find(TestChar2.first) == TestCharMap1.end());

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			TestStringMap1.Insert(TestString3);
			TestStringMap1.Remove(TestString2.first);
			Assert::IsTrue(TestStringMap1.Find(TestString2.first) == TestStringMap1.end());

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			TestFooMap1.Insert(TestFoo3);
			TestFooMap1.Remove(TestFoo2.first);
			Assert::IsTrue(TestFooMap1.Find(TestFoo2.first) == TestFooMap1.end());
		}
		TEST_METHOD(HASHMAP_CLEAR)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			TestIntMap1.Insert(TestInt3);
			TestIntMap1.Clear();
			Assert::AreEqual(TestIntMap1.Count(),0U);

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			TestPtrMap1.Insert(TestPtr2);
			TestPtrMap1.Insert(TestPtr3);
			TestPtrMap1.Clear();
			Assert::AreEqual(TestPtrMap1.Count(), 0U);

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			TestCharMap1.Insert(TestChar3);
			TestCharMap1.Clear();
			Assert::AreEqual(TestCharMap1.Count(), 0U);

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			TestStringMap1.Insert(TestString3);
			TestStringMap1.Clear();
			Assert::AreEqual(TestStringMap1.Count(), 0U);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			TestFooMap1.Insert(TestFoo3);
			TestFooMap1.Clear();
			Assert::AreEqual(TestFooMap1.Count(), 0U);
		}

		TEST_METHOD(HASHMAP_CONTAINSKEY)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			Assert::IsTrue(TestIntMap1.ContainsKey(TestInt1.first));
			Assert::IsFalse(TestIntMap1.ContainsKey(TestInt3.first));

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			TestPtrMap1.Insert(TestPtr2);
			Assert::IsTrue(TestPtrMap1.ContainsKey(TestPtr1.first));
			Assert::IsFalse(TestPtrMap1.ContainsKey(TestPtr3.first));

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			Assert::IsTrue(TestCharMap1.ContainsKey(TestChar1.first));
			Assert::IsFalse(TestCharMap1.ContainsKey(TestChar3.first));

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			Assert::IsTrue(TestStringMap1.ContainsKey(TestString1.first));
			Assert::IsFalse(TestStringMap1.ContainsKey(TestString3.first));

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			Assert::IsTrue(TestFooMap1.ContainsKey(TestFoo1.first));
			Assert::IsFalse(TestFooMap1.ContainsKey(TestFoo3.first));
		}
		TEST_METHOD(HASHMAP_BEGIN)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			Hashmap<int, int>::Iterator TestIntIter = TestIntMap1.begin();
			Assert::IsTrue(TestIntIter == TestIntMap1.end());
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			TestIntIter = TestIntMap1.begin();
			Assert::IsTrue(TestIntIter->first == TestInt1.first);

			Hashmap<int*, int> TestPtrMap1;
			Hashmap<int*, int>::Iterator TestPtrIter = TestPtrMap1.begin();
			Assert::IsTrue(TestPtrIter == TestPtrMap1.end());
			TestPtrMap1.Insert(TestPtr1);
			TestPtrIter = TestPtrMap1.begin();
			Assert::IsTrue(TestPtrIter->second == TestPtr1.second);

			Hashmap<char*, int> TestCharMap1;
			Hashmap<char*, int>::Iterator TestCharIter = TestCharMap1.begin();
			Assert::IsTrue(TestCharIter == TestCharMap1.end());
			TestCharMap1.Insert(TestChar1);
			TestCharIter = TestCharMap1.begin();
			Assert::IsTrue((*TestCharIter).first == TestChar1.first);

			Hashmap<std::string,int> TestStringMap1;
			Hashmap<std::string,int>::Iterator TestStringIter = TestStringMap1.begin();
			Assert::IsTrue(TestStringIter == TestStringMap1.end());
			TestStringMap1.Insert(TestString1);
			TestStringIter = TestStringMap1.begin();
			Assert::IsTrue(TestStringIter->first == TestString1.first);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			Hashmap<Foo, int,FooHash>::Iterator TestFooIter = TestFooMap1.begin();
			Assert::IsTrue(TestFooIter == TestFooMap1.end());
			TestFooMap1.Insert(TestFoo1);
			TestFooIter = TestFooMap1.begin();
			Assert::IsTrue(TestFooIter->first == TestFoo1.first);
		}
		TEST_METHOD(HASHMAP_REHASH)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;	
			TestIntMap1.Insert(TestInt1);
			TestIntMap1.Insert(TestInt2);
			Assert::AreEqual(TestIntMap1.Size(), 11U);
			TestIntMap1.ReHash(17U);
			Assert::AreEqual(TestIntMap1.Size(), 17U);
			Assert::IsTrue(TestIntMap1.ContainsKey(TestInt1.first));

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			TestPtrMap1.Insert(TestPtr2);
			Assert::AreEqual(TestPtrMap1.Size(), 11U);
			TestPtrMap1.ReHash(17U);
			Assert::AreEqual(TestPtrMap1.Size(), 17U);
			Assert::IsTrue(TestPtrMap1.ContainsKey(TestPtr1.first));

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1.Insert(TestChar2);
			Assert::AreEqual(TestCharMap1.Size(), 11U);
			TestCharMap1.ReHash(17U);
			Assert::AreEqual(TestCharMap1.Size(), 17U);
			Assert::IsTrue(TestCharMap1.ContainsKey(TestChar1.first));

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1.Insert(TestString2);
			Assert::AreEqual(TestStringMap1.Size(), 11U);
			TestStringMap1.ReHash(17U);
			Assert::AreEqual(TestStringMap1.Size(), 17U);
			Assert::IsTrue(TestStringMap1.ContainsKey(TestString1.first));

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1.Insert(TestFoo2);
			Assert::AreEqual(TestFooMap1.Size(), 11U);
			TestFooMap1.ReHash(17U);
			Assert::AreEqual(TestFooMap1.Size(), 17U);
		}
		TEST_METHOD(HASHMAP_OPERATORS)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			TestIntMap1[TestInt1.first] = TestInt2.second;
			Assert::IsTrue(TestIntMap1.begin()->second == TestInt2.second);
			TestIntMap1[TestInt3.first] = TestInt3.second;
			Assert::IsTrue(TestIntMap1.ContainsKey(TestInt3.first));

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			TestPtrMap1[TestPtr1.first] = TestPtr2.second;
			Assert::IsTrue(TestPtrMap1.begin()->second == TestPtr2.second);
			TestPtrMap1[TestPtr3.first] = TestPtr3.second;
			Assert::IsTrue(TestPtrMap1.ContainsKey(TestPtr3.first));

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			TestCharMap1[TestChar1.first] = TestChar2.second;
			Assert::IsTrue(TestCharMap1.begin()->second == TestChar2.second);
			TestCharMap1[TestChar3.first] = TestChar3.second;
			Assert::IsTrue(TestCharMap1.ContainsKey(TestChar3.first));

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			TestStringMap1[TestString1.first] = TestString2.second;
			Assert::IsTrue(TestStringMap1.begin()->second == TestString2.second);
			TestStringMap1[TestString3.first] = TestString3.second;
			Assert::IsTrue(TestStringMap1.ContainsKey(TestString3.first));

			/*Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			TestFooMap1[TestFoo1.first] = TestFoo2.second;
			Assert::IsTrue(TestFooMap1.begin()->second == TestFoo2.second);
			TestFooMap1[TestFoo3.first] = TestFoo3.second;
			Assert::IsTrue(TestFooMap1.ContainsKey(TestFoo3.first));*/
		
		}
		TEST_METHOD(HASHMAP_ITER_MOVECTOR)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			Hashmap<int, int>::Iterator TestIntIter = TestIntMap1.begin();
			Hashmap<int, int>::Iterator TestIntIter2 = std::move(TestIntIter);
			Assert::IsTrue(TestIntIter2->second == TestInt1.second);

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			Hashmap<int*, int>::Iterator TestPtrIter = TestPtrMap1.begin();
			Hashmap<int*, int>::Iterator TestPtrIter2 = std::move(TestPtrIter);
			Assert::IsTrue(TestPtrIter2->second == TestPtr1.second);

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			Hashmap<char*, int>::Iterator TestCharIter = TestCharMap1.begin();
			Hashmap<char*, int>::Iterator TestCharIter2 = std::move(TestCharIter);
			Assert::IsTrue(TestCharIter2->second == TestChar1.second);

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			Hashmap<std::string,int>::Iterator TestStringIter = TestStringMap1.begin();
			Hashmap<std::string,int>::Iterator TestStringIter2 = std::move(TestStringIter);
			Assert::IsTrue(TestStringIter2->second == TestString1.second);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			Hashmap<Foo, int,FooHash>::Iterator TestFooIter = TestFooMap1.begin();
			Hashmap<Foo, int,FooHash>::Iterator TestFooIter2 = std::move(TestFooIter);
			Assert::IsTrue(TestFooIter2->second == TestFoo1.second);
		}
		TEST_METHOD(HASHMAP_ITER_OPERATORS)
		{
			int a = 1;
			int b = 2;
			int c = 3;
			int *aptr = &a;
			int *bptr = &b;
			int *cptr = &c;
			char* achar = "Test1";
			char* bchar = "Test2";
			char* cchar = "Test3";
			string astring = "Test1";
			string bstring = "Test2";
			string cstring = "Test3";
			Foo aFoo(a, a);
			Foo bFoo(b, b);
			Foo cFoo(c, c);
			std::pair<int, int>  TestInt1 = std::pair<int, int>(a, b);
			std::pair<int, int>  TestInt2 = std::pair<int, int>(b, c);
			std::pair<int, int>  TestInt3 = std::pair<int, int>(c, a);
			std::pair<int*, int> TestPtr1 = std::pair<int*, int>(aptr, a);
			std::pair<int*, int> TestPtr2 = std::pair<int*, int>(bptr, b);
			std::pair<int*, int> TestPtr3 = std::pair<int*, int>(cptr, c);
			std::pair<char*, int> TestChar1 = std::pair<char*, int>(achar, a);
			std::pair<char*, int> TestChar2 = std::pair<char*, int>(bchar, b);
			std::pair<char*, int> TestChar3 = std::pair<char*, int>(cchar, c);
			std::pair<std::string,int> TestString1 = std::pair<std::string,int>(astring, a);
			std::pair<std::string,int> TestString2 = std::pair<std::string,int>(bstring, b);
			std::pair<std::string,int> TestString3 = std::pair<std::string,int>(cstring, c);
			std::pair<Foo, int>  TestFoo1 = std::pair<Foo, int>(aFoo, a);
			std::pair<Foo, int>  TestFoo2 = std::pair<Foo, int>(bFoo, b);
			std::pair<Foo, int>  TestFoo3 = std::pair<Foo, int>(cFoo, c);

			Hashmap<int, int> TestIntMap1;
			TestIntMap1.Insert(TestInt1);
			Hashmap<int, int>::Iterator TestIntIter;
			auto FunctionException_TestInt = [&] {TestIntIter.operator++(); };
			Assert::ExpectException<std::exception>(FunctionException_TestInt);
			TestIntIter = TestIntMap1.begin();
			TestIntIter++;
			Assert::IsTrue(TestIntIter == TestIntMap1.end());
			auto FunctionException_TestInt1 = [&] {TestIntIter.operator*(); };
			Assert::ExpectException<std::exception>(FunctionException_TestInt1);
			auto FunctionException_TestInt2 = [&] {TestIntIter.operator->(); };
			Assert::ExpectException<std::exception>(FunctionException_TestInt2);
			TestIntIter = TestIntMap1.begin();
			Assert::IsTrue((*TestIntIter) == TestInt1);
			Assert::IsTrue((TestIntIter->first) == TestInt1.first);

			Hashmap<int*, int> TestPtrMap1;
			TestPtrMap1.Insert(TestPtr1);
			Hashmap<int*, int>::Iterator TestPtrIter;
			auto FunctionException_TestPtr = [&] {TestPtrIter.operator++(); };
			Assert::ExpectException<std::exception>(FunctionException_TestPtr);
			TestPtrIter = TestPtrMap1.begin();
			TestPtrIter++;
			Assert::IsTrue(TestPtrIter == TestPtrMap1.end());
			auto FunctionException_TestPtr1 = [&] {TestPtrIter.operator*(); };
			Assert::ExpectException<std::exception>(FunctionException_TestPtr1);
			auto FunctionException_TestPtr2 = [&] {TestPtrIter.operator->(); };
			Assert::ExpectException<std::exception>(FunctionException_TestPtr2);
			TestPtrIter = TestPtrMap1.begin();
			Assert::IsTrue((*TestPtrIter) == TestPtr1);
			Assert::IsTrue((TestPtrIter->first) == TestPtr1.first);

			Hashmap<char*, int> TestCharMap1;
			TestCharMap1.Insert(TestChar1);
			Hashmap<char*, int>::Iterator TestCharIter;
			auto FunctionException_TestChar = [&] {TestCharIter.operator++(); };
			Assert::ExpectException<std::exception>(FunctionException_TestChar);
			TestCharIter = TestCharMap1.begin();
			TestCharIter++;
			Assert::IsTrue(TestCharIter == TestCharMap1.end());
			auto FunctionException_TestChar1 = [&] {TestCharIter.operator*(); };
			Assert::ExpectException<std::exception>(FunctionException_TestChar1);
			auto FunctionException_TestChar2 = [&] {TestCharIter.operator->(); };
			Assert::ExpectException<std::exception>(FunctionException_TestChar2);
			TestCharIter = TestCharMap1.begin();
			Assert::IsTrue((*TestCharIter) == TestChar1);
			Assert::IsTrue((TestCharIter->first) == TestChar1.first);

			Hashmap<std::string,int> TestStringMap1;
			TestStringMap1.Insert(TestString1);
			Hashmap<std::string,int>::Iterator TestStringIter;
			auto FunctionException_TestString = [&] {TestStringIter.operator++(); };
			Assert::ExpectException<std::exception>(FunctionException_TestString);
			TestStringIter = TestStringMap1.begin();
			TestStringIter++;
			Assert::IsTrue(TestStringIter == TestStringMap1.end());
			auto FunctionException_TestString1 = [&] {TestStringIter.operator*(); };
			Assert::ExpectException<std::exception>(FunctionException_TestString1);
			auto FunctionException_TestString2 = [&] {TestStringIter.operator->(); };
			Assert::ExpectException<std::exception>(FunctionException_TestString2);
			TestStringIter = TestStringMap1.begin();
			Assert::IsTrue((*TestStringIter) == TestString1);
			Assert::IsTrue((TestStringIter->first) == TestString1.first);

			Hashmap<Foo, int,FooHash> TestFooMap1;
			TestFooMap1.Insert(TestFoo1);
			Hashmap<Foo, int,FooHash>::Iterator TestFooIter;
			auto FunctionException_TestFoo = [&] {TestFooIter.operator++(); };
			Assert::ExpectException<std::exception>(FunctionException_TestFoo);
			TestFooIter = TestFooMap1.begin();
			TestFooIter++;
			Assert::IsTrue(TestFooIter == TestFooMap1.end());
			auto FunctionException_TestFoo1 = [&] {TestFooIter.operator*(); };
			Assert::ExpectException<std::exception>(FunctionException_TestFoo1);
			auto FunctionException_TestFoo2 = [&] {TestFooIter.operator->(); };
			Assert::ExpectException<std::exception>(FunctionException_TestFoo2);
			TestFooIter = TestFooMap1.begin();
			Assert::IsTrue((*TestFooIter) == TestFoo1);
			Assert::IsTrue((TestFooIter->first) == TestFoo1.first);
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	 _CrtMemState HashTest::sStartMemState;
#endif
}