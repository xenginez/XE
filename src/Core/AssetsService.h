/*!
 * \file   AssetsService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/13
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ASSETSSERVICE_H__68A7444E_AF99_4A9A_804F_B524B90E80EC
#define __ASSETSSERVICE_H__68A7444E_AF99_4A9A_804F_B524B90E80EC

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AssetsService : public IAssetsService
{
	OBJECT( AssetsService, IAssetsService )

private:
	struct Private;

public:
	static constexpr XE::float32 AssetCacheTime = 120.0f; // 2 minutes

public:
	AssetsService();

	~AssetsService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	ObjectPtr Load( const String & val ) override;

	void AsyncLoad( const String & val ) override;

public:
	ObjectPtr GetAsset( const String & val ) const override;

	AssetStatus GetAssetStatus( const String & val ) const override;

public:
	void ResetMD5Cache();

protected:
	virtual XE::ObjectPtr SearchAssetData( const XE::String & val ) const;

private:
	XE::ObjectPtr LoadAsset( const XE::String & val );

	XE::MD5 PathToMD5( const XE::String & val ) const;

	void SetAssetStatus( const XE::MD5 & md5, const XE::ObjectPtr & asset, AssetStatus status );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __ASSETSSERVICE_H__68A7444E_AF99_4A9A_804F_B524B90E80EC
