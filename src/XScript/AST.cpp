#include "AST.h"

USING_XE

XE::AST::AST( const std::string & val )
{

}

XE::AST::~AST()
{

}

void XE::AST::AddUsing( const std::string & val )
{

}

XE::XSMetaEnumPtr XE::AST::AddEnum( const std::string & name )
{
	return nullptr;
}

XE::XSMetaClassPtr XE::AST::AddClass( const std::string & name, const std::string & base )
{
	return nullptr;
}

XE::XSMetaMethodPtr XE::AST::AddMethod( const std::string & name, List<std::string> && params )
{
	return nullptr;
}

XE::XSMetaOperatorPtr XE::AST::AddOperator( const std::string & name, List<std::string> && params )
{
	return nullptr;
}

XE::XSMetaPropertyPtr XE::AST::AddProperty( const std::string & name )
{
	return nullptr;
}

void XE::AST::PushBlock()
{

}

void XE::AST::PopBlock()
{

}

void XE::AST::AddStatement()
{

}
