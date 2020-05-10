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

class XE_API IThreadService : public IService
{
	OBJECT( IThreadService, IService )

public:
	IThreadService();

	~IThreadService() override;

public:
	virtual ThreadType GetCurrentThreadType() const = 0;

protected:
	virtual void _PostTask( std::function<void()> && task, ThreadType type ) = 0;

public:
	template< typename T, typename ... Args >
	std::future<typename std::result_of<T( Args... )>::type> PostTask( ThreadType type, T && t, Args &&... args )
	{
		using return_type = typename std::result_of<T( Args... )>::type;

		auto _task = XE::MakeShared< std::packaged_task< return_type() > >( std::bind(std::forward<T>(t), std::forward<Args>(args)...) );

		_PostTask( [_task]()
				   {
					   ( *_task )( );
				   }, type );

		return std::move( _task->get_future() );
	}

	template< typename F, typename T, typename ... Args >
	std::future<typename std::result_of<T( Args... )>::type> PostTask( const std::shared_future < F > & future, ThreadType type, T && t, Args &&... args )
	{
		using return_type = typename std::result_of<T( Args... )>::type;

		auto _task = XE::MakeShared< std::packaged_task< return_type() > >( std::bind( std::forward<T>( t ), std::forward<Args>( args )... ) );

		_PostTask( future, std::forward( _task ), type );

		return std::move( _task->get_future() );
	}

private:
    template< typename F, typename T > void _PostTask( const std::shared_future < F > & future, T && task, ThreadType type )
    {
		PostTask( [this, future, _task, type]()
				  {
					  if( std::is_ready( future ) )
					  {
						  ( *_task )( );
					  }
					  else
					  {
						  _PostTask( future, std::forward( _task ), type, pri );
					  }

				  }, type );
    }

};

END_XE_NAMESPACE

#endif // __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
