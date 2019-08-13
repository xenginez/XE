/*!
 * \file   Object.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __OBJECT_H__E9308405_DB33_49CC_953A_8011B015CAA9
#define __OBJECT_H__E9308405_DB33_49CC_953A_8011B015CAA9

#include "Variant.h"
#include "Archive.h"
#include "InvokeStack.h"
#include "ParameterType.hpp"

BEG_XE_NAMESPACE

class REFLECT_API Object : public std::enable_shared_from_this< Object >, public XE::NonCopyable
{
	template< typename T > friend struct MetaDataCollector;

public:
	static const IMetaClassPtr GetMetaClassStatic();

	virtual const IMetaClassPtr GetMetaClass() const;

public:
	Object();

	virtual ~Object();

public:
	Variant GetProperty( const String& name );

	void SetProperty( const String& name, const Variant& val );

	template< typename ... _Args > Variant Invoke( const String & name, _Args && ...args )
	{
		InvokeStack params( this, args.. );

		if( auto method = GetMetaClass()->FindMethod( name, MakeParameterType<_Args...>() ) )
		{
			return method->Invoke( &params );
		}
	}

public:
	virtual ObjectPtr Clone() const;

public:
	virtual void Serialize( Archive &val );

};

END_XE_NAMESPACE

#endif // __OBJECT_H__E9308405_DB33_49CC_953A_8011B015CAA9
