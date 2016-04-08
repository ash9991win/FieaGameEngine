#include "Factory.h"
namespace Library
{
#pragma warning(disable : 4592)
	template<typename T>
	Hashmap<std::string,  const Factory<T>* const > Factory<T>::FactoryTable;
#pragma warning(default : 4592)
	template<typename T>
	 const Factory<T>* const Factory<T>::Find(const std::string& name)
	{
		Hashmap<std::string,  const Factory* const >::Iterator findIter = FactoryTable.Find(name);
		if (findIter != FactoryTable.end())
		{
			return (findIter->second);
		}
		else
		{
			return nullptr;
		}
	}
	template<typename T>
	T* Factory<T>::Create(const std::string & name)
	{
		
		const Factory* createdFactory = Find(name);
		if (createdFactory != nullptr)
		{

			return (createdFactory->Create());
		}	
		return nullptr;
	}

	template<typename T>
	typename Hashmap<std::string,const Factory<T>* const>::Iterator Factory<T>::Begin()
	{
		return FactoryTable.begin();
	}
	template<typename T>
	typename Hashmap<std::string, const Factory<T>* const>::Iterator Factory<T>::End()
	{
		return FactoryTable.end();
	}
	template<typename T>
	std::uint32_t Factory<T>::Size()
	{
		return FactoryTable.Count();
	}
	template<typename T>
	void Factory<T>::Add( const Factory& factory)
	{
		FactoryTable.Insert(std::pair<std::string, const Factory<T>* const>(factory.GetClassID(), &factory));
	}

	template<typename T>
	void Factory<T>::Remove(const Factory& factory)
	{
		FactoryTable.Remove(factory.GetClassID());
	}
	

}