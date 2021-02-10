#include "PhysicsShape.h"

BEG_META( XE::PhysicsShape )
END_META()

XE::PhysicsShape::PhysicsShape()
{

}

XE::PhysicsShape::~PhysicsShape()
{

}

XE::PhysicsShapeHandle XE::PhysicsShape::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsShape::SetHandle( XE::PhysicsShapeHandle val )
{
	_Handle = val;
}

const XE::String & XE::PhysicsShape::GetName() const
{
	return _Name;
}

void XE::PhysicsShape::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4x4f & XE::PhysicsShape::GetLocalTransform() const
{
	return _LocalTransform;
}

void XE::PhysicsShape::SetLocalTransform( const XE::Mat4x4f & val )
{
	_LocalTransform = val;
}

XE::PhysicsShapeFlags XE::PhysicsShape::GetShapeFlags() const
{
	return _ShapeFlags;
}

void XE::PhysicsShape::SetShapeFlags( XE::PhysicsShapeFlags val )
{
	_ShapeFlags = val;
}

XE::float32 XE::PhysicsShape::GetRestOffset() const
{
	return _RestOffset;
}

void XE::PhysicsShape::SetRestOffset( XE::float32 val )
{
	_RestOffset = val;
}

XE::float32 XE::PhysicsShape::GetContactOffset() const
{
	return _ContactOffset;
}

void XE::PhysicsShape::SetContactOffset( XE::float32 val )
{
	_ContactOffset = val;
}

XE::Layer XE::PhysicsShape::GetQueryFilter() const
{
	return _QueryFilter;
}

void XE::PhysicsShape::SetQueryFilter( const XE::Layer & val )
{
	_QueryFilter = val;
}

XE::Layer XE::PhysicsShape::GetSimulationFilter() const
{
	return _SimulationFilter;
}

void XE::PhysicsShape::SetSimulationFilter( const XE::Layer & val )
{
	_SimulationFilter = val;
}

XE::float32 XE::PhysicsShape::GetTorsionalPatchRadius() const
{
	return _TorsionalPatchRadius;
}

void XE::PhysicsShape::SetTorsionalPatchRadius( XE::float32 val )
{
	_TorsionalPatchRadius = val;
}

XE::float32 XE::PhysicsShape::GetMinTorsionalPatchRadius() const
{
	return _MinTorsionalPatchRadius;
}

void XE::PhysicsShape::SetMinTorsionalPatchRadius( XE::float32 val )
{
	_MinTorsionalPatchRadius = val;
}

const XE::Array<XE::PhysicsMaterialHandle> & XE::PhysicsShape::GetPhysicsMaterials() const
{
	return _PhysicsMaterials;
}

void XE::PhysicsShape::SetPhysicsMaterials( const XE::Array<XE::PhysicsMaterialHandle> & val )
{
	_PhysicsMaterials = val;
}

BEG_META( XE::PhysicsBoxShape )
END_META()

XE::PhysicsBoxShape::PhysicsBoxShape()
{

}

XE::PhysicsBoxShape::~PhysicsBoxShape()
{

}

const XE::AABB & XE::PhysicsBoxShape::GetBox() const
{
	return _AABB;
}

void XE::PhysicsBoxShape::SetBox( const XE::AABB & val )
{
	_AABB = val;
}

BEG_META( XE::PhysicsPlaneShape )
END_META()

XE::PhysicsPlaneShape::PhysicsPlaneShape()
{

}

XE::PhysicsPlaneShape::~PhysicsPlaneShape()
{

}

const XE::Plane & XE::PhysicsPlaneShape::GetPlane() const
{
	return _Plane;
}

void XE::PhysicsPlaneShape::SetPlane( const XE::Plane & val )
{
	_Plane = val;
}

BEG_META( XE::PhysicsSphereShape )
END_META()

XE::PhysicsSphereShape::PhysicsSphereShape()
{

}

XE::PhysicsSphereShape::~PhysicsSphereShape()
{

}

const XE::Sphere & XE::PhysicsSphereShape::GetSphere() const
{
	return _Sphere;
}

void XE::PhysicsSphereShape::SetSphere( const XE::Sphere & val )
{
	_Sphere = val;
}

