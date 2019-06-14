#include "Color.h"

#include "Mathf.h"

USING_XE

BEG_META(Color)
		type->Property("r", &Color::r);
		type->Property("g", &Color::g);
		type->Property("b", &Color::b);
		type->Property("a", &Color::a);
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
		:r(0), g(0), b(0), a(0)
{
}

XE::Color::Color( XE::uint32 val )
		:hex(val)
{

}

XE::Color::Color( const Color &val )
		:r(val.r), g(val.g), b(val.b), a(val.a)
{

}

XE::Color::Color( const FColor &val )
		: r((XE::uint8)(val.r * 255)), g((XE::uint8)(val.g * 255)), b((XE::uint8)(val.b * 255)), a((XE::uint8)(val.a * 255))
{

}

XE::Color::Color( XE::uint8 r, XE::uint8 g, XE::uint8 b, XE::uint8 a /*= 1 */ )
		:r(r), g(g), b(b), a(a)
{

}

XE::Color::~Color()
{
}

XE::uint32 XE::Color::GetHex() const
{
	return hex;
}

void XE::Color::SetHex( XE::uint32 val )
{
	hex = val;
}

Color Color::Lerp( const Color &val1, const Color &val2, XE::uint8 val )
{
	return val1 * ( 255 - val ) + val2 * val;
}

bool Color::operator !=( const Color &val ) const
{
	return GetHex() != val.GetHex();
}

bool Color::operator ==( const Color &val ) const
{
	return GetHex() == val.GetHex();
}

Color Color::operator *( const Color &val ) const
{
	return Color(r * val.r, g * val.g, b * val.b, a * val.a);
}

Color Color::operator *( XE::uint8 val ) const
{
	return ( *this ) * Color(XE::uint8(val * 255), XE::uint8(val * 255), XE::uint8(val * 255), XE::uint8(val * 255));
}

Color Color::operator -( const Color &val ) const
{
	return Color(r - val.r, g - val.g, b - val.b, a - val.a);
}

Color Color::operator +( const Color &val ) const
{
	return Color(r + val.r, g + val.g, b + val.b, a + val.a);
}

Color &Color::operator *=( const Color &val )
{
	r *= val.r;
	g *= val.g;
	b *= val.b;
	a *= val.a;
	
	return *this;
}

Color &Color::operator *=( XE::uint8 val )
{
	r *= val;
	g *= val;
	b *= val;
	a *= val;
	
	return *this;
}

Color &Color::operator -=( const Color &val )
{
	r = r - val.r;
	g = g - val.g;
	b = b - val.b;
	a = a - val.a;
	
	return *this;
}

Color &Color::operator +=( const Color &val )
{
	r = r + val.r;
	g = g + val.g;
	b = b + val.b;
	a = a + val.a;
	
	return *this;
}

Color &Color::operator =( const Color &val )
{
	r = val.r;
	g = val.g;
	b = val.b;
	a = val.a;
	
	return *this;
}

XE::Color operator *( XE::uint8 a, const Color &b )
{
	return b * a;
}


BEG_META(FColor)
		type->Property("r", &FColor::r);
		type->Property("g", &FColor::g);
		type->Property("b", &FColor::b);
		type->Property("a", &FColor::a);
END_META()


const XE::FColor XE::FColor::White = { 0xffffff };
const XE::FColor XE::FColor::Black = { 0x000000 };
const XE::FColor XE::FColor::Red = { 0xff0000 };
const XE::FColor XE::FColor::DarkRed = { 0x800000 };
const XE::FColor XE::FColor::Green = { 0x00ff00 };
const XE::FColor XE::FColor::DarkGreen = { 0x008000 };
const XE::FColor XE::FColor::Blue = { 0x0000ff };
const XE::FColor XE::FColor::DarkBlue = { 0x000080 };
const XE::FColor XE::FColor::Cyan = { 0x00ffff };
const XE::FColor XE::FColor::DarkCyan = { 0x008080 };
const XE::FColor XE::FColor::Magenta = { 0xff00ff };
const XE::FColor XE::FColor::DarkMagenta = { 0x800080 };
const XE::FColor XE::FColor::Yellow = { 0xffff00 };
const XE::FColor XE::FColor::DarkYellow = { 0x808000 };
const XE::FColor XE::FColor::Gray = { 0xa0a0a4 };
const XE::FColor XE::FColor::DarkGray = { 0x808080 };
const XE::FColor XE::FColor::LightGray = { 0xc0c0c0 };


XE::FColor::FColor()
		:r(0), g(0), b(0), a(0)
{
}

XE::FColor::FColor( XE::uint32 val )
		:r((( val & 0xFF000000 ) >> 24 ) / 255.0f),
		g((( val & 0x00FF0000 ) >> 16 ) / 255.0f),
		b((( val & 0x0000FF00 ) >> 8 ) / 255.0f),
		a((( val & 0x000000FF ) >> 0 ) / 255.0f)
{

}

