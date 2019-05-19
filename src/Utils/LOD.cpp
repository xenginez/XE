#include "LOD.h"

USING_XE

BEG_META(LOD)
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

float XE::LOD::GetLowerDistance( XE::uint64 lod )
{
	XE_ASSERT(lod < _Lods.size());
	
	return _Lods[lod].first;
}

void XE::LOD::SetLowerDistance( XE::uint64 lod, float val )
{
	XE_ASSERT(lod < _Lods.size());
	
	_Lods[lod].first = val;
}

float XE::LOD::GetUpperDistance( XE::uint64 lod )
{
	XE_ASSERT(lod < _Lods.size());
	
	return _Lods[lod].second;
}

void XE::LOD::SetUpperDistance( XE::uint64 lod, float val )
{
	XE_ASSERT(lod < _Lods.size());
	
	_Lods[lod].second = val;
}

const XE::Array < XE::Pair < float, float>> &XE::LOD::GetLODs() const
{
	return _Lods;
}

void XE::LOD::SetLODs( const Array < Pair < float, float>> &val )
{
	_Lods = val;
}

XE::uint64 LOD::GetLODLimits( float val ) const
{
	for( int i = 0; i < _Lods.size(); ++i )
	{
		if( val > _Lods[i].first && val <= _Lods[i].second )
		{
			return static_cast<uint64>(i);
		}
	}
	
	return 0;
}
