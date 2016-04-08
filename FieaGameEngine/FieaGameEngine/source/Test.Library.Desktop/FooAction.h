#pragma once
#include"Action.h"
using namespace Library;
class FooAction : public Action
{
	// Inherited via Action
	RTTI_DECLARATIONS(FooAction,Action)
public:
	virtual void Update(WorldState & state) override;
};