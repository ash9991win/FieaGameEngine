#include "pch.h"
#include "Datum.h"
#include"Scope.h"
#include<expat.h>
namespace Library
{
#pragma warning(disable : 4592)
	std::uint32_t Datum::DefaultSize = 1;
	std::string Datum::DatumTypeNames[] = { "UNASSIGNED","int","float","vec","mat","string","pointer","scope" };
#pragma warning(default : 4592)
	Datum::Datum()
		:Size(0), Capacity(0), CurrentType(DatumType::UNASSIGNED),IsExternal(false),Values()
	{
	}
	Datum::Datum(DatumType type, std::uint32_t capacity, bool fixedSize)
		:CurrentType(type),Size(0),Capacity(0),IsExternal(false),Values()
	{
		Reserve(capacity,fixedSize);
	}
	Datum::~Datum()
	{
		if(!IsExternal)
			Clear();
	}
	Datum::Datum(const Datum& rhs)
		:Datum()
	{
		operator=(rhs);
	}
	Datum::Datum(Datum&& rhs)
		: CurrentType(rhs.CurrentType),Values(rhs.Values),Size(rhs.Size),Capacity(rhs.Capacity),IsExternal(rhs.IsExternal)
	{
		rhs.Capacity = 0;
		rhs.Size = 0;
		rhs.CurrentType = DatumType::UNASSIGNED;
		rhs.Values.VP = nullptr;
	}
	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			if (!IsExternal)
				Clear();
			if (!rhs.IsExternal)
			{
				Capacity = 0U;
				Size = 0U;
				Values.VP = nullptr;
				CurrentType = rhs.CurrentType;
				IsExternal = rhs.IsExternal;
				Reserve(rhs.Capacity);
				for (std::uint32_t i = 0; i < rhs.Size; i++)
				{
					switch (CurrentType)
					{
					case DatumType::FLOAT:
					{
						PushBack(rhs.Get<float>(i));
						break;
					}
					case DatumType::INTEGER:
					{
						PushBack(rhs.Get<int>(i));
						break;
					}
					case DatumType::MATRIX:
					{
						PushBack(rhs.Get<Matrix4>(i));
						break;
					}
					case DatumType::VECTOR:
					{
						PushBack(rhs.Get<Vector4>(i));
						break;
					}
					case DatumType::STRING:
					{
						PushBack(rhs.Get<std::string>(i));
						break;
					}			
					case DatumType::POINTER:
					{
						PushBack(rhs.Get<RTTI*>(i));
					break;
					}
					case DatumType::TABLE:
					{
						PushBack(*rhs.Get<Scope*>(i));
						break;
					}
					}
				}
			}
			if (rhs.IsExternal)
			{
				IsExternal = true;
				CurrentType = rhs.CurrentType;
				Size = rhs.Size;
				Capacity = rhs.Capacity;
				Values = rhs.Values;
			}
		}
		return *this;
	}
	Datum& Datum::operator=(Datum&& rhs)
	{
		if (this != &rhs)
		{
			if (!IsExternal)
				Clear();
			Values = rhs.Values;
			CurrentType = rhs.CurrentType;
			Size = rhs.Size;
			Capacity = rhs.Capacity;

			rhs.Values.VP = nullptr;
			rhs.Capacity = 0;
			rhs.Size = 0;
			IsExternal = rhs.IsExternal;
			rhs.CurrentType = DatumType::UNASSIGNED;
		}
		return *this;
	}
	Datum& Datum::operator=(const int& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::INTEGER;
		}
		if (CurrentType == DatumType::INTEGER)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=(const float& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::FLOAT;
		}
		if (CurrentType == DatumType::FLOAT)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=(const std::string& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::STRING;
		}
		if (CurrentType == DatumType::STRING)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=(const Matrix4& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::MATRIX;
		}
		if (CurrentType == DatumType::MATRIX)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=( RTTI* rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::POINTER;
		}
		if (CurrentType == DatumType::POINTER)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=(Scope& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::TABLE;
		}
		if (CurrentType == DatumType::TABLE)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum& Datum::operator=(const Vector4& rhs)
	{
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = DatumType::VECTOR;
		}
		if (CurrentType == DatumType::VECTOR)
		{
			Set(rhs);
			return *this;
		}
		throw std::exception("Incompatible types");
	}
	Datum::DatumType Datum::Type() const
	{
		return CurrentType;
	}
	void Datum::SetType(Datum::DatumType newType)
	{
		if (CurrentType == DatumType::UNASSIGNED || CurrentType == newType)
		{
			CurrentType = newType;
			return;
		}
		throw std::exception("Type already assigned");
	}
	void Datum::PopBack()
	{
		if (!IsExternal)
		{
			if (Size > 0)
			{
				--Size;
				switch (CurrentType)
				{
				case DatumType::MATRIX:
					Values.Matrix[Size].~Matrix4();
					break;
				case DatumType::STRING:
					Values.String[Size].~String();
					break;
				case DatumType::VECTOR:
					Values.Vector[Size].~Vector4();
					break;
				case DatumType::POINTER:
					Values.Rtti[Size] = nullptr;
					break;
				case DatumType::TABLE:
					Values.Table[Size] = nullptr;
					break;
				case DatumType::UNASSIGNED:
					Size++;
					break;
				}
			}
			return;
		}
		throw std::exception("Invalid operation on external storage");
	}
	void Datum::Clear()
	{
		if (!IsExternal)
		{
			while (Size > 0)
			{
				PopBack();
			}
			Capacity = 0;
			if (Values.VP)
			{
				free(Values.VP);
				Values.VP = nullptr;
			}
			return;
		}
		throw std::exception("Invalid operation on external storage");
	}
	bool Datum::operator!=(const Datum& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const int& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const float& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const std::string& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const Matrix4& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const Vector4& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const RTTI*& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}
	bool Datum::operator==(const Datum& rhs) const
	{
		return ((CurrentType == rhs.CurrentType) && (Size == rhs.Size) && (Capacity == rhs.Capacity) && CompareContents(rhs));
	}
	bool Datum::operator==(const int& rhs) const
	{
		return (Get<int>() == rhs);
	}
	bool Datum::operator==(const float& rhs) const
	{
		return (Get<float>() == rhs);
	}
	bool Datum::operator==(const std::string& rhs) const
	{
		return ((Get<std::string>().compare(rhs)) == 0);
	}
	bool Datum::operator==(const Vector4& rhs) const
	{
		return ((Get<Vector4>() == (rhs)));
	}
	bool Datum::operator==(const Matrix4& rhs) const
	{
		return ((Get<Matrix4>() == (rhs)));
	}
	bool Datum::operator==(const RTTI*& rhs) const
	{
		//TODO Add RTTI's equals method
		return((Get<RTTI*>() == (rhs)));
	}
	bool Datum::operator==(const Scope& rhs) const
	{
		//TODO Overload the equals operator of the scope, so add Scope.h here and then call the == operator of the scope
		return(Get<Scope*>()->operator==(rhs));
	}
	void Datum::Reserve(std::uint32_t newCapacity, bool fixedSize)
	{
		if (!IsExternal)
		{
			if (Capacity < newCapacity)
			{
				switch (CurrentType)
				{
				case DatumType::FLOAT:
				{
					Values.Float = reinterpret_cast<float*>(std::realloc(Values.Float, (sizeof(float) * newCapacity)));
					break;
				}
				case DatumType::INTEGER:
				{
					Values.Integer = reinterpret_cast<int*>(std::realloc(Values.Integer, (sizeof(int) * newCapacity)));
					break;
				}
				case DatumType::MATRIX:
				{
					Values.Matrix = reinterpret_cast<Matrix4*>(std::realloc(Values.Matrix, (sizeof(Matrix4) * newCapacity)));
					break;
				}
				case DatumType::VECTOR:
				{
					Values.Vector = reinterpret_cast<Vector4*>(std::realloc(Values.Vector, (sizeof(Vector4) * newCapacity)));
					break;
				}
				case DatumType::STRING:
				{
					Values.String = reinterpret_cast<std::string*>(std::realloc(Values.String, (sizeof(std::string) * newCapacity)));
					break;
				}
				case DatumType::POINTER:
				{
					Values.Rtti = reinterpret_cast<RTTI**>(std::realloc(Values.Rtti, (sizeof(RTTI*) * newCapacity)));
					break;
				}
				case DatumType::TABLE:
				{
					Values.Table = reinterpret_cast<Scope**>(std::realloc(Values.Table, (sizeof(Scope*) * newCapacity)));
					break;
				}
				default:
					throw std::exception("Uninitalized data type");
					break;
				}
				Capacity = newCapacity;
				if (fixedSize)
				{
					for (std::uint32_t i = Size; i < Capacity; i++)
					{
						SetDefault(i);
					}
					Size = Capacity;
				}
			}
			return;
		}
		throw std::exception("Invalid operation on external storage");
	}
	void Datum::SetStorage(int* values, std::uint32_t size)
	{
		if(!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::INTEGER;
		Values.Integer = values;
		Size = Capacity = size;
	}
	void Datum::SetStorage(float* values, std::uint32_t size)
	{
		if(!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::FLOAT;
		Values.Float = values;
		Size = Capacity = size;

	}
	void Datum::SetStorage(std::string* values, std::uint32_t size)
	{
		if (!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::STRING;
		Values.String = values;
		Size = Capacity = size;

	}
	void Datum::SetStorage(Matrix4* values, std::uint32_t size)
	{
		if (!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::MATRIX;
		Values.Matrix = values;
		Size = Capacity = size;

	}
	void Datum::SetStorage(Vector4* values, std::uint32_t size)
	{
		if (!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::VECTOR;
		Values.Vector = values;
		Size = Capacity = size;
	}
	void Datum::SetStorage(RTTI** values, std::uint32_t size)
	{
		if (!IsExternal)
			Clear();
		IsExternal = true;
		CurrentType = DatumType::POINTER;
		Values.Rtti = values;
		Size = Capacity = size;
	}
	void Datum::Set(const int& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::INTEGER;
		if (CurrentType == DatumType::INTEGER)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}
				if (index == Size)
				{
					PushBack(value);
					return;
				}
			}
			Values.Integer[index] = value;
			return;
		}

		throw std::exception("Invalid type");
	}
	void Datum::Set(const float& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::FLOAT;
		if (CurrentType == DatumType::FLOAT)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}
				if (index == Size)
				{
					PushBack(value);
					return;
				}
			}
			Values.Float[index] = value;
			return;
		}
		throw std::exception("Invalid type");

	}
	void Datum::Set(const std::string& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::STRING;
		if (CurrentType == DatumType::STRING)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{		
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}	
				if (index == Size)
				{
					PushBack(value);
					return;
				}
			}
			Values.String[index] = value;
			return;
		}
		throw std::exception("Invalid type");
	}
	void Datum::Set(const glm::vec4& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::VECTOR;
		if (CurrentType == DatumType::VECTOR)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}
				if (index == Size)
				{
					PushBack(value);
					return;
				}
			}
				Values.Vector[index] = value;
			return;
		}
		throw std::exception("Invalid type");

	}
	void Datum::Set(const glm::mat4& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::MATRIX;
		if (CurrentType == DatumType::MATRIX)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}
				if (index == Size)
				{
					PushBack(value);
					return;
				}
			}	
			Values.Matrix[index] = value;
			return;
		}
		throw std::exception("Invalid type");

	}
	void Datum::Set( RTTI* const& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::POINTER;
		if (CurrentType == DatumType::POINTER)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (Size >= Capacity)
				{
					Reserve(Capacity + 1);
				}
				if (index == Size)
				{
					PushBack(value);
				}
			}
			
				Values.Rtti[index] = value;
			return;
		}
		throw std::exception("Invalid type");

	}
	void Datum::Set( Scope& value, std::uint32_t index)
	{
		if (CurrentType == DatumType::UNASSIGNED)
			CurrentType = DatumType::TABLE;
		if (CurrentType == DatumType::TABLE)
		{
			if (index > Size)
				throw std::exception("Invalid index");
			if (!IsExternal)
			{
				if (index == Size)
				{
					PushBack(value);
				}
			}

			Values.Table[index] = &value;
			return;
		}
		throw std::exception("Invalid type");

	}
	void Datum::PushBack(const int& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::INTEGER))
		{
			CurrentType = DatumType::INTEGER;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			new (Values.Integer + Size)int(value);
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");
	}
	void Datum::PushBack(const float& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::FLOAT))
		{
			CurrentType = DatumType::FLOAT;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			new (Values.Float + Size)float(value);
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::PushBack(const std::string& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::STRING))
		{
			CurrentType = DatumType::STRING;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			new (Values.String + Size)std::string(value);
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::PushBack(const Vector4& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::VECTOR))
		{
			CurrentType = DatumType::VECTOR;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			new (Values.Vector + Size)Vector4(value);
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::PushBack(const Matrix4& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::MATRIX))
		{
			CurrentType = DatumType::MATRIX;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			new (Values.Integer + Size)Matrix4(value);
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::PushBack( RTTI* const& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::POINTER))
		{
			CurrentType = DatumType::POINTER;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			Values.Rtti[Size] = value;
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::PushBack(Scope& value)
	{
		if (!IsExternal && (CurrentType == DatumType::UNASSIGNED || CurrentType == DatumType::TABLE))
		{
			CurrentType = DatumType::TABLE;
			if (Size >= Capacity)
			{
				Reserve(Capacity + 1);
			}
			Values.Table[Size] = &value;
			++Size;
			return;
		}
		throw std::exception("Invalid operation on external storage");

	}
	void Datum::Remove(std::uint32_t index)
	{
		if (!IsExternal)
		{
			if (index < Size)
			{
				switch (CurrentType)
				{
				case DatumType::INTEGER:
				{
					std::memmove(Values.Integer + index, Values.Integer + index + 1, (sizeof(int) * (Size - index - 1)));
					break;
				}
				case DatumType::FLOAT:
				{
					std::memmove(Values.Float + index, Values.Float + index + 1, (sizeof(float) * (Size - index - 1)));
					break;
				}
				case DatumType::MATRIX:
				{
					Values.Matrix[index].~Matrix4();
					std::memmove(Values.Matrix + index, Values.Matrix + index + 1, (sizeof(Matrix4) * (Size - index - 1)));
					break;
				}
				case DatumType::VECTOR:
				{
					Values.Vector[index].~Vector4();
					std::memmove(Values.Vector + index, Values.Vector + index + 1, (sizeof(Vector4) * (Size - index - 1)));
					break;
				}
				case DatumType::STRING:
				{
					Values.String[index].~String();
					std::memmove(Values.String + index, Values.String + index + 1, (sizeof(String) * (Size - index - 1)));
					break;
				}
				case DatumType::POINTER:
				{
					Values.Rtti[index] = nullptr;
					std::memmove(Values.Rtti + index, Values.Rtti + index + 1, (sizeof(RTTI*) * (Size - index - 1)));
					break;
				}
				case DatumType::TABLE:
				{
					Values.Table[index] = nullptr;
					std::memmove(Values.Table + index, Values.Table + index + 1, (sizeof(Scope*) * (Size - index - 1)));
					break;
				}
				default:
					++Size;
					break;
				}
				--Size;
			}
			return;
		}
		throw std::exception("Invalid operation on external storage");
	}
	void Datum::SetFromString(const std::string& value, DatumType type,std::uint32_t index)
	{
		if (type == DatumType::UNASSIGNED || (CurrentType != type && CurrentType != DatumType::UNASSIGNED))
		{
			throw std::exception("Invalid type");
		}
		if (CurrentType == DatumType::UNASSIGNED)
		{
			CurrentType = type;
		}
		if (CurrentType == type)
		{
		//	CurrentType = type;
			switch(CurrentType)
			{
			case DatumType::INTEGER:
			{
				int tempValue;
				sscanf_s(value.c_str(), "%d", &tempValue);
				Set(tempValue,index);
				break;
			}
			case DatumType::FLOAT:
			{
				float tempValue;
				sscanf_s(value.c_str(), "%f", &tempValue);
				Set(tempValue,index);
				break;
			}
			case DatumType::STRING:
			{
				Set(value,index);
				break;
			}
			case DatumType::MATRIX:
			{
				float tempFloats[16];
				std::stringstream tempStream(value);
				for (int i = 0; i < 15; i++)
				{
					tempStream >> tempFloats[i];
				}
				Set(glm::make_mat4x4(tempFloats),index);
				break;
			}
			case DatumType::VECTOR:
			{
				{
					glm::vec4 vec;
					sscanf_s(value.c_str(), "%f %f %f %f", &vec.x, &vec.y, &vec.z, &vec.w);
					Set(vec,index);
					break;
				}
			}
			}
			return;
		}
	}
	void Datum::SetFromString(const std::string& value)
	{
		if (CurrentType != DatumType::UNASSIGNED)
		{
			SetFromString(value, CurrentType);
			return;
		}
		throw std::exception("Initialize the type first");
	}
	std::string Datum::ToString(std::uint32_t index) const
	{
		std::string tempString;
		switch (CurrentType)
		{
		case DatumType::FLOAT:
		{
			tempString = std::to_string(Get<float>(index));
			break;
		}
		case DatumType::INTEGER:
		{
			tempString = std::to_string(Get<int>(index));
			break;
		}
		case DatumType::MATRIX:
		{
			tempString = glm::to_string(Get<Matrix4>(index));
			break;
		}
		case DatumType::VECTOR:
		{
			tempString = glm::to_string(Get<Vector4>(index));
			break;
		}
		case DatumType::POINTER:
		{
			tempString = Get<RTTI*>(index)->ToString();
			break;
		}
		case DatumType::STRING:
		{
			tempString = Get<std::string>(index);
			break;
		}
			default:
			{
				throw std::exception("Invalid type");
			}
		}
		return tempString;
	}
	std::uint32_t Datum::GetCapacity() const
	{
		return Capacity;
	}
	std::uint32_t Datum::GetSize() const
	{
		return Size;
	}
	void Datum::SetDefault(std::uint32_t index)
	{
		switch (CurrentType)
		{
		case DatumType::FLOAT:
		{
			new (Values.Float + index)float();
			break;
		}
		case DatumType::INTEGER:
		{
			new (Values.Integer + index)int();
			break;
		}
		case DatumType::STRING:
		{
			new (Values.String + index)std::string();
			break;
		}
		case DatumType::VECTOR:
		{
			new (Values.Vector + index)glm::vec4();
			break;
		}
		case DatumType::MATRIX:
		{
			new (Values.Matrix + index)glm::mat4();
			break;
		}
		case DatumType::POINTER:
		{
			Values.Rtti[index] = nullptr;
		}
		case DatumType::TABLE:
		{
			Values.Table[index] = nullptr;
		}
		default:

			break;
		}
		}
	template<>
	const int& Datum::Get<int>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::INTEGER)
		{
			if (index < Size)
			{
				return Values.Integer[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	const float& Datum::Get<float>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::FLOAT)
		{
			if (index < Size)
			{
				return Values.Float[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	const std::string& Datum::Get<std::string>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::STRING)
		{
			if (index < Size)
			{
				return Values.String[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	const Datum::Matrix4& Datum::Get<Datum::Matrix4>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::MATRIX)
		{
			if (index < Size)
			{
				return Values.Matrix[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	const Datum::Vector4& Datum::Get<Datum::Vector4>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::VECTOR)
		{
			if (index < Size)
			{
				return Values.Vector[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	RTTI* const& Datum::Get<RTTI*>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::POINTER)
		{
			if (index < Size)
			{
				return Values.Rtti[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	Scope* const& Datum::Get<Scope*>(std::uint32_t index) const
	{
		if (CurrentType == DatumType::TABLE)
		{
			if (index < Size)
			{
				return Values.Table[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	int& Datum::Get<int>(std::uint32_t index)
	{
		if (CurrentType == DatumType::INTEGER)
		{
			if (index < Size)
			{
				return Values.Integer[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	float& Datum::Get<float>(std::uint32_t index)
	{
		if (CurrentType == DatumType::FLOAT)
		{
			if (index < Size)
			{
				return Values.Float[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	std::string& Datum::Get<std::string>(std::uint32_t index)
	{
		if (CurrentType == DatumType::STRING)
		{
			if (index < Size)
			{
				return Values.String[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	Datum::Matrix4& Datum::Get<glm::mat4>(std::uint32_t index)
	{
		if (CurrentType == DatumType::MATRIX)
		{
			if (index < Size)
			{
				return Values.Matrix[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	Datum::Vector4& Datum::Get<Datum::Vector4>(std::uint32_t index)
	{
		if (CurrentType == DatumType::VECTOR)
		{
			if (index < Size)
			{
				return Values.Vector[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	RTTI*& Datum::Get<RTTI*>(std::uint32_t index)
	{
		if (CurrentType == DatumType::POINTER)
		{
			if (index < Size)
			{
				return Values.Rtti[index];
			}
		}
		throw std::exception("Invalid index");
	}
	template<>
	Scope*& Datum::Get<Scope*>(std::uint32_t index)
	{
		if (CurrentType == DatumType::TABLE)
		{
			if (index < Size)
			{
				return Values.Table[index];
			}
		}
		throw std::exception("Invalid index");
	}
	bool Datum::CompareContents(const Datum& rhs) const
	{
		if (CurrentType == rhs.CurrentType)
		{
			switch (CurrentType)
			{
			case DatumType::FLOAT:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<float>(i) != rhs.Get<float>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::INTEGER:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<int>(i) != rhs.Get<int>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::STRING:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<std::string>(i) != rhs.Get<std::string>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::VECTOR:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<Vector4>(i) != rhs.Get<Vector4>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::MATRIX:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<Matrix4>(i) != rhs.Get<Matrix4>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::POINTER:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					if (Get<RTTI*>(i) != rhs.Get<RTTI*>(i))
					{
						return false;
					}
				}
				break;
			}
			case DatumType::TABLE:
			{
				for (std::uint32_t i = 0; i < Size; i++)
				{
					//TODO Change this to dereference scope and access scope's equal operators
					if (Get<Scope*>(i)->operator!=(*rhs.Get<Scope*>(i)))
					{
						return false;
					}
				}
				break;
			}
			}
			return true;

		}
		return false;
	}
	bool Datum::IsExternalStorage()
	{
		return IsExternal;
	}
	Scope& Datum::operator[](std::uint32_t index)
	{
		return (*(Get<Scope*>(index)));
	}
	Scope & Datum::GetScope(std::uint32_t index)
	{
		if (index >= Size)
			throw std::exception("Invalid index");
		if (CurrentType != DatumType::TABLE)
			throw std::exception("Not a table");
		return *Values.Table[index];
	}
}