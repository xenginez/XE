/*!
 * \file   IPluginService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/04
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IPLUGINSERVICE_H__9FB84A70_984B_4C87_B3F1_1C4FE97D7C14
#define __IPLUGINSERVICE_H__9FB84A70_984B_4C87_B3F1_1C4FE97D7C14

#include "IService.h"

BEG_XE_NAMESPACE

class XE_API IPlugin
{
public:
	IPlugin( IFrameworkPtr framework );

	virtual ~IPlugin();

public:
	virtual String GetName() const = 0;

public:
	virtual void Startup() = 0;

	virtual void Clearup() = 0;

protected:
	IFrameworkPtr GetFramework() const;

private:
	IFrameworkPtr _Framework;
};

class XE_API IPluginService : public IService
{
	OBJECT( IPluginService, IService )

public:
	IPluginService();

	~IPluginService() override;

public:
	virtual void RegisterPlugin( const String& name ) = 0;

	virtual void UnregisterPlugin( const String& name ) = 0;

};

END_XE_NAMESPACE

#endif // __IPLUGINSERVICE_H__9FB84A70_984B_4C87_B3F1_1C4FE97D7C14
