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

#include "Entity.h"

BEG_XE_NAMESPACE

class XE_API World : public XE::Object
{
	OBJECT( World, Object )

public:
	World();

	~World() override;

public:
	const String & GetName() const;

	void SetName( const String & val );

public:
	bool AddEntity( const EntityPtr & val );

	bool RemoveEntity( const EntityPtr & val );

	EntityPtr FindEntity( const String & val ) const;

	EntityPtr FindEntity( EntityHandle val ) const;

	const Array< EntityPtr > & GetEntitys() const;

public:
	void Startup();

	void Update( XE::float32 dt );

	void Clearup();

private:
	String _Name;
	Array< EntityPtr > _Entities;
	XE::EntityHandleAllocator _HandleTable;
};

END_XE_NAMESPACE

#endif // WORLD_H__BEE693B5_480D_4746_BBDA_EEECB0455761