BEG_META( XE::PhysicsCapsuleShape )
END_META()

XE::PhysicsCapsuleShape::PhysicsCapsuleShape()
{

}

XE::PhysicsCapsuleShape::~PhysicsCapsuleShape()
{

}

const XE::Capsule & XE::PhysicsCapsuleShape::GetCapsule() const
{
	return _Capsule;
}

void XE::PhysicsCapsuleShape::SetCapsule( const XE::Capsule & val )
{
	_Capsule = val;
}

BEG_META( XE::PhysicsConvexMeshShape )
END_META()

XE::PhysicsConvexMeshShape::PhysicsConvexMeshShape()
{

}

XE::PhysicsConvexMeshShape::~PhysicsConvexMeshShape()
{

}

const XE::Vec3f & XE::PhysicsConvexMeshShape::GetScale() const
{
	return _Scale;
}

void XE::PhysicsConvexMeshShape::SetScale( const XE::Vec3f & val )
{
	_Scale = val;
}

const XE::Quat & XE::PhysicsConvexMeshShape::GetRotation() const
{
	return _Rotation;
}

void XE::PhysicsConvexMeshShape::SetRotation( const XE::Quat & val )
{
	_Rotation = val;
}

const XE::Array<XE::uint8> & XE::PhysicsConvexMeshShape::GetIndexBuffer() const
{
	return _IndexBuffer;
}

void XE::PhysicsConvexMeshShape::SetIndexBuffer( const XE::Array<XE::uint8> & val )
{
	_IndexBuffer = val;
}

const XE::Array<XE::Vec3f> & XE::PhysicsConvexMeshShape::GetVertexBuffer() const
{
	return _VertexBuffer;
}

void XE::PhysicsConvexMeshShape::SetVertexBuffer( const XE::Array<XE::Vec3f> & val )
{
	_VertexBuffer = val;
}

BEG_META( XE::PhysicsHeightFieldShape )
END_META()

XE::PhysicsHeightFieldShape::PhysicsHeightFieldShape()
{

}

XE::PhysicsHeightFieldShape::~PhysicsHeightFieldShape()
{

}

XE::float32 XE::PhysicsHeightFieldShape::GetRowCount() const
{
	return _Row;
}

void XE::PhysicsHeightFieldShape::SetRowCount( XE::float32 val )
{
	_Row = val;
}

XE::float32 XE::PhysicsHeightFieldShape::GetColCount() const
{
	return _Col;
}

void XE::PhysicsHeightFieldShape::SetColCount( XE::float32 val )
{
	_Col = val;
}

XE::float32 XE::PhysicsHeightFieldShape::GetRowScale() const
{
	return _RowScale;
}

void XE::PhysicsHeightFieldShape::SetRowScale( XE::float32 val )
{
	_RowScale = val;
}

XE::float32 XE::PhysicsHeightFieldShape::GetColScale() const
{
	return _ColScale;
}

void XE::PhysicsHeightFieldShape::SetColScale( XE::float32 val )
{
	_ColScale = val;
}

XE::float32 XE::PhysicsHeightFieldShape::GetHeightScale() const
{
	return _HeightScale;
}

void XE::PhysicsHeightFieldShape::SetHeightScale( XE::float32 val )
{
	_HeightScale = val;
}

XE::uint32 XE::PhysicsHeightFieldShape::GetSampleStride() const
{
	return _SampleStride;
}

void XE::PhysicsHeightFieldShape::SetSampleStride( XE::uint32 val )
{
	_SampleStride = val;
}

XE::float32 XE::PhysicsHeightFieldShape::GetConvexEdgeThreshold() const
{
	return _ConvexEdgeThreshold;
}

void XE::PhysicsHeightFieldShape::SetConvexEdgeThreshold( XE::float32 val )
{
	_ConvexEdgeThreshold = val;
}

const XE::Array<XE::float32> & XE::PhysicsHeightFieldShape::GetHeightData() const
{
	return _HeightData;
}

void XE::PhysicsHeightFieldShape::SetHeightData( const XE::Array<XE::float32> & val )
{
	_HeightData = val;
}
