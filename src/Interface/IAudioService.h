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

class INTERFACE_API IAudioService : public IService
{
	OBJECT( IAudioService, IService )

public:
	IAudioService();

	~IAudioService() override;

};

END_XE_NAMESAPCE

#endif // __IAUDIOSERVICE_H__D7BA5E87_2EE6_42C5_BDF4_403590223096
