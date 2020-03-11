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

class XE_API IAssetsService : public IService
{
	OBJECT( IAssetsService, IService )

public:
	IAssetsService();

	~IAssetsService() override;

public:
	virtual ObjectPtr Load( const String & val ) = 0;

	virtual void AsynLoad( const String & val ) = 0;

public:
	virtual ObjectPtr GetAsset( const String & val ) const = 0;

	virtual AssetStatus GetAssetStatus( const String & val ) const = 0;

};

END_XE_NAMESPACE

#endif // __IASSETSSERVICE_H__2BEDDFA1_6F1E_46E9_951D_60D1D4DC6B7A
