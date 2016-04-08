#pragma once
#include"EventSubscriber.h"
using namespace Library;
class FooEvent :
	public EventSubscriber
{
public:
	FooEvent();
	~FooEvent();
	int Message;
	// Inherited via EventSubscriber
	virtual void Notify(EventPublisher &) override;
};

