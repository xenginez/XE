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

class XE_API InputService : public IInputService
{
	OBJECT( InputService, IInputService )

private:
	struct Private;

public:
	InputService();

	~InputService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void ResetInputValues() override;

public:
	XE::Follow RegisterButtonPressed( XE::KeyCode key, const ButtonChangedCallbackType & callback ) override;

	XE::Follow RegisterButtonRelease( XE::KeyCode key, const ButtonChangedCallbackType & callback ) override;

protected:
	XE::Variant GetValue( const String & val ) const override;

	void SetValue( const String & code, XE::Variant val ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __INPUTSERVICE_H__1AA680A2_3C45_4FAF_A62A_EF525EE5FFFD
