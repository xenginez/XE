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

class XE_API ThreadService : public IThreadService
{
	OBJECT( ThreadService, IThreadService )

private:
	struct Private;

public:
	ThreadService();

	~ThreadService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	ThreadType GetCurrentThreadType() const override;

public:
	std::future<XE::uint32> PostTask( TaskType task, ThreadType type, ThreadPriority pri = ThreadPriority::NORM ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __THREADSERVICE_H__5E718656_36CC_4C4A_9077_F6887B508EC8
