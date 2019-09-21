/*!
 * \file   ProfilerService.h
 *
 * \author ZhengYuanQing
 * \date   2019/07/20
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PROFILERSERVICE_H__A30EEDC1_A6E6_4253_9004_F69B001EBECD
#define __PROFILERSERVICE_H__A30EEDC1_A6E6_4253_9004_F69B001EBECD

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ProfilerService : public IProfilerService
{
	OBJECT( ProfilerService, IProfilerService )

private:
	struct Private;

public:
	ProfilerService();

	~ProfilerService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void BeginFrame() override;

	void EndFrame() override;

public:
	XE::uint64 RegisterListener( const ListenerType& val ) override;

	bool UnregisterListener( XE::uint64 val ) override;

public:
	ProfilerItem* AcquireTrack( const String& val ) override;

	void ReleaseTrack( ProfilerItem* val ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __PROFILERSERVICE_H__A30EEDC1_A6E6_4253_9004_F69B001EBECD
