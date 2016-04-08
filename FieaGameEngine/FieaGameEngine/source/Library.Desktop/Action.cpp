#include "pch.h"
#include "Action.h"
#include"Entity.h"
#include"ActionList.h"
namespace Library
{
	RTTI_DEFINITIONS(Action)
	Action::Action()
	{
		AddExternalSignature("ActionName", &ActionName, 1);
	}
	const std::string & Action::Name() const
	{
		return ActionName;
	}
	void Action::SetName(const std::string & name)
	{
		ActionName = name;
	}
	void Action::SetEntity(Entity & entity)
	{
		entity.Adopt(*this, Entity::ActionArea);
	}
	Entity * Action::GetEntity()
	{
		assert(GetParent() != nullptr);
		return GetParent()->As<Entity>();
	}
	ActionList * Action::GetActionList()
	{
		assert(GetParent() != nullptr);
		return GetParent()->As<ActionList>();
	}
	void Action::SetActionList(ActionList& list)
	{
		list.Adopt(*this, ActionList::ActionsInListArea);
	}
}