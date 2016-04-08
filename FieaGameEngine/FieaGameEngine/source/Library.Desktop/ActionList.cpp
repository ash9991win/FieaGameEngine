#include "pch.h"
#include "ActionList.h"
#include"WorldState.h"
namespace Library
{
	RTTI_DEFINITIONS(ActionList)
#pragma warning(disable : 4592)
	std::string ActionList::ActionsInListArea = "ActionsInList";
#pragma warning(default : 4592)
	void ActionList::Update(WorldState & state)
	{
		Datum* actions = ContainedActions();
		for (std::uint32_t i = 0; i < actions->GetSize(); i++)
		{
			Action* currentAction = actions->GetScope(i).As<Action>();
			assert(currentAction != nullptr);
			state.Action = currentAction;
			currentAction->Update(state);
		}
	}

	Datum* ActionList::ContainedActions()
	{
		Datum* actions = Find(ActionsInListArea);
		return actions;
	}

	Action * ActionList::CreateActionInList(const std::string& className, const std::string& instanceName)
	{
		Action* actionCreated = Factory<Action>::Create(className);
		assert(actionCreated != nullptr);
		actionCreated->SetActionList(*this);
		return actionCreated;
	}

}