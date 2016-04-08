#pragma once
#include"Attributed.h"
#include"Factory.h"
using namespace Library;
class AttributedFoo : public Attributed
{
	RTTI_DECLARATIONS(AttributedFoo, Attributed)
	
	public:
		//INTERNAL SIGNATURES
		int i;
		float f;
		std::string s;
		glm::mat4 mat;
		glm::vec4 vec;
		//TODO RTTI 

		//EXTERNAL SIGNATURES
		int *iExternal;
		float *fExternal;
		std::string *sExternal;
		glm::mat4* matExternal;
		glm::vec4* vecExternal;
		RTTI* testRtti;
		RTTI* testRttiExternal;
		//SCOPES
		Scope *mynestedScope;

		AttributedFoo();
		AttributedFoo(int i, int j);
		virtual void InitializeSignatures();
		AttributedFoo(const AttributedFoo& rhs);
		AttributedFoo operator=(const AttributedFoo& rhs);
		AttributedFoo(AttributedFoo&& rhs);
		AttributedFoo& operator=(AttributedFoo&& rhs);
		virtual ~AttributedFoo();
		void ClearFoo();
};
class AttributedBar : public AttributedFoo
{
	RTTI_DECLARATIONS(AttributedBar,AttributedFoo)
public:
	int iBar;
	int *iBarExternal;
	AttributedBar();
	AttributedBar(const AttributedBar& rhs);
	AttributedBar(AttributedBar&& rhs);
	AttributedBar& operator=(const AttributedBar& rhs);
	AttributedBar& operator=(AttributedBar&& rhs);
	virtual void InitializeSignatures() override;
	~AttributedBar();
};


