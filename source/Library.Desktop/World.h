#pragma once
#include"Attributed.h"
namespace Library
{
	class Sector;
	class WorldState;
	class Entity;
	class EventQueue;
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World,Attributed)
	public:
		/*!
		\fn World()
		\brief The constructor which initializes the world
		*/
		World();
		/*!
		\fn World(name)
		\brief The constructor which initialzies the world with the given name
		\param The name of the world
		*/
		explicit World(const std::string& name);
		World(const World& rhs) = delete;
		World& operator=(const World& rhs) = delete;
		~World() = default;
		/*!
		\fn Name()
		\brief Gets the name of the world
		\return Returns the name of the world
		*/
		const std::string& Name() const;
		/*!
		\fn SetName(name)
		\brief Sets the name of the world
		\param The name of the world
		*/
		void SetName(const std::string& newname);
		/*!
		\fn Sectors()
		\brief Returns the sectors in the world
		\return Returns a datum with the sectors in the world
		*/
		Datum* Sectors();
		/*!
		\fn CreateSector(name)
		\brief Creates the sector with the given name
		\return Returns the created sector 
		\param The name of the sector to be created
		*/
		Sector& CreateSector(const std::string& sectorName);
		/*!
		\fn FindSector(name)
		\brief Finds the given sector in the world
		\param the name of the sector to find
		\return The address of the sector that was found
		*/
		Sector* FindSector(const std::string& name);
		/*
		\fn FindEntity(name)
		\brief Finds the entity in the world
		\return Returns the entity to be found
		\name THe name of the entity to be found
		*/
		Entity* FindEntity(const std::string& name);
		/*!
		\fn Update(state)
		\brief Updates the world with the world state
		\param THe worldstate to be updated
		*/
		void Update(WorldState& state);
		const static std::string SectorArea;
		const EventQueue& GetQueue() const;
		void SetQueue(EventQueue& queue);
	private:
		std::string WorldName;
		Datum* sectorDatum;
		friend class Sector;
		EventQueue* Queue;
	};
}