/*!
 * \file   IInputControl.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/11
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef IINPUTCONTROL_H__47F3B585_7B86_41CE_8C55_DAF31DB9C4C2
#define IINPUTCONTROL_H__47F3B585_7B86_41CE_8C55_DAF31DB9C4C2

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API IInputControl
{
	OBJECT( IInputControl )

	friend class IInputService;

public:
	IInputControl();

	virtual ~IInputControl();

public:
	virtual bool Startup() = 0;

	virtual void Update() = 0;

	virtual void Clearup() = 0;

protected:
	void SetValue( const String & code, XE::Variant val );

public:
	IInputServicePtr _InputService;
};

END_XE_NAMESPACE

#endif // IINPUTCONTROL_H__47F3B585_7B86_41CE_8C55_DAF31DB9C4C2
