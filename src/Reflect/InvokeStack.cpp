#include "InvokeStack.h"

USING_XE

XE::InvokeStack::InvokeStack()
{

}

XE::InvokeStack::~InvokeStack()
{

}

void XE::InvokeStack::Push( InvokeStack * val )
{
	_Stack.insert( _Stack.end(), val->_Stack.begin(), val->_Stack.end() );
}

void XE::InvokeStack::Push( const InvokeStack * val )
{
	_Stack.insert( _Stack.end(), val->_Stack.begin(), val->_Stack.end() );
}

void XE::InvokeStack::Push( InvokeStack & val )
{
	_Stack.insert( _Stack.end(), val._Stack.begin(), val._Stack.end() );
}

void XE::InvokeStack::Push( const InvokeStack & val )
{
	_Stack.insert( _Stack.end(), val._Stack.begin(), val._Stack.end() );
}
