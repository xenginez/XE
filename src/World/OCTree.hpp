/*!
 * \file	OCTree.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/07/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef OCTREE_HPP__A57E4FF7_6104_48B7_A4FD_0114648F4E85
#define OCTREE_HPP__A57E4FF7_6104_48B7_A4FD_0114648F4E85

#include "Type.h"

BEG_XE_NAMESPACE

template< typename _Ty, typename _By = MakeAABB< _Ty > >
class OCTree : public NonCopyable
{
public:
	static constexpr XE::uint32 MaxDepthCount = 16;

public:
	using ValueType = typename _Ty;
	using BoundBoxType = typename _By;

public:
	struct Node
	{
		XE::AABB Box;
		Array< ValueType > _Objects;
	};

public:
	OCTree()
		:_Dirty( false ), _Depth( 8 )
	{
	}

	OCTree( XE::uint32 val )
		:_Dirty( false ), _Depth( std::min( val, MaxDepthCount ) )
	{
	}

	~OCTree() = default;

public:
	void Marker()
	{
		_Dirty = true;
	}

	XE::uint32 DepthCount() const
	{
		return _Depth;
	}

public:
	void Insert( const ValueType & val );

	template< typename _Iter >
	void Insert( _Iter first, _Iter last );

	void Erase( const ValueType & val );

	template< typename _Iter >
	void Erase( _Iter first, _Iter last );

public:
	void Update();

	void Clear();

private:
	bool _Dirty;
	XE::uint32 _Depth;
	Array< Node > _Nodes;
	BoundBoxType _BoundBox;
};

END_XE_NAMESPACE

#endif // OCTREE_HPP__A57E4FF7_6104_48B7_A4FD_0114648F4E85
