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
	CXXMetaEnum( const String& Name, IMetaInfoPtr Owner, IMetaModulePtr Module )
		:IMetaEnum( Name, sizeof( T ), Owner, Module )
	{

	}

public:
	void Value( const String& Name, T val )
	{
		_RegisterValue( Name, val );
	}
};

END_XE_NAMESPACE

#define DECL_META_ENUM(_DLL_EXPORT, _ENUM) \
template<> struct _DLL_EXPORT ::XE_EnumID< _ENUM > \
{ \
	static XE::IMetaEnumPtr Get( const _ENUM * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaEnum< _ENUM > >( #_ENUM, nullptr, GetModule() ); \
		return p; \
	} \
}

#endif // __CXXMETAENUM_HPP__1D036321_0050_4C40_8B6D_4EDFD9A417F4
