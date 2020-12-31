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
	AssetsService();

	~AssetsService() override;

public:
	void Prepare()override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	XE::MemoryView Load( const std::filesystem::path & path ) override;

	void AsyncLoad( const std::filesystem::path & path, const LoadFinishCallback & callback ) override;

public:
	XE::ObjectPtr LoadObject( const std::filesystem::path & path ) override;

	void AsyncLoadObject( const std::filesystem::path & path, const LoadObjectFinishCallback & callback ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __ASSETSSERVICE_H__68A7444E_AF99_4A9A_804F_B524B90E80EC
