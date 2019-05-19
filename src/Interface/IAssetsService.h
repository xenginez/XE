/*!
 * \file   IAssetsService.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
#define __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A

#include "IService.h"

BEG_XE_NAMESPACE

class INTERFACE_API IAssetsService : public IService
{
	friend class Prefab;

	OBJECT( IAssetsService, IService )

public:
	IAssetsService();

	~IAssetsService() override;

public:
	virtual PrefabPtr Load( const String& val ) = 0;

	virtual PrefabPtr AsynLoad( const String& val ) = 0;

	virtual void Unload( const String& val ) = 0;

protected:
	virtual ObjectPtr GetAsset( const String& val ) const = 0;

	virtual AssetStatus GetAssetStatus( const String& val ) const = 0;

protected:
	PrefabPtr CreatePrefab( const String& val );
	
};

END_XE_NAMESAPCE

#endif // __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
