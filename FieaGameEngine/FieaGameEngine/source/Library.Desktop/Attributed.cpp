#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)
	Attributed::Attributed()
		:SignatureList()
	{
		(*this)["this"] = (RTTI*)this;
		SignatureList.PushBack("this");
	}
	Attributed::Attributed(const Attributed& rhs)
		:Scope(rhs),SignatureList(rhs.SignatureList)
	{
		(*this)["this"] = (RTTI*)this;

	}
	Attributed::Attributed(Attributed&& rhs)
		:Scope(std::move(rhs)),SignatureList(std::move(SignatureList))
	{
		(*this)["this"] = (RTTI*)this;

	}
	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			SignatureList = rhs.SignatureList;
			(*this)["this"] = (RTTI*)this;
		}
		return *this;
	}
	Attributed& Attributed::operator=(Attributed&& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(std::move(rhs));
			SignatureList = std::move(rhs.SignatureList);
			(*this)["this"] = (RTTI*)this;
		}
		return *this;
	}
	Attributed::~Attributed()
	{
		SignatureList.Clear();
	}
	bool Attributed::IsPrescribedAttribute(const std::string& key) const
	{
		return (SignatureList.Find(key) != SignatureList.end());
	}
	bool Attributed::IsAuxilliaryAttribute(const std::string& key) const
	{
		return (IsAttribute(key) && (!IsPrescribedAttribute(key)));
	}
	bool Attributed::IsAttribute(const std::string& key) const
	{
		return (Find(key) != nullptr);
	}
	void Attributed::AddInternalSignature(const std::string& name, const int& defaultvalue, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::INTEGER);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultvalue);
		}
		SignatureList.PushBack(name);
	}
	void Attributed::AddInternalSignature(const std::string& name,const float& defaultvalue, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::FLOAT);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultvalue);
		}
		SignatureList.PushBack(name);

	}
	void Attributed::AddInternalSignature(const std::string& name,const  std::string& defaultvalue, std::uint32_t size)
	{

		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::STRING);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultvalue);
		}
		SignatureList.PushBack(name);

	}
	void Attributed::AddInternalSignature(const std::string& name, const glm::vec4& defaultvalue, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::VECTOR);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultvalue);
		}
		SignatureList.PushBack(name);

	}
	void Attributed::AddInternalSignature(const std::string& name,const glm::mat4& defaultvalue, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::MATRIX);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultvalue);
		}
		SignatureList.PushBack(name);

	}
	void Attributed::AddInternalSignature(const std::string& name, RTTI* const&  defaultValue, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");

		Datum& newDatum = Append(name);
		newDatum.SetType(Datum::DatumType::POINTER);
		newDatum.Reserve(size + 1);
		for (std::uint32_t i = 0; i < size; i++)
		{
			newDatum.PushBack(defaultValue);
		}
		SignatureList.PushBack(name);

	}
	void Attributed::AddExternalSignature(const std::string& name, int* address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);
	}
	void Attributed::AddExternalSignature(const std::string& name, float* address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);

	}
	void Attributed::AddExternalSignature(const std::string& name, glm::vec4* address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);
	}
	void Attributed::AddExternalSignature(const std::string& name, glm::mat4* address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);
	}
	void Attributed::AddExternalSignature(const std::string& name, std::string* address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);
	}
	void Attributed::AddExternalSignature(const std::string& name, RTTI** address, std::uint32_t size)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& newDatum = Append(name);
		newDatum.SetStorage(address, size);
		SignatureList.PushBack(name);
	}
	Datum& Attributed::AddNestedScopes(const std::string& name, Scope& scopeToAdopt)
	{
		if (IsPrescribedAttribute(name))
			throw std::exception("Attribute already exists");
		Datum& nestedDatum = Adopt(scopeToAdopt, name);
		SignatureList.PushBack(name);
		return nestedDatum;
	}
	Datum& Attributed::AppendAuxilliaryAttribute(const std::string& key)
	{
		if (IsPrescribedAttribute(key))
		{
			throw std::exception("Attribute already exists!");
		}
		return Append(key);
	}
	std::uint32_t Attributed::AuxilliaryBegin() const
	{
		return SignatureList.GetSize() + 1;
	}
}

