/*!
 * \file	PhysicsMaterial.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B
#define PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsMaterial : public XE::Object
{
	OBJECT( PhysicsMaterial, Object )

public:
	PhysicsMaterial();

	~PhysicsMaterial() override;

public:
	PhysicsMaterialFlag	GetFlag() const;

	void SetFlag( PhysicsMaterialFlag val );

	XE::float32 GetRestitution() const;

	void SetRestitution( XE::float32 val );

	XE::float32 GetStaticFriction() const;

	void SetStaticFriction( XE::float32 val );

	XE::float32 GetDynamicFriction() const;

	void SetDynamicFriction( XE::float32 val );

	CombineMode	GetFrictionCombineMode() const;

	void SetFrictionCombineMode( CombineMode val );

	CombineMode	GetRestitutionCombineMode() const;

	void SetRestitutionCombineMode( CombineMode val );

private:
	PhysicsMaterialFlag _Flag;
	XE::float32 _Restitution;
	XE::float32 _StaticFriction;
	XE::float32 _DynamicFriction;
	CombineMode _FrictionCombineMode;
	CombineMode _RestitutionCombineMode;
};

END_XE_NAMESPACE

#endif // PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B
