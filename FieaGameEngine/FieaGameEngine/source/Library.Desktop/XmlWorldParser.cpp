#include"pch.h"
#include"XmlWorldParser.h"
#include"World.h"
namespace Library
{
	bool XmlWorldParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		
		std::string currentType;
		if (!attributes.ContainsKey("type", currentType) || currentType != WorldString)
		{
			return false;
		}
		std::string worldname = name;
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Name cannot be a keyword");
		}
		World* world = new World(worldname);
		sharedData->CurrentScope->Adopt(*world, worldname);
		sharedData->CurrentScope = world;
		sharedData->TypeStack.Push (WorldString);
		return true;
	}
	bool XmlWorldParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() && sharedData->TypeStack.Top() != WorldString)
			return false;
		sharedData->TypeStack.Pop();
		if (sharedData->CurrentScope->GetParent())
			sharedData->CurrentScope = sharedData->CurrentScope->GetParent();
		return true;

	}
	bool XmlWorldParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		return true;
	}
	IXmlParseHelper * XmlWorldParser::Clone() const
	{
		return new XmlWorldParser();
	}
}