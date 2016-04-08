#pragma once
#include "IXmlParseHelper.h"
#include"XmlTableParser.h"
namespace Library
{
	class XmlActionExpressionParser :
		public IXmlParseHelper
	{
	public:
		XmlActionExpressionParser() = default;
		~XmlActionExpressionParser() = default;

		virtual void Initialize() override {}
		/*!
		\fn StartElementHandler()
		\brief The callback when a start element tag is encountered
		\param SharedData* the table data
		\param name The Name of the tag
		\param valuePair A hashmap of the attribute fields in the xml file
		\return Returns true if the handler processes the request
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData& userData, const std::string& name, Hashmap<std::string, std::string>& valuePair) override;
		/*!
		\fn EndElementHandler
		\brief The callback when a tag element is ended
		\param userData the table data
		\param name the name of the tag thats being ended
		\return Returns true if the handler processes the request
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData& userData, const std::string& name) override;
		/*!
		\fn CharDataHandler()
		\brief The handler that handles char data
		\param userData the table data
		\param data the chardata of the tag
		\return returns true if the handler can process it
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData& userData, const std::string& data) override;
		/*!
		\fn Clone()
		\brief Clones the given parser
		\return Returns a IXmlParserHelper which was cloned
		*/
		virtual IXmlParseHelper* Clone() const override;
	private:
		static Hashmap<std::string, int> OperatorPrecedenceTable;
		 Vector<std::string> FinalExpression;
		void ShuntingYard(const std::string& expression, bool& isFloat);
		typedef XmlTableParser::SharedData SharedData;
		bool IsAFloat(const std::string& value);
		bool IsANumber( std::string value);
	};
}
