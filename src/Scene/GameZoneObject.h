/*!
 * \file   GameZoneObject.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef GAMEZONEOBJECT_H__3E5FE61C_19D7_41FF_BA1D_4FEBEFE23F1C
#define GAMEZONEOBJECT_H__3E5FE61C_19D7_41FF_BA1D_4FEBEFE23F1C

#include "SceneObject.h"

BEG_XE_NAMESPACE

class XE_API GameZoneObject : public XE::SceneObject
{
	OBJECT( GameZoneObject, SceneObject )

public:
	GameZoneObject();

	~GameZoneObject();

public:
	void InsertObject( const XE::SceneObjectHandle & val );

	void RemoveObject( const XE::SceneObjectHandle & val );

	const XE::Array< XE::SceneObjectHandle > & GetChildren() const;

protected:
	void OnEnable() override;

	void OnDisable() override;

private:
	XE::Array< bool > _ChildrenEnable;
	XE::Array< XE::SceneObjectHandle > _Children;
};

END_XE_NAMESPACE

#endif // GAMEZONEOBJECT_H__3E5FE61C_19D7_41FF_BA1D_4FEBEFE23F1C
