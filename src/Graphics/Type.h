/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
#define __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848

#include "Global.h"

BEG_XE_NAMESPACE

class DrawCall;
class RenderQueue;


DECL_PTR( Mesh );
DECL_PTR( Camera );
DECL_PTR( Material );
DECL_PTR( Renderer );
DECL_PTR( RenderPass );
DECL_PTR( Renderable );


enum class ProjectType
{
	PERSPECTIVE,
	ORTHOGRAPHIC,
};
DECL_META_ENUM( GRAPHICS_API, ProjectType );

enum RenderGroup
{
	BACKGROUND = 10,
	GEOMETRY = 20,
	ALPHATEST = 30,
	TRANSPARENT = 40,
	OVERLAY = 50,
};
DECL_META_ENUM( GRAPHICS_API, RenderGroup );



union SortKey
{
	SortKey()
		:key( 0 )
	{
	}

	SortKey( XE::uint64 k )
		:key( k )
	{
	}

	XE::uint64 key;
	struct
	{
		XE::uint8 group : 6;
		XE::uint32 trans : 3;
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

	constexpr bool operator()( const SortKeyPair & _Left, const SortKeyPair & _Right ) const
	{
		return _Left.key.key < _Right.key.key;
	}
};
struct GeometryLess
{
	typedef SortKeyPair first_argument_type;
	typedef SortKeyPair second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const SortKeyPair & _Left, const SortKeyPair & _Right ) const
	{
		return _Left.key.key < _Right.key.key;
	}
};
struct AlphaTestLess
{
	typedef SortKeyPair first_argument_type;
	typedef SortKeyPair second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const SortKeyPair & _Left, const SortKeyPair & _Right ) const
	{
		return _Left.key.key < _Right.key.key;
	}
};
struct TransparentLess
{
	typedef SortKeyPair first_argument_type;
	typedef SortKeyPair second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const SortKeyPair & _Left, const SortKeyPair & _Right ) const
	{
		return _Left.key.key < _Right.key.key;
	}
};
struct OverlayLess
{
	typedef SortKeyPair first_argument_type;
	typedef SortKeyPair second_argument_type;
	typedef bool result_type;

	constexpr bool operator()( const SortKeyPair & _Left, const SortKeyPair & _Right ) const
	{
		return _Left.key.key < _Right.key.key;
	}
};

END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
