#include "Layer.h"

USING_XE

BEGIN_META( Layer )
type->Property( "Value", &Layer::Value );
END_META()

XE::Layer::Layer()
	:Value( Default )
{

}

XE::Layer::Layer( uint64 val )
	: Value( val )
{

}

XE::Layer::Layer( const Layer& val )
	:Value( val.Value )
{

}

XE::Layer::~Layer()
{

}

XE::Layer& XE::Layer::operator=( uint64 val )
{
	Value = val;
	return *this;
}

XE::Layer& XE::Layer::operator=( const Layer& val )
{
	Value = val.Value;
	return *this;
}

XE::Layer& XE::Layer::operator|=( uint64 val )
{
	Value |= val;
	return *this;
}

XE::Layer& XE::Layer::operator|=( const Layer& val )
{
	Value |= val.Value;
	return *this;
}

XE::Layer& XE::Layer::operator&=( uint64 val )
{
	Value &= val;
	return *this;
}

XE::Layer& XE::Layer::operator&=( const Layer& val )
{
	Value &= val.Value;
	return *this;
}

bool XE::Layer::operator||( uint64 val ) const
{
	return Value || val;
}

bool XE::Layer::operator||( const Layer& val ) const
{
	return Value || val.Value;
}

bool XE::Layer::operator&&( uint64 val ) const
{
	return Value && val;
}

bool XE::Layer::operator&&( const Layer& val ) const
{
	return Value && val.Value;
}

bool XE::Layer::operator==( uint64 val ) const
{
	return Value == val;
}

bool XE::Layer::operator==( const Layer& val ) const
{
	return Value == val.Value;
}

bool XE::Layer::operator!=( uint64 val ) const
{
	return Value != val;
}

bool XE::Layer::operator!=( const Layer& val ) const
{
	return Value != val.Value;
}

bool operator ||( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 || val2.Value;
}

bool operator &&( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 && val2.Value;
}

bool operator ==( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 == val2.Value;
}

bool operator !=( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 != val2.Value;
}
