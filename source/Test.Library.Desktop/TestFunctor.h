#pragma once
#include<cstdint>
namespace Library
{
	class TestFunctor
	{
	public:
		std::uint32_t operator()(std::uint32_t, std::uint32_t);
	};
}

