#pragma once
#include "Action.h"
namespace Library
{
	/*!
	\class ActionCreateAction
	\brief This action creates an action of the given type and updates it
	*/
	class ActionCreateAction :
		public Action
	{
	public:
		/*!
		\fn ActionCreateAction()
		\brief The constructor of the create action
		*/
		ActionCreateAction();
		/*!
		\fn ~ActionCreateAction()
		\brief The destructor of the create aciton
		*/
		~ActionCreateAction() = default;
		/*!
		\fn GetPrototypeName()
		\brief returns the prototype name of the action that was created
		\return The name of the prototyped action
		*/
		const std::string& GetPrototypeName() const;
		/*!
		\fn GetActionName()
		\brief Returns the name of the action that was created based on a prototype
		\return The name of the action created
		*/
		const std::string& GetActionName() const;
		/*!
		\fn SetPrototypeName(name)
		\brief Sets the name of the prototype to be created
		\param The name of the prototype from which the action has to be created
		*/
		void SetPrototypeName(const std::string& name);
		/*
		\fn SetActionName(name)
		\brief Sets the created action's name
		\param the name of the created action
		*/
		void SetActionName(const std::string& name);
		/*!
		\fn Update(State)
		\brief The overriden update which creates an action every step
		\param The world state reference
		*/
		virtual void Update(WorldState & state) override;
		ActionCreateAction(const ActionCreateAction& rhs) = delete;
		ActionCreateAction& operator=(const ActionCreateAction& rhs) = delete;
	private: 
		/*!
		\var PrototypeName
		\brief The name of the prototype to be created from
		*/
		std::string PrototypeName;
		/*!
		\var ActionName
		\brief The name of the action that has to be created
		*/
		std::string ActionName;
	};
}
