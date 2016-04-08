#include"pch.h"
#include"MonsterEntity.h"
RTTI_DEFINITIONS(MonsterEntity)
MonsterEntity::MonsterEntity()
	:health(0), type()
{
	AddExternalSignature("health", &health, 1);
	AddExternalSignature("type", &type, 1);
}
int MonsterEntity::GetHealth()
{
	return health;
}
std::string MonsterEntity::GetType()
{
	return type;
}