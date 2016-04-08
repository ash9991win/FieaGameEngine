#pragma once
#include"IXmlParseHelper.h"
#include "XmlParseMaster.h"
using namespace Library;
namespace TestLibraryDesktop
{
	class TestXmlParserFoo : public IXmlParseHelper
	{
	public:
		class SharedFooData : public XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedFooData,XmlParseMaster::SharedData)
		public:
			virtual SharedFooData* Clone()  const override;
			friend class TestXmlParserFoo;
			virtual void Reset() override;
			const string& getCategory() const
			{
				return category;
			}
			const string& getName() const
			{
				return FooName;
			}
			int getHealth()
			{
				return health;
			}
			int getArmor()
			{
				return armor;
			}
		private:
			string category;
			string FooName;
			int health;
			int armor;

		};
		virtual void Initialize() override;
		TestXmlParserFoo();
		virtual bool StartElementHandler(XmlParseMaster::SharedData& userData, const string& name, Hashmap<string, string>& valuepair) override;
		virtual bool EndElementHandler(XmlParseMaster::SharedData& userData, const string& name) override;
		virtual bool CharDataHandler(XmlParseMaster::SharedData& userData, const string& data) override;
		virtual IXmlParseHelper* Clone() const override;
		~TestXmlParserFoo();
	};
}