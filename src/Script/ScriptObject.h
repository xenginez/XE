/*!
 *file	ScriptObject.h
 *
 *author	ZhengYuanQing
 *date	2021/02/25
 *email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2
#define SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ScriptObject : public XE::Object
{
public:
	template< typename T > friend struct XE::MetaDataCollector;

public:
	typedef void ( *FinalizeCallbackType )( ScriptObject * );

public:
	static XE::IMetaClassPtr GetMetaClassStatic();

	virtual XE::IMetaClassPtr GetMetaClass() const;

public:
	ScriptObject();

	~ScriptObject();

public:
	XE::ScriptGCMarker GetMarker() const;

	void SetMarker( XE::ScriptGCMarker val );

	FinalizeCallbackType GetFinalizeCallback() const;

	void SetFinalizeCallback( FinalizeCallbackType val );

	void SetMetaClass( const XE::IMetaClassPtr & val );

private:
	XE::IMetaClassPtr _MetaClass = nullptr;
	FinalizeCallbackType _Finalize = nullptr;
	XE::ScriptGCMarker _Marker = ScriptGCMarker::WHITE1;
};

END_XE_NAMESPACE

#endif // SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2
