#include "Shape.h"

#include "PhysicsMaterial.h"

USING_XE

BEG_META( Shape )
type->Property( "Material", &Shape::_Material );
END_META()

XE::Shape::Shape()
{

}

XE::Shape::~Shape()
{

}

const PhysicsMaterialPtr & XE::Shape::GetMaterial() const
{
	return _Material;
}

void XE::Shape::SetMaterial( const PhysicsMaterialPtr & val )
{
	_Material = val;
}

XE::ShapeFlag XE::Shape::GetFlag() const
{
	return _Flag;
}

void XE::Shape::SetFlag( ShapeFlag val )
{
	_Flag = val;
}

const XE::Mat4 & XE::Shape::GetLocalTransform() const
{
	return _LocalTransform;
}

void XE::Shape::SetLocalTransform( const XE::Mat4 & val )
{
	_LocalTransform = val;
}

const XE::Layer & XE::Shape::GetSimulationFilter() const
{
	return _SimulationFilter;
}

void XE::Shape::SetSimulationFilter( const XE::Layer & val )
{
	_SimulationFilter = val;
}

const XE::Layer & XE::Shape::GetQueryFilter() const
{
	return _QueryFilter;
}

void XE::Shape::SetQueryFilter( const XE::Layer & val )
{
	_QueryFilter = val;
}

XE::real XE::Shape::GetContactOffset() const
{
	return _ContactOffset;
}

void XE::Shape::SetContactOffset( XE::real val )
{
	_ContactOffset = val;
}

XE::real XE::Shape::GetRestOffset() const
{
	return _RestOffset;
}

void XE::Shape::SetRestOffset( XE::real val )
{
	_RestOffset = val;
}

XE::real XE::Shape::GetTorsionalPatchRadius() const
{
	return _TorsionalPatchRadius;
}

void XE::Shape::SetTorsionalPatchRadius( XE::real val )
{
	_TorsionalPatchRadius = val;
}

XE::real XE::Shape::GetMinTorsionalPatchRadius() const
{
	return _MinTorsionalPatchRadius;
}

void XE::Shape::SetMinTorsionalPatchRadius( XE::real val )
{
	_MinTorsionalPatchRadius = val;
}

BEG_META( BoxShape )
END_META()

XE::BoxShape::BoxShape()
{

}

XE::BoxShape::~BoxShape()
{

}

const XE::AABB & XE::BoxShape::GetBox() const
{
	return _Box;
}

void XE::BoxShape::SetBox( const XE::AABB & val )
{
	_Box = val;
}

BEG_META( SphereShape )
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

BEG_META( CapsuleShape )
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

BEG_META( PlaneShape )
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

BEG_META( HeightFieldShape )
END_META()

XE::HeightFieldShape::HeightFieldShape()
{

}

XE::HeightFieldShape::~HeightFieldShape()
{

}

XE::uint32 XE::HeightFieldShape::GetWidth() const
{
	return _Width;
}

void XE::HeightFieldShape::SetWidth( XE::uint32 val )
{
	_Width = val;
}

XE::uint32 XE::HeightFieldShape::GetHeight() const
{
	return _Height;
}

void XE::HeightFieldShape::SetHeight( XE::uint32 val )
{
	_Height = val;
}

XE::float32 XE::HeightFieldShape::GetDepth() const
{
	return _Depth;
}

void XE::HeightFieldShape::SetDepth( XE::float32 val )
{
	_Depth = val;
}

const XE::Array<XE::float16> & XE::HeightFieldShape::GetHeightData() const
{
	return _HeightData;
}

void XE::HeightFieldShape::SetHeightData( const XE::Array<XE::float16> & val )
{
	_HeightData = val;
}
