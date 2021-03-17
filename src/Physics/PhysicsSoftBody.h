/*!
 * \file	PhysicsSoftBody.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSSOFTBODY_H__7B96C83F_630C_4299_95FB_AED0CD304F96
#define PHYSICSSOFTBODY_H__7B96C83F_630C_4299_95FB_AED0CD304F96

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsSoftBody : public XE::Object
{
	OBJECT( PhysicsSoftBody, Object )

public:
	PhysicsSoftBody();

	~PhysicsSoftBody();
};

END_XE_NAMESPACE

#endif // PHYSICSSOFTBODY_H__7B96C83F_630C_4299_95FB_AED0CD304F96
