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

class RHI_API InputLayout
{
public:
	struct Element
	{
		String Name;
		uint32 Offset;
		LayoutFormat Format;
	};

public:
	InputLayout();
	
	~InputLayout();

public:
	InputLayout &Add( const String &name, uint32 offset, LayoutFormat format );

public:
	uint32 ElementCount() const;
	
	Element &GetElement( uint32 val );
	
	const Element &GetElement( uint32 val ) const;
	
	const Array < Element > &GetElements() const;

public:
	Element &operator []( uint32 val );
	
	const Element &operator []( uint32 val ) const;

private:
	Array < Element > _Elements;
};

END_XE_NAMESPACE

#endif //__INPUTLAYOUT_H__65007D70_65D0_4A16_980E_84890890F11C
