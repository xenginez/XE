/*!
 * \file	ScriptModule.h
 *
 * \author	ZhengYuanQing
 * \date	2021/02/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCRIPTMODULE_H__70A802F9_6119_49FE_B893_F334FC1A4B2D
#define SCRIPTMODULE_H__70A802F9_6119_49FE_B893_F334FC1A4B2D

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ScriptModule : public XE::Object
{
	OBJECT( ScriptModule, Object )

public:
	ScriptModule();

	~ScriptModule();

public:
	XE::IMetaModulePtr GetMetaModule() const;

public:
	static ScriptModulePtr LoadModule( const std::filesystem::path & path );

private:
	XE::String _Name;
	XE::uint64 _Start;

	XE::Array< int > _Customs;
	XE::Array< int > _Types;
	XE::Array< int > _Imports;
	XE::Array< int > _Functions;
	XE::Array< int > _Tables;
	XE::Array< int > _Memorys;
	XE::Array< int > _Globals;
	XE::Array< int > _Exports;
	XE::Array< int > _Elems;
	XE::Array< int > _Datas;

	XE::IMetaModulePtr _MetaModule;
};

END_XE_NAMESPACE

#endif // SCRIPTMODULE_H__70A802F9_6119_49FE_B893_F334FC1A4B2D
