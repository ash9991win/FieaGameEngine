#pragma once
#include"Hashmap.h"
#include"Datum.h"
#include<string>
namespace Library
{
	/*!
	\class Scope
	\brief A class which represents the scope. A dynamic table of dynamic types
	*/
	class Scope : public RTTI
	{
		/*!
		\brief The RTTI declarations
		\param The Scope class and the RTTI will be passed in so that a runtime type identification can be done
		*/
		RTTI_DECLARATIONS(Scope, RTTI)
	public:
		/*!
		\fn Scope(std::uint32 capacity)
		\brief A paramter overloaded constructor
		\param A capacity that the user can pass in in case he knows the size of the table in advance
		*/
		class Iterator
		{
			friend class Scope;
		public:
			Iterator();
			Iterator(const Iterator& rhs) = default;
			Iterator& operator=(const Iterator& rhs) = default;
			Iterator& operator++();
			Iterator operator++(int);
			Datum& operator*() ;
			bool operator==(const Iterator& rhs) const;
			bool operator!=(const Iterator& rhs) const;
		private:
			const Scope* Owner;
			Iterator(const Scope* owner, std::uint32_t index);
			std::uint32_t Index;
		};
		explicit Scope(std::uint32_t capacity = DefaultCapacity);
		/*!
		\fn Scope(const Scope& rhs)
		\brief The copy constructor
		\param The Scope to be copied from
		*/
		Scope(const Scope& rhs);
		/*!
		\fn Scope( Scope&& rhs)
		\brief The move constructor
		\param The Scope to be moved from
		*/
		Scope(Scope&& rhs);
		/*!
		\fn Scope& operator=(const Scope& rhs)
		\brief The overloaded assignment operator
		\param The Scope to be copied from
		\return The copied to scope
		*/
		Scope& operator=(const Scope& rhs);
		/*!
		\fn Scope& operator=( Scope&& rhs)
		\brief The overloaded assignment operator
		\param The Scope to be copied from
		\return The copied to scope
		*/
		Scope& operator=(Scope&& rhs);
		/*!
		\fn Datum* Find(const std::string& key) const
		\brief Finds a datum with the given key and returns the address of the datum
		\param The string key which has to be searched in the scope
		\return  The pointer to the datum that contains the key or a nullptr otherwise
		*/
		Datum* Find(const std::string& key) const;
		/*!
		\fn Datum* Search(const std::string& key, const Scope** scope) const
		\brief Searches for a string in the current scope and if not found searches in it's ancestry
		\param A string key to search for
		\param A double pointer to the scope that the key was found in. Its the out paramter
		\return returns the pointer to the datum that the key was found in
		*/
		Datum* Search(const std::string& key,  const Scope** scope = nullptr) const ;
		/*!
		\fn Search(const std::string& key)
		\brief Appends the given key into the scope
		\param The name of the datum that has to appended into the scope
		\return returns a reference to the datum inserted / found
		*/
		Datum& Append(const std::string& key);
		/*!
		\fn AppendScope(std::string& key)
		\brief Nests a scope of the given name into the current scope
		\param the name of the nested scope
		\return returns a reference to the scope inserted
		*/
		Scope& AppendScope(const std::string& key);
		/*!
		\fn Adopt(Scope& child,const std::string& name)
		\brief Adds a passed scope to the current scope
		\param The child to adopt
		\param The name of adopted child
		*/
		Datum& Adopt(Scope& child,const std::string& name);
		/*!
		\fn GetParent()
		\brief returns a reference to the parent of the current scope
		\return Returns a Scope* which is the pointer
		*/
		Scope* GetParent();
		/*!
		\fn operator[](const std::string& key)
		\brief Returns a datum that has the current key
		\return Returns a reference to the datum that matches the key
		*/
		Datum& operator[](const std::string& key);
		/*!
		\fn operator[](std::uint32_t index)
		\brief Returns a datum that the index holds
		\param The index that the scope has to access
		\return returns a reference to the datum at the particular index
		*/
		Datum& operator[](const std::uint32_t key);
		Datum& operator[](const std::uint32_t key) const;
		/*!
		\fn bool operator==(const Scope& rhs) const
		\brief Compares the two scopes
		\param The scope to be compared to
		\return Returns a bool ( true if equal)
		*/
		bool operator==(const Scope& rhs) const;
		/*!
		\fn bool operator!=(const Scope& rhs) const
		\brief Compares the two scopes
		\param The scope to be compared to
		\return Returns a bool ( false if equal)
		*/
		bool operator!=(const Scope& rhs) const;
		/*!
		\fn FindName(Scope*)
		\brief Finds the given scope and returns its name
		\param The scope whose name has to be returned
		\return returns a name of the scope found
		*/
		std::string FindName(Scope *const scopeToFind) const;
		/*!
		\fn bool Equals(const RTTI* rhs)
		\brief Overrides the equals function of the RTTI
		\param The RTTI to be compared to 
		\return returns bool ( true if equal)
		*/
		virtual bool Equals(const RTTI* rhs) const override;
		/*!
		\fn ToString() const 
		\brief Converts the given scope to a string representation 
		\return Returns a string representation of the given scope
		*/
		virtual std::string ToString() const override;
		/*!
		\fn Clear()
		\brief Clears the scope
		*/
		virtual void Clear();
		/*!
		\fn Orphan()
		\brief Severs the link between the current scope and it's parent
		*/
		void Orphan();
		/*!
		\fn Size()
		\brief returns the size of the scope
		\return returns the size of the scope
		*/
		std::uint32_t Size() const;
		/*!
		\fn ~Scope()
		\brief The destructor that clears the scope 
		*/
		Iterator begin() const;
		Iterator end() const;
		virtual ~Scope();
	private:
		
		typedef std::pair<std::string, Datum> ScopePair;
		/*!
		\var Hashmap<string,Datum> ScopeTable
		\brief The SCope table of the scope that stores the string-datum pair
		*/
		Hashmap<std::string, Datum> ScopeTable;
		/*!
		\var Vector<ScopePair> ScopeVector
		\brief The ordered representation of the scope's data
		*/
		Vector<ScopePair*> ScopeVector;
		/*!
		\var DefaulCapacity
		\brief This is the default capacity of the scope
		*/
		static std::uint32_t DefaultCapacity;
		/*!
		\var ParentScope
		\brief A pointer to the parent of the current scope
		*/
		Scope *ParentScope;
		/*!
		\fn FindContainedScope(const Scope& scopeToFind,std::uint32_t index)
		\brief Finds the given scope in the current scope and returns it's index 
		\param The scope to find 
		\param An out int that stores the index of the found scope
		\return Returns a pointer to the datum that was found
		*/
		Datum* FindContainedScope( Scope& scopeToFind, std::uint32_t& index) const ;
		void Reparent(Scope&& rhs);
	};
}
