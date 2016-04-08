#include "pch.h"
#include "XmlParseMaster.h"
#include"IXmlParseHelper.h"
#include<fstream>
namespace Library
{
	RTTI_DEFINITIONS(XmlParseMaster::SharedData)
	XmlParseMaster::SharedData::SharedData()
		:Depth(0),ParseMaster(nullptr)
	{
	}
	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster& master)
	{
		ParseMaster = &master;
	}
	XmlParseMaster& XmlParseMaster::SharedData::GetXmlParseMaster() const
	{
		return (*ParseMaster);
	}
	void XmlParseMaster::SharedData::IncrementDepth()
	{
		Depth++;
	}
	void XmlParseMaster::SharedData::DecrementDepth()
	{
		if (Depth <= 0)
			throw std::exception("Depth should always be greater than or equal to 1");
		--Depth;
	}
	uint32_t XmlParseMaster::SharedData::GetDepth() const
	{
		return Depth;
	}
	void XmlParseMaster::SharedData::Reset()
	{
		Depth = 0;
	}
	XmlParseMaster::XmlParseMaster(XmlParseMaster::SharedData& sharedData)
		: Parser(XML_ParserCreate(NULL)),UserData(&sharedData),Helpers(),Filename(),IsCloned(false)
	{
		UserData->SetXmlParseMaster(*this);
		XML_SetElementHandler(Parser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(Parser, CharDataHandler);
		XML_SetUserData(Parser, UserData);

	}
	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster *clonedMaster = new XmlParseMaster(*UserData->Clone());
		for (auto currentHelper : Helpers)
		{
			clonedMaster->AddHelper(*(currentHelper->Clone()));
		}
		clonedMaster->IsCloned = true;
		return clonedMaster;
	}
	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		if (IsCloned)
			throw std::exception("Cant add helper to a cloned parser");
		Helpers.PushBack(&helper);
	}
	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
			Helpers.Remove(&helper);
	}
	void XmlParseMaster::Parse(const XML_Char* data, int length, int isLast)  const
	{
		XML_Status status = XML_Parse(Parser, data, length, isLast);
	
		if (status == XML_Status::XML_STATUS_ERROR)
		{
			std::string error = XML_ErrorString(XML_GetErrorCode(Parser));
			throw std::exception(error.c_str());
		}

	}

	void XmlParseMaster::ParseFromFile(const string& name) 
	{
		ifstream fileStream(name);
		string lineFromFile;
		Reset();
		if (fileStream.is_open())
		{
			while (getline(fileStream, lineFromFile))
			{
				
				Parse(lineFromFile.c_str(), (int)lineFromFile.length(), !fileStream.good());
			}
			
		}
		Filename = string(name);
	}
	const string& XmlParseMaster::GetFileName() const
	{
		return Filename;
	}
	XmlParseMaster::SharedData& XmlParseMaster::GetSharedData() const
	{
		return *UserData;
	}
	void XmlParseMaster::SetSharedData(XmlParseMaster::SharedData& newUserData)
	{
		//TODO THROW EXCEPTION
		if (UserData != nullptr)
		{
			if (IsCloned)
				delete UserData;
		}
		UserData = &newUserData;
		UserData->SetXmlParseMaster(*this);
		XML_SetUserData(Parser, UserData);
	}
	XmlParseMaster::~XmlParseMaster()
	{
		if (IsCloned)
		{
			delete UserData;
			for (auto currentHelper : Helpers)
			{
				delete currentHelper;
			}
		}
		XML_ParserFree(Parser);
	}
	void XmlParseMaster::Reset()
	{
		for (auto currentHelper : Helpers)
		{
			currentHelper->Initialize();
		}
		if(UserData)
			UserData->Reset();
		XML_ParserReset(Parser, nullptr);
		XML_SetElementHandler(Parser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(Parser, CharDataHandler);
		XML_SetUserData(Parser, UserData);
		Filename.clear();
	}
	void XmlParseMaster::StartElementHandler(void *userdata, const XML_Char* name, const XML_Char** attribute)
	{
		SharedData* newUserdata = reinterpret_cast<SharedData*>(userdata);
		if (newUserdata == nullptr)
			return;
		XmlParseMaster& master = newUserdata->GetXmlParseMaster();
		Hashmap<string, string> dataTable;
		for (uint32_t i = 0; attribute[i] != nullptr; i += 2)
		{
			dataTable.Insert(std::pair<string, string>(attribute[i], attribute[i + 1]));
		}
		newUserdata->IncrementDepth();
		for (auto currentHelper : master.Helpers)
		{
			if (currentHelper->StartElementHandler(*newUserdata,string(name), dataTable))
				break;
		}
	}
	void XmlParseMaster::CharDataHandler(void *userData, const XML_Char* s, int len)
	{
		SharedData* newUserdata = reinterpret_cast<SharedData*>(userData);
		if (newUserdata == nullptr)
			return;
		string builtString(s, len);
		XmlParseMaster& master = newUserdata->GetXmlParseMaster();
		for (auto currentHelper : master.Helpers)
		{
			if (currentHelper->CharDataHandler(*newUserdata,builtString))
				break;
		}
	}
	void XmlParseMaster::EndElementHandler(void *userData, const XML_Char* endElementName)
	{
		SharedData* newUserdata = reinterpret_cast<SharedData*>(userData);
		if (newUserdata == nullptr)
			return;
		XmlParseMaster& master = newUserdata->GetXmlParseMaster();
		for (auto currentHelper : master.Helpers)
		{
			if (currentHelper->EndElementHandler(*newUserdata,string(endElementName)))
				break;
		}
		newUserdata->DecrementDepth();

	}
}
