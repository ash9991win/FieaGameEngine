#include "pch.h"
#include "WorldState.h"

namespace Library
{
	const GameTime & WorldState::GetGameTime() const
	{
		return *Time;
	}
	void WorldState::SetGameTime(GameTime & gameTime)
	{
		Time = &gameTime;
	}
}