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

	~IPhysicsContext() override;

public:
	virtual void Startup() = 0;

	virtual void FixedUpdate() = 0;

	virtual void Clearup() = 0;

public:
	virtual PhysicsContextType GetType() const = 0;

public:
	virtual ShapeHandle CreateBoxShape( RigidBodyHandle rigidbody, const AABB & aabb ) = 0;

	virtual ShapeHandle CreatePlaneShape( RigidBodyHandle rigidbody, const Plane & plane ) = 0;

	virtual ShapeHandle CreateSphereShape( RigidBodyHandle rigidbody, const Sphere & sphere ) = 0;

	virtual ShapeHandle CreateCapsuleShape( RigidBodyHandle rigidbody, const Capsule & capsule ) = 0;

	virtual ShapeHandle CreateConvexMeshShape( RigidBodyHandle rigidbody, XE::basic_memory_view< Vec3 > vertex, XE::basic_memory_view< uint32 > index, real scale ) = 0;

	virtual ShapeHandle CreateHeightFieldShape( RigidBodyHandle rigidbody, XE::basic_memory_view< real > height, real scale, uint32 row, uint32 col ) = 0;

	virtual void Destory( ShapeHandle handle ) = 0;

	virtual JointHandle CreateJoint() = 0;

	virtual void Destory( JointHandle handle ) = 0;

	virtual RigidBodyHandle CreateRigidBody( RigidBodyType type, const String & name, const Mat4 & pose ) = 0;

	virtual void Destory( RigidBodyHandle handle ) = 0;

	virtual ConstraintHandle CreateConstraint( RigidBodyHandle rigidbody0, RigidBodyHandle rigidbody1 ) = 0;

	virtual void Destory( ConstraintHandle handle ) = 0;

	// Scene
public:
	virtual void SetGravity( const Vec3 & gravity ) = 0;

	virtual void SetCCDMaxPasses( uint32 passes ) = 0;

	virtual void SetBounceThresholdVelocity( real threshold ) = 0;

	virtual void SetClothInterCollisionDistance( real distance ) = 0;

	virtual void SetClothInterCollisionStiffness( real stiffness ) = 0;

	virtual void SetClothInterCollisionNbIterations( uint32 iteration ) = 0;

	virtual void Raycast( const Ray & ray, const real distance, uint64 layer ) const = 0;

	// Shape
public:
	virtual void SetRestitution( ShapeHandle shape, real restitution ) = 0;

	virtual void SetStaticFriction( ShapeHandle shape, real friction ) = 0;

	virtual void SetDynamicFriction( ShapeHandle shape, real friction ) = 0;

	virtual void SetContactOffset( ShapeHandle shape, real offset ) = 0;

	virtual void SetRestOffset( ShapeHandle shape, real offset ) = 0;

	// RigidBody
public:
	virtual void AttachShape( RigidBodyHandle rigidbody, ShapeHandle shape ) = 0;

	virtual void AttachShape( RigidBodyHandle rigidbody, XE::basic_memory_view< ShapeHandle > shape ) = 0;

	virtual void SetCMassLocalPose( RigidBodyHandle rigidbody, const Mat4 & pose ) = 0;

	virtual void SetMass( RigidBodyHandle rigidbody, real mass ) = 0;

	virtual void SetMassSpaceInertiaTensor( RigidBodyHandle rigidbody, const Vec3 & mass ) = 0;

	virtual void SetLinearVelocity( RigidBodyHandle rigidbody, const Vec3 & velocity ) = 0;

	virtual void SetAngularVelocity( RigidBodyHandle rigidbody, const Vec3 & velocity ) = 0;

	virtual void AddForce( RigidBodyHandle rigidbody, const Vec3 & force ) = 0;

	virtual void AddTorque( RigidBodyHandle rigidbody, const Vec3 & torque ) = 0;

	virtual void ClearForce( RigidBodyHandle rigidbody, const Vec3 & force ) = 0;

	virtual void ClearTorque( RigidBodyHandle rigidbody, const Vec3 & torque ) = 0;

	virtual void SetMinCCDAdvanceCoefficient( RigidBodyHandle rigidbody, real advanceCoefficient ) = 0;

	virtual void SetMaxDepenetrationVelocity( RigidBodyHandle rigidbody, real biasClamp ) = 0;

	virtual void SetMaxContactImpulse( RigidBodyHandle rigidbody, real maxImpulse ) = 0;

	virtual void SetKinematicTarget( RigidBodyHandle rigidbody, const Mat4 & pose ) = 0;

	virtual void SetLinearDamping( RigidBodyHandle rigidbody, real damping ) = 0;

	virtual void SetAngularDamping( RigidBodyHandle rigidbody, real damping ) = 0;

	virtual void SetMaxAngularVelocity( RigidBodyHandle rigidbody, real  velocity ) = 0;

	virtual void SetSleepThreshold( RigidBodyHandle rigidbody, real  threshold ) = 0;

	virtual void SetStabilizationThreshold( RigidBodyHandle rigidbody, real  threshold ) = 0;

	virtual void SetSolverIterationCounts( RigidBodyHandle rigidbody, uint32 count ) = 0;

	virtual void SetContactReportThreshold( RigidBodyHandle rigidbody, real threshold ) = 0;

	virtual void WeakUp( RigidBodyHandle rigidbody ) = 0;

	virtual void Sleeping( RigidBodyHandle rigidbody ) = 0;

};

END_XE_NAMESPACE

#endif // IPHYSICSCONTEXT_H__B800F332_C8D1_4D9F_8BBC_FA54C5E5AF91
