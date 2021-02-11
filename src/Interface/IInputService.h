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

#include "Math/Vec2.h"
#include "Utils/Follow.h"

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IInputService : public IService
{
	OBJECT( IInputService, IService )

	friend class IInputControl;

public:
	using ButtonChangedCallbackType = std::function< void() >;

public:
	IInputService();

	~IInputService() override;

public:
	XE::float32 GetAxis( XE::KeyCode val ) const;

	XE::float32 GetAxis( const XE::String & val ) const;

public:
	bool GetButton( XE::KeyCode val ) const;

	bool GetButton( const XE::String & val ) const;

	bool GetButtonPressed( XE::KeyCode val ) const;

	bool GetButtonPressed( const XE::String & val ) const;

	bool GetButtonRelease( XE::KeyCode val ) const;

	bool GetButtonRelease( const XE::String & val ) const;

public:
	XE::float32 GetMouseWheel() const;

	XE::Vec2i GetMousePosition() const;

public:
	virtual void ResetInputValues() = 0;

public:
	virtual XE::Follow RegisterButtonPressed( XE::KeyCode key, const ButtonChangedCallbackType & callback ) = 0;

	virtual XE::Follow RegisterButtonRelease( XE::KeyCode key, const ButtonChangedCallbackType & callback ) = 0;

public:
	virtual XE::Variant GetValue( const XE::String & val ) const = 0;

protected:
	virtual void SetValue( const XE::String & code, XE::Variant val ) = 0;
};

END_XE_NAMESPACE

#endif // __IINPUTSERVICE_H__C8BF1C9C_DABC_4831_9A86_582C71F3DF2C
