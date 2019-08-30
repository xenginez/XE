/*!
 * \file	VertexLayout.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef VERTEXLAYOUT_H__0E5FC22E_B638_4507_9F10_BA8EB9559D5D
#define VERTEXLAYOUT_H__0E5FC22E_B638_4507_9F10_BA8EB9559D5D

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API VertexLayout
{
public:
	struct Element
	{
		String Name;
		XE::uint32 Size = 0;
		XE::uint32 Count = 0;
		XE::uint32 Offset = 0;
		AttributeType Type = AttributeType::FLOAT32;
	};

public:
	VertexLayout();

	~VertexLayout();

public:
	VertexLayout & Add( const String & name, XE::uint32 count, AttributeType type );

public:
	XE::uint64 GetElementCount() const;

public:
	const Element & GetElement( XE::uint64 val ) const;

public:
	const Element & operator []( XE::uint64 val ) const;

private:
	Array < Element > _Elements;
};

END_XE_NAMESPACE

#endif // VERTEXLAYOUT_H__0E5FC22E_B638_4507_9F10_BA8EB9559D5D
