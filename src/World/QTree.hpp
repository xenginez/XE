/*!
 * \file	QTree.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/07/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef QTREE_HPP__29CC31D8_FEF9_4084_8E7E_531966B9692A
#define QTREE_HPP__29CC31D8_FEF9_4084_8E7E_531966B9692A

#include "Type.h"

BEG_XE_NAMESPACE

template< typename _Ty, typename _By = MakeAABB< _Ty > >
class QTree : public NonCopyable
{
public:
	static constexpr XE::uint32 MaxDepthCount = 16;

public:
	using ValueType = typename _Ty;
	using BoundBoxType = typename _By;

public:
	struct Node
	{
		XE::Rect Rect;
		Array< ValueType > _Objects;
	};

public:
	QTree();

	QTree( XE::uint32 val );

	~QTree();

private:
	bool _Dirty;
	XE::uint32 _Depth;
	Array< Node > _Nodes;
	BoundBoxType _BoundBox;
};

END_XE_NAMESPACE

#endif // QTREE_HPP__29CC31D8_FEF9_4084_8E7E_531966B9692A
