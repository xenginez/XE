#include "ThreadService.h"

#include <tbb/concurrent_priority_queue.h>

#define TOOL_THREAD (5)
#define THREAD_COUNT (std::thread::hardware_concurrency() + TOOL_THREAD)

#define IO_INDEX 0
#define GAME_INDEX 1
#define RENDER_INDEX 2
#define PHYSICS_INDEX 3
#define NAVIGATION_INDEX 4

USING_XE

BEG_META( ThreadService )
END_META()

struct XEPTask
{
	ThreadPriority Pri = XE::ThreadPriority::NORM;
	IThreadService::TaskType Task = nullptr;
};

template<> struct std::less<XEPTask>
{
	typedef XEPTask first_argument_type;
	typedef XEPTask second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const first_argument_type& _Left, const second_argument_type& _Right ) const
	{
		return ( _Left.Pri < _Right.Pri );
	}
};

struct XEPMainThread
{
	XEPMainThread()
		:_CurrentTasks( 0 )
	{

	}

	XEPMainThread( TID id )
		:_CurrentTasks( 0 ), _Tid( id )
	{

	}

	~XEPMainThread()
	{

	}

	void Handler()
	{
		tbb::concurrent_priority_queue<XEPTask> * Tasks = _CurrentTasks == 0 ? &_FrontTasks : &_BackTasks;

		_CurrentTasks = ( _CurrentTasks + 1 ) % 2;

		XEPTask task;
		while ( Tasks->try_pop( task ) )
		{
			if ( task.Task )
			{
				task.Task();
			}
		}
	}

	void PushTask( XEPTask && val )
	{
		_CurrentTasks == 0 ? _FrontTasks.push( val ) : _BackTasks.push( val );
	}

	TID _Tid;
	XE::uint64 _CurrentTasks;
	tbb::concurrent_priority_queue<XEPTask> _FrontTasks;
	tbb::concurrent_priority_queue<XEPTask> _BackTasks;
};

struct XEPWorkThread : public XEPMainThread
{
	XEPWorkThread()
		:_Exit( false ), _Thread( &XEPWorkThread::Handler2, this )
	{
		_Tid = _Thread.get_id();
	}

	~XEPWorkThread()
	{
		if ( _Thread.joinable() )
		{
			_Thread.join();
		}
	}

	void Handler2()
	{
		std::unique_lock<std::mutex> Lock( _Lock );

		while ( !_Exit )
		{
			Handler();

			if ( _Exit )
			{
				return;
			}

			_Variable.wait( Lock );
		}
	}

	bool _Exit;
	std::mutex _Lock;
	std::thread _Thread;
	std::condition_variable _Variable;
};

struct ThreadService::Private
{
	XEPMainThread * _MainThread = nullptr;
	XEPWorkThread ** _Threads = nullptr;
};

XE::ThreadService::ThreadService()
	:_p( new Private )
{

}

XE::ThreadService::~ThreadService()
{
	delete _p;
}

bool XE::ThreadService::Startup()
{
	_p->_MainThread = new XEPMainThread( std::this_thread::get_id() );

	_p->_Threads = (XEPWorkThread**)( new XEPWorkThread[THREAD_COUNT] );

	return true;
}

void XE::ThreadService::Update()
{
	_p->_MainThread->Handler();
}

void XE::ThreadService::Clearup()
{
	if( _p->_MainThread )
	{
		delete _p->_MainThread;
	}

	if( _p->_Threads )
	{
		for( XE::uint64 i = 0; i < THREAD_COUNT; i++ )
		{
			_p->_Threads[i]->_Exit = true;
		}

		delete[]( (XEPWorkThread * )_p->_Threads );
	}
}

XE::TID XE::ThreadService::GetIOThread() const
{
	return _p->_Threads[IO_INDEX]->_Tid;
}

XE::TID XE::ThreadService::GetMainThread() const
{
	return _p->_MainThread->_Tid;
}

XE::TID XE::ThreadService::GetGameThread() const
{
	return _p->_Threads[GAME_INDEX]->_Tid;
}

XE::TID XE::ThreadService::GetRenderThread() const
{
	return _p->_Threads[RENDER_INDEX]->_Tid;
}

XE::TID XE::ThreadService::GetPhysicsThread() const
{
	return _p->_Threads[PHYSICS_INDEX]->_Thread.get_id();
}

XE::TID XE::ThreadService::GetNavigationThread() const
{
	return _p->_Threads[NAVIGATION_INDEX]->_Tid;
}

XE::TID XE::ThreadService::GetWorkThread( XE::uint64 val ) const
{
	XE_ASSERT( val < std::thread::hardware_concurrency() );

	return _p->_Threads[TOOL_THREAD + val]->_Tid;
}

bool XE::ThreadService::RegisterTask( TaskType task, TID tid /*= std::this_thread::get_id() */, ThreadPriority pri /*= ThreadPriority::NORM*/ )
{
	XEPTask tk;
	tk.Pri = pri;
	tk.Task = task;

	if ( tid == _p->_MainThread->_Tid )
	{
		_p->_MainThread->PushTask( std::move( tk ) );
		return true;
	}

	for ( XE::uint64 i = 0; i < THREAD_COUNT; ++i )
	{
		if ( tid == _p->_Threads[i]->_Tid )
		{
			_p->_Threads[i]->PushTask( std::move( tk ) );
			_p->_Threads[i]->_Variable.notify_one();
			return true;
		}
	}

	return false;
}
