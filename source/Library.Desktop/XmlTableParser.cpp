#include "pch.h"
#include "XmlTableParser.h"

namespace Library
{
	RTTI_DEFINITIONS(XmlTableParser::SharedData)

	
	XmlTableParser::SharedData::SharedData(Scope& scope)
		:CurrentScope(&scope)
	{

	}
	void XmlTableParser::SharedData::Reset()
	{
		XmlParseMaster::SharedData::Reset();
		CurrentScope->Clear();
	}
	XmlTableParser::SharedData* XmlTableParser::SharedData::Clone() const
	{
		return new SharedData(*CurrentScope);
	}
	const Scope& XmlTableParser::SharedData::GetScope() const
	{
		return *CurrentScope;
	}
	void XmlTableParser::Initialize()
	{
	}
	bool XmlTableParser::StartElementHandler(XmlParseMaster::SharedData& sharedData, const std::string& name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData *tableData = sharedData.As<SharedData>();
		if (tableData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();
		std::string scopeName = name;
		std::string typeString;
		if (!attributes.ContainsKey("type", typeString))
		{
			return false;
		}
		if (typeString != ScopeString)
			return false;
		if (KeyWordStrings.IsFound(name))
		{
			throw std::exception("Name cannot be a keyword");
		}
		tableData->TypeStack.Push(ScopeString);
		tableData->CurrentScope = &(tableData->CurrentScope->AppendScope(scopeName));
		return true;
	}
	bool XmlTableParser::EndElementHandler(XmlParseMaster::SharedData& userData, const string& name)
	{
		SharedData *tableData = userData.As<SharedData>();
		if (tableData == nullptr)
			return false;
		if (tableData->TypeStack.Top() != ScopeString)
			return false;
			
		if (tableData->CurrentScope->GetParent() != nullptr)
			tableData->CurrentScope = (tableData->CurrentScope->GetParent());
	
		tableData->TypeStack.Pop();
		return true;
	}
	bool XmlTableParser::CharDataHandler(XmlParseMaster::SharedData& userData, const string& data)
	{
		SharedData *tableData = userData.As<SharedData>();
		if (tableData == nullptr)
			return false;
		return true;
	}
	IXmlParseHelper* XmlTableParser::Clone() const
	{
		return new XmlTableParser();
	}
}