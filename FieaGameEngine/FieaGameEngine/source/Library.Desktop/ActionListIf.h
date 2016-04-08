#pragma once
#include "ActionList.h"
namespace Library
{
	/*!
	\class ActionListIf
	\brief The if action class
	*/
	class ActionListIf :
		public ActionList
	{
		RTTI_DECLARATIONS(ActionListIf,ActionList)
	public:
		/*!
		\fn ActionListIf()
		\brief The constructor
		*/
		ActionListIf();
		~ActionListIf() = default;
		/*!
		\fn GetCondition()
		\brief Returns the condition that gets checked
		\return Returns the condition
		*/
		int GetCondition();
		/*!
		\fn CreateThenAction(className,InstanceName)
		\brief Creates a then action for the current list
		\param The name of the class form which the action has to be created
		\param The name of the aciton created
		*/
		Action* CreateThenAction(const std::string& className,const std::string& InsanceName);
		/*!
		\fn CreateElseAction(className,InstanceName)
		\brief Creates an else action for the current list
		\param The name of the class form which the action has to be created
		\param The name of the aciton created
		*/
		Action* CreateElseAction(const std::string& className,const std::string& InstanceName);
		/*!
		\fn SetCondition(int condition)
		\brief Sets the condition to be checked
		\param The condition to be checked
		*/
		void SetCondition(int condition);
		/*!
		\fn Update(state)
		\brief The override update method
		\param The worldstate reference
		*/
		virtual void Update(WorldState& state) override;
		/*
		\var ActionThenArea
		\brief The name under which all the then actions are stored
		*/
		static std::string ActionThenArea;
		/*!
		\var ActionElseArea
		\brief The name under which all the else actions are stored
		*/
		static std::string ActionElseArea;
		ActionListIf(const ActionListIf& rhs) = delete;
		ActionListIf& operator=(const ActionListIf& rhs) = delete;
	private:
		/*
		\var Condition 
		\brief The condition which is checked
		*/
		int Condition;
		/*!
		\var ThenActions
		\brief The datum that holds all the then actions
		*/
		Datum* ThenActions;
		/*!
		\var ElseActions
		\brief The datum that holds all the else actions
		*/
		Datum* ElseActions;
	};
}
