#include "Shape.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxShape * >( GetHandle().GetValue() )

BEG_META( XE::Shape )
END_META()

XE::Shape::Shape()
{

}

XE::Shape::~Shape()
{

}

XE::ShapePtr XE::Shape::CreateShape( XE::ShapeHandle val )
{
	XE::ShapePtr res = nullptr;

	switch( reinterpret_cast< physx::PxShape * >( val.GetValue() )->getGeometryType() )
	{
	case physx::PxGeometryType::eSPHERE:
		res = XE::MakeShared<XE::SphereShape>();
		break;
	case physx::PxGeometryType::ePLANE:
		res = XE::MakeShared<XE::PlaneShape>();
		break;
	case physx::PxGeometryType::eCAPSULE:
		res = XE::MakeShared<XE::CapsuleShape>();
		break;
	case physx::PxGeometryType::eBOX:
		res = XE::MakeShared<XE::BoxShape>();
		break;
	case physx::PxGeometryType::eCONVEXMESH:
		res = XE::MakeShared<XE::ConvexMeshShape>();
		break;
	case physx::PxGeometryType::eHEIGHTFIELD:
		res = XE::MakeShared<XE::HeightFieldShape>();
		break;
	case physx::PxGeometryType::eTRIANGLEMESH:
	case physx::PxGeometryType::eGEOMETRY_COUNT:
	case physx::PxGeometryType::eINVALID:
	default:
		break;
	}

	if( res )
	{
		res->SetHandle( val );
	}

	return res;
}

XE::ShapeHandle XE::Shape::GetHandle() const
{
	return _Handle;
}

void XE::Shape::SetHandle( XE::ShapeHandle val )
{
	_Handle = val;
}

XE::String XE::Shape::GetName() const
{
	return _p->getName();
}

void XE::Shape::SetName( const XE::String & val )
{
	_p->setName( val.ToCString() );
}

