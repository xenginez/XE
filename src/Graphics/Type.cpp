#include "Type.h"

#include "GFX.h"

USING_XE

BEGIN_META(BoneWeight)
		type->Property("Index", &BoneWeight::Index);
		type->Property("Weight0", &BoneWeight::Weight0);
		type->Property("Weight1", &BoneWeight::Weight1);
		type->Property("Weight2", &BoneWeight::Weight2);
		type->Property("Weight3", &BoneWeight::Weight3);
		type->Property("Bone0", &BoneWeight::Bone0);
		type->Property("Bone1", &BoneWeight::Bone1);
		type->Property("Bone2", &BoneWeight::Bone2);
		type->Property("Bone3", &BoneWeight::Bone3);
END_META()

XE::BoneWeight::BoneWeight()
		:Index(static_cast<uint64>(-1)),
		Weight0(0),
		Weight1(0),
		Weight2(0),
		Weight3(0),
		Bone0(static_cast<uint32>(-1)),
		Bone1(static_cast<uint32>(-1)),
		Bone2(static_cast<uint32>(-1)),
		Bone3(static_cast<uint32>(-1))
{

}

XE::BoneWeight::~BoneWeight()
{

}



// BEGIN_META( ViewHandle )
// END_META()
// BEGIN_META( DynamicIndexBufferHandle )
// END_META()
// BEGIN_META( DynamicVertexBufferHandle )
// END_META()
// BEGIN_META( FrameBufferHandle )
// END_META()
// BEGIN_META( IndexBufferHandle )
// END_META()
// BEGIN_META( IndirectBufferHandle )
// END_META()
// BEGIN_META( OcclusionQueryHandle )
// END_META()
// BEGIN_META( ProgramHandle )
// END_META()
// BEGIN_META( ShaderHandle )
// END_META()
// BEGIN_META( TextureHandle )
// END_META()
// BEGIN_META( UniformHandle )
// END_META()
// BEGIN_META( VertexBufferHandle )
// END_META()
// BEGIN_META( VertexDeclHandle )
// END_META()