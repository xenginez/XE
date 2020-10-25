/*!
 * \file	SkeletonTransform.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SKELETONTRANSFORM_H__DB43A5B7_F2FD_428B_9029_D9EA1DA6529B
#define SKELETONTRANSFORM_H__DB43A5B7_F2FD_428B_9029_D9EA1DA6529B

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SkeletonTransform
{
private:
	struct Private;

public:
	SkeletonTransform();

	~SkeletonTransform();

public:
	XE::SkeletonTransformHandle GetHandle() const;

public:
	const XE::Array< XE::Mat4 > & GetTransform() const;

	void SetTransform( const XE::Array< XE::Mat4 > & val );

private:
	Private * _p;
};
DECL_META_CLASS( XE_API, SkeletonTransform );

END_XE_NAMESPACE

#endif // SKELETONTRANSFORM_H__DB43A5B7_F2FD_428B_9029_D9EA1DA6529B
