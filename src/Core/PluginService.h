/*!
 * \file   PluginService.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/07
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PLUGINSERVICE_H__6C1C6402_37FE_4F5E_91ED_4E7BF16C6086
#define __PLUGINSERVICE_H__6C1C6402_37FE_4F5E_91ED_4E7BF16C6086

#include "Type.h"

BEG_XE_NAMESPACE

struct CORE_API PluginDesc
{
	String Name = "";
	XE::uint64 Library = 0;
	String Description = "";
};

class CORE_API PluginService : public IPluginService
{
	OBJECT(PluginService, IPluginService)

private:
	struct Private;

public:
	PluginService();
	
	~PluginService() override;

public:
	void Prepare()override;

	bool Startup() override;
	
	void Update() override;
	
	void Clearup() override;

public:
	void RegisterPlugin( const String & name ) override;
	
	void UnregisterPlugin( const String & name ) override;

private:
	PluginDesc LoadPlugin( const String & name );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __PLUGINSERVICE_H__6C1C6402_37FE_4F5E_91ED_4E7BF16C6086
