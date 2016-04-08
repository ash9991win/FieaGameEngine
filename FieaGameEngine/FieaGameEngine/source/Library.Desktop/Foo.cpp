#include"pch.h"
namespace FooC
{
	Foo::Foo()
		: mData(0), mPointerData(new int(0))
	{
	}
	Foo::Foo(int pData) :mData(pData), mPointerData(new int(0))
	{
	}
	Foo::Foo(const Foo& rhs)
		:Foo()
	{
		operator=(rhs);
	}
	Foo::Foo(int data, int pointerdata)
		:mData(data),mPointerData(new int(pointerdata))
	{
	}
	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			delete mPointerData;
			mData = rhs.mData;
			if (rhs.mPointerData != nullptr)
			{
				mPointerData = new int(*(rhs.mPointerData));
			}
			else
			{
				mPointerData = nullptr;
			}
		}
		return *this;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return ((mData == rhs.mData) && (*mPointerData == *(rhs.mPointerData)));
	}
	bool Foo::operator!=(const Foo& rhs) const
	{
		return (!(operator==(rhs)));
	}

	void Foo::setData(int newDataValue)
	{
		mData = newDataValue;
	}
	void Foo::setPointerData(int newValue)
	{
		*mPointerData = newValue;
	}
	Foo::~Foo()
	{
		delete mPointerData;
		mPointerData = nullptr;
	}

	int Foo::Data() const
	{
		return mData;
	}

}