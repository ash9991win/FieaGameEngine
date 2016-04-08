#include "pch.h"
#include "TestFunctor.h"
namespace Library
{
	std::uint32_t TestFunctor::operator()(std::uint32_t size, std::uint32_t capacity)
	{
		if (capacity == 0)
		{
			return 3U;
		}
		else
		{
			return (capacity + size / 2);
		}
	}
}
