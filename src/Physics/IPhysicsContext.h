/*!
 * \file	IPhysicsContext.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IPHYSICSCONTEXT_H__8E46D505_31B4_4FA8_ADAF_B307EDE3F8DF
#define IPHYSICSCONTEXT_H__8E46D505_31B4_4FA8_ADAF_B307EDE3F8DF

#include "Type.h"

BEG_XE_NAMESPACE

class PHYSICS_API IPhysicsContext : public XE::Object, public NonCopyable
{
	OBJECT( IPhysicsContext, Object )

};

END_XE_NAMESPACE

#endif // IPHYSICSCONTEXT_H__8E46D505_31B4_4FA8_ADAF_B307EDE3F8DF
