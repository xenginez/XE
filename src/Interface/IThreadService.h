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
	virtual TID GetIOThread() const = 0;

	virtual TID GetMainThread() const = 0;

	virtual TID GetGameThread() const = 0;

	virtual TID GetRenderThread() const = 0;

	virtual TID GetPhysicsThread() const = 0;

	virtual TID GetNavigationThread() const = 0;

	virtual TID GetWorkThread( XE::uint64 val ) const = 0;

public:
	virtual bool RegisterTask( TaskType task, TID tid = std::this_thread::get_id(), ThreadPriority pri = ThreadPriority::NORM ) = 0;

};

END_XE_NAMESPACE

#endif // __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
