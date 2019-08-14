/*!
 * \file    InputLayout.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-30
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INPUTLAYOUT_H__65007D70_65D0_4A16_980E_84890890F11C
#define __INPUTLAYOUT_H__65007D70_65D0_4A16_980E_84890890F11C

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API InputLayout : public XE::Object
{
	OBJECT( InputLayout, Object )

public:
	struct Element
	{
		String Name;
		XE::uint32 Offset = 0;
		LayoutFormat Format = LayoutFormat::UINT8;
	};

public:
	InputLayout();
	
	~InputLayout() override;

public:
	InputLayout &Add( const String &name, XE::uint32 offset, LayoutFormat format );

public:
	XE::uint64 ElementCount() const;
	
public:
	Element &GetElement( XE::uint64 val );
	
	const Element &GetElement( XE::uint64 val ) const;
	
	const Array < Element > &GetElements() const;

public:
	Element &operator []( XE::uint64 val );
	
	const Element &operator []( XE::uint64 val ) const;

private:
	Array < Element > _Elements;
};

END_XE_NAMESPACE

#endif //__INPUTLAYOUT_H__65007D70_65D0_4A16_980E_84890890F11C
