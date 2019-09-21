/*!
 * \file   LOD.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/19
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LOD_H__D82EC22B_03DB_4A27_BFFD_703E674481D2
#define __LOD_H__D82EC22B_03DB_4A27_BFFD_703E674481D2

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API LOD
{
public:
	LOD();

	LOD( XE::uint64 val );

	~LOD();

public:
	XE::uint64 GetLODCount() const;

	void SetLODCount( XE::uint64 val );

	XE::float32 GetLowerDistance( XE::uint64 lod );

	void SetLowerDistance( XE::uint64 lod, XE::float32 val );

	XE::float32 GetUpperDistance( XE::uint64 lod );

	void SetUpperDistance( XE::uint64 lod, XE::float32 val );

	const Array<Pair<XE::float32, XE::float32>>& GetLODs() const;

	void SetLODs( const Array<Pair<XE::float32, XE::float32>> & val );

public:
	XE::uint64 GetLODLimits( XE::float32 val ) const;
	
private:
	Array<Pair<XE::float32, XE::float32>> _Lods;
};
DECL_META_CLASS( XE_API, LOD );

END_XE_NAMESPACE

#endif // __LOD_H__D82EC22B_03DB_4A27_BFFD_703E674481D2
