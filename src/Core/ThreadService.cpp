#include "ThreadService.h"

#include <tbb/concurrent_priority_queue.h>

USING_XE

BEG_META( ThreadService )
END_META()

struct XEPTask
{
	XE::uint32 ExecCount = 0;
	std::promise<XE::uint32> Promise;
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

	virtual bool HasThreadID( const thread_id & val ) = 0;

};

struct XEPMainThread : public XEPThread
{
	XEPMainThread()
		:_CurrentTasks( 0 ), _ID( std::this_thread::get_id() )
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
				bool ret = task.Task();

				task.Promise.set_value( ++task.ExecCount );

				if( ret )
				{
					PushTask( std::move( task ) );
				}
			}
		}
	}

	void PushTask( XEPTask && val ) override
	{
		_CurrentTasks == 0 ? _FrontTasks.push( std::move( val ) ) : _BackTasks.push( std::move( val ) );
	}

	XE::uint64 QueueSize() override
	{
		return _CurrentTasks == 0 ? _FrontTasks.size() : _BackTasks.size();
	}

	void Notify() override
	{

	}

	bool HasThreadID( const thread_id & val )  override
	{
		return _ID == val;
	}

	thread_id _ID;
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
			FrameAlloc::Reset();

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
					bool ret = task.Task();

					task.Promise.set_value( ++task.ExecCount );

					if( ret )
					{
						PushTask( std::move( task ) );
					}
				}
			}
		}
	}

	virtual void PushTask( XEPTask && val ) override
	{
		_Tasks.push( std::move( val ) );
	}

	virtual XE::uint64 QueueSize() override
	{
		return _Tasks.size();
	}

	virtual void Notify() override
	{
		_Variable.notify_one();
	}

	bool HasThreadID( const thread_id & val )  override
	{
		return _Thread.get_id() == val;
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
			FrameAlloc::Reset();

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
					bool ret = task.Task();

					task.Promise.set_value( ++task.ExecCount );

					if( ret )
					{
						PushTask( std::move( task ) );
					}
				}
			}

		}
	}

	virtual void PushTask( XEPTask && val ) override
	{
		_Tasks.push( std::move( val ) );
	}

	virtual XE::uint64 QueueSize() override
	{
		return _Tasks.size();
	}

	virtual void Notify() override
	{
		_Variable.notify_one();
	}

	bool HasThreadID( const thread_id & val )  override
	{
		for( const auto & it : _Threads )
		{
			if( it.get_id() == val )
			{
				return true;
			}
		}

		return false;
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

void XE::ThreadService::Prepare()
{

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

XE::ThreadType XE::ThreadService::GetCurrentThreadType() const
{
	auto id = std::this_thread::get_id();

	for( XE::uint64 i = 0; i < _p->_Threads.size(); ++i )
	{
		if( _p->_Threads[i]->HasThreadID( id ) )
		{
			return ( XE::ThreadType )( i );
		}
	}

	return XE::ThreadType::UNKNOWN;
}

std::future<XE::uint32> XE::ThreadService::PostTask( TaskType task, ThreadType type, ThreadPriority pri /*= ThreadPriority::NORM*/ )
{
	XEPTask tk;

	tk.Pri = pri;
	tk.Task = task;

	std::future<XE::uint32> future = tk.Promise.get_future();

	_p->_Threads[( XE::uint64 )type]->PushTask( std::move( tk ) );
	_p->_Threads[( XE::uint64 )type]->Notify();

	return std::move( future );
}
