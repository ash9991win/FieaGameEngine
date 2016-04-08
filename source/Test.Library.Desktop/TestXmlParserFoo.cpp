#include"pch.h"
#include"TestXmlParserFoo.h"
namespace TestLibraryDesktop
{
	RTTI_DEFINITIONS(TestXmlParserFoo::SharedFooData)
	TestXmlParserFoo::SharedFooData* TestXmlParserFoo::SharedFooData::Clone() const
	{
		SharedFooData* sharedDataClone = new SharedFooData();
		sharedDataClone->FooName = FooName;
		sharedDataClone->health = health;
		sharedDataClone->armor = armor;

		return sharedDataClone;
	}
	void TestXmlParserFoo::SharedFooData::Reset()
	{
		SharedData::Reset();
		FooName.clear();
		health = 0;
		armor = 0;
		category.clear();
	}
	void TestXmlParserFoo::Initialize()
	{
	}
	TestXmlParserFoo::TestXmlParserFoo()
	{
	}
	bool TestXmlParserFoo::StartElementHandler(XmlParseMaster::SharedData& userData,const string& name, Hashmap<string, string>& valuepair)
	{
		SharedFooData *FooData = userData.As<SharedFooData>();
		if (FooData == nullptr)
			return false;

		if (name == "Category")
		{
			if (valuepair.ContainsKey("type"))
			{

				FooData->category = valuepair["type"];
				return true;
			}
			return false;
		}
		if (name == "stats")
		{
			if (valuepair.ContainsKey("health") && valuepair.ContainsKey("armor"))
			{

				FooData->armor = std::stoi(valuepair["armor"]);
				FooData->health = std::stoi(valuepair["health"]);
				return true;
			}
			return false;
		}
		return false;
		//TODO ADD STATE MACHINE FOR PARSING AND NOT PARSING STATES
	}
	 bool 	TestXmlParserFoo::EndElementHandler(XmlParseMaster::SharedData& userData,const string& name) 
	{
		if (name == "Monster")
			return true;

		return false;
	}
	 bool TestXmlParserFoo::CharDataHandler(XmlParseMaster::SharedData& userData, const string& data) 
	{
		SharedFooData *FooData = userData.As<SharedFooData>();
		if (FooData == nullptr)
			return false;
		FooData->FooName = data;
		return true;
	}
	 TestXmlParserFoo::IXmlParseHelper* TestXmlParserFoo::Clone() const
	{
		TestXmlParserFoo *ClonedFoo = new TestXmlParserFoo();
		return ClonedFoo;
	}
	 TestXmlParserFoo::~TestXmlParserFoo()
	{
	}
}