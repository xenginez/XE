/*!
 * \file	Encoder.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD
#define ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD

#include "Type.h"

BEG_XE_NAMESPACE

class DrawCall;

class RHI_API Encoder
{
public:
	Encoder( ContextPtr val );

	~Encoder();

public:
	void Begin();

public:
	void SetScissor( const Rect & val );

	void SetViewTransform( const Mat4 & val );

public:
	void Push( DrawCall && val );

public:
	void End();

};

END_XE_NAMESPACE

#endif // ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD
