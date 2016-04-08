#include "pch.h"
#include "CppUnitTest.h"
#include"World.h"
#include"Factory.h"
#include"Sector.h"
#include"Entity.h"
#include<string>
#include"WorldState.h"
#include"Factory.h"
#include"Action.h"
#include"ActionCreateAction.h"
#include"ActionDestroy.h"
#include"ActionExpression.h"
#include"ActionList.h"
#include"ActionListIf.h"
#include"FooAction.h"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;
namespace TestLibraryDesktop
{
	TEST_CLASS(ActionTest)
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

		TEST_METHOD(ActionTests)
		{
			WorldState state;
			Entity entity;
			entity.SetName("TestEntity");
			ActionFactory(FooAction)
				FooActionFactory f;
			ActionList list;
			list.SetName("TestactionList");
			FooAction foo;
			foo.SetName("FooAction");
			foo.SetActionList(list);
			list.SetEntity(entity);
			foo.Update(state);
			list.Update(state);
			list.CreateActionInList("FooAction", "FooTest2");
			Assert::IsTrue(list.ContainedActions()->GetSize() == 2U);
			Assert::IsTrue(foo.Name() == "FooAction");
			Assert::IsTrue(foo.GetEntity() == nullptr);
			Assert::IsTrue(foo.GetActionList()->Name() == list.Name());
		}
		TEST_METHOD(ActionCreateTests)
		{
			ActionFactory(FooAction)
				FooActionFactory f;
			WorldState state;
			Entity entity;
			ActionCreateAction createAction;
			createAction.SetPrototypeName("FooAction");
			createAction.SetActionName("FooActionInstance");
			createAction.SetEntity(entity);
			createAction.Update(state);
			Assert::IsTrue(createAction.GetPrototypeName() == "FooAction");
			Assert::IsTrue(createAction.GetActionName() == "FooActionInstance");
		}
		TEST_METHOD(ActionIfTests)
		{
			WorldState state;
			ActionFactory(FooAction)
				FooActionFactory f;
			Entity entity;
			ActionListIf ifList;
			ifList.SetCondition(1);
			Assert::ExpectException<std::exception>([&] {ifList.Update(state); });
			ifList.CreateThenAction("FooAction", "FooThen");
			ifList.CreateElseAction("FooAction", "FooElse");
			ifList.Update(state);
			ifList.SetCondition(0);
			ifList.Update(state);
			Assert::IsTrue(ifList.GetCondition() == 0U);
		}
		TEST_METHOD(ActionDestroyTests)
		{
			WorldState state;
			ActionFactory(FooAction)
				FooActionFactory f;
			Entity entity;
			FooAction* foo = new FooAction();
			foo->SetName("fooDestroy");
			foo->SetEntity(entity);
			ActionDestroy destroyAction;
			destroyAction.SetEntityToDestroy(entity);
			destroyAction.SetActionName("fooDestroy");
			destroyAction.Update(state);
		}
		TEST_METHOD(ActionExpressionTests)
		{
			ActionFactory(FooAction)
				FooActionFactory f;
			WorldState state;
			Vector<std::string> correctExpression = { "1","2","+","3","*","18","/","++","6","%" };
			Vector<std::string> incorrectUnaryExpression = { "++" };
			Vector<std::string> incorrectBinaryExpression = { "1","+" };
			Vector<std::string> incorrectOperationExpression = { ":" };
			Datum targetDatumFloat;
			targetDatumFloat.SetType(Datum::DatumType::FLOAT);
			Datum targetDatumInt;
			targetDatumInt.SetType(Datum::DatumType::INTEGER);
			ActionExpression expression;
			expression.SetTarget(targetDatumFloat);
			expression.setExpression(correctExpression);
			expression.Update(state);
			Assert::IsTrue(targetDatumFloat.Get<float>(0) == 0);
			expression.SetTarget(targetDatumInt);
			expression.Update(state);
			Assert::IsTrue(targetDatumInt.Get<int>(0) == 0);
			expression.setExpression(incorrectUnaryExpression);
			expression.SetTarget(targetDatumFloat);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
			expression.setExpression(incorrectOperationExpression);
			expression.SetTarget(targetDatumFloat);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
			expression.setExpression(incorrectOperationExpression);
			expression.SetTarget(targetDatumFloat);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
			expression.setExpression(incorrectBinaryExpression);
			expression.SetTarget(targetDatumInt);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
			expression.setExpression(incorrectUnaryExpression);
			expression.SetTarget(targetDatumInt);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
			expression.setExpression(incorrectOperationExpression);
			expression.SetTarget(targetDatumInt);
			Assert::ExpectException<std::exception>([&] {expression.Update(state); });
		}
		TEST_METHOD(Actions_RTTI)
		{

			FooAction testWorld;
			RTTI* testRTTI = &testWorld;
			uint64_t staticID = FooAction::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(FooAction::TypeName() == "FooAction");
			Assert::IsTrue(testWorld.Is(staticID));
			Assert::IsFalse(testWorld.Is(0));
			Assert::IsTrue(testWorld.Is("FooAction"));
			Assert::IsFalse(testWorld.Is("TEST"));
			Assert::IsTrue(testWorld.QueryInterface(0) == nullptr);
			Assert::IsTrue(testWorld.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testWorld.ToString() != "");
			Assert::IsTrue(testWorld.Equals(testRTTI));
		}
		TEST_METHOD(ActionIf_RTTI)
		{

			ActionListIf testWorld;
			RTTI* testRTTI = &testWorld;
			uint64_t staticID = ActionListIf::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(ActionListIf::TypeName() == "ActionListIf");
			Assert::IsTrue(testWorld.Is(staticID));
			Assert::IsFalse(testWorld.Is(0));
			Assert::IsTrue(testWorld.Is("ActionListIf"));
			Assert::IsFalse(testWorld.Is("TEST"));
			Assert::IsTrue(testWorld.QueryInterface(0) == nullptr);
			Assert::IsTrue(testWorld.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testWorld.ToString() != "");
			Assert::IsTrue(testWorld.Equals(testRTTI));
		}
		TEST_METHOD(ActionListIf_RTTI)
		{

			ActionList testWorld;
			RTTI* testRTTI = &testWorld;
			uint64_t staticID = ActionList::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(ActionList::TypeName() == "ActionList");
			Assert::IsTrue(testWorld.Is(staticID));
			Assert::IsFalse(testWorld.Is(0));
			Assert::IsTrue(testWorld.Is("ActionList"));
			Assert::IsFalse(testWorld.Is("TEST"));
			Assert::IsTrue(testWorld.QueryInterface(0) == nullptr);
			Assert::IsTrue(testWorld.QueryInterface(staticID) != nullptr);
			Assert::IsTrue(testWorld.ToString() != "");
			Assert::IsTrue(testWorld.Equals(testRTTI));
		}
		TEST_METHOD(ActionExpression_RTTI)
		{

			ActionExpression testWorld;
			RTTI* testRTTI = &testWorld;
			uint64_t staticID = ActionExpression::TypeIdClass();
			Assert::IsTrue(testRTTI->TypeIdInstance() == staticID);
			Assert::IsTrue(ActionExpression::TypeName() == "ActionExpression");
			Assert::IsTrue(testWorld.Is(staticID));
			Assert::IsFalse(testWorld.Is(0));
			Assert::IsTrue(testWorld.Is("ActionExpression"));
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
	_CrtMemState ActionTest::sStartMemState;
#endif

}