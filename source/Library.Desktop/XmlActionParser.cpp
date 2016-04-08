#include "pch.h"
#include "XmlActionParser.h"
#include"Action.h"
#include "ActionList.h"
#include"ActionListIf.h"
#include"Entity.h"
#include"Sector.h"
#include"World.h"
#include"ActionCreateAction.h"
#include"ActionDestroy.h"
namespace Library
{
	bool Library::XmlActionParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string className;
		if (!attributes.ContainsKey("type", CurrentType) ||( CurrentType != ActionString && CurrentType != ActionCreateString && CurrentType != ActionDestroyString))
		{
			return false;
		}
		if (!attributes.ContainsKey("class", className) && CurrentType != ActionDestroyString)
		{
			return false;
		}
		std::string InstanceName = name;
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Invalid name");
		}
		std::string AttributeName;
		if (!attributes.ContainsKey("name",AttributeName) && CurrentType == ActionDestroyString)
		{
			throw std::exception("Destroy action should have an aciton name");
		}
		std::string ParentType = sharedData->TypeStack.Top();
		bool result = false;
		if (ParentType == EntityString)
		{
			result = EntityActionHandler(*sharedData, className, InstanceName,AttributeName);
		}
		else
		{
			result = ActionListIfHandler(*sharedData, className, InstanceName, ParentType);
		}

		sharedData->TypeStack.Push(ActionString);
		return result;
	}

	bool Library::XmlActionParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() && sharedData->TypeStack.Top() != ActionString)
			return false;
		sharedData->TypeStack.Pop();
		return true;
	}

	bool XmlActionParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		return false;
	}

	IXmlParseHelper * Library::XmlActionParser::Clone() const
	{
		return new XmlActionParser();
	}
	bool XmlActionParser::EntityActionHandler(SharedData & data, std::string className, std::string InstanceName,std::string Attributename)
	{
		Entity * entity = data.CurrentScope->As<Entity>();
		if (!entity)
			return false;
		if (CurrentType == ActionString)
		{
			entity->CreateAction(className, InstanceName);
		}
		else if (CurrentType == ActionCreateString)
		{
			ActionCreateAction* createAction = new ActionCreateAction();
			createAction->SetPrototypeName(className);
			createAction->SetActionName(InstanceName);
			createAction->SetEntity(*entity);
		}
		else if (CurrentType == ActionDestroyString)
		{
			ActionDestroy* destroyAction = new ActionDestroy();
			destroyAction->SetName(InstanceName);
			destroyAction->SetEntityToDestroy(*entity);
			destroyAction->SetActionName(Attributename);
			destroyAction->SetEntity(*entity);
		}
		return true;
	}
	bool XmlActionParser::ActionListIfHandler(SharedData & data, std::string className, std::string InstanceName,std::string ifthen)
	{
		ActionListIf *ownerAction = data.CurrentScope->As<ActionListIf>();
		if (!ownerAction)
			return false;

		if(ifthen == ActionListThenString)
			ownerAction->CreateThenAction(className, InstanceName);
		else if (ifthen == ActionListElseString)
			ownerAction->CreateElseAction(className, InstanceName);
		else 
			return false;

		return true;
	}
}