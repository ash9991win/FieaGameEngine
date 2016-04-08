#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"XmlTableParser.h"
#include"XmlPrimitiveParser.h"
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
	TEST_CLASS(XmlTableParserTest)
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
		TEST_METHOD(XML_Reset)
		{
			Scope scopeToRead;
			XmlTableParser::SharedData sharedData(scopeToRead);
			XmlTableParser tableParser;
			XmlPrimitiveParser primitiveParser;
			XmlParseMaster xmlParser(sharedData);
			xmlParser.AddHelper(tableParser);
			xmlParser.AddHelper(primitiveParser);
			xmlParser.ParseFromFile("Contents/ScopeTestXml.xml");
			sharedData.Reset();
		}
		TEST_METHOD(XML_Clone)
		{
			Scope scopeToRead;
			XmlTableParser::SharedData sharedData(scopeToRead);
			XmlTableParser tableParser;
			XmlPrimitiveParser primitiveParser;
			XmlParseMaster xmlParser(sharedData);
			xmlParser.AddHelper(tableParser);
			xmlParser.AddHelper(primitiveParser);
			xmlParser.ParseFromFile("Contents/ScopeTestXml.xml");
			XmlParseMaster* clonedMaster = xmlParser.Clone();
			IXmlParseHelper* clonedPrimitiveMaster = primitiveParser.Clone();
			IXmlParseHelper* clonedTableParser = tableParser.Clone();
			XmlTableParser::SharedData* clonedData = clonedMaster->GetSharedData().As<XmlTableParser::SharedData>();
			clonedData;
			delete clonedPrimitiveMaster;
			delete clonedTableParser;
			delete clonedMaster;
		}
		TEST_METHOD(XML_Getters)
		{
			Scope scopeToRead;
			XmlTableParser::SharedData sharedData(scopeToRead);
			XmlTableParser tableParser;
			XmlPrimitiveParser primitiveParser;
			XmlParseMaster xmlParser(sharedData);
			xmlParser.AddHelper(tableParser);
			xmlParser.AddHelper(primitiveParser);
			xmlParser.ParseFromFile("Contents/ScopeTestXml.xml");
			Scope sharedDataScope = sharedData.GetScope();
			std::string readS = scopeToRead.ToString();
			Assert::IsTrue(sharedDataScope.Find("TestScope") != nullptr);
		}
		TEST_METHOD(XML_Parse)
		{
			Scope scopeToRead;
			XmlTableParser::SharedData sharedData(scopeToRead);
			TestXmlParserFoo::SharedFooData sharedFooData;
			XmlTableParser tableParser;
			XmlParseMaster xmlParser(sharedFooData);
			xmlParser.AddHelper(tableParser);
			xmlParser.ParseFromFile("Contents/ScopeTestXml.xml");
			xmlParser.SetSharedData(sharedData);
		    Assert::ExpectException<std::exception>([&] {xmlParser.ParseFromFile("Contents/ScopeTestFaultyXML.xml"); });

		}
		TEST_METHOD(XML_Rtti)
		{
			Scope testScope;
			XmlTableParser tableTest;
			XmlTableParser::SharedData tableData(testScope);
			RTTI* testRTTI = &tableData;
			uint64_t staticID = XmlTableParser::SharedData::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(XmlTableParser::SharedData::TypeName() == "SharedData");
			Assert::IsTrue(tableData.Is(staticID));
			Assert::IsFalse(tableData.Is(0));
			Assert::IsTrue(tableData.Is("SharedData"));
			Assert::IsFalse(tableData.Is("TEST"));
			Assert::IsTrue(tableData.QueryInterface(0) == nullptr);
			Assert::IsTrue(tableData.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(tableData.ToString() == "RTTI");
			Assert::IsTrue(tableData.Equals(testRTTI));
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XmlTableParserTest::sStartMemState;
#endif
};