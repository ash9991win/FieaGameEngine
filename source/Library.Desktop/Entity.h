#pragma once
#include"Attributed.h"
namespace Library
{
	class Sector;
	class WorldState;
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity,Attributed)
	public:
		/*!
		\fn Entity()
		\brief The parameterless constructor
		*/
		Entity();
		Entity(const Entity& rhs) = delete;
		Entity& operator=(const Entity& rhs) = delete;
		/*!
		\fn Name()
		\brief Returns the name of the entity
		\return The name of the entity
		*/
		const std::string& Name() const;
		/*!
		\fn SetName(name)
		\brief Sets the name of the entity 
		\param The new name of the entity
		*/
		void SetName(const std::string& newname);
		/*
		\fn GetSector()
		\brief Returns the sector that is owned by the entity
		\return The address of the sector that the entity owns
		*/
		 Sector* GetSector() ;
		 /*!
		 \fn SetSector()
		 \brief Sets the sector with the given value
		 \param The sector to which the entity has to be adopted
		 */
		void SetSector(Sector& sector);
		/*!
		\fn Update(state)
		\brief Updates the entity 
		\param The world state with which the entity has to be applied
		*/
		void Update(WorldState& state); 
		/*!
		\fn Actions()
		\brief Returns the actions assosicated with this entity
		\return Returns a datum address
		*/
		Datum* Actions();
		/*!
		\fn CreateAction(actionName,instanceName)
		\brief Creates an action in this entity with the given name 
		\param The name of the action type to be created
		\param The instance of the action name
		*/
		class Action* CreateAction(std::string actionName, std::string instanceName);
		virtual ~Entity() = default;
		/*!
		\fn FindAction(name)
		\brief Finds the given action in the entity
		\return The action that has been found ( null otherwise)
		\param The name of the action
		*/
		Action* FindAction(const std::string& name);
		/*!
		\fn DestroyAction(name)
		\brief Destroys the given action 
		\param The name of the action
		*/
		void DestroyAction(const std::string name);
		/*!
		\var ActionArea
		\brief The name under which all teh actions for this entity is stored
		*/
		static std::string ActionArea;
	private:
		std::string EntityName;
	};
}