XE::Mat4 XE::Shape::GetLocalPose() const
{
	auto trans = _p->getLocalPose();

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

void XE::Shape::SetLocalPose( const XE::Mat4 & val )
{
	XE::Quat rot;
	XE::Vec3 pos, scale;

	XE::Mathf::TRS( val, pos, rot, scale );

	_p->setLocalPose( physx::PxTransform( { pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z, rot.w } ) );
}

XE::ShapeFlags XE::Shape::GetShapeFlags() const
{
	return XE::uint8( _p->getFlags() );
}

void XE::Shape::SetShapeFlags( XE::ShapeFlags val )
{
	_p->setFlags( physx::PxShapeFlags( val.GetValue() ) );
}

XE::float32 XE::Shape::GetRestOffset() const
{
	return _p->getRestOffset();
}

void XE::Shape::SetRestOffset( XE::float32 val )
{
	_p->setRestOffset( val );
}

XE::float32 XE::Shape::GetContactOffset() const
{
	return _p->getContactOffset();
}

void XE::Shape::SetContactOffset( XE::float32 val )
{
	_p->setContactOffset( val );
}

XE::Layer XE::Shape::GetQueryFilter() const
{
	physx::PxFilterData data = _p->getQueryFilterData();

	return XE::uint64( data.word0 ) || ( XE::uint64( data.word1 ) << 32 );
}

void XE::Shape::SetQueryFilter( const XE::Layer & val )
{
	physx::PxFilterData data;

	data.word0 = val.GetValue() && 0xFFFFFFFF;
	data.word1 = ( val.GetValue() >> 32 ) && 0xFFFFFFFF;

	_p->setQueryFilterData( data );
}

XE::Layer XE::Shape::GetSimulationFilter() const
{
	physx::PxFilterData data = _p->getSimulationFilterData();

	return XE::uint64( data.word0 ) || ( XE::uint64( data.word1 ) << 32 );
}

void XE::Shape::SetSimulationFilter( const XE::Layer & val )
{
	physx::PxFilterData data;

	data.word0 = val.GetValue() && 0xFFFFFFFF;
	data.word1 = ( val.GetValue() >> 32 ) && 0xFFFFFFFF;

	_p->setSimulationFilterData( data );
}

XE::float32 XE::Shape::GetTorsionalPatchRadius() const
{
	return _p->getTorsionalPatchRadius();
}

void XE::Shape::SetTorsionalPatchRadius( XE::float32 val )
{
	_p->setTorsionalPatchRadius( val );
}

XE::float32 XE::Shape::GetMinTorsionalPatchRadius() const
{
	return _p->getMinTorsionalPatchRadius();
}

void XE::Shape::SetMinTorsionalPatchRadius( XE::float32 val )
{
	_p->setMinTorsionalPatchRadius( val );
}

XE::uint64 XE::Shape::GetPhysicsMaterialCount() const
{
	return _p->getNbMaterials();
}

XE::Array<XE::PhysicsMaterialHandle> XE::Shape::GetPhysicsMaterials() const
{
	XE::Array<XE::PhysicsMaterialHandle> res;

	physx::PxMaterial * materials[1024];

	auto size = _p->getMaterials( materials, 1024 );

	for( XE::uint32 i = 0; i < size; ++i )
	{
		res.push_back( reinterpret_cast< XE::uint64 >( materials[i] ) );
	}

	return std::move( res );
}

XE::PhysicsMaterialHandle XE::Shape::GetPhysicsMaterial( XE::uint64 val ) const
{
	return reinterpret_cast< XE::uint64 >( _p->getMaterialFromInternalFaceIndex( val ) );
}

void XE::Shape::SetPhysicsMaterials( const XE::Array<XE::PhysicsMaterialHandle> & val )
{
	physx::PxMaterial * materials[1024];

	std::memcpy( materials, val.data(), val.size() * sizeof( physx::PxMaterial * ) );

	_p->setMaterials( materials, val.size() );
}

BEG_META( XE::BoxShape )
END_META()

XE::BoxShape::BoxShape()
{

}

XE::BoxShape::~BoxShape()
{

}

XE::AABB XE::BoxShape::GetBox() const
{
	physx::PxBoxGeometry box;
	if( _p->getBoxGeometry( box ) )
	{
		return { XE::Vec3::Zero, { box.halfExtents.x * 2, box.halfExtents.y * 2, box.halfExtents.z * 2 } };
	}

	return {};
}

void XE::BoxShape::SetBox( const XE::AABB & val )
{
	_p->setGeometry( physx::PxBoxGeometry( val.GetSize().x, val.GetSize().y, val.GetSize().z ) );
}

BEG_META( XE::PlaneShape )
END_META()

XE::PlaneShape::PlaneShape()
{

}

XE::PlaneShape::~PlaneShape()
{

}

XE::Plane XE::PlaneShape::GetPlane() const
{
	physx::PxPlaneGeometry plane;
	if( _p->getPlaneGeometry( plane ) )
	{
		return { 1.0f, 0.0f, 0.0f, 0.0f };
	}

	return {};
}

void XE::PlaneShape::SetPlane( const XE::Plane & val )
{
	_p->setGeometry( physx::PxPlaneGeometry() );
}

BEG_META( XE::SphereShape )
END_META()

XE::SphereShape::SphereShape()
{

}

XE::SphereShape::~SphereShape()
{

}

XE::Sphere XE::SphereShape::GetSphere() const
{
	physx::PxSphereGeometry sphere;
	if( _p->getSphereGeometry( sphere ) )
	{
		return { { sphere.radius / 2.0f, sphere.radius / 2.0f, sphere.radius / 2.0f }, sphere.radius };
	}

	return {};
}

void XE::SphereShape::SetSphere( const XE::Sphere & val )
{
	_p->setGeometry( physx::PxSphereGeometry( val.radius ) );
}

BEG_META( XE::CapsuleShape )
END_META()

XE::CapsuleShape::CapsuleShape()
{

}

XE::CapsuleShape::~CapsuleShape()
{

}

XE::Capsule XE::CapsuleShape::GetCapsule() const
{
	physx::PxCapsuleGeometry capsule;
	if( _p->getCapsuleGeometry( capsule ) )
	{
		return { capsule.radius, capsule.halfHeight * 2.0f };
	}

	return {};
}

void XE::CapsuleShape::SetCapsule( const XE::Capsule & val )
{
	_p->setGeometry( physx::PxCapsuleGeometry( val.radius, val.height / 2.0f ) );
}

BEG_META( XE::ConvexMeshShape )
END_META()

XE::ConvexMeshShape::ConvexMeshShape()
{

}

XE::ConvexMeshShape::~ConvexMeshShape()
{

}

XE::Vec3 XE::ConvexMeshShape::GetScale() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		return { geometry.scale.scale.x, geometry.scale.scale.y, geometry.scale.scale.z };
	}

	return {};
}

