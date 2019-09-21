/*!
 * \file   IProfilerService.h
 *
 * \author ZhengYuanQing
 * \date   2019/07/20
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IPROFILERSERVICE_H__F147BDBE_B82D_4711_9BE9_971C36ABF3E9
#define __IPROFILERSERVICE_H__F147BDBE_B82D_4711_9BE9_971C36ABF3E9

#include "IService.h"

BEG_XE_NAMESPACE


class XE_API ProfilerItem
{
public:
	std::chrono::system_clock::time_point StartTime;
	std::chrono::system_clock::time_point StopTime;
	Array<ProfilerItem> Children;
	String Text;
};

class XE_API ProfilerFrame : public std::enable_shared_from_this<ProfilerFrame>
{
public:
	thread_id tid;
	Array<ProfilerItem> Children;
};

class XE_API ProfilerTrack
{
public:
	ProfilerTrack( ProfilerItem * val );

	~ProfilerTrack();

private:
	ProfilerItem * _Item;
};



class XE_API IProfilerService : public IService
{
	OBJECT( IProfilerService, IService )
		
public:
	using ListenerType = std::function< void(ProfilerFramePtr) >;

public:
	IProfilerService();

	~IProfilerService() override;

public:
	virtual void BeginFrame() = 0;

	virtual void EndFrame() = 0;

public:
	virtual XE::uint64 RegisterListener( const ListenerType& val ) = 0;

	virtual bool UnregisterListener( XE::uint64 val ) = 0;

public:
	virtual ProfilerItem * AcquireTrack( const String& val ) = 0;

	virtual void ReleaseTrack( ProfilerItem * val ) = 0;

};

END_XE_NAMESPACE

#endif // __IPROFILERSERVICE_H__F147BDBE_B82D_4711_9BE9_971C36ABF3E9
