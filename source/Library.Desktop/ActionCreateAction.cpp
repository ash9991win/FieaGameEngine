#include "pch.h"
#include "ActionCreateAction.h"
#include"Entity.h"
#include"WorldState.h"
namespace Library
{
	ActionCreateAction::ActionCreateAction()
	{
		AddExternalSignature("PrototypeName", &PrototypeName, 1);
		AddExternalSignature("NewActionName", &ActionName, 1);
	}

	const std::string & ActionCreateAction::GetPrototypeName() const
	{
		return PrototypeName;
	}

	const std::string & ActionCreateAction::GetActionName() const
	{
		return ActionName;
	}

	void ActionCreateAction::SetPrototypeName(const std::string & name)
	{
		PrototypeName = name;
	}

	void ActionCreateAction::SetActionName(const std::string & name)
	{
		ActionName = name;
	}

	void Library::ActionCreateAction::Update(WorldState & state)
	{
		state.Action = this;
		if (!(PrototypeName.empty() && ActionName.empty()))
		{
			Entity* parentEntity = GetEntity();
			assert(parentEntity != nullptr);
			parentEntity->CreateAction(PrototypeName, ActionName);
		}
	}
}