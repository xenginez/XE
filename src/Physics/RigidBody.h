/*!
 * \file	RigidBody.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
#define RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RigidBody : public XE::Object
{
	OBJECT( RigidBody, Object )

public:
	RigidBody();

	~RigidBody() override;

public:
	void Startup();

	void Update();

	void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnUpdate() = 0;

	virtual void OnClearup() = 0;

public:
	const XE::Mat4 & GetWorldTransform() const;

	void SetWorldTransform( const XE::Mat4 & val );

	const XE::Vec3 & GetCenterMass() const;

	void SetCenterMass( const XE::Vec3 & val );

	XE::float32 GetMass() const;

	void SetMass( XE::float32 val );

	const XE::Vec3 & GetMassSpaceInertiaTensor() const;

	void SetMassSpaceInertiaTensor( const XE::Vec3 & val );

	XE::float32 GetLinearDamping() const;

	void SetLinearDamping( XE::float32 val );

	XE::float32 GetAngularDamping() const;

	void SetAngularDamping( XE::float32 val );

	const XE::Vec3 & GetLinearVelocity() const;

	void SetLinearVelocity( const XE::Vec3 & val );

	const XE::Vec3 & GetAngularVelocity() const;

	void SetAngularVelocity( const XE::Vec3 & val );

	XE::float32 GetMaxLinearVelocity() const;

	void SetMaxLinearVelocity( XE::float32 val );

	XE::float32 GetMaxAngularVelocity() const;

	void SetMaxAngularVelocity( XE::float32 val );

public:
	void AddForce( const XE::Vec3 & force );

	void AddTorque( const XE::Vec3 & torque );

public:
	RigidBodyHandle GetHandle() const;

	void SetHandle( RigidBodyHandle val );

public:
	const Array<ShapePtr> & GetShapes() const;

	void SetShapes( const Array<ShapePtr> & val );

	const Array<ConstraintPtr> & GetConstraints() const;

	void SetConstraints( const Array<ConstraintPtr> & val );

private:
	XE::Mat4 _Transform;
	RigidBodyHandle _Handle;
	Array<ShapePtr> _Shapes;
	Array<ConstraintPtr> _Constraints;

	XE::float32 _Mass;
	XE::Vec3 _CenterMass;
	XE::Vec3 _LinearVelocity;
	XE::Vec3 _AngularVelocity;
	XE::float32 _LinearDamping;
	XE::float32 _AngularDamping;
	XE::float32 _MaxLinearVelocity;
	XE::float32 _MaxAngularVelocity;
	XE::Vec3 _MassSpaceInertiaTensor;

	XE::Vec3 _AddForce;
	XE::Vec3 _AddTorque;
};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
