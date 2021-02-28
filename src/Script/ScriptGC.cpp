#include "ScriptGC.h"

#include <shared_mutex>

#include <tbb/concurrent_queue.h>
#include <tbb/concurrent_vector.h>
#include <tbb/scalable_allocator.h>

#include "ScriptRoot.h"
#include "ScriptObject.h"

struct XE::ScriptGC::Private
{
	std::shared_mutex _Mutex;

	XE::ScriptGCMarker _DefaultMark = ScriptGCMarker::WHITE1;
	std::atomic< XE::ScriptGCStatus > _Status = ScriptGCStatus::NONE;

	std::chrono::steady_clock::time_point _MarkerStartTime;
	std::chrono::steady_clock::duration _MarkerDurationTime;

	tbb::concurrent_queue< ScriptObject * > _MarkQueue;
	tbb::concurrent_queue< ScriptObject * > _FinalizeQueue;
	tbb::concurrent_queue< ScriptObject * > _AgainMarkQueue;

	tbb::concurrent_queue<XE::uint64> _FreeScriptRoots;
	tbb::concurrent_vector< XE::ScriptRoot * > _ScriptRoots;

	tbb::concurrent_queue<XE::uint64> _FreeScriptObjects;
	tbb::concurrent_vector< XE::ScriptObject * > _ScriptObjects;

	tbb::concurrent_queue<XE::uint64> _FreeSharedPointers;
	tbb::concurrent_vector< XE::SharedPtr< void > > _SharedPointers;
};

XE::ScriptGC::ScriptGC()
	:_p( new Private )
{

}

XE::ScriptGC::~ScriptGC()
{
	delete _p;
}

XE::ScriptObject * XE::ScriptGC::Alloc( XE::uint64 size )
{
	std::shared_lock< std::shared_mutex > lock( _p->_Mutex );

	XE::ScriptObject * p = new ( scalable_malloc( size ) ) XE::ScriptObject();

	p->SetMarker( _p->_DefaultMark );
	
	XE::uint64 index = 0;
	if( _p->_FreeScriptObjects.try_pop( index ) )
	{
		_p->_ScriptObjects[index] = p;
	}
	else
	{
		_p->_ScriptObjects.push_back( p );
	}

	return p;
}

void XE::ScriptGC::RegisterScriptRoot( XE::ScriptRoot * val )
{
	XE::uint64 index = 0;
	if( _p->_FreeScriptRoots.try_pop( index ) )
	{
		_p->_ScriptRoots[index] = val;
	}
	else
	{
		_p->_ScriptRoots.push_back( val );
	}
}

void XE::ScriptGC::UnregisterScriptRoot( XE::ScriptRoot * val )
{
	for( XE::uint64 i = 0; i < _p->_ScriptRoots.size(); ++i )
	{
		if( _p->_ScriptRoots[i] == val )
		{
			_p->_ScriptRoots[i] = nullptr;
			_p->_FreeScriptRoots.push( i );
			return;
		}
	}
}

void XE::ScriptGC::RegisterShaderPointer( const XE::SharedPtr< void > & val )
{
	XE::uint64 index = 0;
	if( _p->_FreeSharedPointers.try_pop( index ) )
	{
		_p->_SharedPointers[index] = val;
	}
	else
	{
		_p->_SharedPointers.push_back( val );
	}
}

void XE::ScriptGC::UnregisterShaderPointer( const XE::SharedPtr< void > & val )
{
	for( XE::uint64 i = 0; i < _p->_SharedPointers.size(); ++i )
	{
		if( _p->_SharedPointers[i] == val )
		{
			_p->_SharedPointers[i] = nullptr;
			_p->_FreeSharedPointers.push( i );
			return;
		}
	}
}

void XE::ScriptGC::WriteBarrier( XE::ScriptObject * val )
{
	_p->_AgainMarkQueue.push( val );
}

XE::ScriptGCStatus XE::ScriptGC::GetStatus() const
{
	return _p->_Status;
}

