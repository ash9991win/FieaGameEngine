#pragma once
#include"IXmlParseHelper.h"
#include"Scope.h"
#include"Stack.h"
namespace Library
{
	/*!
	\class XmlTableParser
	\brief A class that helps parse scopes from xml
	*/
	class XmlTableParser : public IXmlParseHelper
	{
		
	public:
		/*!
		\class SharedData
		\brief A shareddata that holds the parsed scopes data
		*/
		class SharedData : public XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedData,XmlParseMaster::SharedData)
		public:
			/*!
			\fn SharedData(Scope& scope)
			\brief A constructor that takes in a scope to populate
			\param The scope to populate with the parsed data
			*/
			explicit SharedData(Scope& scope);
			SharedData(const SharedData& rhs) = delete;
			SharedData& operator=(const SharedData& rhs) = delete;
			/*!
			\fn ~SharedData()
			\brief The destructor which has been defaulted
			*/
			virtual ~SharedData() = default;
			/*!
			\fn Reset()
			\brief The reset that clears the shared data
			*/
			virtual void Reset() override;
			/*!
			\fn Clone()
			\brief Clones the shared data 
			\return A pointer to the cloned shareddata
			*/
			virtual SharedData* Clone() const override;
			/*!
			\fn GetScope()
			\brief Returns the scope being processed
			\return The scope being processed
			*/
			const Scope& GetScope() const ;

		private:
			Scope* CurrentScope;
			Stack<std::string> TypeStack;
			friend class XmlTableParser;
			friend class XmlEntityParser;
			friend class XmlWorldParser;
			friend class XmlSectorParser;
			friend class XmlPrimitiveParser;
			friend class XmlActionParser;
			friend class XmlActionIfParser;
			friend class XmlActionListParser;
			friend class XmlActionExpressionParser;
		};
		/*!
		\fn XmlTableParser()
		\brief The constructor which initializes the table parser
		*/
		XmlTableParser() = default;
		virtual ~XmlTableParser() = default;
		/*!
		\fn Initialize()
		\brief Initializes the table parser
		*/
		virtual void Initialize() override;
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
		typedef XmlTableParser::SharedData SharedData;
	};
}

