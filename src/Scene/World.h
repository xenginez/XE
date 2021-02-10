/*!
 * \file	World.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef WORLD_H__BEE693B5_480D_4746_BBDA_EEECB0455761
#define WORLD_H__BEE693B5_480D_4746_BBDA_EEECB0455761

#include "SceneObject.h"

BEG_XE_NAMESPACE

class XE_API World final : public XE::Object
{
	OBJECT( World, Object )

public:
	World();

	~World() override;

public:
	const String & GetName() const;

	void SetName( const String & val );

public:
	bool AddObject( const SceneObjectPtr & val );

	bool RemoveObject( const SceneObjectPtr & val );

	SceneObjectPtr FindObject( const String & val ) const;

	SceneObjectPtr FindObject( SceneObjectHandle val ) const;

	const Array< SceneObjectPtr > & GetObjects() const;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

public:
	XE::Transform & GetTransform();

private:
	String _Name;
	XE::Transform _Transform;
	Array< SceneObjectPtr > _Objects;
	XE::SceneObjectHandleAllocator _HandleTable;

};

END_XE_NAMESPACE

#endif // WORLD_H__BEE693B5_480D_4746_BBDA_EEECB0455761
