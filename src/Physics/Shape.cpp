#include "Shape.h"

BEG_META( XE::Shape )
END_META()

XE::Shape::Shape()
{

}

XE::Shape::~Shape()
{

}

XE::ShapeHandle XE::Shape::GetHandle() const
{
	return _Handle;
}

void XE::Shape::SetHandle( XE::ShapeHandle val )
{
	_Handle = val;
}

const XE::String & XE::Shape::GetName() const
{
	return _Name;
}

void XE::Shape::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4f & XE::Shape::GetLocalTransform() const
{
	return _LocalTransform;
}

void XE::Shape::SetLocalTransform( const XE::Mat4f & val )
{
	_LocalTransform = val;
}

XE::ShapeFlags XE::Shape::GetShapeFlags() const
{
	return _ShapeFlags;
}

void XE::Shape::SetShapeFlags( XE::ShapeFlags val )
{
	_ShapeFlags = val;
}

XE::float32 XE::Shape::GetRestOffset() const
{
	return _RestOffset;
}

void XE::Shape::SetRestOffset( XE::float32 val )
{
	_RestOffset = val;
}

XE::float32 XE::Shape::GetContactOffset() const
{
	return _ContactOffset;
}

void XE::Shape::SetContactOffset( XE::float32 val )
{
	_ContactOffset = val;
}

XE::Layer XE::Shape::GetQueryFilter() const
{
	return _QueryFilter;
}

void XE::Shape::SetQueryFilter( const XE::Layer & val )
{
	_QueryFilter = val;
}

XE::Layer XE::Shape::GetSimulationFilter() const
{
	return _SimulationFilter;
}

void XE::Shape::SetSimulationFilter( const XE::Layer & val )
{
	_SimulationFilter = val;
}

XE::float32 XE::Shape::GetTorsionalPatchRadius() const
{
	return _TorsionalPatchRadius;
}

void XE::Shape::SetTorsionalPatchRadius( XE::float32 val )
{
	_TorsionalPatchRadius = val;
}

XE::float32 XE::Shape::GetMinTorsionalPatchRadius() const
{
	return _MinTorsionalPatchRadius;
}

void XE::Shape::SetMinTorsionalPatchRadius( XE::float32 val )
{
	_MinTorsionalPatchRadius = val;
}

const XE::Array<XE::PhysicsMaterialHandle> & XE::Shape::GetPhysicsMaterials() const
{
	return _PhysicsMaterials;
}

void XE::Shape::SetPhysicsMaterials( const XE::Array<XE::PhysicsMaterialHandle> & val )
{
	_PhysicsMaterials = val;
}

BEG_META( XE::BoxShape )
END_META()

XE::BoxShape::BoxShape()
{

}

XE::BoxShape::~BoxShape()
{

}

const XE::AABB & XE::BoxShape::GetBox() const
{
	return _AABB;
}

void XE::BoxShape::SetBox( const XE::AABB & val )
{
	_AABB = val;
}

BEG_META( XE::PlaneShape )
END_META()

XE::PlaneShape::PlaneShape()
{

}

XE::PlaneShape::~PlaneShape()
{

}

const XE::Plane & XE::PlaneShape::GetPlane() const
{
	return _Plane;
}

void XE::PlaneShape::SetPlane( const XE::Plane & val )
{
	_Plane = val;
}

BEG_META( XE::SphereShape )
END_META()

XE::SphereShape::SphereShape()
{

}

XE::SphereShape::~SphereShape()
{

}

const XE::Sphere & XE::SphereShape::GetSphere() const
{
	return _Sphere;
}

void XE::SphereShape::SetSphere( const XE::Sphere & val )
{
	_Sphere = val;
}

BEG_META( XE::CapsuleShape )
END_META()

XE::CapsuleShape::CapsuleShape()
{

}

XE::CapsuleShape::~CapsuleShape()
{

}

const XE::Capsule & XE::CapsuleShape::GetCapsule() const
{
	return _Capsule;
}

void XE::CapsuleShape::SetCapsule( const XE::Capsule & val )
{
	_Capsule = val;
}

BEG_META( XE::ConvexMeshShape )
END_META()

XE::ConvexMeshShape::ConvexMeshShape()
{

}

XE::ConvexMeshShape::~ConvexMeshShape()
{

}

const XE::Vec3f & XE::ConvexMeshShape::GetScale() const
{
	return _Scale;
}

void XE::ConvexMeshShape::SetScale( const XE::Vec3f & val )
{
	_Scale = val;
}

const XE::Quat & XE::ConvexMeshShape::GetRotation() const
{
	return _Rotation;
}

void XE::ConvexMeshShape::SetRotation( const XE::Quat & val )
{
	_Rotation = val;
}

const XE::Array<XE::uint8> & XE::ConvexMeshShape::GetIndexBuffer() const
{
	return _IndexBuffer;
}

void XE::ConvexMeshShape::SetIndexBuffer( const XE::Array<XE::uint8> & val )
{
	_IndexBuffer = val;
}

const XE::Array<XE::Vec3f> & XE::ConvexMeshShape::GetVertexBuffer() const
{
	return _VertexBuffer;
}

void XE::ConvexMeshShape::SetVertexBuffer( const XE::Array<XE::Vec3f> & val )
{
	_VertexBuffer = val;
}

BEG_META( XE::HeightFieldShape )
END_META()

XE::HeightFieldShape::HeightFieldShape()
{

}

XE::HeightFieldShape::~HeightFieldShape()
{

}

XE::float32 XE::HeightFieldShape::GetRowCount() const
{
	return _Row;
}

void XE::HeightFieldShape::SetRowCount( XE::float32 val )
{
	_Row = val;
}

XE::float32 XE::HeightFieldShape::GetColCount() const
{
	return _Col;
}

void XE::HeightFieldShape::SetColCount( XE::float32 val )
{
	_Col = val;
}

XE::float32 XE::HeightFieldShape::GetRowScale() const
{
	return _RowScale;
}

void XE::HeightFieldShape::SetRowScale( XE::float32 val )
{
	_RowScale = val;
}

XE::float32 XE::HeightFieldShape::GetColScale() const
{
	return _ColScale;
}

void XE::HeightFieldShape::SetColScale( XE::float32 val )
{
	_ColScale = val;
}

XE::float32 XE::HeightFieldShape::GetHeightScale() const
{
	return _HeightScale;
}

void XE::HeightFieldShape::SetHeightScale( XE::float32 val )
{
	_HeightScale = val;
}

XE::uint32 XE::HeightFieldShape::GetSampleStride() const
{
	return _SampleStride;
}

void XE::HeightFieldShape::SetSampleStride( XE::uint32 val )
{
	_SampleStride = val;
}

XE::float32 XE::HeightFieldShape::GetConvexEdgeThreshold() const
{
	return _ConvexEdgeThreshold;
}

void XE::HeightFieldShape::SetConvexEdgeThreshold( XE::float32 val )
{
	_ConvexEdgeThreshold = val;
}

const XE::Array<XE::float32> & XE::HeightFieldShape::GetHeightData() const
{
	return _HeightData;
}

void XE::HeightFieldShape::SetHeightData( const XE::Array<XE::float32> & val )
{
	_HeightData = val;
}
