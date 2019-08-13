/*!
 * \file	RenderQueue.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
#define RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD

#include "SortKey.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderQueue : public std::enable_shared_from_this< RenderQueue > , public NonCopyable
{
public:
	using DrawCallPair = Pair<SortKey, XE::uint64>;

public:
	RenderQueue();

	virtual ~RenderQueue();

public:
	template<typename _DC, typename ... _Args> _DC * Generate( _Args && ...val )
	{
		static_assert( std::is_base_of_v<DrawCall, _DC>, "must inherit from XE::DrawCall !" );

		XE::uint64 size = _DrawCalls.size();

		_DrawCalls.insert( _DrawCalls.end(), sizeof( _DC ), 0 );

		return new ( _DrawCalls.data() + size ) _DC( val... );
	}

	template< typename _DC > void Submit( _DC * val )
	{
		static_assert( std::is_base_of_v<DrawCall, _DC>, "must inherit from XE::DrawCall !" );

		XE_ASSERT( val >= _DrawCalls.data() && ( val < _DrawCalls.data() + _DrawCalls.size() ) && "" );

		DrawCallPair pair;

		pair.first = MakeSortKey( val );
		pair.second = ( XE::uint64 )val - ( XE::uint64 )_DrawCalls.data();

		_Queue.push( std::move( pair ) );
	}

public:
	void Flush( CommandListPtr & val );

private:
	Array<XE::uint8> _DrawCalls;
	std::priority_queue<DrawCallPair, Array<DrawCallPair>> _Queue;
};

END_XE_NAMESPACE

#endif // RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
