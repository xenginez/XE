/*!
 * \file   ThreadService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/04
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __THREADSERVICE_H__5E718656_36CC_4C4A_9077_F6887B508EC8
#define __THREADSERVICE_H__5E718656_36CC_4C4A_9077_F6887B508EC8

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API ThreadService : public IThreadService
{
	OBJECT( ThreadService, IThreadService )

private:
	struct Private;

public:
	ThreadService();

	~ThreadService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

public:
	virtual TID GetIOThread() const override;

	virtual TID GetMainThread() const override;

	virtual TID GetGameThread() const override;

	virtual TID GetRenderThread() const override;

	virtual TID GetPhysicsThread() const override;

	virtual TID GetNavigationThread() const override;

	virtual TID GetWorkThread( XE::uint64 val ) const override;

public:
	virtual bool RegisterTask( TaskType task, TID tid = std::this_thread::get_id(), ThreadPriority pri = ThreadPriority::NORM ) override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __THREADSERVICE_H__5E718656_36CC_4C4A_9077_F6887B508EC8
