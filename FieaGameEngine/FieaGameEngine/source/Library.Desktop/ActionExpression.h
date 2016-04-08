#pragma once
#include "Action.h"
namespace Library
{
	/*!
	\class ActionExpression
	\brief The class which parses an arithmetic expression
	*/
	class ActionExpression :
		public Action
	{
		RTTI_DECLARATIONS(ActionExpression,Action)
	public:
		/*!
		\fn ActionExpression()
		\brief The constructor
		*/
		ActionExpression() = default;
		~ActionExpression() = default;
		/*!
		\fn SetTarget(target)
		\brief The Datum target whose values are to be populated with the result of the expression
		\param The reference to the datum 
		*/
		void SetTarget(Datum& target);
		/*!
		\fn SetExpression(expression)
		\brief Sets the RPN expression
		\param A vector of strings to set as the expression
		*/
		void setExpression(const Vector<std::string>& expression);
		/*!
		\fn Update(state)
		\brief The override update which calculates the expression every frame
		\param The world state reference
		*/
		virtual void Update(WorldState & state) override;

	private:
		/*!
		\fn ProcessExpression()
		\brief The function which processes the expression every frame
		*/
		void ProcessExpression();
		/*!
		\fn CalculateFloatResult()
		\brief Calculates the result of the floating point expression
		*/
		void CalculateFloatResult();
		/*!
		\fn CalculateIntegerResult()
		\brief Calculates the result of the integer expression
		*/
		void CalculateIntegerResult();
		/*!
		\fn IsADigit(string)
		\brief Checks if the given string is a digit 
		\return Returns a bool if it is a digit
		*/
		bool IsADigit(const std::string& value);
		/*!
		\fn IsAnOperator(value)
		\brief Checks if the given string is present in the list of operators
		\return Returns true if the string is an operator
		\param The value to be checked
		*/
		bool IsAnOperator(const std::string& value);
		/*!
		\fn IsUnaryOperator(value)
		\brief Checks if the given string is a unary operator or no
		\return Returns true if the value is unary
		\param The value to be checked
		*/
		bool IsUnaryOperator(const std::string& value);
		/*!
		\var ValidOperatorTable
		\brief A hashmap that has all the valid operators 
		*/
		static Hashmap<std::string, bool> ValidOperatorTable;
		/*!
		\var ExpressionString
		\brief The expression that will be parsed every update
		*/
		Vector<std::string> ExpressionString;
		/*!
		\var Target
		\brief The target datum onto which the value of the expression will be set
		*/
		Datum* Target;
	};
}
