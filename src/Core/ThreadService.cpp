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

struct XEPThread
{
	XEPThread() = default;

	~XEPThread() = default;

	virtual void Handler() = 0;

	virtual void PushTask( XEPTask && val ) = 0;

	virtual XE::uint64 QueueSize() = 0;

	virtual void Notify() = 0;
};

struct XEPMainThread : public XEPThread
{
	XEPMainThread()
		:_CurrentTasks( 0 )
	{

	}

	void Handler() override
	{
		tbb::concurrent_priority_queue<XEPTask> * Tasks = _CurrentTasks == 0 ? &_FrontTasks : &_BackTasks;
		_CurrentTasks = ( _CurrentTasks + 1 ) % 2;

		XEPTask task;
		while( Tasks->try_pop( task ) )
		{
			if( task.Task )
			{
				if( task.Task() )
				{
					PushTask( std::move( task ) );
				}
			}
		}
	}

	void PushTask( XEPTask && val ) override
	{
		_CurrentTasks == 0 ? _FrontTasks.push( val ) : _BackTasks.push( val );
	}

	XE::uint64 QueueSize() override
	{
		return _CurrentTasks == 0 ? _FrontTasks.size() : _BackTasks.size();
	}

	void Notify() override
	{

	}

	std::atomic<XE::uint64> _CurrentTasks;
	tbb::concurrent_priority_queue<XEPTask> _FrontTasks;
	tbb::concurrent_priority_queue<XEPTask> _BackTasks;
};

struct XEPSpecialThread : public XEPThread
{
	XEPSpecialThread()
		:_Thread( &XEPSpecialThread::Handler, this )
	{

	}

	~XEPSpecialThread()
	{
		_Exit = true;

		_Variable.notify_all();

		if( _Thread.joinable() )
		{
			_Thread.join();
		}
	}

	void Handler() override
	{
		std::unique_lock<std::mutex> Lock( _Lock );

		while( !_Exit )
		{
			if( QueueSize() == 0 )
			{
				_Variable.wait( Lock );
			}

			if( _Exit )
			{
				return;
			}

			XEPTask task;
			while( _Tasks.try_pop( task ) )
			{
				if( task.Task )
				{
					if( task.Task() )
					{
						PushTask( std::move( task ) );
					}
				}
			}


		}
	}

	virtual void PushTask( XEPTask && val ) override
	{
		_Tasks.push( val );
	}

	virtual XE::uint64 QueueSize() override
	{
		return _Tasks.size();
	}

	virtual void Notify() override
	{
		_Variable.notify_one();
	}

	bool _Exit = false;
	std::mutex _Lock;
	std::thread _Thread;
	std::condition_variable _Variable;
	tbb::concurrent_priority_queue<XEPTask> _Tasks;
};

struct XEPWorkThread : public XEPThread
{
	XEPWorkThread()
	{
		for( XE::uint64 i = 0; i < std::thread::hardware_concurrency(); ++i )
		{
			_Threads.push_back( std::thread( &XEPWorkThread::Handler, this ) );
		}
	}

	~XEPWorkThread()
	{
		_Exit = true;

		_Variable.notify_all();

		for( int i = 0; i < _Threads.size(); ++i )
		{
			if( _Threads[i].joinable() )
			{
				_Threads[i].join();
			}
		}
	}

	void Handler()
	{
		std::unique_lock<std::mutex> Lock( _Lock );

		while( !_Exit )
		{
			if( QueueSize() == 0 )
			{
				_Variable.wait( Lock );
			}

			if( _Exit )
			{
				return;
			}

			XEPTask task;
			while( _Tasks.try_pop( task ) )
			{
				if( task.Task )
				{
					if( task.Task() )
					{
						PushTask( std::move( task ) );
					}
				}
			}

		}
	}

	virtual void PushTask( XEPTask && val ) override
	{
		_Tasks.push( val );
	}

	virtual XE::uint64 QueueSize() override
	{
		return _Tasks.size();
	}

	virtual void Notify() override
	{
		_Variable.notify_one();
	}

	bool _Exit = false;
	std::mutex _Lock;
	Array<std::thread> _Threads;
	std::condition_variable _Variable;
	tbb::concurrent_priority_queue<XEPTask> _Tasks;
};


struct ThreadService::Private
{
	Array<XEPThread *> _Threads;
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
	_p->_Threads.resize( EnumID<ThreadType>::Get()->GetEnumCount() );

	_p->_Threads[( XE::uint64 )ThreadType::IO] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )ThreadType::MAIN] = new XEPMainThread();
	_p->_Threads[( XE::uint64 )ThreadType::GAME] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )ThreadType::RENDER] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )ThreadType::PHYSICS] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )ThreadType::NAVIGATION] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )ThreadType::WORKS] = new XEPWorkThread();

	return true;
}

void XE::ThreadService::Update()
{
	_p->_Threads[( XE::uint64 )ThreadType::MAIN]->Handler();
}

void XE::ThreadService::Clearup()
{
	for( auto p : _p->_Threads )
	{
		delete p;
	}

	_p->_Threads.clear();
}

bool XE::ThreadService::PostTask( TaskType task, ThreadType type, ThreadPriority pri /*= ThreadPriority::NORM*/ )
{
	XEPTask tk;
	tk.Pri = pri;
	tk.Task = task;

	_p->_Threads[( XE::uint64 )type]->PushTask( std::move( tk ) );
	_p->_Threads[( XE::uint64 )type]->Notify();

	return true;
}

void XE::ThreadService::Prepare()
{

}
