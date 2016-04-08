#include "pch.h"
#include "IXmlParseHelper.h"
namespace Library
{
#pragma warning(disable : 4592)
	Vector<std::string> IXmlParseHelper::KeyWordStrings = { "switch","case","if","else","then","condition","for","while","foreach","expression" };
	std::string IXmlParseHelper::SectorString = "sector";
	std::string IXmlParseHelper::EntityString = "entity";
	std::string IXmlParseHelper::PrimitiveString = "primitive";
	std::string IXmlParseHelper::ActionString = "action";
	std::string IXmlParseHelper::ActionCreateString = "create";
	std::string IXmlParseHelper::ActionDestroyString = "destroy";
	std::string IXmlParseHelper::WorldString = "world";
	std::string IXmlParseHelper::ScopeString = "scope";
	std::string IXmlParseHelper::ActionListThenString = "actionListThen";
	std::string IXmlParseHelper::ActionListElseString = "actionListElse";
	std::string IXmlParseHelper::ActionListIfString = "if";
	std::string IXmlParseHelper::ExpressionString = "expression";
#pragma warning(default : 4592)
	bool IXmlParseHelper::CharDataHandler(XmlParseMaster::SharedData& userData, const std::string& data)
	{
		return false;
	}
}