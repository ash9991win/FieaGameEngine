#pragma once
#include"Hashmap.h"
#include"RTTI.h"
#include<expat.h>
namespace Library
{
	class IXmlParseHelper;
	/*!
	\class XmlParseMaster
	\brief The class that represents the encapsulation of Xml file parsing
	*/
	class XmlParseMaster final
	{
	public:
		/*!
		\class SharedData
		\brief An embedded class which represents the data that will be shared by the helpers
		*/
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData,RTTI)
		public:
			/*!
			\fn SharedData()
			\brief The constructor that initilizes the members of the shared data class
			*/
			SharedData();
			/*!
			\fn SharedData* Clone()
			\brief The function clones the data found inside this class. It acts as a virtual constructor
			\return SharedData* the address of the clone
			*/
			virtual SharedData* Clone() const = 0 ;
			/*!
			\fn SetXmlParseMaster(XmlParseMaster& parseMaster)
			\brief Sets which parseMaster is using the shareddata
			\param The parseMaster which owns the shared data
			*/
			void SetXmlParseMaster(XmlParseMaster& parseMaster);
			/*!
			\fn GetXmlParseMaster()
			\brief Returns the parseMaster which is using the shared data
			\return A reference to the owner paseMaster
			*/
			XmlParseMaster& GetXmlParseMaster() const;
			/*!
			\fn IncrementDepth
			\brief Increments the depth of the parsing
			*/
			void IncrementDepth();
			/*!
			\fn DecrementDepth()
			\brief Decreases the depth of the parsing
			*/
			void DecrementDepth();
			/*!
			\fn GetDepth()
			\brief returns the current depth of the parsing
			*/
			uint32_t GetDepth() const;
			/*!
			\fn Reset()
			\brief Resets the depth to 0 for the parser
			*/
			virtual void Reset();
			virtual ~SharedData() = default;
		private:
			/*!
			\var ParseMaster
			\brief The owner of the current parsemaster
			*/
			XmlParseMaster *ParseMaster;
			/*!
			\var Depth
			\brief The current depth of the parsing
			*/
			uint32_t Depth;
		};
		/*!
		\fn XmlParseMaster(SharedData& )
		\brief The constructor which sets the shareddata variable
		\param A reference to the SharedData to be set
		*/
		explicit XmlParseMaster(SharedData& data);

		XmlParseMaster(const XmlParseMaster& rhs) = delete;
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		/*!
		\fn Clone()
		\brief Clones the current master and returns an indentical reference
		\return XmlParseMaster address
		*/
		XmlParseMaster* Clone() const;
		/*!
		\fn AddHelper(IXmlParseHelper)
		\brief Adds a helper for the parser to check through
		\param A reference to a IXMLParseHelper instance
		*/
		void AddHelper(IXmlParseHelper& helper);
		/*!
		\fn RemoveHelper(IXmlParseHelper&)
		\brief removes the given helper from the list of helpers 
		\param The helper to remove
		*/
		void RemoveHelper(IXmlParseHelper& helper);
		/*!
		\fn Parse(const char* charData, int Length,int isLast)
		\brief Parses the given string
		\param The string to parse
		\param The length of the passed string
		\param A flag to check if the given string is the last element
		*/
		void Parse(const XML_Char* charData,int length, int isLast) const ;
		/*!
		\fn ParseFromFile(string Filename)
		\brief Parse from the given file
		\param The filename
		*/
		void ParseFromFile(const string& filename) ;
		/*!
		\fn GetFinename()
		\brief Returns the filename being processed
		\return The filename
		*/
		const string& GetFileName() const;
		/*!
		\fn GetSharedData()
		\brief Returns the shareddata being used by the parseMaster
		\return Returns a reference to the SharedData
		*/
		SharedData& GetSharedData() const;
		/*!
		\fn SetSharedData()
		\brief Sets the shared data 
		\param The sharedData to be set
		*/
		void SetSharedData(SharedData& data);
		/*!
		\fn ~XmlParseMaster()
		\brief The destructor which clears any memory allocated
		*/
		~XmlParseMaster();
		/*!
		\fn Reset()
		\brief Reset the parser
		*/
		void Reset();
	private:
		/*!
		\fn StartElementHandler()
		\brief The function which parses the given element
		\param The UserData which gets populated according to the parsed line
		\param The element being parsed
		\param The attribute list of the line, if any
		*/
		static void StartElementHandler(void* userData,const XML_Char* elementName , const XML_Char** attributes);
		/*!
		\fn EndElementHandler
		\brief The callback called when an end of element occurs
		\param The userdata to be set
		\param The name of the element
		*/
		static void EndElementHandler(void *userData, const XML_Char* elementName);
		/*!
		\fn CharDataHandler
		\brief The callback for characters in the XML file
		\param The user data
		\param The character to be parsed
		\param The length of the character
		*/
		static void CharDataHandler(void *userData, const XML_Char* s,int len);
		/*!
		\var Helpers
		\brief A list of helpers assosciated with the parser
		*/
		Vector<IXmlParseHelper*> Helpers;
		/*!
		\var isCloned
		\brief A bool flag to indicate if the parser owns the memory
		*/
		bool IsCloned;
		/*!
		\var Filename
		\brief The filnename being parsed
		*/
		string Filename;
		/*!
		\var Parser
		\brief A XML_parser
		*/
		XML_Parser Parser;
		/*!
		\var UserData
		\brief The shared data that the helpers use
		*/
		SharedData *UserData;

	};
}
