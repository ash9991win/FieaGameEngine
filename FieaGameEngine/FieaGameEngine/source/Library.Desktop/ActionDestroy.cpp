#include "pch.h"
#include "ActionDestroy.h"
#include "Entity.h"
#include"WorldState.h"
namespace Library
{
	ActionDestroy::ActionDestroy()
		:ActionEntity(nullptr)
	{
		AddExternalSignature("DestroyActionName", &ActionToDestroy, 1);
	}
	void Library::ActionDestroy::Update(WorldState & state)
	{
		state.Action = this;
		if (!ActionToDestroy.empty() && ActionEntity)
		{
			ActionEntity->DestroyAction(ActionToDestroy);
		}
	}

	const std::string & Library::ActionDestroy::GetActionName() const
	{
		return ActionToDestroy;
	}

	void Library::ActionDestroy::SetActionName(const std::string & name)
	{
		ActionToDestroy = name;
	}
	void ActionDestroy::SetEntityToDestroy(Entity & entity)
	{
		ActionEntity = &entity;
	}
}