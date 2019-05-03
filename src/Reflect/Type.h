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

#include "Global.h"

BEG_XE_NAMESPACE

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

class REFLECT_API MetaException : public RuntimeException
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

IMetaTypePtr REFLECT_API GetReclectionType( const String& val );

END_XE_NAMESAPCE

#endif // __TYPE_H__69A9E04E_44A6_4DEE_B145_845B7E13E31C