FColor::FColor( const Color &val )
		:r(val.r / 255.0f), g(val.g / 255.0f), b(val.b / 255.0f), a(val.a / 255.0f)
{

}

XE::FColor::FColor( const FColor &val )
		:r(val.r), g(val.g), b(val.b), a(val.a)
{

}

XE::FColor::FColor( XE::float32 r, XE::float32 g, XE::float32 b, XE::float32 a /*= 1.0f */ )
		:r(r), g(g), b(b), a(a)
{

}

XE::FColor::~FColor()
{
}

XE::uint32 XE::FColor::GetHex() const
{
	return ( XE::uint32(r * 255.0f) << 24 ) | ( XE::uint32(g * 255.0f) << 16 ) | ( XE::uint32(b * 255.0f) << 8 ) |
		   ( XE::uint32(a * 255.0f) << 0 );
}

void XE::FColor::SetHex( XE::uint32 val )
{
	r = XE::uint8(( val & 0xFF000000 ) >> 24) / 255.0f;
	g = XE::uint8(( val & 0x00FF0000 ) >> 16) / 255.0f;
	b = XE::uint8(( val & 0x0000FF00 ) >> 8) / 255.0f;
	a = XE::uint8(( val & 0x000000FF ) >> 0) / 255.0f;
}

FColor FColor::Lerp( const FColor &val1, const FColor &val2, XE::float32 val )
{
	return val1 * ( 1.0f - val ) + val2 * val;
}

bool FColor::operator !=( const FColor &val ) const
{
	return ( Mathf::Abs(r - val.r) > std::numeric_limits<XE::float32>::epsilon() ) && ( Mathf::Abs(g - val.g) > std::numeric_limits<XE::float32>::epsilon() ) &&
		   ( Mathf::Abs(b - val.b) > std::numeric_limits<XE::float32>::epsilon() ) && ( Mathf::Abs(a - val.a) > std::numeric_limits<XE::float32>::epsilon() );
}

bool FColor::operator ==( const FColor &val ) const
{
	return ( Mathf::Abs(r - val.r) <= std::numeric_limits<XE::float32>::epsilon() ) && ( Mathf::Abs(g - val.g) <= std::numeric_limits<XE::float32>::epsilon() ) &&
		   ( Mathf::Abs(b - val.b) <= std::numeric_limits<XE::float32>::epsilon() ) && ( Mathf::Abs(a - val.a) <= std::numeric_limits<XE::float32>::epsilon() );
}

FColor FColor::operator *( const FColor &val ) const
{
	return FColor(r * val.r, g * val.g, b * val.b, a * val.a);
}

FColor FColor::operator *( XE::float32 val ) const
{
	return *this * FColor(val, val, val, val);
}

FColor FColor::operator -( const FColor &val ) const
{
	return FColor(Mathf::Clamp(r - val.r, 0.0f, 1.0f), Mathf::Clamp(g - val.g, 0.0f, 1.0f), Mathf::Clamp(
			b - val.b, 0.0f, 1.0f), Mathf::Clamp(a - val.a, 0.0f, 1.0f));
}

FColor FColor::operator +( const FColor &val ) const
{
	return FColor(Mathf::Clamp(r + val.r, 0.0f, 1.0f), Mathf::Clamp(g + val.g, 0.0f, 1.0f), Mathf::Clamp(
			b + val.b, 0.0f, 1.0f), Mathf::Clamp(a + val.a, 0.0f, 1.0f));
}

FColor &FColor::operator *=( const FColor &val )
{
	r *= val.r;
	g *= val.g;
	b *= val.b;
	a *= val.a;
	
	return *this;
}

FColor &FColor::operator *=( XE::float32 val )
{
	r *= val;
	g *= val;
	b *= val;
	a *= val;
	
	return *this;
}

FColor &FColor::operator -=( const FColor &val )
{
	r = Mathf::Clamp(r - val.r, 0.0f, 1.0f);
	g = Mathf::Clamp(g - val.g, 0.0f, 1.0f);
	b = Mathf::Clamp(b - val.b, 0.0f, 1.0f);
	a = Mathf::Clamp(a - val.a, 0.0f, 1.0f);
	
	return *this;
}

FColor &FColor::operator +=( const FColor &val )
{
	r = Mathf::Clamp(r + val.r, 0.0f, 1.0f);
	g = Mathf::Clamp(g + val.g, 0.0f, 1.0f);
	b = Mathf::Clamp(b + val.b, 0.0f, 1.0f);
	a = Mathf::Clamp(a + val.a, 0.0f, 1.0f);
	
	return *this;
}

FColor &FColor::operator =( const FColor &val )
{
	r = val.r;
	g = val.g;
	b = val.b;
	a = val.a;
	
	return *this;
}

XE::FColor operator *( XE::float32 a, const FColor &b )
{
	return b * a;
}
