#include "Type.h"

#include "GFX.h"

USING_XE

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
XE::SkinBindData::SkinBindData()
{

}

XE::SkinBindData::~SkinBindData()
{

}

void XE::SkinBindData::AddBone( const XE::BoneInfluence &bone )
{
	_Bones.push_back(bone);
}

void XE::SkinBindData::RemoveEmptyBones()
{
	for( int i = 0; i < _Bones.size(); )
	{
		if( _Bones[i].Influences.empty())
		{
			_Bones.erase(_Bones.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void
XE::SkinBindData::BuildVertexTable( std::uint32_t vertex_count, const std::vector < std::uint32_t > &vertex_remap, XE::Array < XE::VertexData > &table )
{
	XE::uint32 vertex;
	
	table.reserve(vertex_count);
	for( vertex = 0; vertex < vertex_count; ++vertex )
	{
		VertexData data;
		data.Palette = -1;
		data.Origin = vertex;
		table.push_back(data);
		
	}
	
	for( size_t i = 0; i < _Bones.size(); ++i )
	{
		Array < VertexInfluence > &influences = _Bones[i].Influences;
		for( auto &influence : influences )
		{
			if( !vertex_remap.empty())
			{
				vertex = vertex_remap[influence.VertexIndex];
				if( vertex == 0xFFFFFFFF )
					continue;
				auto &data = table[vertex];
				
				data.Influences.push_back(static_cast<std::int32_t>(i));
				data.Weights.push_back(influence.Weight);
			}
			else
			{
				auto &data = table[influence.VertexIndex];
				
				data.Influences.push_back(static_cast<std::int32_t>(i));
				data.Weights.push_back(influence.Weight);
			}
		}
	}
}

void XE::SkinBindData::RemapVertices( const std::vector < std::uint32_t > &remap )
{
	for( auto &_Bone : _Bones )
	{
		Array < VertexInfluence > new_influences;
		Array < VertexInfluence > &influences = _Bone.Influences;
		new_influences.reserve(influences.size());
		for( auto &influence : influences )
		{
			std::uint32_t new_index = remap[influence.VertexIndex];
			if( new_index != 0xFFFFFFFF )
			{
				VertexInfluence t_vertex_inf{};
				t_vertex_inf.VertexIndex = new_index;
				t_vertex_inf.Weight = influence.Weight;
				new_influences.push_back(t_vertex_inf);
				
				if( new_index >= remap.size())
				{
					new_influences.push_back(influence);
				}
			}
		}
		
		_Bone.Influences = new_influences;
	}
}

const XE::Array < XE::BoneInfluence > &XE::SkinBindData::GetBones() const
{
	return _Bones;
}

XE::Array < XE::BoneInfluence > &XE::SkinBindData::GetBones()
{
	return _Bones;
}

bool XE::SkinBindData::HasBones() const
{
	return !_Bones.empty();
}

const XE::BoneInfluence * XE::SkinBindData::FindBoneById( const String &id ) const
{
	auto it = std::find_if(std::begin(_Bones), std::end(_Bones), [id]( const BoneInfluence &bone )
	{ return id == bone.Name; });
	
	if( it != std::end(_Bones))
	{
		return &( *it );
	}
	
	return nullptr;
}

void XE::SkinBindData::ClearVertexInfluences()
{
	for( auto &it : _Bones )
	{
		it.Influences.clear();
	}
}

void XE::SkinBindData::Clear()
{
	_Bones.clear();
}

XE::BonePalette::BonePalette()
		:_DataGroupID(0), _MaxSize(0), _MaxBlendIndex(-1)
{

}

XE::BonePalette::BonePalette( XE::uint32 val )
		:_DataGroupID(0), _MaxSize(val), _MaxBlendIndex(-1)
{

}

XE::BonePalette::BonePalette( const XE::BonePalette &val )
		:_BonesLut(val._BonesLut),
		_Bones(val._Bones),
		_Faces(val._Faces),
		_DataGroupID(val._DataGroupID),
		_MaxSize(val._MaxSize),
		_MaxBlendIndex(val._MaxBlendIndex)
{

}

XE::BonePalette::~BonePalette()
{

}

XE::Array < XE::Mat4 >
XE::BonePalette::GetSkinningMatrices( const Array < XE::Mat4 > &node_transforms, const XE::SkinBindData &bind_data, bool compute_inverse_transpose ) const
{
	const auto &bind_list = bind_data.GetBones();
	if( node_transforms.empty())
		return node_transforms;
	
	const std::uint32_t max_blend_transforms = GFX::GetMaxBlendTransforms();
	Array < XE::Mat4 > transforms;
	transforms.resize(max_blend_transforms);
	
	for( size_t i = 0; i < _Bones.size(); ++i )
	{
		auto bone = _Bones[i];
		const auto &bone_transform = node_transforms[bone];
		const auto &bone_data = bind_list[bone];
		auto &transform = transforms[i];
		transform = bone_transform * bone_data.Transform;
		if( compute_inverse_transpose )
		{
			transform = Mathf::Transpose(Mathf::Inverse(transform));
		}
		
	}
	
	return transforms;
}

void
XE::BonePalette::ComputePaletteFit( XE::BonePalette::BoneIndexMap &input, XE::int32 &current_space, XE::int32 &common_bones, XE::int32 &additional_bones )
{
	current_space = static_cast<XE::int32>(_MaxSize - static_cast<std::uint32_t>(_Bones.size()));
	common_bones = 0;
	additional_bones = 0;
	
	if( _Bones.empty())
	{
		additional_bones = static_cast<std::int32_t>(input.size());
		return;
		
	}
	else if( input.empty())
	{
		return;
		
	}
	
	BoneIndexMap::iterator it_bone, it_bone2;
	for( it_bone = input.begin(); it_bone != input.end(); ++it_bone )
	{
		it_bone2 = _BonesLut.find(it_bone->first);
		if( it_bone2 != _BonesLut.end())
			common_bones++;
		else
			additional_bones++;
	}
}

void XE::BonePalette::AssignBones( XE::BonePalette::BoneIndexMap &bones, XE::Array < XE::uint32 > &faces )
{
	BoneIndexMap::iterator it_bone, it_bone2;
	
	for( it_bone = bones.begin(); it_bone != bones.end(); ++it_bone )
	{
		it_bone2 = _BonesLut.find(it_bone->first);
		if( it_bone2 == _BonesLut.end())
		{
			_BonesLut[it_bone->first] = static_cast<std::uint32_t>(_Bones.size());
			_Bones.push_back(it_bone->first);
		}
	}
	
	_Faces.insert(_Faces.end(), faces.begin(), faces.end());
}

void XE::BonePalette::AssignBones( const XE::Array < XE::uint32 > &bones )
{
	BoneIndexMap::iterator it_bone;
	
	_Bones.clear();
	_BonesLut.clear();
	
	for( size_t i = 0; i < bones.size(); ++i )
	{
		it_bone = _BonesLut.find(bones[i]);
		if( it_bone == _BonesLut.end())
		{
			_BonesLut[bones[i]] = static_cast<std::uint32_t>(_Bones.size());
			_Bones.push_back(bones[i]);
		}
	}
}

XE::uint32 XE::BonePalette::TranslateBoneToPalette( XE::uint32 bone_index ) const
{
	auto it_bone = _BonesLut.find(bone_index);
	
	if( it_bone == _BonesLut.end())
		return 0xFFFFFFFF;
	
	return it_bone->second;
}

XE::int32 XE::BonePalette::GetMaximumBlendIndex() const
{
	return _MaxBlendIndex;
}

XE::uint32 XE::BonePalette::GetMaximumSize() const
{
	return _MaxSize;
}

XE::uint32 XE::BonePalette::GetDataGroup() const
{
	return _DataGroupID;
}

XE::Array < unsigned int > &XE::BonePalette::GetInfluencedFaces()
{
	return _Faces;
}

const XE::Array < unsigned int > &XE::BonePalette::GetBones() const
{
	return _Bones;
}

void XE::BonePalette::SetMaximumBlendIndex( int index )
{
	_MaxBlendIndex = index;
}

void XE::BonePalette::SetDataGroup( XE::uint32 group )
{
	_DataGroupID = group;
}

void XE::BonePalette::ClearInfluencedFaces()
{
	_Faces.clear();
}
