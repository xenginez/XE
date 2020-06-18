#include "LOD.h"



BEG_META( XE::LOD )
		type->Property("LODs", &LOD::GetLODs, &LOD::SetLODs, IMetaProperty::NoDesign);
END_META()

XE::LOD::LOD()
		:_Lods(3)
{

}

XE::LOD::LOD( XE::uint64 val )
		:_Lods(val)
{

}

XE::LOD::~LOD()
{

}

XE::uint64 XE::LOD::GetLODCount() const
{
	return _Lods.size();
}

void XE::LOD::SetLODCount( XE::uint64 val )
{
	if( val != _Lods.size())
	{
		_Lods.resize(val);
	}
}

XE::float32 XE::LOD::GetLowerDistance( XE::uint64 lod )
{
	XE_ASSERT(lod < _Lods.size());
	
	return _Lods[lod].first;
}

void XE::LOD::SetLowerDistance( XE::uint64 lod, XE::float32 val )
{
	XE_ASSERT(lod < _Lods.size());
	
	_Lods[lod].first = val;
}

XE::float32 XE::LOD::GetUpperDistance( XE::uint64 lod )
{
	XE_ASSERT(lod < _Lods.size());
	
	return _Lods[lod].second;
}

void XE::LOD::SetUpperDistance( XE::uint64 lod, XE::float32 val )
{
	XE_ASSERT(lod < _Lods.size());
	
	_Lods[lod].second = val;
}

const XE::Array < XE::Pair < XE::float32, XE::float32>> &XE::LOD::GetLODs() const
{
	return _Lods;
}

void XE::LOD::SetLODs( const Array < Pair < XE::float32, XE::float32>> &val )
{
	_Lods = val;
}

XE::uint64 XE::LOD::GetLODLimits( XE::float32 val ) const
{
	for( int i = 0; i < _Lods.size(); ++i )
	{
		if( val > _Lods[i].first && val <= _Lods[i].second )
		{
			return static_cast<XE::uint64>(i);
		}
	}
	
	return 0;
}
