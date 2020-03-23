/*!
 * \file   Reflection.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __REFLECTION_H__7A09BEF6_4373_410D_94CD_7AF277A37AB3
#define __REFLECTION_H__7A09BEF6_4373_410D_94CD_7AF277A37AB3

#include "Type.h"

#include "CXXMetaEnum.hpp"
#include "CXXMetaClass.hpp"

BEG_XE_NAMESPACE

class XE_API Reflection : public XE::Singleton< Reflection >
{
public:
	struct Private;

public:
	Reflection();

	~Reflection();

public:
	template< typename T > struct Enum
	{
		static XE::SharedPtr<CXXMetaEnum<T>> Get()
		{
			return SP_CAST<CXXMetaEnum<T>>( EnumID<T>::Get() );
		}
	};

	template< typename T > struct Class
	{
		static XE::SharedPtr<CXXMetaClass<T>> Get()
		{
			return SP_CAST<CXXMetaClass<T>>( ClassID<T>::Get() );
		}
	};

public:
	static void Clear();

public:
	static void RegisterMetaInfo( IMetaInfoPtr val );

public:
	static void VisitMeta( const std::function<void( IMetaInfoPtr )> & val );

	static void VisitType( const std::function<void( IMetaTypePtr )> & val );

	static void VisitEnum( const std::function<void( IMetaEnumPtr )> & val );

	static void VisitClass( const std::function<void( IMetaClassPtr )> & val );

	static void VisitMethod( const  std::function<void( IMetaMethodPtr )> & val );

	static void VisitProperty( const std::function<void( IMetaPropertyPtr )> & val );

	static void VisitOperator( const std::function<void( IMetaOperatorPtr )> & val );

public:
	static IMetaInfoPtr FindMeta( const String & FullName );

	static IMetaTypePtr FindType( const String & FullName );

	static IMetaEnumPtr FindEnum( const String& FullName );

	static IMetaClassPtr FindClass( const String& FullName );

	static IMetaPropertyPtr FindProperty( const String& FullName );

	static IMetaOperatorPtr FindOperator( const String& FullName, const IMetaInfoPtr& Type = nullptr );

	static IMetaMethodPtr FindMethod( const String& FullName, const ParameterType& Types = MakeParameterType() );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __REFLECTION_H__7A09BEF6_4373_410D_94CD_7AF277A37AB3
