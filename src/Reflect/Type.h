/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__69A9E04E_44A6_4DEE_B145_845B7E13E31C
#define __TYPE_H__69A9E04E_44A6_4DEE_B145_845B7E13E31C

#include "GC/GC.h"

BEG_XE_NAMESPACE

DECL_PTR( ReflectObject );
DECL_PTR( IMetaInfo );
DECL_PTR( IMetaType );
DECL_PTR( IMetaEnum );
DECL_PTR( IMetaClass );
DECL_PTR( IMetaMethod );
DECL_PTR( IMetaProperty );
DECL_PTR( IMetaOperator );

enum class MetaType
{
	ENUM,
	CLASS,
	METHOD,
	PROPERTY,
	OPERATOR,
};

enum class ArchiveType
{
	LOAD,
	SAVE,
};

class XE_API MetaException : public XE::RuntimeException
{
public:
	MetaException( IMetaInfoCPtr Meta, const String& Msg );

	~MetaException();

public:
	virtual char const* What() const;

public:
	IMetaInfoCPtr GetMetaInfo() const;

private:
	String _Msg;
	IMetaInfoCPtr _Meta;
};

template <class T> class ActiveSingleton
{
public:
	static ActiveSingleton<T>& Register()
	{
		static ActiveSingleton<T> t;

		Use( _Reference );

		return t;
	}

private:
	static void Use( T * )
	{
	}

	static void Use( ActiveSingleton<T> const & )
	{
		T Collector;
		Use( &Collector );
	}

private:
	static ActiveSingleton<T> & _Reference;
};
template<class T> ActiveSingleton<T> & ActiveSingleton<T>::_Reference = ActiveSingleton<T>::Register();
template< typename T > struct MetaDataCollector;

END_XE_NAMESPACE

#endif // __TYPE_H__69A9E04E_44A6_4DEE_B145_845B7E13E31C
