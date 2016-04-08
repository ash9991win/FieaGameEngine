#include "pch.h"
#include "Entity.h"
#include"Sector.h"
#include"WorldState.h"
#include"Action.h"
namespace Library
{
	RTTI_DEFINITIONS(Entity)
#pragma warning(disable : 4592)
		std::string Entity::ActionArea = "Actions";
#pragma warning(default : 4592)
	Entity::Entity()
		:EntityName()
	{
		AddExternalSignature("Name", &EntityName, 1);
	}
	void  Entity::SetName(const std::string& newname)
	{
		EntityName = newname;
	}
	const std::string& Entity::Name() const
	{
		return EntityName;
	}
	 Sector* Entity::GetSector() 
	{
		assert(GetParent() != nullptr);
		return (GetParent()->As<Sector>());
	}
	void Entity::SetSector(Sector& sector)
	{
		sector.Adopt(*this, Sector::EntityArea);
		if (sector.entityDatum == nullptr)
		{
			sector.entityDatum = sector.Find(Sector::EntityArea);
		}
	}
	void Entity::Update(WorldState& state)
	{
		state.entity = this;
		Datum* actionDatum = Find(ActionArea);
		if (actionDatum)
		{
			for (std::uint32_t i = 0; i < actionDatum->GetSize(); i++)
			{
				Action* action = actionDatum->GetScope(i).As<Action>();
				action->Update(state);
			}
		}
	}
	Datum* Entity::Actions()
	{
		Datum* actionDatum = Find(ActionArea);
		return actionDatum;
	}
	Action * Entity::CreateAction(std::string actionName, std::string instanceName)
	{
		Action* createdAction = Factory<Action>::Create(actionName);
		assert(createdAction != nullptr);
		createdAction->SetName(instanceName);
		createdAction->SetEntity(*this);
		return createdAction;
	}
	Action * Entity::FindAction(const std::string & name)
	{
		Datum* actions = Find(ActionArea);
		if (!actions)
			return nullptr;
		Action* actionToFind = nullptr;
		for (std::uint32_t i = 0; i < actions->GetSize(); i++)
		{
			actionToFind = actions->GetScope(i).As<Action>();
			if (actionToFind->Name() == name)
			{
				return actionToFind;
			}
		}
		return nullptr;
	}
	void Entity::DestroyAction(std::string name)
	{
		Action* actionToDestroy = FindAction(name);
		if (actionToDestroy)
		{
			actionToDestroy->Orphan();
			delete actionToDestroy;
		}
	}
}
