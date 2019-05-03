/*!
 * \file   CoreFramework.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/26
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COREFRAMEWORK_H__3160BD89_FCC4_4C30_B3D4_D540CB0A51E0
#define __COREFRAMEWORK_H__3160BD89_FCC4_4C30_B3D4_D540CB0A51E0

#include "Type.h"

BEG_XE_NAMESPACE

class CORE_API CoreFramework : public XE::IFramework
{
	OBJECT( CoreFramework, IFramework )

private:
	struct Private;

public:
	CoreFramework();

	~CoreFramework();

public:
	virtual int Exec() override;

public:
	virtual IGUIServicePtr GetGUIService() const override;

	virtual ITimerServicePtr GetTimerService() const override;

	virtual IEventServicePtr GetEventService() const override;

	virtual IInputServicePtr GetInputService() const override;

	virtual IAudioServicePtr GetAudioService() const override;

	virtual IWorldServicePtr GetWorldService() const override;

	virtual IPluginServicePtr GetPluginService() const override;

	virtual IThreadServicePtr GetThreadService() const override;

	virtual IAssetsServicePtr GetAssetsService() const override;

	virtual IConfigServicePtr GetConfigService() const override;

	virtual ILoggerServicePtr GetLoggerService() const override;

	virtual IRenderServicePtr GetRenderService() const override;

	virtual IPhysicsServicePtr GetPhysicsService() const override;

	virtual ILocalizationServicePtr GetLocalizationService() const override;

	virtual IServicePtr GetService( const IMetaClassPtr val ) const override;

	virtual bool RegisterService( IMetaClassPtr val ) override;

	virtual void UnregisterService( IMetaClassPtr val ) override;

public:
	virtual Language GetSystemLanguage() const override;
	
	virtual std::filesystem::path GetPluginPath() const override;

	virtual std::filesystem::path GetAssetsPath() const override;

	virtual std::filesystem::path GetUserDataPath() const override;

	virtual std::filesystem::path GetApplicationPath() const override;

private:
	void Prepare();

	void Startup();

	void Update();

	void Clearup();

private:
	Private * _p;
};

END_XE_NAMESAPCE

#endif // __COREFRAMEWORK_H__3160BD89_FCC4_4C30_B3D4_D540CB0A51E0
