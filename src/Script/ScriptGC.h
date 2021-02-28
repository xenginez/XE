/*!
 * \file	ScriptGC.h
 *
 * \author	ZhengYuanQing
 * \date	2021/02/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCRIPTGC_H__798AE184_87ED_4A11_B667_BF5B704A44D1
#define SCRIPTGC_H__798AE184_87ED_4A11_B667_BF5B704A44D1

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ScriptGC
{
private:
	struct Private;

public:
	ScriptGC();

	~ScriptGC();

public:
	XE::ScriptObject * Alloc( XE::uint64 size );

public:
	void RegisterScriptRoot( XE::ScriptRoot * val );

	void UnregisterScriptRoot( XE::ScriptRoot * val );

public:
	void RegisterShaderPointer( const XE::SharedPtr< void > & val );

	void UnregisterShaderPointer( const XE::SharedPtr< void > & val );

public:
	void WriteBarrier( XE::ScriptObject * val );

public:
	ScriptGCStatus GetStatus() const;

public:
	bool Collect( const std::chrono::steady_clock::duration & val = std::chrono::milliseconds( 6 ) );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // SCRIPTGC_H__798AE184_87ED_4A11_B667_BF5B704A44D1
