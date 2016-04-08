#pragma once
#include "Scope.h"
namespace Library
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed,Scope)
		/*!
		\fn Attributed()
		\brief The constructor which allocates memory for contained objects
		*/
	public:
		Attributed();
		/*!
		\fn ~Attributed
		\brief Since attributed is to be derived from, the destructor is made virtual
		*/
		virtual ~Attributed();
		/*!
		\fn Attributed(const Attributed& rhs)
		\brief The copy ctor
		\param The attributed class to be copied from
		*/
		Attributed(const Attributed& rhs);
		/*!
		\fn Attributed( Attributed&& rhs)
		\brief The move ctor
		\param The attributed class to be moved from
		*/
		Attributed(Attributed&& rhs);
		/*!
		\fn operator=(const Attributed& rhs)
		\brief The copy assignment operator
		\return Returns the copied attributed
		\param The attributed class to be copied from
		*/
		Attributed& operator=(const Attributed& rhs);
		/*!
		\fn operator=( Attributed&& rhs)
		\brief The move assignment operator
		\return Returns the moved attributed
		\param The attributed class to be moved from
		*/
		Attributed& operator=(Attributed&& rhs);
		/*!
		\fn IsPrescribedAttributed(const std::String& key) const
		\brief Checks if the given key is a prescribed attribute for the assosciated class
		\return REturns true if the key is found in the prescribed signature list
		\param The key to search for in the signature list
		*/
		bool IsPrescribedAttribute(const std::string& key) const;
		/*!
		\fn IsAuxilliaryAttribute(const std::string& key) const
		\brief Checks if the given key is an AUXILLIARY attribute
		\param The key to search for
		\return Returns true if the key is an auxilliary attribute
		*/
		bool IsAuxilliaryAttribute(const std::string& key) const;
		/*!
		\fn IsAttributed(const std::String& key) const
		\brief Checks if the given key is an attribute for the assosciated class
		\return REturns true if the key is found in the  signature list
		\param The key to search for in the signature list
		*/
		bool IsAttribute(const std::string& key) const;
		/*!
		\fn AppendAuxilliaryAttribute(const std::string& key)
		\brief Appends an auxilliary attribute onto the scope assosciated with this class
		\param The key to append
		\return Returns a datum reference which was created
		*/
		Datum& AppendAuxilliaryAttribute(const std::string& key);
		/*!
		\fn AuxilliaryBegin()
		\brief Returns the index of the first auxilliary attribute
		\return Returns the index
		*/
		std::uint32_t AuxilliaryBegin() const;
	protected:
		/*!
		\fn AddInternalSignature(std::string& name, DatumType type, default value)
		\brief Adds a singature of the given type onto the signature list
		\param NAme of the signature to be added
		\param Type of the signature to be added
		\param Value to be assigned to the signature list
		*/
		void AddInternalSignature(const std::string& name, const int& defaultvalue,std::uint32_t size = 0);
		void AddInternalSignature(const std::string& name, const float& defaultvalue, std::uint32_t size = 0);
		void AddInternalSignature(const std::string& name, const glm::vec4& defaultvalue, std::uint32_t size = 0);
		void AddInternalSignature(const std::string& name, const glm::mat4& defaultvalue , std::uint32_t size = 0);
		void AddInternalSignature(const std::string& name, const std::string& defaultvalue = "", std::uint32_t size = 0);
		void AddInternalSignature(const std::string& name, RTTI* const&  defaultvalue ,std::uint32_t size = 0);

		/*!
		\fn AddExternalSignature(string name, DatumType type, void* address)
		\brief Adds an external signature onto the signature list
		\param Name of the signature to be added
		\param Type of the signature to be added
		\param Address of the field to be added
		*/
		void AddExternalSignature(const std::string& name, int* address,std::uint32_t size);
		void AddExternalSignature(const std::string& name, float* address, std::uint32_t size);
		void AddExternalSignature(const std::string& name, std::string* address, std::uint32_t size);
		void AddExternalSignature(const std::string& name, glm::vec4* address, std::uint32_t size);
		void AddExternalSignature(const std::string& name, glm::mat4* address, std::uint32_t size);
		void AddExternalSignature(const std::string& name, RTTI** address, std::uint32_t size);
		Datum& AddNestedScopes(const std::string& name, Scope& adoptedScope);

#define DEFINE_INTERNAL_SIGNATURE(x,value,size) AddInternalSignature(std::string(#x),value,size);
#define DEFINE_EXTERNAL_SIGNATURE(x,size)       AddExternalSignature(std::string(#x),x,size);

		private:
		Vector<std::string> SignatureList;

	};
}

