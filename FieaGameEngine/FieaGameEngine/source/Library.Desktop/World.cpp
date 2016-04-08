#include "pch.h"
#include "World.h"
#include"Sector.h"
#include"Factory.h"
#include"WorldState.h"
#include"Entity.h"
#include "EventQueue.h"
namespace Library
{

	RTTI_DEFINITIONS(World)
#pragma warning(disable : 4592)
	const std::string World::SectorArea = "Sector";
#pragma warning(default : 4592)
	World::World()
		:WorldName(),sectorDatum(nullptr),Queue(nullptr)
	{
		AddExternalSignature("Name", &WorldName, 1);
	}
	World::World(const std::string& name)
		:World()
	{
		WorldName = name;
	}
	const std::string& World::Name() const
	{
		return WorldName;
	}
	void World::SetName(const std::string& newname)
	{
		WorldName = newname;
	}
	Datum* World::Sectors()
	{
		if (sectorDatum == nullptr)
		{
			sectorDatum = Find(SectorArea);
		}
		return sectorDatum;
	}
	Sector& World::CreateSector(const std::string& sectorName)
	{
		Sector *createdSector = new Sector(sectorName);
		createdSector->SetWorld(*this);
		if (sectorDatum == nullptr)
		{
			sectorDatum = Find(SectorArea);
		}
		return *createdSector;
	}
	Sector * World::FindSector(const std::string& name)
	{
		if (!sectorDatum)
			return nullptr;

		for (std::uint32_t i = 0; i < sectorDatum->GetSize(); i++)
		{
			Scope* currentScope = sectorDatum->Get<Scope*>(i);
			if (currentScope != nullptr)
			{
				Sector* sector = currentScope->As<Sector>();
				if (sector && sector->Name() == name)
				{
					return sector;
				}
			}
		}
		return nullptr;
	}
	Entity * World::FindEntity(const std::string& name)
	{
		Entity* entity = nullptr;
		Datum* sectors = (Sectors());
		for (std::uint32_t i = 0; i < sectors->GetSize(); i++)
		{
			Sector* currentSector = sectors->GetScope(i).As<Sector>();
			entity = currentSector->FindEntity(name);
			if (entity != nullptr)
				return entity;
		}

		return entity;
	}
	void World::Update(WorldState& state)
	{
		state.world = this;
		Datum* sectors = Sectors();
		for (std::uint32_t i = 0; i < sectors->GetSize(); i++)
		{
			Sector* sector = sectors->GetScope(i).As<Sector>();
			sector->Update(state);
		}
		if (Queue)
		{
			Queue->Update(state.GetGameTime());
		}
	}

	const EventQueue & World::GetQueue() const
	{
		return *Queue;
	}

	void World::SetQueue(EventQueue & queue)
	{
		Queue = &queue;
	}

}