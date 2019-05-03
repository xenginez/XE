/*!
 * \file   InputService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/08
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __INPUTSERVICE_H__1AA680A2_3C45_4FAF_A62A_EF525EE5FFFD
#define __INPUTSERVICE_H__1AA680A2_3C45_4FAF_A62A_EF525EE5FFFD

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API InputService : public IInputService
{
	OBJECT( InputService, IInputService )

private:
	struct Private;

public:
	InputService();

	~InputService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual int32 GetPov( const String& val ) const override;

	virtual float GetAxis( const String& val ) const override;

	virtual int32 GetButton( const String& val ) const override;

	virtual Variant GetValue( const String& val ) const override;

public:
	virtual int32 GetPov( KeyCode val ) const override;

	virtual float GetAxis( KeyCode val ) const override;

	virtual int32 GetButton( KeyCode val ) const override;

	virtual Variant GetValue( KeyCode val ) const override;

protected:
	virtual void SetValue( const String& code, const Variant& val ) override;

private:
	String GetKeycodeString( KeyCode val ) const;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __INPUTSERVICE_H__1AA680A2_3C45_4FAF_A62A_EF525EE5FFFD
