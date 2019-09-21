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

class XE_API IPhysicsContext : public NonCopyable
{
public:
	IPhysicsContext();

	virtual ~IPhysicsContext();

public:
	virtual void Startup() = 0;

	virtual void FixedUpdate() = 0;

	virtual void Clearup() = 0;

public:
	virtual PhysicsContextType GetType() const = 0;

public:
	virtual ShapeHandle CreateBoxShape( RigidBodyHandle rigidbody, const XE::AABB & aabb ) = 0;

	virtual ShapeHandle CreatePlaneShape( RigidBodyHandle rigidbody, const XE::Plane & plane ) = 0;

	virtual ShapeHandle CreateSphereShape( RigidBodyHandle rigidbody, const XE::Sphere & sphere ) = 0;

	virtual ShapeHandle CreateCapsuleShape( RigidBodyHandle rigidbody, const XE::Capsule & capsule ) = 0;

	virtual ShapeHandle CreateConvexMeshShape( RigidBodyHandle rigidbody, XE::basic_memory_view< Vec3 > vertex, XE::basic_memory_view< uint32 > index, XE::real scale ) = 0;

	virtual ShapeHandle CreateHeightFieldShape( RigidBodyHandle rigidbody, XE::basic_memory_view < XE::float32 > height, XE::real scale, XE::uint32 row, XE::uint32 col ) = 0;

	virtual void Destory( ShapeHandle handle ) = 0;

	virtual JointHandle CreateJoint() = 0;

	virtual void Destory( JointHandle handle ) = 0;

	virtual SoftBodyHandle CreateSoftBody(
		const XE::String & name,
		XE::real air_density,
		XE::real water_density,
		XE::real water_offset,
		XE::real maxDisplacement,
		const XE::Vec3 & water_normal,
		const XE::Vec3 & gravity,
		const XE::Vec3 & from,
		const XE::Vec3 & to,
		int res,
		int fixeds ) = 0;

	virtual SoftBodyHandle CreateSoftBody(
		const XE::String & name,
		XE::real air_density,
		XE::real water_density,
		XE::real water_offset,
		XE::real maxDisplacement,
		const XE::Vec3 & water_normal,
		const XE::Vec3 & gravity,
		const XE::Vec3 & corner00,
		const XE::Vec3 & corner10,
		const XE::Vec3 & corner01,
		const XE::Vec3 & corner11,
		int resx,
		int resy,
		int fixeds,
		bool gendiags,
		XE::real perturbation ) = 0;

	virtual SoftBodyHandle CreateSoftBody(
		const XE::String & name,
		XE::real air_density,
		XE::real water_density,
		XE::real water_offset,
		XE::real maxDisplacement,
		const XE::Vec3 & water_normal,
		const XE::Vec3 & gravity,
		const XE::Vec3 & center,
		const XE::Vec3 & radius,
		int res ) = 0;

	virtual SoftBodyHandle CreateSoftBody(
		const XE::String & name,
		XE::real air_density,
		XE::real water_density,
		XE::real water_offset,
		XE::real maxDisplacement,
		const XE::Vec3 & water_normal,
		const XE::Vec3 & gravity,
		XE::basic_memory_view<XE::Vec3> vertices,
		bool randomizeConstraints ) = 0;

	virtual void Destory( SoftBodyHandle handle ) = 0;

	virtual RigidBodyHandle CreateRigidBody( const XE::String & name ) = 0;

	virtual void Destory( RigidBodyHandle handle ) = 0;

	virtual ConstraintHandle CreateConstraint( RigidBodyHandle rigidbody0, RigidBodyHandle rigidbody1 ) = 0;

	virtual void Destory( ConstraintHandle handle ) = 0;

public:
	// Scene
	virtual void addSoftBody( SoftBodyHandle handle ) = 0;

	virtual void removeSoftBody( SoftBodyHandle handle ) = 0;

	virtual void addRigidBody( RigidBodyHandle handle ) = 0;

	virtual void removeRigidBody( RigidBodyHandle handle ) = 0;

	virtual void addConstraint( ConstraintHandle handle ) = 0;

	virtual void removeConstraint( ConstraintHandle handle ) = 0;

	virtual bool rayCast( RayHitResult & result ) const = 0;
											 
	virtual bool rayCast( BoxHitResult & result ) const = 0;

	virtual bool rayCast( PointHitResult & result ) const = 0;

	virtual bool rayCast( SphereHitResult & result ) const = 0;

	virtual void clearForces() = 0;

	virtual void setGravity( const XE::Vec3 & gravity ) = 0;

public:
	// RigidBody
	virtual void activate( RigidBodyHandle handle, bool forceActivation ) = 0;

