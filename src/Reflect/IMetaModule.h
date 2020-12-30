/*!
 * \file	IMetaModule.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IMETAMODULE_H__1E0F37E8_64B1_4FE5_B030_88A6326CB205
#define IMETAMODULE_H__1E0F37E8_64B1_4FE5_B030_88A6326CB205

#include <functional>

#include "IMetaInfo.h"

BEG_XE_NAMESPACE

class XE_API IMetaModule : public XE::IMetaInfo
{
public:
	IMetaModule( const String & Name, IMetaInfoPtr Owner );

	~IMetaModule();

public:
	XE::IMetaInfoPtr FindMetaInfo( const String & val ) const;

	void Visit( const std::function<void( XE::IMetaInfoPtr )> & val ) const;

private:
	XE::Array<XE::IMetaInfoPtr> _MetaInfos;
};

END_XE_NAMESPACE

#define DECL_META_MODULE(_DLL_EXPORT) _DLL_EXPORT XE::IMetaModulePtr GetModule();


#define IMPLEMENT_META_MODULE_1( _MODULE ) \
namespace _MODULE \
{ \
	XE::IMetaModulePtr GetModule() \
	{ \
		static XE::IMetaModulePtr _Module = XE::MakeShared<XE::IMetaModule>( #_MODULE, nullptr ); \
		return _Module; \
	} \
	struct MetaDataCollector##_MODULE \
	{ \
		MetaDataCollector##_MODULE() \
		{ \
			XE::Reflection::RegisterMetaInfo( _MODULE::GetModule() ); \
		} \
		static void Use() \
		{ \
			XE::ActiveSingleton< _MODULE::MetaDataCollector##_MODULE >::Register(); \
		} \
	}; \
}

#define IMPLEMENT_META_MODULE_2( _MODULE, _OWNER ) \
namespace _MODULE \
{ \
	XE::IMetaModulePtr GetModule() \
	{ \
			static XE::IMetaModulePtr _Module = XE::MakeShared<XE::IMetaModule>( #_MODULE, _OWNER::GetModule() ); \
		return _Module; \
	} \
	struct MetaDataCollector##_MODULE \
	{ \
		MetaDataCollector##_MODULE() \
		{ \
			XE::Reflection::RegisterMetaInfo( _MODULE::GetModule() ); \
		} \
		static void Use() \
		{ \
			XE::ActiveSingleton< _MODULE::MetaDataCollector##_MODULE >::Register(); \
		} \
	}; \
}
#define IMPLEMENT_META_MODULE(...)            MACRO_EXP_(MACRO_GLUE(IMPLEMENT_META_MODULE_,MACRO_ARGS_CONTER(__VA_ARGS__))(__VA_ARGS__))

XE_API XE::IMetaModulePtr GetModule();

BEG_XE_NAMESPACE
	DECL_META_MODULE( XE_API );
END_XE_NAMESPACE

#endif // IMETAMODULE_H__1E0F37E8_64B1_4FE5_B030_88A6326CB205
