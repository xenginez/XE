/*!
 * \file	DrawCall.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/23
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120
#define DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API DrawCall : public XE::NonCopyable
{
public:
	DrawCall();

	virtual ~DrawCall();

public:
	void operator()( CommandListPtr& val )
	{
		_Callback( std::ref( val ) );
	}

protected:
	std::function<void( CommandListPtr& )> _Callback;
};

template< typename ... _DC >class DrawCallPacket : public DrawCall
{
public:
	DrawCallPacket()
	{
		_Callback = std::bind( &DrawCallPacket<_DC...>::operator(), this, std::placeholders::_1 );
	}

	~DrawCallPacket() override = default;

public:
	void operator()( CommandListPtr& val )
	{
		for_each_in_tuple( _DrawCalls, [val]( const auto& x )
			{
				x( val );
			} );
	}

private:
	template<class F, class...Ts, std::size_t...Is>
	void for_each_in_tuple( const std::tuple<Ts...>& tuple, F func, std::index_sequence<Is...> )
	{
		using expander = int[];
		( void ) expander 
		{
			0, ( ( void ) func( std::get<Is>( tuple ) ), 0 )...
		};
	}

	template<class F, class...Ts>
	void for_each_in_tuple( const std::tuple<Ts...>& tuple, F func )
	{
		for_each_in_tuple( tuple, func, std::make_index_sequence<sizeof...( Ts )>() );
	}

private:
	std::tuple<_DC...> _DrawCalls;
};

END_XE_NAMESPACE

#endif // DRAWCALL_H__6689FA03_2D4B_4E73_98E6_984256426120
