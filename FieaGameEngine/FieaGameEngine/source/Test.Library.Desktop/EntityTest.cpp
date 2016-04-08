#include "pch.h"
#include "CppUnitTest.h"
#include"World.h"
#include"Factory.h"
#include"Sector.h"
#include"Entity.h"
#include<string>
#include"WorldState.h"
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(EntityTest)
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
		TEST_METHOD(Entity_Tests)
		{
			Sector testSector("TestSector");
			Entity testEntity;
			testEntity.SetName("TestEntity");
			Assert::IsTrue(testEntity.Name() == "TestEntity");
			testEntity.SetSector(testSector);
			Assert::IsTrue((*testEntity.GetParent()) == testSector);
		}
		TEST_METHOD(EntityRTTI)
		{
			Entity testEntity;
			RTTI* testRTTI = &testEntity;
			uint64_t staticID = Entity::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(Entity::TypeName() == "Entity");
			Assert::IsTrue(testEntity.Is(staticID));
			Assert::IsFalse(testEntity.Is(0));
			Assert::IsTrue(testEntity.Is("Entity"));
			Assert::IsFalse(testEntity.Is("TEST"));
			Assert::IsTrue(testEntity.QueryInterface(0) == nullptr);
			Assert::IsTrue(testEntity.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testEntity.ToString() != "");
			Assert::IsTrue(testEntity.Equals(testRTTI));
		}
		
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EntityTest::sStartMemState;
#endif
	TEST_CLASS(WorldTest)
	{
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
		TEST_METHOD(WorldTests)
		{
			CONCRETEFACTORY(Entity, RTTI)
				EntityFactory f;
			World testWorld("testWorld");
			Assert::IsTrue(testWorld.Name() == "testWorld");
			testWorld.SetName("testWorld1");
			testWorld.CreateSector("testSector");
			Datum& sectors = *(testWorld.Sectors());
			Assert::IsTrue(sectors.GetScope().As<Sector>()->Name() == "testSector");
			Assert::IsTrue(testWorld.FindSector("testSector") != nullptr);
			Assert::IsTrue(testWorld.FindSector("Sector1") == nullptr);
			Assert::IsTrue(testWorld.FindEntity("testEntity") == nullptr);
			sectors.GetScope().As<Sector>()->CreateEntity("Entity", "testentity");
			Assert::IsTrue(testWorld.FindEntity("testentity") != nullptr);
			WorldState state;
			testWorld.Update(state);
		}
		TEST_METHOD(WorldRTTI)
		{
			World testWorld;
			RTTI* testRTTI = &testWorld;
			uint64_t staticID = World::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(World::TypeName() == "World");
			Assert::IsTrue(testWorld.Is(staticID));
			Assert::IsFalse(testWorld.Is(0));
			Assert::IsTrue(testWorld.Is("World"));
			Assert::IsFalse(testWorld.Is("TEST"));
			Assert::IsTrue(testWorld.QueryInterface(0) == nullptr);
			Assert::IsTrue(testWorld.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testWorld.ToString() != "");
			Assert::IsTrue(testWorld.Equals(testRTTI));
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState WorldTest::sStartMemState;
#endif
	TEST_CLASS(SectorTest)
	{
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
		TEST_METHOD(SectorTests)
		{
			CONCRETEFACTORY(Entity, RTTI)
				EntityFactory e;
			World testWorld;
			Sector sector("testSector1");
			sector.setName("testSector");
			Assert::IsTrue(sector.Name() == "testSector");
			sector.CreateEntity("Entity", "testEntity");
			Datum& entities = *(sector.Entities());
			Assert::IsTrue(entities.GetSize() == 1U);
			Assert::IsTrue(sector.FindEntity("entity1") == nullptr);
			Assert::IsTrue(sector.FindEntity("testEntity") != nullptr);
			sector.SetWorld(testWorld);
			Assert::IsTrue(sector.GetWorld() != nullptr);
		}
		TEST_METHOD(SectorRTTI)
		{
			Sector testSector;
			RTTI* testRTTI = &testSector;
			uint64_t staticID = Sector::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(Sector::TypeName() == "Sector");
			Assert::IsTrue(testSector.Is(staticID));
			Assert::IsFalse(testSector.Is(0));
			Assert::IsTrue(testSector.Is("Sector"));
			Assert::IsFalse(testSector.Is("TEST"));
			Assert::IsTrue(testSector.QueryInterface(0) == nullptr);
			Assert::IsTrue(testSector.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testSector.ToString() != "");
			Assert::IsTrue(testSector.Equals(testRTTI));
		}
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif
	};
#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState SectorTest::sStartMemState;
#endif
}