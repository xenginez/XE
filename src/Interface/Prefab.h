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

#include "IAssetsService.h"

BEG_XE_NAMESPACE

class XE_API Prefab : public std::enable_shared_from_this< Prefab >
{
public:
	Prefab( IAssetsServicePtr val, const String& link );

public:
	const String& GetLink() const;
	
	AssetStatus GetStatus() const;

public:
	template< typename T > std::shared_ptr<T> GetClone() const
	{
		return GetStatus() == AssetStatus::Ready ? Cloneable<T>::Clone( dynamic_cast< T * >( _Service->GetAsset( _Link ).get() ) ) : nullptr;
	}

	template< typename T > std::shared_ptr<const T> GetReference() const
	{
		return DP_CAST<const T>( GetStatus() == AssetStatus::Ready ? _Service->GetAsset( _Link ) : nullptr );
	}

private:
	String _Link;
	IAssetsServicePtr _Service;
};

END_XE_NAMESPACE

#endif // __PREFAB_H__A6AEEDC5_FCE5_4139_8B44_6A57BEB2DD7F
