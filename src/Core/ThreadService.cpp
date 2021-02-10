#include "ThreadService.h"

#include <tbb/concurrent_queue.h>

BEG_META( XE::ThreadService )
END_META()

struct XEPThread
{
	XEPThread() = default;

	~XEPThread() = default;

	virtual void Handler() = 0;

	virtual void PushTask( const std::function<void()> & val ) = 0;

	virtual bool HasThreadID( const std::thread::id & val ) = 0;

};

struct XEPMainThread : public XEPThread
{
	XEPMainThread()
		:_CurrentTasks( 0 ), _ID( std::this_thread::get_id() )
	{

	}

	void Handler() override
	{
		tbb::concurrent_queue< std::function<void()> > * Tasks = _CurrentTasks == 0 ? &_FrontTasks : &_BackTasks;
		_CurrentTasks = ( _CurrentTasks + 1 ) % 2;

		std::function<void()>  task;
		while( Tasks->try_pop( task ) )
		{
			if( task )
			{
				task();
			}
		}
	}

	void PushTask( const std::function<void()> & val ) override
	{
		_CurrentTasks == 0 ? _FrontTasks.push( val ) : _BackTasks.push( val );
	}

	bool HasThreadID( const std::thread::id & val )  override
	{
		return _ID == val;
	}

	std::thread::id _ID;
	std::atomic<XE::uint64> _CurrentTasks;
	tbb::concurrent_queue< std::function<void()> > _FrontTasks;
	tbb::concurrent_queue< std::function<void()> > _BackTasks;
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
		while( !_Exit )
		{
			if( _Tasks.empty() )
			{
				std::unique_lock<std::mutex> Lock( _Lock );

				_Variable.wait( Lock );
			}

			std::function<void()>  task;
			while( _Tasks.try_pop( task ) )
			{
				if( task )
				{
					task();
				}
			}
		}
	}

	virtual void PushTask( const std::function<void()> & val ) override
	{
		_Tasks.push( val );

		_Variable.notify_one();
	}

	bool HasThreadID( const std::thread::id & val )  override
	{
		return _Thread.get_id() == val;
	}

	bool _Exit = false;
	std::mutex _Lock;
	std::thread _Thread;
	std::condition_variable _Variable;
	tbb::concurrent_queue< std::function<void()> > _Tasks;
};

struct XEPWorkThread : public XEPThread
{
	XEPWorkThread()
	{
		for( XE::uint64 i = 0; i < std::thread::hardware_concurrency(); ++i )
		{
			_Threads.emplace_back( [this]() { Handler(); } );
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
		while( !_Exit )
		{
			if( _Tasks.empty() )
			{
				std::unique_lock<std::mutex> Lock( _Lock );

				_Variable.wait( Lock );
			}

			std::function<void()>  task;
			while( _Tasks.try_pop( task ) )
			{
				if( task )
				{
					task();
				}
			}

		}
	}

	virtual void PushTask( const std::function<void()> & val ) override
	{
		_Tasks.push( val );

		_Variable.notify_one();
	}

	bool HasThreadID( const std::thread::id & val )  override
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
	XE::Array<std::thread> _Threads;
	std::condition_variable _Variable;
	tbb::concurrent_queue< std::function<void()> > _Tasks;
};

struct XE::ThreadService::Private
{
	XE::Array<XEPThread *> _Threads;
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
	_p->_Threads.resize( ::XE_EnumID<XE::ThreadType>::Get()->GetEnumCount() );

	_p->_Threads[( XE::uint64 )XE::ThreadType::GAME] = new XEPMainThread();

	_p->_Threads[( XE::uint64 )XE::ThreadType::WORKS] = new XEPWorkThread();

	_p->_Threads[( XE::uint64 )XE::ThreadType::IO] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )XE::ThreadType::RENDER] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )XE::ThreadType::PHYSICS] = new XEPSpecialThread();
	_p->_Threads[( XE::uint64 )XE::ThreadType::NAVIGATION] = new XEPSpecialThread();

	return true;
}

void XE::ThreadService::Update()
{
	_p->_Threads[( XE::uint64 )XE::ThreadType::GAME]->Handler();
}

void XE::ThreadService::Clearup()
{
	_p->_Threads[( XE::uint64 )XE::ThreadType::GAME]->Handler();
	_p->_Threads[( XE::uint64 )XE::ThreadType::GAME]->Handler();

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
 
void XE::ThreadService::PostTask( ThreadType type, const TaskCallback & task )
{
	if( task )
	{
		if( GetCurrentThreadType() == type )
		{
			task();
		}
		else
		{
			_p->_Threads[( XE::uint64 )type]->PushTask( task );
		}
	}
}
