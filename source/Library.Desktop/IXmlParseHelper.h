#pragma once
#include"Hashmap.h"
#include<expat.h>
#include<string>
#include"XmlParseMaster.h"
namespace Library
{
	class IXmlParseHelper
	{
	public:
		/*!
		\fn IXmlParseHelper()
		\brief The constructor of the interface
		*/
		IXmlParseHelper() = default;
		/*!
		\fn Initiliaze()
		\brief Initializes the interface
		*/
		virtual void Initialize() = 0;
		/*!
		\fn StartElementHandler
		\brief The handle for Expat's start element handler
		\param Name of the element
		\param A Hashmap of string, string that is used for parsing
		\return returns true if it can process the data
		*/

		//TODO Change string to const string&
		virtual bool StartElementHandler(XmlParseMaster::SharedData& userData,const std::string& name, Hashmap<std::string, std::string>& valuePair) = 0;
		/*!
		\fn EndElementHandler()
		\param the name of the element's end tag
		\return Returns bool if the handler can process the name
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData& userData,const std::string& name) = 0;
		/*!
		\fn CharDataHandler
		\brief Process character data from the xml
		\param The data to process
		\param the size of the data
		\return Returns true if it can process the data
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData& userData,const std::string& data) ;
		/*!
		\fn Clone()
		\brief A virtual constructor
		*/
		virtual IXmlParseHelper* Clone() const = 0;
		/*!
		\fn ~IXmlParserHelper()
		\brief A virtual destructor
		*/
		virtual ~IXmlParseHelper() = default;
	protected:
		static Vector<std::string> KeyWordStrings;
		static std::string SectorString;
		static std::string EntityString;
		static std::string PrimitiveString;
		static std::string ActionString;
		static std::string ActionListString;
		static std::string WorldString;
		static std::string ScopeString;
		static std::string ActionListThenString;
		static std::string ActionListElseString;
		static std::string ActionListIfString;
		static std::string ActionCreateString;
		static std::string ActionDestroyString;
		static std::string ActionIfString;
		static std::string ExpressionString;
	};
}

