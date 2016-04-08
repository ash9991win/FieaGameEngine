#include "pch.h"
#include "XmlActionListParser.h"
#include "Entity.h"
#include "Action.h"
#include"ActionList.h"
namespace Library
{
	XmlActionListParser::XmlActionListParser()
	{
	}


	XmlActionListParser::~XmlActionListParser()
	{
	}

	void Library::XmlActionListParser::Initialize()
	{
	}

	bool Library::XmlActionListParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{

		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string className;
		std::string CurrentType;
		if (!attributes.ContainsKey("type", CurrentType) || CurrentType != ActionListString)
		{
			return false;
		}
		Entity * entity = sharedData->CurrentScope->As<Entity>();
		if (!entity)
			return false;
		if (sharedData->TypeStack.Top() != EntityString)
			return false;
		ActionList *actionList = new ActionList();
		actionList->Set
		sharedData->TypeStack.Push(ActionListString);
		return false;
	}

	bool Library::XmlActionListParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() && sharedData->TypeStack.Top() != ActionListString)
			return false;
		sharedData->TypeStack.Pop();
		if (sharedData->CurrentScope->GetParent())
			sharedData->CurrentScope = sharedData->CurrentScope->GetParent();
		return true;
	}

	IXmlParseHelper * Library::XmlActionListParser::Clone() const
	{
		return nullptr;
	}
}