#include "pch.h"
#include "XmlActionIfParser.h"
#include "Entity.h"
#include"ActionListIf.h"
namespace Library
{
#pragma warning(disable : 4592)
	Vector<std::string> XmlActionIfParser::ValidTags = { "if","else","then" };
#pragma warning(default : 4592)
	bool Library::XmlActionIfParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();

		if (!ValidTags.IsFound(name))
		{
			return false;
		}
		std::string Condition;
		if (!attributes.ContainsKey("condition", Condition) && name == "if")
		{
			throw std::exception("If needs a condition");
		}
		if (sharedData->TypeStack.Top() != EntityString && name=="if")
		{
			return false;
		}
		if (name == "if")
		{
			Entity* currentEntity = sharedData->CurrentScope->As<Entity>();
			ActionListIf* listIf = new ActionListIf();
			listIf->SetCondition(std::stoi(Condition));
			listIf->SetEntity(*currentEntity);
			sharedData->CurrentScope = listIf;
			sharedData->TypeStack.Push(ActionListIfString);
			return true;
		}
		std::string PreviousType = sharedData->TypeStack.Top();
		if (PreviousType != ActionListIfString)
		{
			return false;
		}
		if (name == "then")
		{
			sharedData->TypeStack.Push(ActionListThenString);
		}
		if (name == "else")
		{
			sharedData->TypeStack.Push(ActionListElseString);
		}
		
		return true;
	}

	bool Library::XmlActionIfParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!ValidTags.IsFound(name))
		{
			return false;
		}
		if (name == "if")
		{
			sharedData->CurrentScope = sharedData->CurrentScope->GetParent();
		}
		sharedData->TypeStack.Pop();

		return true;
	}

	bool XmlActionIfParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (!sharedData)
			return false;
		return true;
	}

	IXmlParseHelper * Library::XmlActionIfParser::Clone() const
	{
		return new XmlActionIfParser();
	}
}