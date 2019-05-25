/*!
 * \file   IInputService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IINPUTSERVICE_H__C8BF1C9C_DABC_4831_9A86_582C71F3DF2C
#define __IINPUTSERVICE_H__C8BF1C9C_DABC_4831_9A86_582C71F3DF2C

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API IInputControl
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
	void SetValue( const String& code, const Variant& val );

public:
	IInputServicePtr _InputService;
};
DECL_PTR( IInputControl );

class INTERFACE_API IInputService : public IService
{
	OBJECT( IInputService, IService )

	friend class IInputControl;

public:
	IInputService();

	~IInputService() override;

public:
	virtual int32 GetPov( const String& val ) const = 0;

	virtual XE::float32 GetAxis( const String& val ) const = 0;

	virtual int32 GetButton( const String& val ) const = 0;

	virtual Variant GetValue( const String& val ) const = 0;

public:
	virtual int32 GetPov( KeyCode val ) const = 0;

	virtual XE::float32 GetAxis( KeyCode val ) const = 0;

	virtual int32 GetButton( KeyCode val ) const = 0;

	virtual Variant GetValue( KeyCode val ) const = 0;

protected:
	virtual void SetValue( const String& code, const Variant& val ) = 0;
};

END_XE_NAMESAPCE

#endif // __IINPUTSERVICE_H__C8BF1C9C_DABC_4831_9A86_582C71F3DF2C
