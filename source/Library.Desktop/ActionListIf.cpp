#include "pch.h"
#include "ActionListIf.h"
#include "WorldState.h"
namespace Library
{
#pragma warning(disable : 4592)
	std::string ActionListIf::ActionElseArea = "else";
	std::string ActionListIf::ActionThenArea = "then";
#pragma warning(default : 4592)
	RTTI_DEFINITIONS(ActionListIf)
	ActionListIf::ActionListIf()
		:ThenActions(nullptr),ElseActions(nullptr)
	{
		AddExternalSignature("Condition", &Condition, 1U);
	}

	int Library::ActionListIf::GetCondition()
	{
		return Condition;
	}
	Action * ActionListIf::CreateThenAction(const std::string& className, const std::string& InstanceName)
	{
		Action* ifAction = Factory<Action>::Create(className);
		assert(ifAction != nullptr);
		ifAction->SetName(InstanceName);
		Adopt(*ifAction, ActionThenArea);
		return ifAction;
	}

	Action * ActionListIf::CreateElseAction(const std::string& className, const std::string& InstanceName)
	{
		Action* ifAction = Factory<Action>::Create(className);
		assert(ifAction != nullptr);
		ifAction->SetName(InstanceName);
		Adopt(*ifAction, ActionElseArea);
		return ifAction;
	}

	void ActionListIf::SetCondition(int condition)
	{
		Condition = condition;
	}

	void ActionListIf::Update(WorldState & state)
	{

		if (ThenActions == nullptr)
		{
			ThenActions = Find(ActionThenArea);
		}
		if (ElseActions == nullptr)
		{
			ElseActions = Find(ActionElseArea);
		}
		if (Condition)
		{
			if (!ThenActions)
			{
				throw std::exception("If cannot be without then");
			}
			for (std::uint32_t i = 0; i < ThenActions->GetSize(); i++)
			{
				Action* action = ThenActions->GetScope(i).As<Action>();
				state.Action = action;
				action->Update(state);
			}
		}
		else
		{
			if (ElseActions)
			{
				for (std::uint32_t i = 0; i < ElseActions->GetSize(); i++)
				{
					Action* action = ElseActions->GetScope(i).As<Action>();
					state.Action = action;
					action->Update(state);
				}
			}
		}
	}
}