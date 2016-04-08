#include"pch.h"
#include"XmlSectorParser.h"
#include"World.h"
#include"Sector.h"
namespace Library
{
	bool XmlSectorParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string currentType;
		if (!attributes.ContainsKey("type", currentType) || currentType != SectorString)
		{
			return false;
		}
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Name cannot be a keyword");
		}
		std::string sectorName = name;
		World* world = sharedData->CurrentScope->As<World>();
		if (world == nullptr)
			return false;
		sharedData->CurrentScope = &(world->CreateSector(sectorName));
		sharedData->TypeStack.Push(SectorString);

		return true;
	}
	bool XmlSectorParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() && sharedData->TypeStack.Top() != SectorString)
			return false;
		sharedData->TypeStack.Pop();
		if (sharedData->CurrentScope->GetParent())
			sharedData->CurrentScope = sharedData->CurrentScope->GetParent();
		return true;

	}
	bool XmlSectorParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		return true;
	}
	IXmlParseHelper * XmlSectorParser::Clone() const
	{
		return new XmlSectorParser();
	}
}