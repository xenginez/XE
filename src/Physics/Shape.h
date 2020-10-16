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

#include "ConvexMesh.h"

BEG_XE_NAMESPACE

class XE_API Shape : public XE::Object
{
	OBJECT( Shape, Object )

public:
	Shape();

	~Shape() override;

public:
	XE::ShapeFlags GetFlags() const;

	void SetFlags( XE::ShapeFlags val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::float32 GetRestOffset() const;

	void SetRestOffset( XE::float32 val );

	XE::float32 GetContactOffset() const;

	void SetContactOffset( XE::float32 val );

	const XE::Mat4 & GetLocalTransform() const;

	void SetLocalTransform( const XE::Mat4 & val );

	const XE::Layer & GetQueryFilter() const;

	void SetQueryFilter( const XE::Layer & val );

	const XE::Layer & GetSimulationFilter() const;

	void SetSimulationFilter( const XE::Layer & val );

	XE::float32 GetTorsionalPatchRadius() const;

	void SetTorsionalPatchRadius( XE::float32 val );

	XE::float32 GetMinTorsionalPatchRadius() const;

	void SetMinTorsionalPatchRadius( XE::float32 val );

	XE::PhysicsMaterialHandle GetMaterial() const;

	void SetMaterial( XE::PhysicsMaterialHandle val );

};

class XE_API BoxShape : public Shape
{
	OBJECT( BoxShape, Shape )

public:
	BoxShape();

	~BoxShape() override;

public:
	const XE::AABB & GetBox() const;

	void SetBox( const XE::AABB & val );

};

class XE_API PlaneShape : public Shape
{
	OBJECT( PlaneShape, Shape )

public:
	PlaneShape();

	~PlaneShape() override;

public:
	const XE::Plane & GetPlane() const;

	void SetPlane( const XE::Plane & val );

};

class XE_API SphereShape : public Shape
{
	OBJECT( SphereShape, Shape )

public:
	SphereShape();

	~SphereShape() override;

public:
	const XE::Sphere & GetSphere() const;

	void SetSphere( const XE::Sphere & val );

};

class XE_API CapsuleShape : public Shape
{
	OBJECT( CapsuleShape, Shape )

public:
	CapsuleShape();

	~CapsuleShape() override;

public:
	const XE::Capsule & GetCapsule() const;

	void SetCapsule( const XE::Capsule & val );

};

class XE_API ConvexMeshShape : public Shape
{
	OBJECT( ConvexMeshShape, Shape )

public:
	ConvexMeshShape();

	~ConvexMeshShape() override;

public:
	const XE::ConvexMesh & GetCapsule() const;

	void SetCapsule( const XE::ConvexMesh & val );

};

class XE_API HeightFieldShape : public Shape
{
	OBJECT( HeightFieldShape, Shape )

public:
	HeightFieldShape();

	~HeightFieldShape() override;

public:
	XE::uint32 GetWidth() const;

	void SetWidth( XE::uint32 val );

	XE::uint32 GetHeight() const;

	void SetHeight( XE::uint32 val );

	XE::float32 GetDepth() const;

	void SetDepth( XE::float32 val );

	const XE::Array<XE::float16> & GetData() const;

	void SetData( const XE::Array<XE::float16> & val );

};

END_XE_NAMESPACE

#endif // SHAPE_H__888F3A03_457E_43C2_9762_4007ECABA020
