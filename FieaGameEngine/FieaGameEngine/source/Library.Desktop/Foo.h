#pragma once
namespace FooC
{
	/*
	\class Foo
	\brief  A basic test class which has one integer member
	*/
	class Foo
	{
	public:
		/*!
		\fn Foo()
		\brief A parameterless constructor that initializes the variables
		*/
		Foo();
		/*!
		\fn Foo(int pData)
		\brief A parametrized constructor
		\param pData The value to be stored in the class variable mData
		*/
		Foo(int value);
		/*!
		\fn Foo(const Foo& rhs)
		\brief The copy constructor
		\param rhs A reference to the Foo class to be copied from. This performs a deep copy of all the data
		*/
		Foo(int value, int pointervalue);
		Foo(const Foo& rhs);
		/*!
		\fn operator=(const Foo& rhs)
		\brief The overloaded assignment operator
		\param rhs A reference to the Foo class to be copied from. This performs a deep copy of all the data
		*/
		Foo& operator=(const Foo& rhs);
		/*!
		\fn ~Foo()
		\brief The destructor of the class, deletes any allcated memory
		*/
		~Foo();
		/*!
		\fn setData(int newDataValue)
		\brief Sets the mData variable of Foo class
		\param newDataValue The value to be set for the mData variable
		*/
		void setData(int newDatavalue);
		/*!
		\fn int Data() const;
		\brief A constant function that returns the value stored in the mData variable
		*/
		int Data() const;

		/*!
		\fn setPointerData(int pointerValue)
		\brief Sets the mPointerData variable of Foo class
		\param pointervalue The value to be set for the mPointerData after allocation
		*/
		void setPointerData(int pointerValue);
		/*!
		\var int mData;
		\brief Test data for the Foo class
		*/
		/*!
		\fn bool operator==(const Foo& rhs) const;
		\brief Checks if the two Foos are equal
		*/
		bool operator==(const Foo& rhs) const;
		/*!
		\fn bool operator!=(const Foo& rhs) const;
		\brief Checks if the two Foos are unequal
		*/
		bool operator!=(const Foo& rhs) const;
	private:
		int mData;
		/*!
		\var int *mPointerData;
		\brief A pointer to an integer test data
		*/
		int *mPointerData;
		/*!
		\var std::wxstring className;
		\brief A string that stores the class name. Used for overloading ToString() method
		*/
	};
}