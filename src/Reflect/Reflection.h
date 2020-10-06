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
	SINGLETON( Reflection )

public:
	struct Private;

private:
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

#define BEG_META( CLASS ) \
namespace XE \
{ \
	template<> struct MetaDataCollector< CLASS > \
	{ \
		typedef CLASS ThisType; \
		MetaDataCollector() \
		{ \
			auto type = std::conditional_t< std::is_enum< ThisType >::value, XE::Reflection::Enum< ThisType >, XE::Reflection::Class< ThisType > >::Get();

#define END_META() \
			XE::Reflection::RegisterMetaInfo( type ); \
		} \
		static void Use() \
		{ \
			XE::ActiveSingleton< XE::MetaDataCollector<ThisType> >::Register(); \
		} \
	}; \
};

#define IMPLEMENT_META(CLASS) BEG_META(CLASS) END_META()

#define OBJECT_2(_CLASS, _SUPER) \
	template< typename T > friend struct XE::MetaDataCollector; \
public: \
    typedef _SUPER Super; \
	static XE::IMetaClassPtr GetMetaClassStatic() \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, XE::ClassID<_SUPER>::Get(), nullptr ); \
		return p; \
	} \
	virtual XE::IMetaClassPtr GetMetaClass() const \
	{ \
		return GetMetaClassStatic(); \
	} \
private:
#define OBJECT_1(_CLASS) \
	template< typename T > friend struct XE::MetaDataCollector; \
public: \
	static XE::IMetaClassPtr GetMetaClassStatic() \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr ); \
		return p; \
	} \
	virtual XE::IMetaClassPtr GetMetaClass() const \
	{ \
		return GetMetaClassStatic(); \
	} \
private:
#define OBJECT(...)            MACRO_EXP_(MACRO_GLUE(OBJECT_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#endif // __REFLECTION_H__7A09BEF6_4373_410D_94CD_7AF277A37AB3
