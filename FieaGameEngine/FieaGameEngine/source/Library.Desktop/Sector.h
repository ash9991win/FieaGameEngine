#pragma once
#include"Attributed.h"
namespace Library
{
	class Entity;
	class World;
	class WorldState;
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector,Attributed)
	public:
		/*!
		\fn Sector()
		\brief The constructor of the sector
		*/
		Sector();
		/*!
		\fn Sector(name)
		\brief The parameterized constructor that sets the name of the sector
		\param The name of the sector
		*/
		Sector(const std::string& name);
		Sector(const Sector& rhs) = delete;
		Sector& operator=(const Sector& rhs) = delete;
		~Sector() = default;
		/*!
		\fn Name()
		\brief Returns the name of the sector
		*/
		const std::string& Name() const;
		/*!
		\fn SetName(newName)
		\brief Sets the name of the sector
		\param The new name of the sector
		*/
		void setName(std::string newname);
		/*!
		\fn Entities()
		\brief Returns the datum reference of the entities contained in the sector
		\return Returns the datum reference of the entities in the sector. Throws an exception if no entities are found
		*/
		Datum* Entities() ;
		/*!
		\fn CreateEntity(classname,instancename)
		\brief Creates an entity of the given class type with the name of the instance 
		\return Returns the address for the entity that was created
		*/
		Entity* CreateEntity(std::string ClassName, std::string InstanceName);
		/*!
		\fn FindEntity(name)
		\brief Finds the entity in the sector
		\param The name of the entity to find
		\return Returns the address of the entity to be found ( null if not found)
		*/
		Entity* FindEntity(std::string name);
		/*!
		\fn SetWorld(world)
		\brief Sets the world as the sector's world
		\param The reference to the world to be set as the sector's parent
		*/
		void SetWorld(World& world);
		/*!
		\fn GetWorld()
		\brief Returns the world that the sector is contained in
		\return The address of the world
		*/
		World* GetWorld();
		/*!
		\fn Update(state)
		\brief Updates the entities contained in the sector
		\param The worldState reference 
		*/
		void Update(WorldState& state);
		static const std::string EntityArea;
	private:
		std::string SectorName;
		Datum* entityDatum;
		friend class Entity;
	};
	
}