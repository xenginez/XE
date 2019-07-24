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

class GRAPHICS_API RenderQueue
{
public:
	RenderQueue();

	~RenderQueue();

public:
	static XE::uint64 GenKey( const RenderablePtr & val );

public:
	template<typename _DC> _DC * CreateDrawCall()
	{
		XE::uint64 size = _DrawCalls.size();

		_DrawCalls.insert( _DrawCalls.end(), sizeof( _DC ), 0 );

		return new ( _DrawCalls.data() + size ) _DC();
	}

	template< typename _DC > void Submit( _DC * val )
	{
		SortKeyPair pair;

		pair.key = val->GetSortKey();
		pair.draw = ( XE::uint64 )val - ( XE::uint64 )_DrawCalls.data();

		if( pair.key.layer <= RenderGroup::BACKGROUND )
		{
			_Background.push( pair );
		}
		else if( pair.key.layer <= RenderGroup::GEOMETRY )
		{
			_Geometry.push( pair );
		}
		else if( pair.key.layer <= RenderGroup::ALPHATEST )
		{
			_Alphatest.push( pair );
		}
		else if( pair.key.layer <= RenderGroup::TRANSPARENT )
		{
			_Transparent.push( pair );
		}
		else if( pair.key.layer <= RenderGroup::OVERLAY )
		{
			_Overlay.push( pair );
		}
	}

private:
	Array<XE::uint8> _DrawCalls;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, BackgroundLess> _Background;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, GeometryLess> _Geometry;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, AlphatestLess> _Alphatest;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, TransparentLess> _Transparent;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, OverlayLess> _Overlay;
};

END_XE_NAMESPACE

#endif // RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
