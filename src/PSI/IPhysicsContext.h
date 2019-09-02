/*!
 * \file	IPhysicsContext.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IPHYSICSCONTEXT_H__B800F332_C8D1_4D9F_8BBC_FA54C5E5AF91
#define IPHYSICSCONTEXT_H__B800F332_C8D1_4D9F_8BBC_FA54C5E5AF91

#include "Type.h"

BEG_XE_NAMESPACE

class PSI_API IPhysicsContext : public XE::Object, public NonCopyable
{
	OBJECT( IPhysicsContext, Object )

public:
	IPhysicsContext();

	virtual ~IPhysicsContext();

public:
	virtual void Startup() = 0;

	virtual void Present() = 0;

	virtual void Clearup() = 0;

};

END_XE_NAMESPACE

#endif // IPHYSICSCONTEXT_H__B800F332_C8D1_4D9F_8BBC_FA54C5E5AF91
