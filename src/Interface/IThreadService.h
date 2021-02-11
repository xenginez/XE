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

#include <future>

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IThreadService : public IService
{
	OBJECT( IThreadService, IService )

public:
	using TaskCallback = std::function<void()>;

public:
	IThreadService();

	~IThreadService() override;

public:
	virtual ThreadType GetCurrentThreadType() const = 0;

public:
	virtual void PostTask( ThreadType type, const TaskCallback & task ) = 0;

public:
    template< typename R > void PostTask( ThreadType type, const std::function< R() > & task, const std::function< void( R ) > & callback )
    {
        PostTask( type, [task, callback]()
                  {
                      if( callback )
					  {
						  callback( task() );
                      }
                  } );
    }
};

END_XE_NAMESPACE

#define ASSERT_THREAD( THREAD_TYPE ) \
    XE_ASSERT( XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->GetCurrentThreadType() != THREAD_TYPE )

#define CHECK_THREAD( THREAD_TYPE ) \
XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->GetCurrentThreadType() == THREAD_TYPE

#endif // __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
