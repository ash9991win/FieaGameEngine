#include"pch.h"
#include"XmlPrimitiveParser.h"
#include"Entity.h"
namespace Library
{
#pragma warning(disable : 4592)
	Hashmap<std::string, Datum::DatumType> XmlPrimitiveParser::primitiveTable =
	{
		{ "int",Datum::DatumType::INTEGER },
		{ "float",Datum::DatumType::FLOAT },
		{ "vec",Datum::DatumType::VECTOR },
		{ "mat",Datum::DatumType::MATRIX },
		{ "string",Datum::DatumType::STRING},
		{"str",Datum::DatumType::STRING}
	};
#pragma warning(default : 4592)
	bool XmlPrimitiveParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string currentTypeString;
		if (!attributes.ContainsKey("type", currentTypeString))
		{
			return false;
		}
		if (!primitiveTable.ContainsKey(currentTypeString, CurrentType))
		{
			return false;
		}
		std::string currentValueString;
		if (!attributes.ContainsKey("value", currentValueString))
		{
			return false;
		}
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Name cannot be a keyword");
		}
		Datum *datum = nullptr;
		if (sharedData->TypeStack.Top() == EntityString)
		{
			Entity* entity = sharedData->CurrentScope->As<Entity>();
			if (!entity->IsPrescribedAttribute(name))
			{
				entity->AppendAuxilliaryAttribute(name);
			}
			datum = entity->Find(name);
		}
		else if (sharedData->TypeStack.Top() == ScopeString)
		{
			datum = &(sharedData->CurrentScope->Append(name));
		}
		else
		{
			return false;
		}
		if (datum)
		{
			datum->SetType(CurrentType);
			datum->SetFromString(currentValueString);
		}
		sharedData->TypeStack.Push(PrimitiveString);
		
		return true;
	}
	bool XmlPrimitiveParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		if (!sharedData->TypeStack.IsEmpty() && sharedData->TypeStack.Top() != PrimitiveString)
			return false;
		sharedData->TypeStack.Pop();
		return true;

	}
	bool XmlPrimitiveParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		return true;
	}
	IXmlParseHelper * XmlPrimitiveParser::Clone() const
	{
		return new XmlPrimitiveParser();
	}
}