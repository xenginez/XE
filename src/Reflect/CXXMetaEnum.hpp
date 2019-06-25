/*!
 * \file   CXXMetaEnum.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CXXMETAENUM_HPP__1D036321_0050_4C40_8B6D_4EDFD9A417F4
#define __CXXMETAENUM_HPP__1D036321_0050_4C40_8B6D_4EDFD9A417F4

#include "IMetaEnum.h"

#include "Archive.h"

BEG_XE_NAMESPACE

template< typename T > class CXXMetaEnum : public IMetaEnum
{
public:
	CXXMetaEnum( const String& Name, IMetaInfoPtr Owner )
		:IMetaEnum( Name, sizeof( T ), Owner )
	{

	}

public:
	void Value( const String& Name, T val )
	{
		_RegisterValue( Name, (XE::int64)val );
	}
};

END_XE_NAMESPACE

#endif // __CXXMETAENUM_HPP__1D036321_0050_4C40_8B6D_4EDFD9A417F4
