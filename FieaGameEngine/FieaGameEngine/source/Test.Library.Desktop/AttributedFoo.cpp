#include "pch.h"
#include "AttributedFoo.h"
RTTI_DEFINITIONS(AttributedFoo)
AttributedFoo::AttributedFoo()
	:Attributed()
{
	i = 1;
	f = 1.1f;
	s = "Internal";
	testRtti = nullptr;
	testRttiExternal = nullptr;
	iExternal = new int(5);
	fExternal = new float(3.14f);
	sExternal = new std::string("Foo");
	vecExternal = new glm::vec4();
	matExternal = new glm::mat4();
	mynestedScope = new Scope();
	Scope *childScope = new Scope();
	childScope->AppendScope("CHILD OF CHILD");
	mynestedScope->Adopt(*childScope, "CHILD");
	InitializeSignatures();
}

AttributedFoo::AttributedFoo(int i, int j)
	:AttributedFoo()
{

}

void AttributedFoo::InitializeSignatures()
{	
	
	DEFINE_INTERNAL_SIGNATURE(i,i,1)
	DEFINE_INTERNAL_SIGNATURE(f,f,1)
	DEFINE_INTERNAL_SIGNATURE(s,s,1)
	DEFINE_INTERNAL_SIGNATURE(mat,mat,1)
	DEFINE_INTERNAL_SIGNATURE(vec,vec,1)
	DEFINE_INTERNAL_SIGNATURE(testRtti,testRtti,1)
	DEFINE_EXTERNAL_SIGNATURE(iExternal,1)
	DEFINE_EXTERNAL_SIGNATURE(fExternal,1)
	DEFINE_EXTERNAL_SIGNATURE(sExternal,1)
	DEFINE_EXTERNAL_SIGNATURE(vecExternal, 1)
	DEFINE_EXTERNAL_SIGNATURE(matExternal, 1)
	DEFINE_EXTERNAL_SIGNATURE(&testRttiExternal,1)
	AddNestedScopes("Scope", *mynestedScope);
	try
	{
		DEFINE_INTERNAL_SIGNATURE(i, i, 1)
	}
	catch (const std::exception&)
	{
	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(f, f, 1)
	}
	catch (const std::exception&)
	{
	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(s, s, 1)
	}
	catch (const std::exception&)
	{
	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(mat, mat, 1)
	}
	catch (const std::exception&)
	{

	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(vec, vec, 1)
	}
	catch (const std::exception&)
	{
	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(testRtti, testRtti, 1)
	}
	catch (const std::exception&)
	{
	}
	try
	{
		DEFINE_INTERNAL_SIGNATURE(testRtti, testRtti, 1)
	}
	catch (const std::exception&)
	{

	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(iExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(fExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(sExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(sExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(sExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(sExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		DEFINE_EXTERNAL_SIGNATURE(&testRttiExternal, 1)
	}
	catch (const std::exception&)
	{
			
	}
	try
	{
		AddNestedScopes("Scope", *mynestedScope);
	}
	catch (const std::exception&)
	{
			
	}
}

AttributedFoo::AttributedFoo(const AttributedFoo & rhs)
	:iExternal(new int(*(rhs.iExternal))),
	 fExternal(new float(*(rhs.fExternal))),
     sExternal(new std::string(*(rhs.sExternal))),
	 matExternal(new glm::mat4(*(rhs.matExternal))),
	 vecExternal(new glm::vec4(*(rhs.vecExternal))),
	Attributed(rhs)
{

	(*this)["iExternal"].SetStorage(iExternal,1);
	(*this)["fExternal"].SetStorage(fExternal,1);
	(*this)["sExternal"].SetStorage(sExternal,1);
	(*this)["vecExternal"].SetStorage(vecExternal,1);
	(*this)["matExternal"].SetStorage(matExternal,1);
}

AttributedFoo AttributedFoo::operator=(const AttributedFoo & rhs)
{
	if (this != &rhs)
	{
		ClearFoo();
		iExternal = new int(*(rhs.iExternal));
		fExternal = (new float(*(rhs.fExternal)));
		sExternal = (new std::string(*(rhs.sExternal)));
		matExternal = (new glm::mat4(*(rhs.matExternal)));
		vecExternal = (new glm::vec4(*(rhs.vecExternal)));
		Attributed::operator=(rhs);
		(*this)["iExternal"].SetStorage(iExternal, 1);
		(*this)["fExternal"].SetStorage(fExternal, 1);
		(*this)["sExternal"].SetStorage(sExternal, 1);
		(*this)["vecExternal"].SetStorage(vecExternal, 1);
		(*this)["matExternal"].SetStorage(matExternal, 1);
		
	}
	return *this;
}

AttributedFoo::AttributedFoo(AttributedFoo && rhs)
	: Attributed(std::move(rhs)),
	iExternal(rhs.iExternal),
	fExternal(rhs.fExternal),
	sExternal(rhs.sExternal),
	matExternal(rhs.matExternal),
	vecExternal (rhs.vecExternal)
{
	rhs.iExternal = nullptr;
	rhs.sExternal = nullptr;
	rhs.fExternal = nullptr;
	rhs.matExternal = nullptr;
	rhs.vecExternal = nullptr;
}

AttributedFoo & AttributedFoo::operator=(AttributedFoo && rhs)
{
	if (this != &rhs)
	{
		ClearFoo();
		Attributed::operator=(std::move(rhs));
		iExternal = rhs.iExternal;
		fExternal = rhs.fExternal;
		sExternal = rhs.sExternal;
		matExternal = rhs.matExternal;
		vecExternal = rhs.vecExternal;

		rhs.iExternal = nullptr;
		rhs.sExternal = nullptr;
		rhs.fExternal = nullptr;
		rhs.matExternal = nullptr;
		rhs.vecExternal = nullptr;
	}
	return *this;
}


AttributedFoo::~AttributedFoo()
{
	ClearFoo();
}
void AttributedFoo::ClearFoo()
{
	delete iExternal;
	delete fExternal;
	delete sExternal;
	delete matExternal;
	delete vecExternal;
}

RTTI_DEFINITIONS(AttributedBar)
AttributedBar::AttributedBar()
	:AttributedFoo(),iBarExternal(new int(5))
{
	InitializeSignatures();
}
AttributedBar::AttributedBar(const AttributedBar& rhs)
	: iBar(rhs.iBar),iBarExternal(new int(*(rhs.iBarExternal))),AttributedFoo(rhs)
{
	(*this)["iBarExternal"].Set(*iBarExternal);
}
AttributedBar::AttributedBar(AttributedBar&& rhs)
	:iBar(rhs.iBar),iBarExternal(rhs.iBarExternal),AttributedFoo(std::move(rhs))
{
	rhs.iBarExternal = nullptr;
}
AttributedBar& AttributedBar::operator=(const AttributedBar& rhs)
{
	if (this != &rhs)
	{
		delete iBarExternal;
		iBarExternal = new int(*(rhs.iBarExternal));
		AttributedFoo::operator=(rhs);
		(*this)["iBarExternal"].Set(*iBarExternal);
	}
	return *this;
}
AttributedBar& AttributedBar::operator=(AttributedBar&& rhs)
{
	if (this != &rhs)
	{
		delete iBarExternal;
		AttributedFoo::operator=(std::move(rhs));
		iBarExternal = rhs.iBarExternal;
		iBar = rhs.iBar;
		rhs.iBarExternal = nullptr;
	}
	return *this;
}
void AttributedBar::InitializeSignatures()
{
	DEFINE_INTERNAL_SIGNATURE(iBar,iBar,1)
	DEFINE_EXTERNAL_SIGNATURE(iBarExternal,1)
}
AttributedBar::~AttributedBar()
{
	delete iBarExternal;
}