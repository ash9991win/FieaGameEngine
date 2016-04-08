#pragma once
#include"Entity.h"
using namespace Library;
class MonsterEntity : public Entity
{
	RTTI_DECLARATIONS(MonsterEntity, Entity)
public:
	MonsterEntity();
	int GetHealth();
	std::string GetType();
private:
	int health;
	string type;
};