/*!
 * \file	ScriptObject.h
 *
 * \author	ZhengYuanQing
 * \date	2021/02/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2
#define SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2

#include "Type.h"

#include "Interface/Object.h"

BEG_XE_NAMESPACE

class XE_API ScriptObject : public XE::Object
{
	OBJECT( ScriptObject, Object )

public:
	ScriptObject();

	~ScriptObject();

};

END_XE_NAMESPACE

#endif // SCRIPTOBJECT_H__92832766_DA69_4626_8258_F838B65D1DC2
