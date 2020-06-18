/*!
 * \file	Reflect.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef REFLECT_H__DB8AE6CB_8BEE_4A58_B0E8_02BA454A5BF3
#define REFLECT_H__DB8AE6CB_8BEE_4A58_B0E8_02BA454A5BF3

#include "TypeID.hpp"
#include "CXXMetaEnum.hpp"
#include "CXXMetaClass.hpp"
#include "CXXMetaMethod.hpp"
#include "CXXMetaProperty.hpp"
#include "CXXMetaOperator.hpp"

#include "Reflection.h"
#include "ReflectObject.h"

#include "Variant.h"
#include "InvokeStack.h"
#include "ParameterType.hpp"


#define OVERLOAD(TYPE, FUNC) (TYPE)&FUNC

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

#define DECL_META_CLASS_3(_DLL_EXPORT, _CLASS, _SUPER) \
template<> struct _DLL_EXPORT XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, XE::ClassID<_SUPER>::Get(), nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_2(_DLL_EXPORT, _CLASS) \
template<> struct _DLL_EXPORT XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS(...)            MACRO_EXP_(MACRO_GLUE(DECL_META_CLASS_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

#define DECL_META_CLASS_P_2(_CLASS, _SUPER) \
template<> struct XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, XE::ClassID<_SUPER>::Get(), nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_P_1(_CLASS) \
template<> struct XE::ClassID<_CLASS> \
{ \
	static XE::IMetaClassPtr Get( const _CLASS * val = nullptr ) \
	{ \
		static auto p = XE::MakeShared< XE::CXXMetaClass<_CLASS> >( #_CLASS, nullptr, nullptr ); \
		return p; \
	} \
}
#define DECL_META_CLASS_P(...)            MACRO_EXP_(MACRO_GLUE(DECL_META_CLASS_P_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

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

#endif // REFLECT_H__DB8AE6CB_8BEE_4A58_B0E8_02BA454A5BF3
