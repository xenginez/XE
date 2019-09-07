/*!
 * \file	PhysicMaterial.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICMATERIAL_H__B925EAD6_16F3_4057_8C93_EE1DD5C1AB2A
#define PHYSICMATERIAL_H__B925EAD6_16F3_4057_8C93_EE1DD5C1AB2A

#include "Type.h"

BEG_XE_NAMESPACE

class PHYSICS_API PhysicMaterial : public XE::Object
{
	OBJECT( PhysicMaterial, Object )

public:
	PhysicMaterial();

	~PhysicMaterial() override;
};

END_XE_NAMESPACE

#endif // PHYSICMATERIAL_H__B925EAD6_16F3_4057_8C93_EE1DD5C1AB2A
