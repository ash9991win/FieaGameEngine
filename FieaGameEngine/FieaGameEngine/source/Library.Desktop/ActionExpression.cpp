#include "pch.h"
#include "ActionExpression.h"
#include"Stack.h"
#include"WorldState.h"
namespace Library
{
	RTTI_DEFINITIONS(ActionExpression)
#pragma warning( disable : 4592)
	Hashmap<std::string,bool> ActionExpression::ValidOperatorTable = 
	{
		{"+",true},
		{"-",true},
		{"/",true},
		{"*",true},
		{">",true},
		{">=",true},
		{"<=",true},
		{"!=",true},
		{"%",true},
		{"++",true},
		{"--",true}
	};
#pragma warning(default : 4592)
	void ActionExpression::SetTarget(Datum & target)
	{
		Target = &target;
	}
	void ActionExpression::setExpression(const Vector<std::string>& expression)
	{
		ExpressionString = expression;
	}

	void Library::ActionExpression::Update(WorldState & state)
	{
		state.Action = this;
		ProcessExpression();
	}
	void ActionExpression::ProcessExpression()
	{
		if (Target == nullptr)
			return;
		if (Target->Type() == Datum::DatumType::INTEGER)
			CalculateIntegerResult();
		else if (Target->Type() == Datum::DatumType::FLOAT)
			CalculateFloatResult();
	}
	void ActionExpression::CalculateIntegerResult()
	{
		int operand1;
		int operand2;
		int result;
		Stack<int> IntegerTokens;
		for (auto& token : ExpressionString)
		{
			if (IsADigit(token))
			{
				IntegerTokens.Push(std::stoi(token));
			}
			else if (IsAnOperator(token))
			{
				if (!ValidOperatorTable.ContainsKey(token))
				{
					throw std::exception("Invalid Expression!");
				}
				if (IsUnaryOperator(token))
				{
					if (IntegerTokens.IsEmpty())
					{
						throw std::exception("Cannot have an operator on an empty stack");
					}
					if (token == "++")
					{
						result = IntegerTokens.Top()++;
					}
					else if (token == "--")
					{
						result = IntegerTokens.Top()--;
					}
					IntegerTokens.Pop();
				}
				else 
				{
					if (IntegerTokens.IsEmpty() || IntegerTokens.Size() < 2)
					{
						throw std::exception("Cannot have an operator on an empty stack");
					}
					operand1 = IntegerTokens.Top();
					IntegerTokens.Pop();
					operand2 = IntegerTokens.Top();
					IntegerTokens.Pop();
					if (token == "+")
					{
						result = operand1 + operand2;
					}
					else if (token == "-")
					{
						result = operand1 - operand2;
					}
					else if (token == "/")
					{
						result = operand1 / operand2;
					}
					else if (token == "*")
					{
						result = operand1 * operand2;
					}
					else if (token == "%")
					{
						result = operand1 % operand2;
					}
				}
				IntegerTokens.Push(result);
			}
		}
		Target->Set(result);
	}
	void ActionExpression::CalculateFloatResult()
	{
		float operand1;
		float operand2;
		float result;
		Stack<float> FloatTokens;
		for (auto& token : ExpressionString)
		{
			if (IsADigit(token))
			{
				FloatTokens.Push(std::stof(token));
			}
			else if (IsAnOperator(token))
			{
				if (!ValidOperatorTable.ContainsKey(token))
				{
					throw std::exception("Invalid Expression!");
				}
				if (IsUnaryOperator(token))
				{
					if (FloatTokens.IsEmpty())
					{
						throw std::exception("Cannot have an operator on an empty stack");
					}
					if (token == "++")
					{
						result = ++FloatTokens.Top();
					}
					else if (token == "--")
					{
						result = --FloatTokens.Top();
					}
					FloatTokens.Pop();
				}
				else
				{
					if (FloatTokens.IsEmpty() || FloatTokens.Size() < 2)
					{
						throw std::exception("Cannot have an operator on an empty stack");
					}
					operand1 = FloatTokens.Top();
					FloatTokens.Pop();
					operand2 = FloatTokens.Top();
					FloatTokens.Pop();
					if (token == "+")
					{
						result = operand1 + operand2;
					}
					else if (token == "-")
					{
						result = operand1 - operand2;
					}
					else if (token == "/")
					{
						result = operand1 / operand2;
					}
					else if (token == "*")
					{
						result = operand1 * operand2;
					}
					else if (token == "%")
					{
						result =static_cast<float>( static_cast<int>(operand1) % static_cast<int>(operand2));
					}
				}
				FloatTokens.Push(result);
			}
		}
		Target->Set(result);
	}
	bool ActionExpression::IsADigit(const std::string& value)
	{
		return !IsAnOperator(value);
	}
	bool ActionExpression::IsAnOperator(const std::string& value)
	{
		return ValidOperatorTable.ContainsKey(value);
	}
	bool ActionExpression::IsUnaryOperator(const std::string & value)
	{
		return (value == "++" || value == "--");
	}
}