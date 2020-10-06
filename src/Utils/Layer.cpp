#include "Layer.h"

BEG_META( XE::Layer )
type->Property( "Value", &Layer::GetValue, &Layer::SetValue );
END_META()

XE::Layer::Layer()
	:_Value( Default )
{

}

XE::Layer::Layer( XE::uint64 val )
	: _Value( val )
{

}

XE::Layer::Layer( const Layer& val )
	:_Value( val._Value )
{

}

XE::Layer::~Layer()
{

}

XE::Layer::operator XE::uint64() const
{
	return _Value;
}

XE::Layer& XE::Layer::operator=( XE::uint64 val )
{
	_Value = val;
	return *this;
}

XE::Layer& XE::Layer::operator=( const Layer& val )
{
	_Value = val._Value;
	return *this;
}

XE::Layer& XE::Layer::operator|=( XE::uint64 val )
{
	_Value |= val;
	return *this;
}

XE::Layer& XE::Layer::operator|=( const Layer& val )
{
	_Value |= val._Value;
	return *this;
}

XE::Layer& XE::Layer::operator&=( XE::uint64 val )
{
	_Value &= val;
	return *this;
}

XE::Layer& XE::Layer::operator&=( const Layer& val )
{
	_Value &= val._Value;
	return *this;
}

bool XE::Layer::operator||( XE::uint64 val ) const
{
	return _Value || val;
}

bool XE::Layer::operator||( const Layer& val ) const
{
	return _Value || val._Value;
}

bool XE::Layer::operator&&( XE::uint64 val ) const
{
	return _Value && val;
}

bool XE::Layer::operator&&( const Layer& val ) const
{
	return _Value && val._Value;
}

bool XE::Layer::operator==( XE::uint64 val ) const
{
	return _Value == val;
}

bool XE::Layer::operator==( const Layer& val ) const
{
	return _Value == val._Value;
}

bool XE::Layer::operator!=( XE::uint64 val ) const
{
	return _Value != val;
}

bool XE::Layer::operator!=( const Layer& val ) const
{
	return _Value != val._Value;
}

XE::uint64 XE::Layer::GetValue() const
{
	return _Value;
}

void XE::Layer::SetValue( XE::uint64 val )
{
	_Value = val;
}

XE::Layer XE::Layer::operator |( XE::uint64 val ) const
{
	return _Value | val;
}

XE::Layer XE::Layer::operator &( XE::uint64 val ) const
{
	return _Value & val;
}

XE::Layer XE::Layer::operator ^( XE::uint64 val ) const
{
	return _Value ^ val;
}

XE::Layer XE::Layer::operator |( const Layer &val ) const
{
	return _Value | val._Value;
}

XE::Layer XE::Layer::operator &( const Layer &val ) const
{
	return _Value & val._Value;
}

XE::Layer XE::Layer::operator ^( const Layer &val ) const
{
	return _Value ^ val._Value;
}

bool operator ||( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 || val2.GetValue();
}

bool operator &&( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 && val2.GetValue();
}

bool operator ==( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 == val2.GetValue();
}

bool operator !=( XE::uint64 val1, const XE::Layer& val2 )
{
	return val1 != val2.GetValue();
}

XE::Layer operator |( XE::uint64 val1, const XE::Layer &val2 )
{
	return val1 | val2.GetValue();
}

XE::Layer operator &( XE::uint64 val1, const XE::Layer &val2 )
{
	return val1 & val2.GetValue();
}

XE::Layer operator ^( XE::uint64 val1, const XE::Layer &val2 )
{
	return val1 ^ val2.GetValue();
}
