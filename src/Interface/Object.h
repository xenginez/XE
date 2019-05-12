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

#include "Type.h"

BEG_XE_NAMESPACE

class IFramework;

class INTERFACE_API Object : public std::enable_shared_from_this< Object >, public XE::NonCopyable
{
	OBJECT( Object )

public:
	Object();

	virtual ~Object();

public:
	Variant GetProperty( const String& name );

	void SetProperty( const String& name, const Variant& val );

public:
	virtual ObjectPtr Clone() const;

public:
	virtual void Load( Archive &val );

	virtual void Save( Archive &val ) const;

public:
	String tr( const String& val ) const;
	
private:
	IFrameworkPtr _Framework;
};

END_XE_NAMESAPCE

#endif // __OBJECT_H__E9308405_DB33_49CC_953A_8011B015CAA9
