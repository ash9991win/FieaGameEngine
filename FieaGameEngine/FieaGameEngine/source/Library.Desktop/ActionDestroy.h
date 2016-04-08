#pragma once
#include "Action.h"
namespace Library
{
	/*!
	\class ActionDestroy
	\brief The action which destroys an action every update
	*/
	class ActionDestroy :
		public Action
	{
	public:
		/*!
		\fn ActionDestroy()
		\brief The constructor 
		*/
		ActionDestroy();
		~ActionDestroy() = default;
		/*!
		\fn Update(state)
		\brief The override update call which destroys an action every update
		\param The worldstate reference
		*/
		virtual void Update(WorldState & state) override;
		/*!
		\fn GetActionName()
		\brief returns teh name of the action being destroyed
		\return The name of the action being destroyed
		*/
		const std::string& GetActionName() const;
		/*!
		\fn SetActionName(name)
		\brief Sets the action to be destroyed
		\param The name of teh action to be destroyed
		*/
		void SetActionName(const std::string& name);
		/*!
		\fn SetEntityToDestroy(newEntity)
		\brief Sets the entity whose action has to be destroyed
		\param the entity reference whose action has to be destroyed
		*/
		void SetEntityToDestroy(Entity&);
	private:
		/*!
		\var ActionToDestroy
		\brief The name of the action being destroyed
		*/
		std::string ActionToDestroy;
		/*!
		\var ActionEntity
		\brief The entity at which the action is present
		*/
		Entity* ActionEntity;
	};
}
