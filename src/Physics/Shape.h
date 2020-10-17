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
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Shape : public XE::Object
{
	OBJECT( Shape, Object )

public:
	Shape();

	~Shape() override;

public:
	static XE::ShapePtr CreateShape( XE::ShapeHandle val );

public:
	XE::ShapeHandle GetHandle() const;

	void SetHandle( XE::ShapeHandle val );

public:
	XE::String GetName() const;

	void SetName( const XE::String & val );

	XE::Mat4 GetLocalPose() const;

	void SetLocalPose( const XE::Mat4 & val );

	XE::ShapeFlags GetShapeFlags() const;

	void SetShapeFlags( XE::ShapeFlags val );

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

public:
	XE::uint64 GetPhysicsMaterialCount() const;

	XE::Array<XE::PhysicsMaterialHandle> GetPhysicsMaterials() const;

	XE::PhysicsMaterialHandle GetPhysicsMaterial( XE::uint64 val ) const;

	void SetPhysicsMaterials( const XE::Array<XE::PhysicsMaterialHandle> & val );

private:
	XE::ShapeHandle _Handle;
};

class XE_API BoxShape : public Shape
{
	OBJECT( BoxShape, Shape )

public:
	BoxShape();

	~BoxShape() override;

public:
	XE::AABB GetBox() const;

	void SetBox( const XE::AABB & val );

};

class XE_API PlaneShape : public Shape
{
	OBJECT( PlaneShape, Shape )

public:
	PlaneShape();

	~PlaneShape() override;

public:
	XE::Plane GetPlane() const;

	void SetPlane( const XE::Plane & val );

};

class XE_API SphereShape : public Shape
{
	OBJECT( SphereShape, Shape )

public:
	SphereShape();

	~SphereShape() override;

public:
	XE::Sphere GetSphere() const;

	void SetSphere( const XE::Sphere & val );

};

class XE_API CapsuleShape : public Shape
{
	OBJECT( CapsuleShape, Shape )

public:
	CapsuleShape();

	~CapsuleShape() override;

public:
	XE::Capsule GetCapsule() const;

	void SetCapsule( const XE::Capsule & val );

};

class XE_API ConvexMeshShape : public Shape
{
	OBJECT( ConvexMeshShape, Shape )

public:
	ConvexMeshShape();

	~ConvexMeshShape() override;

public:
	XE::Vec3 GetScale() const;

	XE::Quat GetRotation() const;

public:
	XE::uint64 GetVertexCount() const;

	XE::uint64 GetPolygonCount() const;

	XE::BasicMemoryView<XE::Vec3> GetVertexBuffer() const;

	XE::BasicMemoryView<XE::uint8> GetIndexBuffer() const;

	XE::HullPolygon GetPolygonData( XE::uint64 val ) const;

};

class XE_API HeightFieldShape : public Shape
{
	OBJECT( HeightFieldShape, Shape )

public:
	HeightFieldShape();

	~HeightFieldShape() override;

public:
	XE::float32 GetRowCount() const;

	XE::float32 GetColCount() const;

	XE::float32 GetRowScale() const;

	XE::float32 GetColScale() const;

	XE::float32 GetHeightScale() const;

	XE::uint32 GetSampleStride() const;

	XE::float32 GetConvexEdgeThreshold() const;

	XE::float32 GetHeight( XE::float32 x, XE::float32 y ) const;

	bool ModifySamples( XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, XE::BasicMemoryView<XE::uint16> data, XE::float32 convex_edge_threshold );

};

END_XE_NAMESPACE

#endif // SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
