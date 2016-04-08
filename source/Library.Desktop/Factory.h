#pragma once
#include<string>
#include"Hashmap.h"
namespace Library
{
	
	template<typename T>
	/*!
	\class Factory
	\brief The abstract factory class used to create objects of a type
	*/
	class Factory
	{
	public:
		typedef typename Hashmap<std::string, const Factory<T>* const>::Iterator Iterator;
		/*!
		\fn GetClassID()
		\brief Returns the class ID of a particular class 
		\return Returns the string id of a class
		*/
		virtual  std::string GetClassID() const = 0;
		/*!
		\fn Find()
		\brief Finds a given class by it's ID and returns a factory of that type
		\param The ID of the class to find
		\return Returns a factory of the given type
		*/
		static  const Factory<T>* const Find(const std::string& name);
		/*!
		\fn Create()
		\brief Creates an abstract type of the given name. Caution : This creates a memory that will then be owned by you. So it is upto you to delete it.
		\param The name of the class to create
		\return Returns the created class object
		*/
		static  T* Create(const std::string& name);
		/*!
		\fn Begin()
		\brief Returns the first element of the factory table
		\return Returns the iterator pointing to the beginning
		*/
		static Iterator Begin();
		/*!
		\fn End()
		\brief Returns the iterator after the end of the factory table
		\return returns the iterator pointing to the end
		*/
		static Iterator End();
		/*!
		\fn Size()
		\brief Returns the number of elements in the factory table
		\return Returns the number of elements 
		*/
		static std::uint32_t Size();

		Factory(const Factory& rhs) = delete;
		Factory& operator=(const Factory& rhs) = delete;
		Factory() = default;
	protected:		
		/*!
		\fn Create() = 0
		\brief A pure virtual create that the derived classes override
		\return Returns an object of the given type
		*/
		virtual T* Create() const = 0;				
		/*!
		\fn Add()
		\brief Adds a factory to the factory table
		\param A factory pointer
		*/
		static void Add(const Factory& factory);	
		/*!
		\fn Remove()
		\brief Removes the given factory from the factory table
		\param The factory to be removed*/
		static void Remove(const Factory& factory);										  
	private:		
		/*!
		\var Hashmap<std:string,Factory*> FactoryTable 
		\brief The factory table
		*/
	static Hashmap<std::string, const Factory* const > FactoryTable;							  
	};
	/*!
	\fn CONCRETEFACTORY()
	\brief The macro for creating a factory of a type
	\param The base class of whith the type has to be created
	\param The derived class from which the type has to be created
	*/
#define CONCRETEFACTORY(ConcreteProduct, AbstractProduct)									\
class ConcreteProduct##Factory : public Factory<AbstractProduct>							\
{																							\
public:																						\
	ConcreteProduct##Factory() { Add(*this); }												\
	~ConcreteProduct##Factory() { Remove(*this); }											\
	virtual  std::string GetClassID() const override {										\
		return  #ConcreteProduct;															\
	}																						\
	virtual AbstractProduct* Create() const override								\
	{																						\
		return new ConcreteProduct();											\
	}																						\
	};																				  
};
#include"Factory.inl"