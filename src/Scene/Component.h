/*!
 * \file   Component.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COMPONENT_H__42D4DE3A_B463_45F4_9181_C554B1A57D9E
#define __COMPONENT_H__42D4DE3A_B463_45F4_9181_C554B1A57D9E

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Component : public XE::Object
{
	OBJECT( Component, Object )

	friend class GameObject;

public:
	Component();

	virtual ~Component();

public:
	XE::ComponentHandle GetHandle() const;

public:
	XE::WorldPtr GetWorld() const;

	XE::GameObjectPtr GetGameObject() const;

public:
	bool GetEnabled() const;

	void SetEnabled( bool val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

protected:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void LateUpdate( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnLateUpdate( XE::float32 dt );

	virtual void OnClearup();

private:
	XE::String _Name;
	bool _Enabled;
	XE::WorldWPtr _World;
	XE::ComponentHandle _Handle;
	XE::GameObjectWPtr _GameObject;
};

END_XE_NAMESPACE

#endif // __COMPONENT_H__42D4DE3A_B463_45F4_9181_C554B1A57D9E