bool XE::ScriptGC::Collect( const std::chrono::steady_clock::duration & val /*= std::chrono::milliseconds( 6 ) */ )
{
	_p->_MarkerStartTime = std::chrono::steady_clock::now();
	_p->_MarkerDurationTime = val;

	if( _p->_Status == ScriptGCStatus::NONE )
	{
		std::unique_lock< std::shared_mutex > lock( _p->_Mutex );

		for( auto root : _p->_ScriptRoots )
		{
			root->Visit( [this]( XE::ScriptObject * obj )
						 {
							 obj->SetMarker( ScriptGCMarker::GRAY );

							 _p->_MarkQueue.push( obj );
						 } );
		}

		_p->_Status = ScriptGCStatus::PROPAGATE;

		if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
		{
			return false;
		}
	}

	if( _p->_Status == ScriptGCStatus::PROPAGATE )
	{
		XE::ScriptObject * obj = nullptr;
		while( _p->_MarkQueue.try_pop( obj ) )
		{
			obj->GetMetaClass()->VisitProperty( [this, obj]( XE::IMetaPropertyPtr prop )
												{
													if( prop->GetValue()->GetType() == XE::MetaType::CLASS )
													{
														if( SP_CAST< XE::IMetaClass >( prop->GetValue() )->CanConvert( XE::ScriptObject::GetMetaClassStatic() ) )
														{
															if( XE::ScriptObject * val = prop->Get( obj ).Value< XE::ScriptObject * >() )
															{
																if( ( XE::uint8 )val->GetMarker() & ( XE::uint8 )ScriptGCMarker::WHITE )
																{
																	val->SetMarker( ScriptGCMarker::GRAY );

																	_p->_MarkQueue.push( val );
																}
															}
														}
													}
												} );

			obj->SetMarker( ScriptGCMarker::BLACK );

			if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
			{
				return false;
			}
		}

		if( _p->_MarkQueue.empty() )
		{
			_p->_Status = ScriptGCStatus::AGAIN_PROPAGATE;
		}
	}

	if( _p->_Status == ScriptGCStatus::AGAIN_PROPAGATE )
	{
		std::unique_lock< std::shared_mutex > lock( _p->_Mutex );

		XE::ScriptObject * obj = nullptr;
		while( _p->_AgainMarkQueue.try_pop( obj ) )
		{
			obj->GetMetaClass()->VisitProperty( [this, obj]( XE::IMetaPropertyPtr prop )
												{
													if( prop->GetValue()->GetType() == XE::MetaType::CLASS )
													{
														if( SP_CAST< XE::IMetaClass >( prop->GetValue() )->CanConvert( XE::ScriptObject::GetMetaClassStatic() ) )
														{
															if( XE::ScriptObject * val = prop->Get( obj ).Value< XE::ScriptObject * >() )
															{
																if( ( XE::uint8 )val->GetMarker() & ( XE::uint8 )ScriptGCMarker::WHITE )
																{
																	val->SetMarker( ScriptGCMarker::GRAY );

																	_p->_MarkQueue.push( val );
																}
															}
														}
													}
												} );

			obj->SetMarker( ScriptGCMarker::BLACK );
		}

		_p->_DefaultMark = _p->_DefaultMark == ScriptGCMarker::WHITE1 ? ScriptGCMarker::WHITE2 : ScriptGCMarker::WHITE1;

		_p->_Status = ScriptGCStatus::SWEEP;

		if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
		{
			return false;
		}
	}

	if( _p->_Status == ScriptGCStatus::SWEEP )
	{
		auto marker = _p->_DefaultMark == ScriptGCMarker::WHITE1 ? ScriptGCMarker::WHITE2 : ScriptGCMarker::WHITE1;

		for( size_t i = 0; i < _p->_ScriptObjects.size(); i++ )
		{
			auto p = _p->_ScriptObjects[i];
			if( p->GetMarker() == marker )
			{
				_p->_FinalizeQueue.push( p );
				_p->_FreeScriptObjects.push( i );
			}

			if( i % 10 == 0 )
			{
				if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
				{
					return false;
				}
			}
		}

		_p->_Status = ScriptGCStatus::FINALIZE;

		if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
		{
			return false;
		}
	}

	if( _p->_Status == ScriptGCStatus::FINALIZE )
	{
		XE::ScriptObject * obj = nullptr;
		while( _p->_FinalizeQueue.try_pop( obj ) )
		{
			auto finalize = obj->GetFinalizeCallback();

			if( finalize )
			{
				finalize( obj );
			}

			scalable_free( obj );

			if( ( std::chrono::steady_clock::now() - _p->_MarkerStartTime ) >= _p->_MarkerDurationTime )
			{
				return false;
			}
		}

		_p->_Status = ScriptGCStatus::NONE;
	}

	return true;
}
