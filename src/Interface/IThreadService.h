/*!
 * \file   IThreadService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
#define __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API IThreadService : public IService
{
	OBJECT( IThreadService, IService )

public:
	using TaskType = std::function<void()>;

public:
	IThreadService();

	~IThreadService() override;

public:
	virtual thread_id GetIOThread() const = 0;

	virtual thread_id GetMainThread() const = 0;

	virtual thread_id GetGameThread() const = 0;

	virtual thread_id GetRenderThread() const = 0;

	virtual thread_id GetPhysicsThread() const = 0;

	virtual thread_id GetNavigationThread() const = 0;

	virtual thread_id GetWorkThread( XE::uint64 val ) const = 0;

public:
	virtual bool RegisterTask( TaskType task, thread_id tid = std::this_thread::get_id(), ThreadPriority pri = ThreadPriority::NORM ) = 0;

};

END_XE_NAMESPACE

#endif // __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
