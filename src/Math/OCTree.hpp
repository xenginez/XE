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
	static constexpr XE::uint32 MaxDepthCount = 8;

public:
	using ValueType = typename _Ty;
	using BoundBoxType = typename _By;

public:
	struct Node
	{
		XE::AABB Box;
		XE::uint32 Depth = 0;
		XE::uint32 Children = 0;
		Array< ValueType > Objects;
	};

public:
	OCTree()
		:_Depth( 4 ), _Nodes( 1 )
	{
	}

	OCTree( XE::uint32 val )
		:_Depth( std::clamp( val, 1, MaxDepthCount ) ), _Nodes( 1 )
	{
		
	}

	~OCTree() = default;

public:
	XE::uint32 DepthCount() const
	{
		return _Depth;
	}

public:
	template< typename _Iter >
	void Rebuild( _Iter first, _Iter last )
	{
		_Nodes.clear();

		_Nodes.resize( 1 );

		std::for_each( first, last, [&]( const ValueType & val )
					   {
						   _Nodes[0].Objects.push_back( val );
						   _Nodes[0].Box.Merge( _BoundBox( val ) );
					   } );

		Build( 0, 0 );
	}

	void Clear()
	{
		_Nodes.clear();
		_Nodes.shrink_to_fit();
	}

public:
	template< typename _Other >
	ValueType Intersect( const _Other & val, const Array<ValueType> & exclude ) const
	{
		return Intersect( 0, exclude, val );
	}

public:
	template< typename _Other >
	Array<ValueType> Intersects( const _Other & val ) const
	{
		Set<ValueType> ret;

		Intersects( 0, ret, val );

		return { ret.begin(), ret.end() };
	}

private:
	void Build( XE::uint64 node, XE::uint32 depth )
	{
		if( _Nodes[node].Objects.size() > 1 )
		{
			_Nodes[node].Depth = depth;

			if( depth < _Depth )
			{
				Vec3f center = _Nodes[node].Box.GetCenter();

				XE::uint64 children = _Nodes.size();

				_Nodes[node].Children = static_cast< XE::uint32 >( children );

				_Nodes.resize( children + 8 );

				for( const auto & child : _Nodes[node].Objects )
				{
					XE::AABB aabb = _BoundBox( child );
					int mark[6];
					mark[0] = aabb.min.x >= center.x ? 1 : 0;
					mark[1] = aabb.min.y >= center.y ? 2 : 0;
					mark[2] = aabb.min.z >= center.z ? 4 : 0;
					mark[3] = aabb.max.x >= center.x ? 1 : 0;
					mark[4] = aabb.max.y >= center.y ? 2 : 0;
					mark[5] = aabb.max.z >= center.z ? 4 : 0;
					for( int i = 0; i < 8; ++i )
					{
						if( i == ( ( i & 1 ) ? mark[3] : mark[0] )
							+ ( ( i & 2 ) ? mark[4] : mark[1] )
							+ ( ( i & 4 ) ? mark[5] : mark[2] ) )
						{
							_Nodes[children + i].Objects.push_back( child );
						}
					}
				}

				for( int i = 0; i < 8; ++i )
				{
					_Nodes[children + i].Box = AABB(
						Vec3f(
							( i & 1 ) ? center.x : _Nodes[node].Box.min.x,
							( i & 2 ) ? center.y : _Nodes[node].Box.min.y,
							( i & 4 ) ? center.z : _Nodes[node].Box.min.z
						),
						Vec3f(
							( i & 1 ) ? _Nodes[node].Box.max.x : center.x,
							( i & 2 ) ? _Nodes[node].Box.max.y : center.y,
							( i & 4 ) ? _Nodes[node].Box.max.z : center.z
						)
					);

					Build( children + i, depth + 1 );
				}
			}
		}

		_Nodes[node].Objects.clear();
		_Nodes[node].Objects.shrink_to_fit();
	}

	template< typename _Other >
	ValueType Intersect( XE::uint64 node, const Array<ValueType> & exclude, const _Other & val ) const
	{
		const Node & n = _Nodes[node];

		if( n.Box.Intersect( val ) )
		{
			if( n.Children == 0 )
			{
				for( const auto & obj : n.Objects )
				{
					if( _BoundBox( obj ).Intersect( val ) )
					{
						for( const auto & ex : exclude )
						{
							if( ex == obj )
							{
								continue;
							}
						}

						return obj;
					}
				}
			}
			else
			{
				for( int i = 0; i < 8; ++i )
				{
					if( ValueType obj = Intersect( node + i, exclude, val ) )
					{
						for( const auto & ex : exclude )
						{
							if( ex == obj )
							{
								continue;
							}
						}

						return obj;
					}
				}
			}
		}

		return nullptr;
	}

	ValueType Intersect( XE::uint64 node, const Array<ValueType> & exclude, const Ray & val ) const
	{
		const Node & n = _Nodes[node];

		if( n.Box.Intersect( val ).first )
		{
			if( n.Children == 0 )
			{
				for( const auto & obj : n.Objects )
				{
					if( _BoundBox( obj ).Intersect( val ).first )
					{
						for( const auto & ex : exclude )
						{
							if( ex == obj )
							{
								continue;
							}
						}

						return obj;
					}
				}
			}
			else
			{
				for( int i = 0; i < 8; ++i )
				{
					if( ValueType obj = Intersect( node + i, exclude, val ) )
					{
						for( const auto & ex : exclude )
						{
							if( ex == obj )
							{
								continue;
							}
						}

						return obj;
					}
				}
			}
		}

		return nullptr;
	}

	template< typename _Other >
	void Intersects( XE::uint64 node, Set<ValueType> & out, const _Other & val ) const
	{
		const Node & n = _Nodes[node];

		if( n.Box.Intersect( val ) )
		{
			if( n.Children == 0 )
			{
				for( const auto & obj : n.Objects )
				{
					if( _BoundBox( obj ).Intersect( val ) )
					{
						out.insert( obj );
					}
				}
			}
			else
			{
				for( int i = 0; i < 8; ++i )
				{
					Intersects( node + i, out, val );
				}
			}
		}
	}

	void Intersects( XE::uint64 node, Set<ValueType> & out, const Ray & val ) const
	{
		const Node & n = _Nodes[node];

		if( n.Box.Intersect( val ).first )
		{
			if( n.Children == 0 )
			{
				for( const auto & obj : n.Objects )
				{
					if( _BoundBox( obj ).Intersect( val ).first )
					{
						out.insert( obj );
					}
				}
			}
			else
			{
				for( int i = 0; i < 8; ++i )
				{
					Intersects( node + i, out, val );
				}
			}
		}
	}

private:
	XE::uint32 _Depth;
	Array< Node > _Nodes;
	BoundBoxType _BoundBox;
};

END_XE_NAMESPACE

#endif // OCTREE_HPP__A57E4FF7_6104_48B7_A4FD_0114648F4E85
