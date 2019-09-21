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
		static std::shared_ptr<CXXMetaEnum<T>> Get()
		{
			return SP_CAST<CXXMetaEnum<T>>( EnumID<T>::Get() );
		}
	};

	template< typename T > struct Class
	{
		static std::shared_ptr<CXXMetaClass<T>> Get()
		{
			return SP_CAST<CXXMetaClass<T>>( ClassID<T>::Get() );
		}
	};

public:
	static void Clear();

public:
	static void RegisterMetaInfo( IMetaInfoPtr val );

public:
	static void VisitMeta( std::function<void( IMetaInfoPtr )> val );

	static void VisitEnum( std::function<void( IMetaEnumPtr )> val );

	static void VisitClass( std::function<void( IMetaClassPtr )> val );

	static void VisitMethod( std::function<void( IMetaMethodPtr )> val );

	static void VisitProperty( std::function<void( IMetaPropertyPtr )> val );

	static void VisitOperator( std::function<void( IMetaOperatorPtr )> val );

public:
	static IMetaInfoPtr FindMeta( const String & FullName );

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
