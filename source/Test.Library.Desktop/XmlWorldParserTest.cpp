#include "pch.h"
#include "CppUnitTest.h"
#include<string>
#include"Factory.h"
#include"XmlTableParser.h"
#include"XmlPrimitiveParser.h"
#include"XmlEntityParser.h"
#include"XmlSectorParser.h"
#include"XmlWorldParser.h"
#include"XmlActionIfParser.h"
#include"XmlActionParser.h"
#include"XmlActionExpressionParser.h"
#include"World.h"
#include"Sector.h"
#include"Entity.h"
#include"FooAction.h"
#include"MonsterEntity.h"
#include"WorldState.h"
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
	TEST_CLASS(XmlWorldParserTest)
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
		TEST_METHOD(XML_Parse)
		{
			CONCRETEFACTORY(Entity, RTTI)
				EntityFactory e;
			CONCRETEFACTORY(MonsterEntity, RTTI)
				MonsterEntityFactory m;
			ActionFactory(FooAction)
				FooActionFactory f;
			Scope scopeToRead;
			XmlTableParser::SharedData sharedData(scopeToRead);
			XmlParseMaster parseMaster(sharedData);
			XmlEntityParser entityParser;
			XmlWorldParser worldParser;
			XmlSectorParser sectorParser;
			XmlPrimitiveParser primitiveParser;
			XmlActionParser actionParser;
			XmlActionIfParser actionIfParser;
			XmlActionExpressionParser expressionParser;
			parseMaster.AddHelper(worldParser);
			parseMaster.AddHelper(sectorParser);
			parseMaster.AddHelper(entityParser);
			parseMaster.AddHelper(primitiveParser);
			parseMaster.AddHelper(actionParser);
			parseMaster.AddHelper(actionIfParser);
			parseMaster.AddHelper(expressionParser);
			parseMaster.ParseFromFile("Contents/WorldTestXml.xml");
			std::string str = scopeToRead.ToString();
			str;
			World* world = scopeToRead[0].Get<Scope*>()->As<World>();
			Sector *sectors = world->Sectors()->Get<Scope*>()->As<Sector>();
			;
			Entity* entity = sectors->Entities()->Get<Scope*>()->As<Entity>();
			entity;
			sectors->CreateEntity("Entity", "Monster");
			world->CreateSector("TestSector2");
			Sector* testSector2 = world->FindSector("TestSector2");
			testSector2;
			Entity* entityFound = world->FindEntity("Monster");
			entityFound;
			WorldState state;
			world->Update(state);
			MonsterEntity* monsterEntity = world->FindEntity("flyingMonster")->As<MonsterEntity>();
			monsterEntity;
			Assert::IsTrue(sectors->GetParent() == world);
			IXmlParseHelper* clonedWorldParser = worldParser.Clone();
			IXmlParseHelper* clonedSectorParser = sectorParser.Clone();
			IXmlParseHelper* clonedEntityParser = entityParser.Clone();
			Entity* testEntity = world->FindEntity("entityTest");
			Datum& action = *(testEntity->Actions());
			action;
			delete clonedEntityParser;
			delete clonedSectorParser;
			delete clonedWorldParser;

			std::string errorXML = { "<entityTest/>" };
			Assert::ExpectException<std::exception>([&] {parseMaster.Parse(errorXML.c_str(), (int)errorXML.length(), 1); });
			
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XmlWorldParserTest::sStartMemState;
#endif
};