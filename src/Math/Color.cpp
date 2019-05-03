#include "Color.h"

#include "Mathf.h"

USING_XE

BEGIN_META( Color )
type->Property( "r", &Color::r );
type->Property( "g", &Color::g );
type->Property( "b", &Color::b );
type->Property( "a", &Color::a );
END_META()


const XE::Color XE::Color::White = { 0xffffff };
const XE::Color XE::Color::Black = { 0x000000 };
const XE::Color XE::Color::Red = { 0xff0000 };
const XE::Color XE::Color::DarkRed = { 0x800000 };
const XE::Color XE::Color::Green = { 0x00ff00 };
const XE::Color XE::Color::DarkGreen = { 0x008000 };
const XE::Color XE::Color::Blue = { 0x0000ff };
const XE::Color XE::Color::DarkBlue = { 0x000080 };
const XE::Color XE::Color::Cyan = { 0x00ffff };
const XE::Color XE::Color::DarkCyan = { 0x008080 };
const XE::Color XE::Color::Magenta = { 0xff00ff };
const XE::Color XE::Color::DarkMagenta = { 0x800080 };
const XE::Color XE::Color::Yellow = { 0xffff00 };
const XE::Color XE::Color::DarkYellow = { 0x808000 };
const XE::Color XE::Color::Gray = { 0xa0a0a4 };
const XE::Color XE::Color::DarkGray = { 0x808080 };
const XE::Color XE::Color::LightGray = { 0xc0c0c0 };


XE::Color::Color()
	:r( 0 ), g( 0 ), b( 0 ), a( 0 )
{
}

XE::Color::Color( uint32 val )
	: r( ( ( val & 0xFF000000 ) >> 24 ) / 255.0f ), g( ( ( val & 0x00FF0000 ) >> 16 ) / 255.0f ), b( ( ( val & 0x0000FF00 ) >> 8 ) / 255.0f ), a( ( ( val & 0x000000FF ) >> 0 ) / 255.0f )
{

}

XE::Color::Color( const Color& val )
	: r( val.r ), g( val.g ), b( val.b ), a( val.a )
{

}

XE::Color::Color( float r, float g, float b, float a /*= 1.0f */ )
	: r( r ), g( g ), b( b ), a( a )
{

}

XE::Color::~Color()
{
}

XE::uint32 XE::Color::GetHex() const
{
	return ( uint32( r * 255 ) << 24 ) | ( uint32( g * 255 ) << 16 ) | ( uint32( b * 255 ) << 8 ) | ( uint32( a * 255 ) << 0 );
}

void XE::Color::SetHex( uint32 val )
{
	r = ( ( val & 0xFF000000 ) >> 24 ) / 255.0f;
	g = ( ( val & 0x00FF0000 ) >> 16 ) / 255.0f;
	b = ( ( val & 0x0000FF00 ) >> 8 ) / 255.0f;
	a = ( ( val & 0x000000FF ) >> 0 ) / 255.0f;
}

XE::uint8 XE::Color::GetR() const
{
	return (uint8)( r * 255 );
}

void XE::Color::SetR( uint8 val )
{
	r = val / 255.0f;
}

XE::uint8 XE::Color::GetG() const
{
	return (uint8)( g * 255 );
}

void XE::Color::SetG( uint8 val )
{
	g = val / 255.0f;
}

XE::uint8 XE::Color::GetB() const
{
	return (uint8)( b * 255 );
}

void XE::Color::SetB( uint8 val )
{
	b = val / 255.0f;
}

XE::uint8 XE::Color::GetA() const
{
	return (uint8)( a * 255 );
}

void XE::Color::SetA( uint8 val )
{
	a = val / 255.0f;
}

Color Color::Lerp( const Color& val1, const Color& val2, float val )
{
	return val1 * ( 1.0f - val ) + val2 * val;
}

bool Color::operator!=( const Color& val ) const
{
	return GetHex() != val.GetHex();
}

bool Color::operator==( const Color& val ) const
{
	return GetHex() == val.GetHex();
}

Color Color::operator*( const Color& val ) const
{
	return Color( r * val.r, g * val.g, b * val.b, a * val.a );
}

Color Color::operator*( float val ) const
{
	return *this * Color( val, val, val, val );
}

Color Color::operator-( const Color& val ) const
{
	return Color( Mathf::Clamp( r - val.r, 0.0f, 1.0f ), Mathf::Clamp( g - val.g, 0.0f, 1.0f ), Mathf::Clamp( b - val.b, 0.0f, 1.0f ), Mathf::Clamp( a - val.a, 0.0f, 1.0f ) );
}

Color Color::operator+( const Color& val ) const
{
	return Color( Mathf::Clamp( r + val.r, 0.0f, 1.0f ), Mathf::Clamp( g + val.g, 0.0f, 1.0f ), Mathf::Clamp( b + val.b, 0.0f, 1.0f ), Mathf::Clamp( a + val.a, 0.0f, 1.0f ) );
}

Color& Color::operator*=( const Color& val )
{
	r *= val.r;
	g *= val.g;
	b *= val.b;
	a *= val.a;

	return *this;
}

Color& Color::operator*=( float val )
{
	assert( val > -1.0f && val <= 1.0f && "" );

	r *= val;
	g *= val;
	b *= val;
	a *= val;

	return *this;
}

Color& Color::operator-=( const Color& val )
{
	r = Mathf::Clamp( r - val.r, 0.0f, 1.0f );
	g = Mathf::Clamp( g - val.g, 0.0f, 1.0f );
	b = Mathf::Clamp( b - val.b, 0.0f, 1.0f );
	a = Mathf::Clamp( a - val.a, 0.0f, 1.0f );

	return *this;
}

Color& Color::operator+=( const Color& val )
{
	r = Mathf::Clamp( r + val.r, 0.0f, 1.0f );
	g = Mathf::Clamp( g + val.g, 0.0f, 1.0f );
	b = Mathf::Clamp( b + val.b, 0.0f, 1.0f );
	a = Mathf::Clamp( a + val.a, 0.0f, 1.0f );

	return *this;
}

Color& Color::operator=( const Color& val )
{
	r = val.r;
	g = val.g;
	b = val.b;
	a = val.a;

	return *this;
}

XE::Color operator*( float a, const Color& b )
{
	return b * a;
}
