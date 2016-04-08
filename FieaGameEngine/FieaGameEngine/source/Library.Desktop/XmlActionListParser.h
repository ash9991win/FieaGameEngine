#pragma once
#include "IXmlParseHelper.h"
#include "XmlTableParser.h"
namespace Library
{
	class XmlActionListParser :
		public IXmlParseHelper
	{
	public:
		XmlActionListParser();
		~XmlActionListParser();

		// Inherited via IXmlParseHelper
		virtual void Initialize() override;
		virtual bool StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& valuePair) override;
		virtual bool EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name) override;
		virtual IXmlParseHelper * Clone() const override;
	private:
		typedef XmlTableParser::SharedData SharedData;
	};
}

