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
	union SortKey
	{
		XE::uint64 key;
		struct 
		{
			XE::uint8 layer;
			XE::uint32 transform;
			XE::uint8 draw : 1;
			XE::uint32 depth : 24;
			XE::uint32 shader : 30;
		};
	};
	struct SortKeyPair
	{
		SortKey key;
		XE::uint64 draw;
	};
	struct BackgroundLess
	{
		typedef SortKeyPair first_argument_type;
		typedef SortKeyPair second_argument_type;
		typedef bool result_type;

		constexpr bool operator()( const SortKeyPair& _Left, const SortKeyPair& _Right ) const
		{
			return _Left.key.key < _Right.key.key;
		}
	};
	struct GeometryLess
	{
		typedef SortKeyPair first_argument_type;
		typedef SortKeyPair second_argument_type;
		typedef bool result_type;

		constexpr bool operator()( const SortKeyPair& _Left, const SortKeyPair& _Right ) const
		{
			return _Left.key.key < _Right.key.key;
		}
	};
	struct AlphatestLess
	{
		typedef SortKeyPair first_argument_type;
		typedef SortKeyPair second_argument_type;
		typedef bool result_type;

		constexpr bool operator()( const SortKeyPair& _Left, const SortKeyPair& _Right ) const
		{
			return _Left.key.key < _Right.key.key;
		}
	};
	struct TransparentLess
	{
		typedef SortKeyPair first_argument_type;
		typedef SortKeyPair second_argument_type;
		typedef bool result_type;

		constexpr bool operator()( const SortKeyPair& _Left, const SortKeyPair& _Right ) const
		{
			return _Left.key.key < _Right.key.key;
		}
	};
	struct OverlayLess
	{
		typedef SortKeyPair first_argument_type;
		typedef SortKeyPair second_argument_type;
		typedef bool result_type;

		constexpr bool operator()( const SortKeyPair& _Left, const SortKeyPair& _Right ) const
		{
			return _Left.key.key < _Right.key.key;
		}
	};

public:
	RenderQueue();

	~RenderQueue();

public:
	static XE::uint64 GenKey( const RenderablePtr & val );

public:
	template<typename _DC> _DC * CreateDrawCall( XE::uint64 key )
	{
		return new ( CreateDrawCall( key, sizeof( _DC ) ) ) _DC();
	}

	template< typename _DC > bool Submit( _DC * val )
	{
		return false;
	}

private:
	XE::uint8 * CreateDrawCall( XE::uint64 key, XE::uint64 size );

private:
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, BackgroundLess> _Background;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, GeometryLess> _Geometry;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, AlphatestLess> _Alphatest;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, TransparentLess> _Transparent;
	std::priority_queue<SortKeyPair, Array<SortKeyPair>, OverlayLess> _Overlay;
	Array<XE::uint8> _DrawCalls;
};

END_XE_NAMESPACE

#endif // RENDERQUEUE_H__1FF515AA_CF8D_4E52_B3AE_808595564BBD
