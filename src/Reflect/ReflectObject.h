/*!
 * \file	ReflectObject.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/03
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef REFLECTOBJECT_H__080637A5_D1CD_4182_81E3_57D5D2025E0D
#define REFLECTOBJECT_H__080637A5_D1CD_4182_81E3_57D5D2025E0D

#include "Variant.h"
#include "Archive.h"
#include "InvokeStack.h"
#include "ParameterType.hpp"

BEG_XE_NAMESPACE

class XE_API ReflectObject : public XE::GCObject
{
	template< typename T > friend struct MetaDataCollector;

public:
	static IMetaClassPtr GetMetaClassStatic();

	virtual IMetaClassPtr GetMetaClass() const;

public:
	ReflectObject();

	~ReflectObject() override;

public:
	Variant GetProperty( const String & name );

	void SetProperty( const String & name, const Variant & val );

	template< typename ... _Args > Variant Invoke( const String & name, _Args && ...args )
	{
		InvokeStack params( this, args... );

		if( auto method = GetMetaClass()->FindMethod( name, MakeParameterType<_Args...>() ) )
		{
			return method->Invoke( &params );
		}
	}

public:
	virtual ReflectObjectPtr Clone() const;

public:
	virtual void Serialize( Archive & val );

};

END_XE_NAMESPACE

#endif // REFLECTOBJECT_H__080637A5_D1CD_4182_81E3_57D5D2025E0D
