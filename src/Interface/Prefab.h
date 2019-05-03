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

#include "Object.h"

BEG_XE_NAMESPACE

class INTERFACE_API Prefab : public Object
{
	OBJECT( Prefab, Object )

public:
	Prefab();

	Prefab( IAssetsServicePtr val, const String& link );

	~Prefab();

public:
	ObjectPtr GetClone() const;

	ObjectPtr GetReference() const;

public:
	AssetStatus GetStatus() const;

	const String& GetLink() const;

public:
	template< typename T > std::shared_ptr<T> GetCloneT() const
	{
		return DP_CAST<T>( GetClone() );
	}

	template< typename T > std::shared_ptr<T> GetReferenceT() const
	{
		return DP_CAST<T>( GetReference() );
	}

private:
	String _Link;
	IAssetsServicePtr _Service;
};

END_XE_NAMESAPCE

#endif // __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