	virtual void addShape( RigidBodyHandle handle, ShapeHandle shape ) = 0;

	virtual void setLinearFactor( RigidBodyHandle handle, const XE::Vec3 & factor ) = 0;

	virtual void setAngularFactor( RigidBodyHandle handle, const XE::Vec3 & factor ) = 0;

	virtual void setRestitution( RigidBodyHandle handle, XE::real restitution ) = 0;

	virtual void setFriction( RigidBodyHandle handle, XE::real friction ) = 0;

	virtual void setRollingFriction( RigidBodyHandle handle, XE::real friction ) = 0;

	virtual void setSpinningFriction( RigidBodyHandle handle, XE::real friction ) = 0;

	virtual void setLinearVelocity( RigidBodyHandle handle, const XE::Vec3 & velocity ) = 0;

	virtual void setAngularVelocity( RigidBodyHandle handle, const XE::Vec3 & velocity ) = 0;

	virtual void setLinearDamping( RigidBodyHandle handle, XE::real damping ) = 0;

	virtual void setAngularDamping( RigidBodyHandle handle, XE::real damping ) = 0;

	virtual void setLinearSleepingThreshold( RigidBodyHandle handle, XE::real damping ) = 0;

	virtual void setAngularSleepingThreshold( RigidBodyHandle handle, XE::real damping ) = 0;

	virtual void setMass( RigidBodyHandle handle, XE::real mass, const XE::Vec3 & inertia ) = 0;

	virtual void setCenterOfMass( RigidBodyHandle handle, const XE::Vec3 & center ) = 0;

	virtual void applyTorque( RigidBodyHandle handle, const XE::Vec3 & torque ) = 0;

	virtual void applyCentralForce( RigidBodyHandle handle, const XE::Vec3 & force ) = 0;

	virtual void applyCentralImpulse( RigidBodyHandle handle, const XE::Vec3 & impulse ) = 0;

	virtual void applyTorqueImpulse( RigidBodyHandle handle, const XE::Vec3 & impulse ) = 0;

	virtual void applyForce( RigidBodyHandle handle, const XE::Vec3 & force, const XE::Vec3 & rel_pos ) = 0;

	virtual void applyImpulse( RigidBodyHandle handle, const XE::Vec3 & impulse, const XE::Vec3 & rel_pos ) = 0;

public:
	// SoftBody
	virtual void activate( SoftBodyHandle handle, bool forceActivation ) = 0;

	virtual void addShape( SoftBodyHandle handle, ShapeHandle shape ) = 0;

	virtual void setLinearFactor( SoftBodyHandle handle, const XE::Vec3 & factor ) = 0;

	virtual void setAngularFactor( SoftBodyHandle handle, const XE::Vec3 & factor ) = 0;

	virtual void setRestitution( SoftBodyHandle handle, XE::real restitution ) = 0;

	virtual void setFriction( SoftBodyHandle handle, XE::real friction ) = 0;

	virtual void setRollingFriction( SoftBodyHandle handle, XE::real friction ) = 0;

	virtual void setSpinningFriction( SoftBodyHandle handle, XE::real friction ) = 0;

	virtual void setLinearVelocity( SoftBodyHandle handle, const XE::Vec3 & velocity ) = 0;

	virtual void setAngularVelocity( SoftBodyHandle handle, const XE::Vec3 & velocity ) = 0;

	virtual void setDampingCoefficient( SoftBodyHandle handle, XE::real damping ) = 0;
	
	virtual void addForce( const XE::Vec3 & force ) = 0;

	virtual void addForce( const XE::Vec3 & force, XE::uint32 node ) = 0;

	virtual void addAeroForceToNode( const XE::Vec3 & force, XE::uint32 node ) = 0;

	virtual void addAeroForceToFace( const XE::Vec3 & force, XE::uint32 face ) = 0;

	virtual void addVelocity( const XE::Vec3 & velocity ) = 0;

	virtual void setVelocity( const XE::Vec3 & velocity ) = 0;

	virtual void addVelocity( const XE::Vec3 & velocity, XE::uint32 node ) = 0;

	virtual void setMass( XE::uint32 node, XE::real mass ) = 0;

	virtual void setTotalMass( XE::real mass, bool fromfaces = false ) = 0;
	
	virtual void setTotalDensity( XE::real density ) = 0;

	virtual void setVolumeMass( XE::real mass ) = 0;

	virtual void setVolumeDensity( XE::real density ) = 0;

