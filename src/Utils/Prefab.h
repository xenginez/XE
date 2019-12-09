/*!
 * \file   Prefab.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/13
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
#define __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Prefab
{
public:
	Prefab();

	virtual ~Prefab();
	
public:
	const String & GetLink() const;

	void SetLink( const XE::String & val );
	
public:
	AssetStatus GetStatus() const;

protected:
	ReflectObjectPtr GetReference() const;
	
private:
	String _Link;
};
DECL_META_CLASS( XE_API, Prefab );

template< typename T > class PrefabPtr : public XE::Prefab
{
public:
	PrefabPtr() = default;

	~PrefabPtr() override = default;

public:
	PrefabPtr( const Prefab & val )
	{
		SetLink( val.GetLink() );
	}

	PrefabPtr & operator=( const Prefab & val )
	{
		if( GetLink() != val.GetLink() )
		{
			_Object = nullptr;
			SetLink( val.GetLink() );
		}

		return *this;
	}

public:
	XE::SharedPtr<T> GetClone() const
	{
		if( _Object )
		{
			return XE::Cloneable<T>::Clone( _Object );
		}

		_Object = GetReference();

		if( _Object )
		{
			return XE::Cloneable<T>::Clone( _Object );
		}

		return nullptr;
	}

	XE::SharedPtr<const T> GetReference() const
	{
		if( _Object )
		{
			return _Object;
		}

		auto ref = Prefab::GetReference();

		if( ref && ref->GetMetaClass()->CanConvert( XE::ClassID<T>::Get() ) )
		{
			_Object = DP_CAST<const T>( ref );
		}

		return _Object;
	}

private:
	XE::SharedPtr<const T> _Object;
};

END_XE_NAMESPACE


template< typename T > struct XE::ClassID< XE::PrefabPtr<T> >
{
	static IMetaClassPtr Get( const PrefabPtr<T> * val = nullptr )
	{
		return ClassID<Prefab>::Get();
	}
};

#endif // __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
