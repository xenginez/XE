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
	ComponentHandle GetHandle() const;

	GameObjectPtr GetGameObject() const;

public:
	bool GetUpdate() const;

	void SetUpdate( bool val );

	bool GetEnabled() const;

	void SetEnabled( bool val );

	const String & GetName() const;

	void SetName( const String & val );

protected:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnClearup();

public:
	String _Name;
	bool _Update;
	bool _Enabled;
	ComponentHandle _Handle;
	GameObjectWPtr _GameObject;
};

END_XE_NAMESPACE

#endif // __COMPONENT_H__42D4DE3A_B463_45F4_9181_C554B1A57D9E
