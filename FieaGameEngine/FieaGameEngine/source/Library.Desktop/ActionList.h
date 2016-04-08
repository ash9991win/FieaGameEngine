#pragma once
#include "Action.h"
namespace Library
{
	/*
	\class ActionList
	\brief The actionlist class 
	*/
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList,Action)
	public:
		/*!
		\fn ActionList()
		\brief The constructor
		*/
		ActionList() = default;
		virtual ~ActionList() = default;
		/*!
		\fn Update(state)
		\brief The override update method 
		\param The worldstate reference
		*/
		virtual void Update(class WorldState& state) override;
		/*!
		\fn ContainedActions()
		\brief Returns a datum of actions within this list
		\return The datum address
		*/
		Datum* ContainedActions();
		/*!
		\fn CreateActionInList(className,InstanceName)
		\brief Creates an aciton of the class className with the name Instancename in this list
		\param The name of the class from which the action has to be created
		\param The action name
		*/
		Action* CreateActionInList(const std::string& className, const std::string& instanceName);
		/*
		\var ActionsInListArea
		\brief The table where all the actionlists are located
		*/
		static std::string ActionsInListArea;
		ActionList(const ActionList& rhs) = delete;
		ActionList& operator=(const ActionList& rhs) = delete;
#define ActionListFactory(ConcreteActionList) ActionFactory(ConcreteActionList)

	};
}
