/*!
 * \file   IAudioService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IAUDIOSERVICE_H__D7BA5E87_2EE6_42C5_BDF4_403590223096
#define __IAUDIOSERVICE_H__D7BA5E87_2EE6_42C5_BDF4_403590223096

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IAudioService : public IService
{
	OBJECT( IAudioService, IService )

private:
	struct Private;

public:
	IAudioService();

	~IAudioService() override;

public:
	virtual void Resume() = 0;

	virtual void Suspend() = 0;

public:
	const XE::Vec3 & GetListenerPosition() const;

	void SetListenerPosition( const XE::Vec3 & val );

	const XE::Vec3 & GetListenerVelocity() const;

	void SetListenerVelocity( const XE::Vec3 & val );

	const XE::Vec3 & GetListenerOrientation() const;

	void SetListenerOrientation( const XE::Vec3 & val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __IAUDIOSERVICE_H__D7BA5E87_2EE6_42C5_BDF4_403590223096
