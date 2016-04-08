
#pragma once
#include "Attributed.h"
#include"Factory.h"
namespace Library
{
	class WorldState;
	class Entity;
	class ActionList;
	/*!
	\class Action
	\brief The class that represents verbs in the game world
	*/
	class Action :  public Attributed
	{
		RTTI_DECLARATIONS(Action,Attributed)
	public:
		/*
		!\fn Action()
		\brief The constructor which registers the attributes of the action
		*/
		Action();
		/*!
		\fn Update(WorldState& state)
		\brief The pure virtual function which gets called every frame
		\param WorldState reference
		*/
		virtual void Update(WorldState& state) = 0;
		/*!
		\fn Name()
		\brief Returns the name of the action
		\return The name of the action
		*/
		const std::string& Name() const;
		/*!
		\fn SetName(name)
		\brief Sets the name of the action
		\param The name of the action to be set
		*/
		void SetName(const std::string& name);
		/*!
		\fn ~Action()
		\brief The virtual destructor
		*/
		virtual ~Action() = default;
		/*!
		\fn SetEntity(entity)
		\brief Assosciates this action with an entity
		\param The entity to set as the parent of the action
		*/
		void SetEntity(Entity& entity);
		/*!
		\fn SetActionList(list)
		\brief Sets the list of actions to be done in this action
		\param The actionlist reference
		*/
		void SetActionList(ActionList& list);
		/*
		\fn GetEntity()
		\brief Gets the entity assosciated with this action
		\return The entity ( null if not found)
		*/
		Entity* GetEntity();
		/*
		\fn GetActionList()
		\brief Returns the list of actions contained in this action
		\return Returns the list of actions (null if none found)
		*/
		ActionList* GetActionList();
		Action(const Action& rhs) = delete;
		Action& operator=(const Action& rhs) = delete;
	private:
		/*
		\var ActionName
		\brief The name of the action
		*/
		std::string ActionName;
	};
#define ActionFactory(ConcreteAction) CONCRETEFACTORY(ConcreteAction,Action)

}

