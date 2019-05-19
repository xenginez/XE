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

class INTERFACE_API Prefab
{
	friend class IAssetsService;

private:
	Prefab( IAssetsServicePtr val, const String& link );

public:
	ObjectPtr GetClone() const;

	ObjectCPtr GetReference() const;

public:
	const String& GetLink() const;
	
	AssetStatus GetStatus() const;

public:
	template< typename T > std::shared_ptr<T> GetCloneT() const
	{
		return DP_CAST<T>( GetClone() );
	}

	template< typename T > std::shared_ptr<const T> GetReferenceT() const
	{
		return DP_CAST<const T>( GetReference() );
	}

private:
	String _Link;
	IAssetsServicePtr _Service;
};

END_XE_NAMESAPCE

#endif // __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
