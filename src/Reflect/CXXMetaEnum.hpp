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
		_RegisterValue( Name, val );
	}
};

END_XE_NAMESPACE

#define DECL_META_ENUM(_DLL_EXPORT, ENUM) \
template<> struct _DLL_EXPORT XE::EnumID<ENUM> \
{ \
	static XE::IMetaEnumPtr Get( const ENUM * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaEnum<ENUM> >( #ENUM, nullptr ); \
		return p; \
	} \
}

#define DECL_META_ENUM_P(ENUM) \
template<> struct XE::EnumID<ENUM> \
{ \
	static XE::IMetaEnumPtr Get( const ENUM * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaEnum<ENUM> >( #ENUM, nullptr ); \
		return p; \
	} \
}

#endif // __CXXMETAENUM_HPP__1D036321_0050_4C40_8B6D_4EDFD9A417F4
