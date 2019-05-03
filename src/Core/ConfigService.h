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

class CORE_API ConfigService : public IConfigService
{
	OBJECT( ConfigService, IConfigService )

private:
	struct Private;

public:
	ConfigService();

	~ConfigService();

public:
	virtual bool Startup() override;

	virtual void Update() override;

	virtual void Clearup() override;

protected:
	virtual std::string GetValue( const std::string& key ) const override;

	virtual void SetValue( const std::string& key, const std::string& val ) const override;

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __CONFIGSERVICE_H__BB260BC9_0290_4E9A_8E4F_8E71164F6C69
