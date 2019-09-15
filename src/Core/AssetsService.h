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

class CORE_API AssetsService : public IAssetsService
{
	OBJECT( AssetsService, IAssetsService )

private:
	struct Private;

public:
	static constexpr XE::float32 AssetCacheTime = 60.0f; // 1 minutes

public:
	AssetsService();

	~AssetsService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	PrefabPtr Load( const String & val ) override;

	PrefabPtr AsynLoad( const String & val ) override;

	void Unload( const String & val ) override;

protected:
	ObjectPtr GetAsset( const String & val ) const override;

	AssetStatus GetAssetStatus( const String & val ) const override;

private:
	void LoadAsset( const String & val );

	void UnloadAsset( const String & val );

	FArray<String> GetDependent( const String & val ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __ASSETSSERVICE_H__68A7444E_AF99_4A9A_804F_B524B90E80EC
