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
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

public:
	bool AddObject( const XE::SceneObjectPtr & val );

	bool RemoveObject( const XE::SceneObjectPtr & val );

	XE::SceneObjectPtr FindObject( const XE::String & val ) const;

	XE::SceneObjectPtr FindObject( XE::SceneObjectHandle val ) const;

	const XE::Array< XE::SceneObjectPtr > & GetObjects() const;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

public:
	XE::Transform & GetTransform();

private:
	XE::String _Name;
	XE::Transform _Transform;
	XE::Array< XE::SceneObjectPtr > _Objects;
	XE::SceneObjectHandleAllocator _HandleAllocator;

};

END_XE_NAMESPACE

#endif // WORLD_H__BEE693B5_480D_4746_BBDA_EEECB0455761
