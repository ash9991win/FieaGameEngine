#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"TestXmlParserFoo.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(XmlParserTest)
	{
	public:
#if defined(DEBUG) || defined(_DEBUG)

		TEST_METHOD_INITIALIZE(XML_INIT)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}
		TEST_METHOD_CLEANUP(XML_CLEANUP)
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
		TEST_METHOD(XML_Depth)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);
			Assert::ExpectException<std::exception>([&] {FooData.DecrementDepth(); });
			Assert::IsTrue(FooData.GetDepth() == 0U);
		}
		TEST_METHOD(XML_Clone)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);
			
			testParser.AddHelper(FooTest);
			testParser.ParseFromFile("Contents/TestFooXml.xml");
			Assert::IsTrue(FooData.getHealth() == 100);
			XmlParseMaster *masterclone = testParser.Clone();
			Assert::IsTrue(masterclone->GetSharedData().As<TestXmlParserFoo::SharedFooData>()->getHealth() == 100);
			Assert::ExpectException<std::exception>([&] {masterclone->AddHelper(FooTest); });
			delete masterclone;
		}
		TEST_METHOD(XML_Parse)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);

			testParser.AddHelper(FooTest);
			testParser.ParseFromFile("Contents/TestFooXml.xml");
			Assert::IsTrue(FooData.getHealth() == 100);
			Assert::IsTrue(FooData.getName() == "Eagle");
			Assert::IsTrue(FooData.getCategory() == "FlyingMonster");
		}
		TEST_METHOD(XML_RemoveHelper)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);

			testParser.AddHelper(FooTest);
			testParser.AddHelper(FooTest);
			testParser.RemoveHelper(FooTest);
		}
		TEST_METHOD(XML_GetFileName)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);

			testParser.AddHelper(FooTest);
			testParser.ParseFromFile("Contents/TestFooXml.xml");
			Assert::IsTrue("Contents/TestFooXml.xml" == testParser.GetFileName());
		}
		TEST_METHOD(XML_SetSharedData)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);

			testParser.AddHelper(FooTest);
			testParser.ParseFromFile("Contents/TestFooXml.xml");
			XmlParseMaster *CloneMaster1 = testParser.Clone();
			TestXmlParserFoo::SharedFooData* FooData1 = FooData.Clone();
			CloneMaster1->SetSharedData(*FooData1);
			delete CloneMaster1;

		}
		TEST_METHOD(XML_Reset)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			XmlParseMaster testParser(FooData);

			testParser.AddHelper(FooTest);
			testParser.ParseFromFile("Contents/TestFooXml.xml");
			testParser.Reset();
			Assert::IsTrue(testParser.GetFileName() == "");
			Assert::IsTrue(FooData.getHealth() == 0);
		}
		TEST_METHOD(XML_Rtti)
		{
			TestXmlParserFoo FooTest;
			TestXmlParserFoo::SharedFooData FooData;
			RTTI* testRTTI = &FooData;
			uint64_t staticID = TestXmlParserFoo::SharedFooData::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(TestXmlParserFoo::SharedFooData::TypeName() == "SharedFooData");
			Assert::IsTrue(FooData.Is(staticID));
			Assert::IsFalse(FooData.Is(0));
			Assert::IsTrue(FooData.Is("SharedFooData"));
			Assert::IsFalse(FooData.Is("TEST"));
			Assert::IsTrue(FooData.QueryInterface(0) == nullptr);
			Assert::IsTrue(FooData.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(FooData.ToString() == "RTTI");
			Assert::IsTrue(FooData.Equals(testRTTI));
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
_CrtMemState XmlParserTest::sStartMemState;
#endif
};