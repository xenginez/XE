/*!
 * \file	Shape.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
#define SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020

#include "Math/Math.h"
#include "Utils/Layer.h"
#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsShape : public XE::Object
{
	OBJECT( PhysicsShape, Object )

public:
	PhysicsShape();

	~PhysicsShape() override;

public:
	XE::PhysicsShapeHandle GetHandle() const;

	void SetHandle( XE::PhysicsShapeHandle val );

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Mat4x4f & GetLocalTransform() const;

	void SetLocalTransform( const XE::Mat4x4f & val );

	XE::PhysicsShapeFlags GetShapeFlags() const;

	void SetShapeFlags( XE::PhysicsShapeFlags val );

	XE::float32 GetRestOffset() const;

	void SetRestOffset( XE::float32 val );

	XE::float32 GetContactOffset() const;

	void SetContactOffset( XE::float32 val );

	XE::Layer GetQueryFilter() const;

	void SetQueryFilter( const XE::Layer & val );

	XE::Layer GetSimulationFilter() const;

	void SetSimulationFilter( const XE::Layer & val );

	XE::float32 GetTorsionalPatchRadius() const;

	void SetTorsionalPatchRadius( XE::float32 val );

	XE::float32 GetMinTorsionalPatchRadius() const;

	void SetMinTorsionalPatchRadius( XE::float32 val );

	const XE::Array<XE::PhysicsMaterialHandle> & GetPhysicsMaterials() const;

	void SetPhysicsMaterials( const XE::Array<XE::PhysicsMaterialHandle> & val );

private:
	XE::String _Name;
	XE::Mat4x4f _LocalTransform;
	XE::PhysicsShapeFlags _ShapeFlags;
	XE::float32 _RestOffset;
	XE::float32 _ContactOffset;
	XE::Layer _QueryFilter;
	XE::Layer _SimulationFilter;
	XE::float32 _TorsionalPatchRadius;
	XE::float32 _MinTorsionalPatchRadius;
	XE::Array<XE::PhysicsMaterialHandle> _PhysicsMaterials;

	XE::PhysicsShapeHandle _Handle;
};

class XE_API PhysicsBoxShape : public PhysicsShape
{
	OBJECT( PhysicsBoxShape, PhysicsShape )

public:
	PhysicsBoxShape();

	~PhysicsBoxShape() override;

public:
	const XE::AABB & GetBox() const;

	void SetBox( const XE::AABB & val );

private:
	XE::AABB _AABB;
};

class XE_API PhysicsPlaneShape : public PhysicsShape
{
	OBJECT( PhysicsPlaneShape, PhysicsShape )

public:
	PhysicsPlaneShape();

	~PhysicsPlaneShape() override;

public:
	const XE::Plane & GetPlane() const;

	void SetPlane( const XE::Plane & val );

private:
	XE::Plane _Plane;
};

class XE_API PhysicsSphereShape : public PhysicsShape
{
	OBJECT( PhysicsSphereShape, PhysicsShape )

public:
	PhysicsSphereShape();

	~PhysicsSphereShape() override;

public:
	const XE::Sphere & GetSphere() const;

	void SetSphere( const XE::Sphere & val );

private:
	XE::Sphere _Sphere;
};

class XE_API PhysicsCapsuleShape : public PhysicsShape
{
	OBJECT( PhysicsCapsuleShape, PhysicsShape )

public:
	PhysicsCapsuleShape();

	~PhysicsCapsuleShape() override;

public:
	const XE::Capsule & GetCapsule() const;

	void SetCapsule( const XE::Capsule & val );

private:
	XE::Capsule _Capsule;
};

class XE_API PhysicsConvexMeshShape : public PhysicsShape
{
	OBJECT( PhysicsConvexMeshShape, PhysicsShape )

public:
	PhysicsConvexMeshShape();

	~PhysicsConvexMeshShape() override;

public:
	const XE::Vec3f & GetScale() const;

	void SetScale( const XE::Vec3f & val );

	const XE::Quat & GetRotation() const;

	void SetRotation( const XE::Quat & val );

public:
	const XE::Array<XE::uint8> & GetIndexBuffer() const;

	void SetIndexBuffer( const XE::Array<XE::uint8> & val );

	const XE::Array<XE::Vec3f> & GetVertexBuffer() const;

	void SetVertexBuffer( const XE::Array<XE::Vec3f> & val );

private:
	XE::Vec3f _Scale;
	XE::Quat _Rotation;
	XE::Array<XE::uint8> _IndexBuffer;
	XE::Array<XE::Vec3f> _VertexBuffer;
};

class XE_API PhysicsHeightFieldShape : public PhysicsShape
{
	OBJECT( PhysicsHeightFieldShape, PhysicsShape )

public:
	PhysicsHeightFieldShape();

	~PhysicsHeightFieldShape() override;

public:
	XE::float32 GetRowCount() const;

	void SetRowCount( XE::float32 val );

	XE::float32 GetColCount() const;

	void SetColCount( XE::float32 val );

	XE::float32 GetRowScale() const;

	void SetRowScale( XE::float32 val );

	XE::float32 GetColScale() const;

	void SetColScale( XE::float32 val );

	XE::float32 GetHeightScale() const;

	void SetHeightScale( XE::float32 val );

	XE::uint32 GetSampleStride() const;

	void SetSampleStride( XE::uint32 val );

	XE::float32 GetConvexEdgeThreshold() const;

	void SetConvexEdgeThreshold( XE::float32 val );

	const XE::Array<XE::float32> & GetHeightData() const;

	void SetHeightData( const XE::Array<XE::float32> & val );

private:
	XE::float32 _Row;
	XE::float32 _Col;
	XE::float32 _RowScale;
	XE::float32 _ColScale;
	XE::float32 _HeightScale;
	XE::uint32 _SampleStride;
	XE::float32 _ConvexEdgeThreshold;
	XE::Array<XE::float32> _HeightData;
};

END_XE_NAMESPACE

#endif // SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
