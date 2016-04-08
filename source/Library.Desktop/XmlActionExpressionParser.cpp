#include "pch.h"
#include "XmlActionExpressionParser.h"
#include "ActionExpression.h"
#include"Entity.h"
#include"World.h"
#include"Sector.h"
#include<iterator>

namespace Library
{
#pragma warning(disable : 4592)
	Hashmap<std::string,int> XmlActionExpressionParser::OperatorPrecedenceTable =
	{
		{"==",0},
		{"!=",0},
		{">=",1},
		{"<=",1},
		{">",1},
		{"<",1 },
		{"+",2},
		{"-",2},
		{"*",3},
		{"/",3},
		{"%",3},
		{"++",4},
		{"--",4}
	};
#pragma warning(default : 4592)
	bool Library::XmlActionExpressionParser::StartElementHandler(XmlParseMaster::SharedData & userData, const std::string & name, Hashmap<std::string, std::string>& attributes)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		Hashmap<std::string, std::string>::Iterator iterator = attributes.begin();

		if (name != ExpressionString)
			return false;
		std::string expression;
		if (!attributes.ContainsKey("value", expression))
		{
			throw std::exception("Expression needs a value");
		}
		std::string currentTypeString;
		std::string Target;
		std::string NameOfAttribute;
		if (!attributes.ContainsKey("name", NameOfAttribute))
		{
			throw std::exception("Cant have an empty name");
		}
		Entity* currentEntity = nullptr;
		if (sharedData->TypeStack.Top() != EntityString)
		{
			return false;
		}
		currentEntity = sharedData->CurrentScope->As<Entity>();
		assert(currentEntity != nullptr);

		bool isExpressionFloat = false;
		ShuntingYard(expression,isExpressionFloat);
		Datum::DatumType currentType;
		currentType = (isExpressionFloat) ? (Datum::DatumType::FLOAT) : (Datum::DatumType::INTEGER);
		Entity* targetEntity = nullptr;
		if (attributes.ContainsKey("target", Target))
		{
			targetEntity = sharedData->CurrentScope->As<Entity>()->GetSector()->GetWorld()->FindEntity(Target);
		}
		if(!targetEntity)
		{
			targetEntity = currentEntity;
		}
		Datum* targetDatum;
			if (!targetEntity->IsPrescribedAttribute(NameOfAttribute))
			{
				targetDatum = &(targetEntity->AppendAuxilliaryAttribute(NameOfAttribute));
				targetDatum->SetType(currentType);
			}
			else
			{
				targetDatum = targetEntity->Find(NameOfAttribute);
			}
		
			ActionExpression *expressionAction = new ActionExpression();
		expressionAction->setExpression(FinalExpression);
		expressionAction->SetTarget(*targetDatum);
		expressionAction->SetEntity(*currentEntity);
		return true;
	}

	bool Library::XmlActionExpressionParser::EndElementHandler(XmlParseMaster::SharedData & userData, const std::string & name)
	{
		SharedData* sharedData = userData.As<SharedData>();
		if (sharedData == nullptr)
			return false;
		
		if (name == ExpressionString)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool XmlActionExpressionParser::CharDataHandler(XmlParseMaster::SharedData & userData, const std::string & data)
	{
		return false;
	}

	IXmlParseHelper * Library::XmlActionExpressionParser::Clone() const
	{
		return new XmlActionExpressionParser();
	}
	void XmlActionExpressionParser::ShuntingYard(const std::string& expression,bool& isFloat)
	{
		std::istringstream stream(expression);
		std::istream_iterator<string> beg(stream), end;
		Vector<std::string> expressionChunks;
		Stack<std::string> processStack;
		for (std::istream_iterator<std::string> i = beg; i != end; i++)
		{
			expressionChunks.PushBack(*i);
		}
		for (auto& token : expressionChunks)
		{
			if (OperatorPrecedenceTable.ContainsKey(token))
			{
				//its an operator 
				int o2 = -1;
				if (!processStack.IsEmpty() && OperatorPrecedenceTable.ContainsKey(processStack.Top(),o2))
				{
					//there is an operator on the stack
					int o1 = OperatorPrecedenceTable[token];
					if (o1 <= o2)
					{
						FinalExpression.PushBack(processStack.Top());
						processStack.Pop();
					}
				}
				processStack.Push(token);
			}
			else if (token == "(")
			{
				processStack.Push(token);
			}
			else if (token == ")")
			{
				while (processStack.Top() != "(")
				{
					FinalExpression.PushBack(processStack.Top());
					processStack.Pop();
				}
				if (processStack.Top() == "(")
				{
					processStack.Pop();
				}
			}
			else if(IsANumber(token))
			{
				FinalExpression.PushBack(token);
			}
		}
		while (!processStack.IsEmpty())
		{
			FinalExpression.PushBack(processStack.Top());
			processStack.Pop();
		}
		for (auto& tokens : FinalExpression)
		{
			if (IsAFloat(tokens))
			{
				isFloat = true;
				break;
			}
		}
	}

	bool XmlActionExpressionParser::IsAFloat(const std::string & value)
	{
		size_t index = value.find('.');
		if (index < 0 || index > value.size())
			return false;
		else
		{
			return true;
		}
	}

	bool XmlActionExpressionParser::IsANumber( std::string value)
	{
		if (IsAFloat(value))
			value.erase(value.find('.'),1);
		for (auto& ch : value)
		{
			if (ch < '0' || ch > '9')
				return false;
		}
		return true;
	}

	
	
}