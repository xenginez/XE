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
	template< typename T > std::shared_future< typename std::invoke_result_t< T > > PostTask( ThreadType type, T && func )
	{
		using result_type = std::invoke_result_t< T >;

		auto task = std::make_shared< std::packaged_task< result_type( void ) > >( std::bind( std::forward< T >( func ) ) );

		auto f = task->get_future().share();

		_PostTask( type, task );

		return f;
	}

	template< typename F, typename T > std::shared_future< typename std::invoke_result_t< T, F > > PostTask( ThreadType type, const std::shared_future< F > & future, T && func )
	{
		using result_type = std::invoke_result_t< T, F >;

		auto task = std::make_shared< std::packaged_task< result_type( F ) > >( std::bind( std::forward< T >( func ), std::placeholders::_1 ) );

		auto f = task->get_future().share();

		_PostTask( type, task, future );

		return f;
	}

	template< typename T > std::shared_future< typename std::invoke_result_t< T > > PostTask( ThreadType type, const std::shared_future< void > & future, T && func )
	{
		using result_type = std::invoke_result_t< T >;

		auto task = std::make_shared< std::packaged_task< result_type( void ) > >( std::bind( std::forward< T >( func ) ) );

		auto f = task->get_future().share();

		_PostTask( type, task, future );

		return f;
	}

private:
	template< typename T > void _PostTask( ThreadType type, const XE::SharedPtr< std::packaged_task< T > > & task )
	{
		_PostTask( [ task ]()
				   {
					   ( *task )( );
				   }, type );
	}

	template< typename T > void _PostTask( ThreadType type, const XE::SharedPtr< std::packaged_task< T > > & task, const std::shared_future< void > & future )
	{
		_PostTask( [ this, task, future ]()
				   {
					   if( std::is_ready( future ) )
					   {
						   ( *task )( );
					   }
					   else
					   {
						   _PostTask( task, future );
					   }
				   }, type );
	}

	template< typename T, typename F > void _PostTask( ThreadType type, const XE::SharedPtr< std::packaged_task< T > > & task, const std::shared_future< F > & future )
	{
		_PostTask( [ this, task, future ]()
				   {
					   if( std::is_ready( future ) )
					   {
						   ( *task )( future.get() );
					   }
					   else
					   {
						   _PostTask( task, future );
					   }
				   }, type );
	}

};

END_XE_NAMESPACE

#endif // __ITHREADSERVICE_H__ED1E7A09_4D24_49BF_BABB_9386218A9039
