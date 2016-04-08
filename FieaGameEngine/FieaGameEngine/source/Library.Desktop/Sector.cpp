#include "pch.h"
#include "Sector.h"
#include"World.h"
#include"Factory.h"
#include"Entity.h"
#include"WorldState.h"
namespace Library
{
	RTTI_DEFINITIONS(Sector)
#pragma warning(disable : 4592)
		const std::string Sector::EntityArea = "Entity";
#pragma warning(default : 4592)
	Sector::Sector()
		:entityDatum(nullptr)
	{
		AddExternalSignature("Name", &SectorName, 1);
	}
	Sector::Sector(const std::string& name)
		:Sector()
	{
		SectorName = name;
	}
	const std::string& Sector::Name() const
	{
		return SectorName;
	}
	void Sector::setName(std::string newname)
	{
		SectorName = newname;
	}
	Datum* Sector::Entities() 
	{
		if (entityDatum == nullptr)
		{
			entityDatum = Find(EntityArea);
		}
		return entityDatum;
	}
	Entity* Sector::CreateEntity(std::string Classname,std::string EntityName)
	{
		RTTI* r = Factory<RTTI>::Create(Classname);
		assert(r != nullptr);
		assert(r->Is(Entity::TypeIdClass()));
		Entity* entity = static_cast<Entity*>(r);
		entity->SetName(EntityName);
		entity->SetSector(*this);
		if (entityDatum == nullptr)
			entityDatum = Find(EntityArea);
		return entity;
	}
	Entity * Sector::FindEntity(std::string name)
	{
		if (!entityDatum)
			return nullptr;
		for (std::uint32_t i = 0; i < entityDatum->GetSize(); i++)
		{
			Scope* currentScope = entityDatum->Get<Scope*>(i);
			if (currentScope != nullptr)
			{
				Entity* entity = currentScope->As<Entity>();
				if (entity != nullptr && entity->Name() == name)
				{
					return entity;
				}
			}
		}
		return nullptr;
	}

	void Sector::SetWorld(World& world)
	{
		world.Adopt(*this, World::SectorArea);
		if (world.sectorDatum == nullptr)
		{
			world.sectorDatum = world.Find(World::SectorArea);
		}
	}
	World* Sector::GetWorld()
	{
		assert(GetParent() != nullptr);
		return GetParent()->As <World>();
	}
	void Sector::Update(WorldState& state)
	{
		state.sector = this;
		Datum* entities = Find(EntityArea);
		if (entities != nullptr)
		{
			for (std::uint32_t i = 0; i < entities->GetSize(); i++)
			{
				Entity* entity = entities->GetScope(i).As<Entity>();
				entity->Update(state);
			}
		}
	}
};
