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

public:
	virtual ObjectPtr Clone() const;

public:
	virtual void Serialize( Archive &val );

};

END_XE_NAMESPACE

#endif // __OBJECT_H__E9308405_DB33_49CC_953A_8011B015CAA9