	virtual void setRestLengthScale( XE::real restLength ) = 0;







// 
// 	// Scene
// public:
// 	virtual void SetGravity( const XE::Vec3 & gravity ) = 0;
// 
// 	virtual void SetCCDMaxPasses( XE::uint32 passes ) = 0;
// 
// 	virtual void SetBounceThresholdVelocity( XE::real threshold ) = 0;
// 
// 	virtual void SetClothInterCollisionDistance( XE::real distance ) = 0;
// 
// 	virtual void SetClothInterCollisionStiffness( XE::real stiffness ) = 0;
// 
// 	virtual void SetClothInterCollisionNbIterations( XE::uint32 iteration ) = 0;
// 
// 	virtual void Raycast( const XE::Ray & ray, const XE::real distance, XE::uint64 layer ) const = 0;
// 
// 	// Shape
// public:
// 	virtual void SetRestitution( ShapeHandle shape, XE::real restitution ) = 0;
// 
// 	virtual void SetvirtualFriction( ShapeHandle shape, XE::real friction ) = 0;
// 
// 	virtual void SetDynamicFriction( ShapeHandle shape, XE::real friction ) = 0;
// 
// 	virtual void SetContactOffset( ShapeHandle shape, XE::real offset ) = 0;
// 
// 	virtual void SetRestOffset( ShapeHandle shape, XE::real offset ) = 0;
// 
// 	// RigidBody
// public:
// 	virtual void AttachShape( RigidBodyHandle rigidbody, ShapeHandle shape ) = 0;
// 
// 	virtual void AttachShape( RigidBodyHandle rigidbody, XE::basic_memory_view< ShapeHandle > shape ) = 0;
// 
// 	virtual void SetCMassLocalPose( RigidBodyHandle rigidbody, const XE::Mat4 & pose ) = 0;
// 
// 	virtual void SetMass( RigidBodyHandle rigidbody, XE::real mass ) = 0;
// 
// 	virtual void SetMassSpaceInertiaTensor( RigidBodyHandle rigidbody, const XE::Vec3 & mass ) = 0;
// 
// 	virtual void SetLinearVelocity( RigidBodyHandle rigidbody, const XE::Vec3 & velocity ) = 0;
// 
// 	virtual void SetAngularVelocity( RigidBodyHandle rigidbody, const XE::Vec3 & velocity ) = 0;
// 
// 	virtual void AddForce( RigidBodyHandle rigidbody, const XE::Vec3 & force ) = 0;
// 
// 	virtual void AddTorque( RigidBodyHandle rigidbody, const XE::Vec3 & torque ) = 0;
// 
// 	virtual void ClearForce( RigidBodyHandle rigidbody, const XE::Vec3 & force ) = 0;
// 
// 	virtual void ClearTorque( RigidBodyHandle rigidbody, const XE::Vec3 & torque ) = 0;
// 
// 	virtual void SetMinCCDAdvanceCoefficient( RigidBodyHandle rigidbody, XE::real advanceCoefficient ) = 0;
// 
// 	virtual void SetMaxDepenetrationVelocity( RigidBodyHandle rigidbody, XE::real biasClamp ) = 0;
// 
// 	virtual void SetMaxContactImpulse( RigidBodyHandle rigidbody, XE::real maxImpulse ) = 0;
// 
// 	virtual void SetKinematicTarget( RigidBodyHandle rigidbody, const XE::Mat4 & pose ) = 0;
// 
// 	virtual void SetLinearDamping( RigidBodyHandle rigidbody, XE::real damping ) = 0;
// 
// 	virtual void SetAngularDamping( RigidBodyHandle rigidbody, XE::real damping ) = 0;
// 
// 	virtual void SetMaxAngularVelocity( RigidBodyHandle rigidbody, XE::real velocity ) = 0;
// 
// 	virtual void SetSleepThreshold( RigidBodyHandle rigidbody, XE::real threshold ) = 0;
// 
// 	virtual void SetStabilizationThreshold( RigidBodyHandle rigidbody, XE::real threshold ) = 0;
// 
// 	virtual void SetSolverIterationCounts( RigidBodyHandle rigidbody, XE::uint32 count ) = 0;
// 
// 	virtual void SetContactReportThreshold( RigidBodyHandle rigidbody, XE::real threshold ) = 0;
// 
// 	virtual void WeakUp( RigidBodyHandle rigidbody ) = 0;
// 
// 	virtual void Sleeping( RigidBodyHandle rigidbody ) = 0;

};

END_XE_NAMESPACE

#endif // IPHYSICSCONTEXT_H__B800F332_C8D1_4D9F_8BBC_FA54C5E5AF91
