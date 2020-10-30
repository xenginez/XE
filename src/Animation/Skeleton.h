/*!
 * \file	Skeleton.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKELETON_H__D1380C62_7342_419B_BF6B_BD973C25445B
#define SKELETON_H__D1380C62_7342_419B_BF6B_BD973C25445B

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Skeleton : public XE::Object
{
	OBJECT( Skeleton, Object )

public:
	Skeleton();

	~Skeleton() override;

public:
	XE::SkeletonHandle GetHandle() const;

private:
	XE::SkeletonHandle _Handle;
};

END_XE_NAMESPACE

#endif // SKELETON_H__D1380C62_7342_419B_BF6B_BD973C25445B