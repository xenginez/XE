/*!
 * \file	SignalSlot.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/12/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SIGNALSLOT_HPP__9F7422B2_7E73_46FB_A430_2863EF498E9E
#define SIGNALSLOT_HPP__9F7422B2_7E73_46FB_A430_2863EF498E9E

#include "Type.h"

BEG_XE_NAMESPACE

template< typename ... Args> class Signal;
template<typename ... Args> class Slot;

template< typename ... Args> class Signal
{
public:
	friend class Slot<Args...>;

public:
	Signal() = default;

	~Signal()
	{
		for( auto slot : _Slots )
		{
			slot->disconnect( this );
		}
	}

public:
	void operator() ( Args && ...args ) const
	{
		for( auto slot : _Slots )
		{
			( *slot )( args... );
		}
	}

public:
	void connect( Slot<Args...> & val )
	{
		connect( &val );
	}

	void connect( Slot<Args...> * val )
	{
		auto it = std::find( _Slots.begin(), _Slots.end(), val );
		if( it == _Slots.end() )
		{
			val->_Signals.push_back( this );
			_Slots.push_back( val );
		}
	}

public:
	void disconnect( Slot<Args...> & val )
	{
		disconnect( &val );
	}

	void disconnect( Slot<Args...> * val )
	{
		auto it = std::find( _Slots.begin(), _Slots.end(), val );
		if( it != _Slots.end() )
		{
			_Slots.erase( it );

			val->disconnect( this );
		}
	}

private:
	XE::Array< Slot<Args...> * > _Slots;
};

template<typename ... Args> class Slot
{
public:
	friend class Signal<Args...>;

public:
	using CallbackType = std::function<void( Args... )>;

public:
	Slot( const CallbackType & val )
		:_Callback( val )
	{

	}

	~Slot()
	{
		for( auto singal : _Signals )
		{
			singal->disconnect( this );
		}
	}

public:
	void operator()( Args && ...args ) const
	{
		_Callback( args... );
	}

public:
	void disconnect( Signal<Args...> & val )
	{
		disconnect( &val );
	}

	void disconnect( Signal<Args...> * val )
	{
		auto it = std::find( _Signals.begin(), _Signals.end(), val );
		if( it != _Signals.end() )
		{
			_Signals.erase( it );

			val->disconnect( this );
		}
	}

private:
	CallbackType _Callback;
	XE::Array< Signal<Args...> * > _Signals;
};

END_XE_NAMESPACE

#endif // SIGNALSLOT_HPP__9F7422B2_7E73_46FB_A430_2863EF498E9E