XE::Quat XE::ConvexMeshShape::GetRotation() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		return { geometry.scale.rotation.x, geometry.scale.rotation.y, geometry.scale.rotation.z, geometry.scale.rotation.w };
	}

	return {};
}

XE::uint64 XE::ConvexMeshShape::GetVertexCount() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		return geometry.convexMesh->getNbVertices();
	}

	return 0;
}

XE::uint64 XE::ConvexMeshShape::GetPolygonCount() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		return geometry.convexMesh->getNbPolygons();
	}

	return 0;
}

XE::BasicMemoryView<XE::Vec3> XE::ConvexMeshShape::GetVertexBuffer() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		auto size = geometry.convexMesh->getNbVertices();
		XE::Vec3 * p = ( XE::Vec3 * )geometry.convexMesh->getVertices();
		return { p, size };
	}

	return {};
}

XE::BasicMemoryView<XE::uint8> XE::ConvexMeshShape::GetIndexBuffer() const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		auto size = geometry.convexMesh->getNbPolygons() * 4;
		XE::uint8 * p = ( XE::uint8 * )geometry.convexMesh->getIndexBuffer();
		return { p, size };
	}

	return {};
}

XE::HullPolygon XE::ConvexMeshShape::GetPolygonData( XE::uint64 val ) const
{
	physx::PxConvexMeshGeometry geometry;
	if( _p->getConvexMeshGeometry( geometry ) )
	{
		physx::PxHullPolygon p;
		if( geometry.convexMesh->getPolygonData( val, p ) )
		{
			XE::HullPolygon res;

			res.Plane = { p.mPlane[0], p.mPlane[1], p.mPlane[2], p.mPlane[3] };
			res.IndexCount = p.mNbVerts;
			res.IndexOffset = p.mIndexBase;

			return res;
		}
	}

	return {};
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
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightField->getNbRows();
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetColCount() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightField->getNbColumns();
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetRowScale() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.rowScale;
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetColScale() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.columnScale;
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetHeightScale() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightScale;
	}

	return 0;
}

XE::uint32 XE::HeightFieldShape::GetSampleStride() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightField->getSampleStride();
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetConvexEdgeThreshold() const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightField->getConvexEdgeThreshold();
	}

	return 0;
}

XE::float32 XE::HeightFieldShape::GetHeight( XE::float32 x, XE::float32 y ) const
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		return geometry.heightField->getHeight( x, y );
	}

	return 0.0f;
}

bool XE::HeightFieldShape::ModifySamples( XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, XE::BasicMemoryView<XE::uint16> data, XE::float32 convex_edge_threshold )
{
	physx::PxHeightFieldGeometry geometry;
	if( _p->getHeightFieldGeometry( geometry ) )
	{
		physx::PxStridedData samples;
		samples.data = data.data();
		samples.stride = sizeof( XE::uint16 );

		physx::PxHeightFieldDesc desc;
		desc.nbRows = w;
		desc.nbColumns = h;
		desc.format = physx::PxHeightFieldFormat::eS16_TM;
		desc.samples = samples;
		desc.convexEdgeThreshold = convex_edge_threshold;
		desc.flags = physx::PxHeightFieldFlags( physx::PxHeightFieldFlag::eNO_BOUNDARY_EDGES );

		return geometry.heightField->modifySamples( x, y, desc );
	}

	return false;
}
