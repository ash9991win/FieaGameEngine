#include "pch.h"
#include "Scope.h"
namespace Library
{
	RTTI_DEFINITIONS(Scope)
#pragma warning(disable : 4592)
	std::uint32_t Scope::DefaultCapacity = 10;
#pragma warning(default : 4592)

	Scope::Scope(std::uint32_t capacity)
		:ScopeTable(),ParentScope(nullptr),ScopeVector(capacity)
	{
	}
	Scope::Scope(const Scope& rhs)
		:ScopeTable(),ParentScope(nullptr),ScopeVector(0)
	{
		operator=(rhs);
	}
	Scope::Scope(Scope&& rhs)
		:ScopeTable(std::move(rhs.ScopeTable)),
		ScopeVector(std::move(rhs.ScopeVector)),
		ParentScope(rhs.ParentScope)
	{
		Reparent(std::move(rhs));
	}
	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			ScopeVector.Reserve(rhs.ScopeVector.GetSize());
			for (auto& currentPair : rhs.ScopeVector)
			{
				Datum& currentDatum = currentPair->second;
				if (currentDatum.Type() == Datum::DatumType::TABLE)
				{
					for (std::uint32_t i = 0; i < currentDatum.GetSize(); ++i)
					{
						Scope *newScope = new Scope(currentDatum[i]);
						Adopt(*newScope, currentPair->first);
					}
				}
				else
				{
					Datum& newDatum = Append(currentPair->first);
					newDatum = currentPair->second;
				}
			}
		}
		return *this;
	}
	Scope& Scope::operator=(Scope&& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			ScopeTable = std::move(rhs.ScopeTable);
			ScopeVector = std::move(rhs.ScopeVector);
			ParentScope = rhs.ParentScope;
			Reparent(std::move(rhs));
		}
		return *this;
	}
	Datum* Scope::Find(const std::string& key) const
	{
		if (key == "" || key.empty())
			throw std::exception("Cant find empty key!");
		for (auto& currentPair : ScopeVector)
		{
			if (currentPair->first == key)
			{
				return &currentPair->second;
			}
		}
		return nullptr;
	}
	Datum* Scope::Search(const std::string& key,const  Scope** scope) const
	{
		Datum* DatumFound = Find(key);
		if (DatumFound)
		{
			if (scope != nullptr)
			{
				*scope = this;
			}
			return DatumFound;
		}
		else if (DatumFound == nullptr && ParentScope)
		{
			return ParentScope->Search(key, scope);
		}
			return nullptr;
	}
	Datum& Scope::Append(const std::string& key)
	{
		if (key.empty())
		{
			throw std::exception("Invalid key");
		}
		Datum tempDatum;
		std::pair<std::string, Datum> tempPair(key, tempDatum);
		bool insertResult = false;
		Hashmap<std::string, Datum>::Iterator insertIter = ScopeTable.Insert(tempPair,insertResult);
		if (insertResult)
		{
			ScopeVector.PushBack(&(*insertIter));
		}
		return insertIter->second;
	}
	Scope& Scope::AppendScope(const std::string& key)
	{
		Datum& foundDatum = Append(key);

		if (foundDatum.Type() != Datum::DatumType::UNASSIGNED && foundDatum.Type() != Datum::DatumType::TABLE)
			throw std::exception("Key already assigned to a different type");

		Scope *tempScope = new Scope();
		tempScope->ParentScope = this;
		foundDatum.PushBack(*tempScope);
		return *tempScope;
	}
	Datum& Scope::Adopt(Scope& child, const std::string& name)
	{
		if (this == &child)
			throw std::exception("Cant adopt self");
		Datum& tempDatum = Append(name);
		if (tempDatum.Type() != Datum::DatumType::UNASSIGNED && tempDatum.Type() != Datum::DatumType::TABLE)
			throw std::exception("Invalid adoption");
		child.Orphan();
		child.ParentScope = this;
		tempDatum.PushBack(child);
		return tempDatum;
	}
	Scope* Scope::GetParent()
	{
		return ParentScope;
	}
	Datum& Scope::operator[](const std::string& key)
	{
		return Append(key);
	}
	Datum& Scope::operator[](const std::uint32_t index)
	{
		return (ScopeVector[index]->second);
	}
	Datum& Scope::operator[](const std::uint32_t index) const
	{
		return const_cast<Datum&>(ScopeVector[index]->second);
	}
	bool Scope::operator==(const Scope& rhs) const
	{
		if (ScopeVector.GetSize() == rhs.ScopeVector.GetSize())
		{
			for (std::uint32_t i = 0; i < ScopeVector.GetSize(); ++i)
			{
				if ((*(ScopeVector[i]) != (*(rhs.ScopeVector[i]))))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool Scope::Equals(const RTTI* rhs) const
	{
		Scope *rhsScope = rhs->As<Scope>();
		if (rhsScope == nullptr)
			return false;
		return operator==(*rhsScope);
	}
	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}
	std::string Scope::FindName(Scope* const scopeToFind) const
	{
		for (auto& currentPair : ScopeVector)
		{
			Datum& currentDatum = currentPair->second;
			if (currentDatum.Type() == Datum::DatumType::TABLE)
			{
				for (std::uint32_t i = 0; i < currentDatum.GetSize(); ++i)
				{
					if (currentDatum[i] == *scopeToFind)
					{
						return currentPair->first;
					}
				}
			}
		}
		return "";
	}
	void Scope::Clear()
	{
		
		Orphan();
		for (auto& currentPair : ScopeVector)
		{
			if (currentPair->second.Type() == Datum::DatumType::TABLE)
			{
				Datum& tempDatum = currentPair->second;
				for (std::uint32_t i = 0; i < tempDatum.GetSize(); ++i)
				{
					if (tempDatum.Get<Scope*>(i))
					{
						tempDatum[i].ParentScope = nullptr;
						delete tempDatum.Get<Scope*>(i);
					}
				}
			}
		}
		ScopeTable.Clear();
		ScopeVector.Clear();
		ParentScope = nullptr;
	}
	void Scope::Orphan()
	{
		if (ParentScope == nullptr)
			return;
		std::uint32_t indexToRemove;
		Datum* scopeToSever = ParentScope->FindContainedScope(*this, indexToRemove);
		if (scopeToSever)
		{
			scopeToSever->Remove(indexToRemove);
			ParentScope = nullptr;
		}
	}
	std::uint32_t Scope::Size() const
	{
		return ScopeTable.Count();
	}
	Datum* Scope::FindContainedScope( Scope& scopeToFind, std::uint32_t& index) const
	{
		for (auto& currentPair : ScopeVector)
		{
			Datum& currentDatum = currentPair->second;
			if (currentDatum.Type() == Datum::DatumType::TABLE)
			{
				for (std::uint32_t i = 0; i < currentDatum.GetSize(); ++i)
				{
					if (currentDatum.Get<Scope*>(i) == &scopeToFind)
					{
						index = i;
						return  &(currentPair->second);
					}
				}
			}
		}
		return nullptr;
	}
	std::string Scope::ToString() const
	{
		stringstream returnStream;
		for (auto& currentPair : ScopeVector)
		{
			Datum& currentDatum = currentPair->second;
			if (currentDatum.Type() == Datum::DatumType::TABLE)
			{
				for (std::uint32_t i = 0; i < currentDatum.GetSize(); ++i)
				{
					returnStream<<std::string(" ")<<currentDatum[i].ToString()<<std::string("\n");
				}
			}
			returnStream << currentPair->first  <<std::string(" ")<< currentDatum.DatumTypeNames[(int)currentDatum.Type()]<<std::string("\n");
		}
		return returnStream.str();
	}
	void Scope::Reparent(Scope&& rhs)
	{
		if (rhs.ParentScope)
		{
			std::uint32_t index;
			Datum* childDatum = rhs.ParentScope->FindContainedScope(rhs, index);
			if (childDatum)
			{
				childDatum->Set(*this, index);
			}
			rhs.ParentScope = nullptr;
		}
		for (auto& currentPair : ScopeVector)
		{
			Datum& currentDatum = currentPair->second;
			if (currentDatum.Type() == Datum::DatumType::TABLE)
			{
				for (std::uint32_t i = 0; i < currentDatum.GetSize(); i++)
				{
					currentDatum[i].ParentScope = this;
				}
			}
		}
	}
	Scope::~Scope()
	{
		Clear();
	}
	Scope::Iterator::Iterator()
		:Owner(nullptr),Index(0)
	{
	}
	Scope::Iterator::Iterator( const Scope* owner, std::uint32_t index)
		:Owner(owner),Index(index)
	{

	}
	Scope::Iterator& Scope::Iterator::operator++()
	{
		if (Index >= Owner->Size())
			throw std::exception("Cant increment");
		Index++;
		return *this;
	}
	Scope::Iterator Scope::Iterator::operator++(int)
	{
		Iterator tempIter = *this;
		operator++();
		return tempIter;
	}
	Datum& Scope::Iterator::operator*() 
	{
		if (Owner == nullptr || Index >= Owner->Size())
			throw std::exception("Invalid iterator");
		return Owner->operator[](Index);
	}
	bool Scope::Iterator::operator==(const Iterator& rhs) const
	{
		return (Owner == rhs.Owner && Index == rhs.Index);
	}
	bool Scope::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}
	Scope::Iterator Scope::begin() const
	{
		return Iterator(this, 0);
	}
	Scope::Iterator Scope::end() const
	{
		return Iterator(this, Size());
	}
}