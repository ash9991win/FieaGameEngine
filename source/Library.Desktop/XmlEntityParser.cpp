#include"pch.h"
#include"XmlEntityParser.h"
#include"World.h"
#include"Sector.h"
#include"Entity.h"
namespace Library
{
	bool XmlEntityParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string currentType;
		if (!attributes.ContainsKey("type", currentType) || currentType != EntityString)
		{
			return false;
		}
		std::string className;
		std::string instanceName = name;
		if (!attributes.ContainsKey("class", className))
		{
			return false;
		}
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Name cannot be a keyword");
		}
		Sector* sector = sharedData->CurrentScope->As<Sector>();
		if (sector == nullptr)
			return false;
		sharedData->CurrentScope = (sector->CreateEntity(className, instanceName));
		sharedData->TypeStack.Push(EntityString);
		
		return true;
	}
	bool XmlEntityParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() &&  sharedData->TypeStack.Top() != EntityString)
			return false;
		sharedData->TypeStack.Pop();
		if (sharedData->CurrentScope->GetParent())
			sharedData->CurrentScope = sharedData->CurrentScope->GetParent();
		return true;

	}
	bool XmlEntityParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		return true;
	}
	IXmlParseHelper * XmlEntityParser::Clone() const
	{
		return new XmlEntityParser();
	}
}