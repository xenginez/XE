/*!
 * \file	InputControl.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef INPUTCONTROL_H__A33FA25A_E85B_470B_8A81_B7A0D777F613
#define INPUTCONTROL_H__A33FA25A_E85B_470B_8A81_B7A0D777F613

#include "Type.h"

BEG_XE_NAMESPACE

class DLL_EXPORT InputControl : public XE::IPlugin
{
public:
	InputControl( IFrameworkPtr framework );

	virtual ~InputControl();

public:
	String GetName() const override;

public:
	void Startup() override;

	void Clearup() override;
};

END_XE_NAMESPACE

#endif // INPUTCONTROL_H__A33FA25A_E85B_470B_8A81_B7A0D777F613
