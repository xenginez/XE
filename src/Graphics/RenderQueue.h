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

#include "DrawCall.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderQueue : public std::enable_shared_from_this< RenderQueue > , public NonCopyable
{
public:
	RenderQueue();

	virtual ~RenderQueue();

public:
	template<typename _DC> _DC * AddDrawCall()
	{
		static_assert( std::is_base_of_v<DrawCall, _DC>, "" );

		XE::uint64 size = _DrawCalls.size();

		_DrawCalls.insert( _DrawCalls.end(), sizeof( _DC ), 0 );

		DrawCall * p = new ( _DrawCalls.data() + size ) _DC();

		p->_Queue = this;

		return static_cast< _DC * >( p );
	}

	template< typename _DC > void Submit( _DC * val )
	{
		static_assert( std::is_base_of_v<DrawCall, _DC>, "" );

		SortKeyPair pair;

		pair.key = val->GetSortKey();
		pair.draw = ( XE::uint64 )val - ( XE::uint64 )_DrawCalls.data();

		if( pair.key.group <= RenderGroup::BACKGROUND )
		{
			_Background.push( pair );
		}
		else if( pair.key.group <= RenderGroup::GEOMETRY )
		{
			_Geometry.push( pair );
		}
		else if( pair.key.group <= RenderGroup::ALPHATEST )
		{
			_AlphaTest.push( pair );
		}
		else if( pair.key.group <= RenderGroup::TRANSPARENT )
		{
			_Transparent.push( pair );
		}
		else if( pair.key.group <= RenderGroup::OVERLAY )
		{
			_Overlay.push( pair );
		}
	}

public:
	void Flush( CommandListPtr & val );

private:
	Array<XE::uint8> _DrawCalls;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, BackgroundLess> _Background;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, GeometryLess> _Geometry;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, AlphaTestLess> _AlphaTest;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, TransparentLess> _Transparent;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, OverlayLess> _Overlay;
};

END_XE_NAMESPACE

#endif // RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
