#pragma once
namespace Library
{
	class GameTime;
	class WorldState 
	{
		
	public:
		WorldState() = default;
		class World* world;
		class Sector* sector;
		class Entity* entity;
		class Action* Action;
		const GameTime& GetGameTime() const;
		void SetGameTime(GameTime& gameTime);
	private:
		const GameTime* Time;
	};
}