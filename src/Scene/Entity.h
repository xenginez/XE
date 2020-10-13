/*!
 * \file	Entity.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A
#define ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A


#include "Math/Math.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Entity : public XE::Object
{
	OBJECT( Entity, Object )

private:
	friend class World;

public:
	Entity();

	~Entity();

public:
	bool GetEnable() const;

	void SetEnable( bool val );

	const String & GetName() const;

	void SetName( const String & val );

protected:
	virtual void Startup() = 0;

	virtual void Update( XE::float32 dt ) = 0;

	virtual void Clearup() = 0;

protected:
	virtual void OnEnable() = 0;

	virtual void OnDisable() = 0;

public:
	XE::EntityHandle GetHandle() const;

private:
	bool _Enable;
	XE::String _Name;
	XE::EntityHandle _Handle;
};

END_XE_NAMESPACE

#endif // ENTITY_H__C84CE01E_E4FF_4530_B337_D1B9F4DBEF7A
