#include "Shape.h"

#include "PhysicsMaterial.h"

BEG_META( XE::Shape )
type->Property( "Material", &Shape::_Material );
END_META()

XE::Shape::Shape()
{

}

XE::Shape::~Shape()
{

}

BEG_META( XE::BoxShape )
END_META()

XE::BoxShape::BoxShape()
{

}

XE::BoxShape::~BoxShape()
{

}

BEG_META( XE::SphereShape )
END_META()

XE::SphereShape::SphereShape()
{

}

XE::SphereShape::~SphereShape()
{

}

BEG_META( XE::CapsuleShape )
END_META()

XE::CapsuleShape::CapsuleShape()
{

}

XE::CapsuleShape::~CapsuleShape()
{

}

BEG_META( XE::PlaneShape )
END_META()

XE::PlaneShape::PlaneShape()
{

}

XE::PlaneShape::~PlaneShape()
{

}

BEG_META( XE::HeightFieldShape )
END_META()

XE::HeightFieldShape::HeightFieldShape()
{

}

XE::HeightFieldShape::~HeightFieldShape()
{

}
