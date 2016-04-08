#pragma once
#include<string>
template<typename TKey>
class EqualityFunctor
{
public: 
	bool operator()(const TKey& lhs, const TKey& rhs)
	{
		return (lhs == rhs);
	}
};
template<>
class EqualityFunctor<char*>
{
public:
	bool operator()(char* const& lhs, char* const& rhs)
	{
		if (std::strcmp(lhs, rhs))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
