#pragma once
#include<cstdint>
#include<string>
#include<sstream>
#include"glm/glm.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"glm/gtx/string_cast.hpp"
#include"RTTI.h"
namespace Library
{
	class Scope;
	/*!
	\class Datum
	\brief A datum class that can decide its type at run time*/
	class Datum
	{
		typedef glm::vec4 Vector4;
		typedef glm::mat4 Matrix4;
		typedef std::string String;
	public:
		/*!
		\class Enum class DatumType
		\brief A enum class describing various types that the datum can store
		*/
		enum class DatumType
		{
			UNASSIGNED, INTEGER, FLOAT, VECTOR, MATRIX, STRING, POINTER, TABLE,END
		};
		static std::string DatumTypeNames[8] ;
		/*
		\fn Datum();
		\brief The default constructor
		*/
		Datum();
		/*!
		\fn 	Datum(DatumType, std::uint32_t newCapacity = 1, bool fixedSize = false)
		\brief A parametrized constructor that sets the current type and reserves a given capacity
		*/
		Datum(DatumType, std::uint32_t newCapacity = 1, bool fixedSize = false);
		/*!
		\fn ~Datum()
		\brief The destructor that frees any allocated memory
		*/
		~Datum();
		/*!
		\fn Datum(const Datum& rhs)
		\brief The copy constructor
		*/
		Datum(const Datum& rhs);
		/*!
		\fn Datum(const Datum& rhs)
		\brief The move constructor
		*/
		Datum(Datum&& rhs);
		/*
		\fn Datum(const Datum& rhs)
		\brief Overloaded = operator that copies from a datum
		*/
		Datum& operator=(const Datum& rhs);
		/*
		\fn Datum(const Datum& rhs)
		\brief Overloaded = operator that moves from a datum
		*/
		Datum& operator=(Datum&& rhs);
		/*
		\fn Datum(const Datum& rhs)
		\brief Overloaded = operator that sets the first data of datum with a given value
		*/
		Datum& operator=(const int& rhs);
		Datum& operator=(const float& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(const Vector4& rhs);
		Datum& operator=(const Matrix4& rhs);
		Datum& operator=( RTTI* rhs);
		Datum& operator=(Scope& rhs);
		/*!
		\fn Type() const
		\brief Returns the current type of the Datum
		*/
		DatumType Type() const;
		/*!
		\fn SetType(DatumType newType)
		\brief Sets teh current type
		*/
		void SetType(DatumType newType);
		/*!
		\fn Clear()
		\brief Clears any allocated memory
		*/
		void Clear();
		/*!
		\fn SetStorage(int* values,size)
		\brief Sets the Datum as an external datum of the given type
		*/
		void SetStorage(int* values,std::uint32_t size);
		void SetStorage(float* values, std::uint32_t size);
		void SetStorage(std::string* values, std::uint32_t size);
		void SetStorage(Matrix4* values, std::uint32_t size);
		void SetStorage(Vector4* values, std::uint32_t size);
		void SetStorage(RTTI** values , std::uint32_t size);
		/*!
		\fn operator!=(const Datum& rhs) const
		\brief Compares if the two datums are unequal
		*/
		bool operator!=(const Datum& rhs) const;
		bool operator!=(const int& rhs) const;
		bool operator!=(const float& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const Vector4& rhs) const;
		bool operator!=(const Matrix4& rhs) const;
		bool operator!=(const RTTI*& rhs) const;
		bool operator!=(const Scope& rhs) const;
		/*!
		\fn operator==(const Datum& rhs) const
		\brief Compares if the two datums are equal
		*/
		bool operator==(const Datum& rhs) const;
		bool operator==(const int& rhs) const;
		bool operator==(const float& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const Matrix4& rhs) const;
		bool operator==(const Vector4& rhs) const;
		bool operator==(const RTTI*& rhs) const;
		bool operator==(const Scope& rhs) const;
		/*!
		\fn Set(const int& value, index)
		\brief Sets a given data at the index if the type is either unassigned or the current type
		*/
		void Set(const int& value, std::uint32_t index = 0);
		void Set(const float& value, std::uint32_t index = 0);
    	void Set(const std::string& value, std::uint32_t index = 0);	
		void Set(const glm::vec4& value, std::uint32_t index = 0);
		void Set(const glm::mat4& value, std::uint32_t index = 0);
		void Set(RTTI* const& rhs, std::uint32_t index = 0);
		void Set( Scope& rhs, std::uint32_t index = 0);
		/*!
		\fn SetsFromString(string,DatumType)
		\brief Parses the current string for the current type
		*/
		void SetFromString(const std::string&, DatumType, std::uint32_t index = 0);
		/*!
		\fn SetFromString(string)
		\brief This is used when the type has already been assigned. Similar to SetFromString(stirng, type)
		*/
		void SetFromString(const std::string&);
		/*!
		\fn ToString(index)
		\brief Converts the data at the given index to its string representation
		*/
		std::string ToString(std::uint32_t index = 0) const;
		/*!
		\fn Reserve(Capacity,fixedSize = false)
		\brief Reserves a given capacity
		*/
		void Reserve(std::uint32_t newCapacity, bool fixedSize = false);
		/*!
		\fn Remove(Index)
		\brief Removes the particualr element at the index from the Datum
		*/
		void Remove(std::uint32_t index);
		/*!
		\fn PopBack()
		\brief Removes the last element from the Datum
		*/
		void PopBack();
		/*!
		\fn PushBack(value)
		\brief Pushes the given value to the end of the datum
		*/
		void PushBack(const int& value);
		void PushBack(const float& value);
		void PushBack(const std::string& value);
		void PushBack(const Vector4& value);
		void PushBack(const Matrix4& value);
		void PushBack( RTTI* const& value);
		void PushBack( Scope& value);
		bool IsExternalStorage();
		/*!
		\fn Get(index) cosnt
		\brief Gets a const reference to the data at the given index
		*/
		template<typename T>
		const T& Get(std::uint32_t index = 0) const;
		template<typename T>
		/*!
		\fn Get(index)
		\brief Gets a  reference to the data at the given index
		*/
		T& Get(std::uint32_t index = 0);
		/*!
		\fn GetCapacity()
		\brief Returns the capacity of the datum
		*/
		std::uint32_t GetCapacity() const;
		/*!
		\fn GetSize()
		\brief Returns the size of the datum
		*/
		std::uint32_t GetSize() const;
		Scope& operator[](std::uint32_t index);
		Scope& GetScope(std::uint32_t index = 0);
	
	private:
		/*!
		\var Size
		\brief The Size of the datum
		*/
		std::uint32_t Size;
		/*!
		\var Capacity
		\brief The capacity of the datum
		*/
		std::uint32_t Capacity;
		/*!
		\var IsExternal
		\brief A flag to check whether the datum is an internal or an external storage
		*/
		bool IsExternal;
		/*!
		\var DatumUnion
		\brief A union that stores the pointers to the various types that the datum can store
		*/
		union DatumUnion
		{
			void* VP;
			int* Integer;
			float* Float;
			std::string* String;
			Vector4* Vector;
			Matrix4* Matrix;
			RTTI** Rtti;
			Scope** Table;
			DatumUnion() :VP(nullptr)
			{
			}
		};
		/*!
		\var Values
		\brief The union instance
		*/
		DatumUnion Values;
		/*!
		\var CurrentType
		\brief The variable that stores the current type of the union
		*/
		DatumType CurrentType;
		/*!
		\var DefaultSize
		\brief The static DefaultSize of the Datum
		*/
		static std::uint32_t DefaultSize;
		/*!
		\fn SetDefault(index)
		\brief A private function taht sets the index with the default value of the type
		*/
		void SetDefault(std::uint32_t index = 0);
		/*!
		\fn CompareContents(Datum)
		\brief Compares the contents of the datum with the given datum
		*/
		bool CompareContents(const Datum& rhs) const;

	};
	template<>
	int& Datum::Get<int>(std::uint32_t index);
	template<>
	float& Datum::Get<float>(std::uint32_t index);
	template<>
	glm::vec4& Datum::Get<glm::vec4>(std::uint32_t index);
	template<>
	std::string& Datum::Get<std::string>(std::uint32_t index);
	template<>
	glm::mat4& Datum::Get<glm::mat4>(std::uint32_t index);
	template<>
	RTTI*& Datum::Get<RTTI*>(std::uint32_t index);
	template<>
	Scope*& Datum::Get<Scope*>(std::uint32_t index);
	template<>
	const int& Datum::Get<int>(std::uint32_t index) const;
	template<>
	const float& Datum::Get<float>(std::uint32_t index) const;
	template<>
	const glm::vec4& Datum::Get<glm::vec4>(std::uint32_t index) const;
	template<>
	const std::string& Datum::Get<std::string>(std::uint32_t index) const;
	template<>
	const glm::mat4& Datum::Get<glm::mat4>(std::uint32_t index) const;
	template<>
	RTTI* const& Datum::Get<RTTI*>(std::uint32_t index) const;
	template<>
	Scope* const& Datum::Get<Scope*>(std::uint32_t index) const;
}