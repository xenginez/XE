/*!
 * \file   Signals.hpp
 *
 * \author ZhengYuanQing
 * \date   2020/10/03
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef SIGNALS_H__C00834C6_81AA_46A8_B17F_1B2A6D85E3BC
#define SIGNALS_H__C00834C6_81AA_46A8_B17F_1B2A6D85E3BC

#include "Type.h"

BEG_XE_NAMESPACE

template< typename ... Args > class Slot;
template< typename ... Args > class Signal;
template< typename ... Args > class Connect;
template< typename ... Args > class Disconnect;

struct XE_API _ConnectNoRepeat
{
};
static constexpr _ConnectNoRepeat ConnectNoRepeat = {};

template< typename ... Args > class Signal : public XE::NonCopyable
{
public:
	friend class Connect<Args...>;
	friend class Disconnect<Args...>;

public:
	Signal() = default;

	virtual ~Signal()
	{
		while( !_Parents.empty() )
		{
			Disconnect<Args...>( _Parents.front(), this );
		}
	}

public:
	virtual void operator() ( Args && ...args ) const
	{
		for( auto emit : _Emits )
		{
			if( emit != nullptr )
				( *emit )( std::forward<Args>( args )... );
		}
	}

private:
	XE::Array< Signal<Args...> * > _Emits;
	XE::Array< Signal<Args...> * > _Parents;
};

template< typename ... Args > class Slot : public Signal< Args... >
{
public:
	using CallbackType = std::function< void( Args... ) >;

public:
	Slot()
	{

	}

	Slot( const CallbackType & val )
		:_Callback( val )
	{

	}

	~Slot() override = default;

public:
	Slot & operator = ( const CallbackType & val )
	{
		_Callback = val;

		return *this;
	}

public:
	void operator()( Args && ...args ) const override
	{
		if( _Callback != nullptr )
			_Callback( std::forward<Args>( args )... );

		Signal< Args... >::operator() ( std::forward<Args>( args )... );
	}

private:
	CallbackType _Callback;
};

template< typename ... Args > class Connect : public XE::NonCopyable
{
public:
	Connect() = delete;

	Connect( Signal<Args...> * left, Signal<Args...> * right )
	{
		if( left != nullptr && right != nullptr )
		{
			left->_Emits.push_back( right );
			right->_Parents.push_back( left );
		}
	}

	Connect( Signal<Args...> * left, Signal<Args...> * right, _ConnectNoRepeat )
	{
		if( left != nullptr && right != nullptr )
		{
			auto it1 = std::find( left->_Emits.begin(), left->_Emits.end(), right );
			if( it1 == left->_Emits.end() )
			{
				left->_Emits.push_back( right );
				right->_Parents.push_back( left );
			}
		}
	}

	~Connect() = default;
};

template< typename ... Args > class Disconnect : public XE::NonCopyable
{
public:
	Disconnect() = delete;

	Disconnect( Signal<Args...> * left )
	{
		if( left != nullptr )
		{
			while( !left->_Parents.empty() )
			{
				Disconnect<Args...>( _Parents.front(), left );
			}
		}
	}

	Disconnect( Signal<Args...> * left, Signal<Args...> * right )
	{
		if( left != nullptr && right != nullptr )
		{
			for( auto it = std::find( left->_Emits.begin(), left->_Emits.end(), right );
				it != left->_Emits.end();
				it = std::find( left->_Emits.begin(), left->_Emits.end(), right ) )
			{
				left->_Emits.erase( it );
			}

			for( auto it = std::find( right->_Parents.begin(), right->_Parents.end(), left );
				it != right->_Parents.end();
				it = std::find( right->_Parents.begin(), right->_Parents.end(), left ) )
			{
				right->_Parents.erase( it );
			}
		}
	}

	~Disconnect() = default;
};

END_XE_NAMESPACE

#endif // SIGNALS_H__C00834C6_81AA_46A8_B17F_1B2A6D85E3BC