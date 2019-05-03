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

class UTILS_API LOD
{
public:
	LOD();

	LOD( XE::uint64 val );

	~LOD();

public:
	XE::uint64 GetLODCount() const;

	void SetLODCount( XE::uint64 val );

	float GetLowerDistance( XE::uint64 lod );

	void SetLowerDistance( XE::uint64 lod, float val );

	float GetUpperDistance( XE::uint64 lod );

	void SetUpperDistance( XE::uint64 lod, float val );

	const Array<Pair<float, float>>& GetLODs() const;

	void SetLODs( const Array<Pair<float, float>> & val );

public:
	XE::uint64 GetLODLimits( float val ) const;
	
private:
	Array<Pair<float, float>> _Lods;
};
DECL_META_CLASS( UTILS_API, LOD );

END_XE_NAMESAPCE

#endif // __LOD_H__D82EC22B_03DB_4A27_BFFD_703E674481D2
