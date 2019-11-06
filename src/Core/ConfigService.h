/*!
 * \file   ConfigService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/04
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CONFIGSERVICE_H__BB260BC9_0290_4E9A_8E4F_8E71164F6C69
#define __CONFIGSERVICE_H__BB260BC9_0290_4E9A_8E4F_8E71164F6C69

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API ConfigService : public IConfigService
{
	OBJECT( ConfigService, IConfigService )

private:
	struct Private;

public:
	ConfigService();

	~ConfigService() override;

public:
	void Prepare() override;

	bool Startup() override;

	void Update() override;

	void Clearup() override;

public:
	void Save() override;

	void Reload() override;

protected:
	void Save( const std::filesystem::path & path, const Map < String, String > & values ) const;

	void Reload( const std::filesystem::path & path, Map < String, String > & values ) const;

protected:
	String GetValue( const String & key ) override;

	void SetValue( const String & key, const String & val ) override;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __CONFIGSERVICE_H__BB260BC9_0290_4E9A_8E4F_8E71164F6C69
