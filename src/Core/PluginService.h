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

class CORE_API PluginService : public IPluginService
{
	OBJECT(PluginService, IPluginService)

private:
	struct Private;

public:
	PluginService();
	
	~PluginService() override;

public:
	bool Startup() override;
	
	void Update() override;
	
	void Clearup() override;

public:
	void RegisterPlugin( const std::filesystem::path &val ) override;
	
	void UnregisterPlugin( const String &val ) override;

private:
	void IteratorDirectory( Array < std::filesystem::path >& list, const std::filesystem::path &val ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __PLUGINSERVICE_H__6C1C6402_37FE_4F5E_91ED_4E7BF16C6086
