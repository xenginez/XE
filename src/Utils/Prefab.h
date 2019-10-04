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

class XE_API Prefab : public std::enable_shared_from_this< Prefab >
{
public:
	Prefab();

	virtual ~Prefab();
	
public:
	const String & GetLink() const;

	void SetLink( const XE::String & val );
	
public:
	AssetStatus GetStatus() const;

public:
	template< typename T > std::shared_ptr<T> GetCloneT() const
	{
		if( auto clone = GetClone() )
		{
			return DP_CAST<T>( clone );
		}
		
		return nullptr;
	}

	template< typename T > std::shared_ptr<const T> GetReferenceT() const
	{
		if(auto ref = GetReference())
		{
			return DP_CAST<const T>( ref );
		}
		
		return nullptr;
	}

public:
	ReflectObjectPtr GetClone() const;
	
	ReflectObjectPtr GetReference() const;
	
private:
	String _Link;
};
DECL_META_CLASS( XE_API, Prefab );

END_XE_NAMESPACE

#endif // __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
