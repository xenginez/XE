/*!
 * \file	DrawCall.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DRAWCALL_H__9A8C9BA8_A1DD_4D3C_8E50_44C4BF744333
#define DRAWCALL_H__9A8C9BA8_A1DD_4D3C_8E50_44C4BF744333

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API DrawCall
{
public:
	union Encode
	{
		XE::uint64 key;
		struct 
		{
			XE::uint16 layer;
			XE::uint16 zorder;
			XE::uint16 shader;
			XE::uint16 texture;
		};
	};

public:
	Encode GetEncode() const;

public:
	void SetIndexBuffer( const IndexBufferPtr & val );

	void SetVertexBuffer( const VertexBufferPtr & val );

private:
	Encode _Encode;
};

END_XE_NAMESPACE

#endif // DRAWCALL_H__9A8C9BA8_A1DD_4D3C_8E50_44C4BF744333
