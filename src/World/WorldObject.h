/*!
 * \file   WorldObject.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD
#define __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD

#include "Type.h"

BEG_XE_NAMESPACE

class WorldService;

class WORLD_API WorldObject : public Object
{
	OBJECT( WorldObject, Object )

public:
	friend class WorldService;

public:
	WorldObject();

	~WorldObject();

public:
	const String& GetName() const;

	void SetName( const String& val );

	IFrameworkPtr GetFramework() const;

	void SetFramework( IFrameworkPtr val );

public:
	GameObjectPtr AddGameObject();

	GameObjectPtr FindGameObject( const String& val ) const;

	GameObjectPtr FindGameObject( GameObjectHandle val ) const;

	const Array< GameObjectPtr >& GetGameObjects() const;

protected:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

private:
	String _Name;
	IFrameworkPtr _Framework;
	Array< GameObjectPtr > _AllGameObjects;
	UnorderedMap< XE::uint64, GameObjectPtr > _GameObjectMap;
};

END_XE_NAMESPACE

#endif // __WORLDOBJECT_H__F419FF88_F84C_4C18_AC3A_D1660070EABD
