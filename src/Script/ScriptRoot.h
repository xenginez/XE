/*!
 * \file	ScriptRoot.h
 *
 * \author	ZhengYuanQing
 * \date	2021/02/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCRIPTROOT_H__DC2FAD58_0F6F_451B_992D_0B9BFDC42CC5
#define SCRIPTROOT_H__DC2FAD58_0F6F_451B_992D_0B9BFDC42CC5

#include <functional>

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ScriptRoot : public XE::NonCopyable
{
public:
	using VisitCallbackType = std::function< void( XE::ScriptObject * ) >;

public:
	ScriptRoot() = default;

	virtual ~ScriptRoot() = default;

public:
	virtual void Visit( const VisitCallbackType & val ) = 0;
};

class XE_API ScriptObjectRoot : public XE::ScriptRoot
{
public:
	ScriptObjectRoot( XE::ScriptObject * val );

public:
	void Visit( const VisitCallbackType & val ) override;

private:
	XE::ScriptObject * _Object = nullptr;
};

END_XE_NAMESPACE

#endif // SCRIPTROOT_H__DC2FAD58_0F6F_451B_992D_0B9BFDC42CC5
