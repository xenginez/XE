/*!
 * \file   IFramework.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57
#define __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API IFramework : public XE::NonCopyable
{
	OBJECT( IFramework )

public:
	IFramework();

	virtual ~IFramework();

public:
	static IFrameworkPtr GetCurrentFramework();

public:
	template< typename T > T GetService() const
	{
		return SP_CAST< typename T::element_type >( GetService( ClassID< typename T::element_type >::Get() ) );
	}

public:
	virtual IGUIServicePtr GetGUIService() const = 0;

	virtual ITimerServicePtr GetTimerService() const = 0;

	virtual IEventServicePtr GetEventService() const = 0;

	virtual IInputServicePtr GetInputService() const = 0;

	virtual IAudioServicePtr GetAudioService() const = 0;

	virtual IWorldServicePtr GetWorldService() const = 0;

	virtual IPluginServicePtr GetPluginService() const = 0;

	virtual IThreadServicePtr GetThreadService() const = 0;

	virtual IAssetsServicePtr GetAssetsService() const = 0;

	virtual IConfigServicePtr GetConfigService() const = 0;

	virtual ILoggerServicePtr GetLoggerService() const = 0;

	virtual IRenderServicePtr GetRenderService() const = 0;

	virtual IPhysicsServicePtr GetPhysicsService() const = 0;

	virtual IProfilerServicePtr GetProfilerService() const = 0;

	virtual ILocalizationServicePtr GetLocalizationService() const = 0;

	virtual IServicePtr GetService( const IMetaClassPtr & val ) const = 0;

	virtual bool RegisterService( const IMetaClassPtr & val ) = 0;

	virtual void UnregisterService( const IMetaClassPtr & val ) = 0;

public:
	virtual void Exit() = 0;

	virtual bool IsExit() const = 0;

	virtual Language GetSystemLanguage() const = 0;

	virtual std::filesystem::path GetPluginPath() const = 0;

	virtual std::filesystem::path GetModulePath() const = 0;

	virtual std::filesystem::path GetAssetsPath() const = 0;

	virtual std::filesystem::path GetUserDataPath() const = 0;

	virtual std::filesystem::path GetApplicationPath() const = 0;

private:
	static IFrameworkPtr _CurrentFramework;
};

END_XE_NAMESPACE

#endif // __IFRAMEWORK_H__AC5510E9_4F81_40B9_A67D_ACE4846F1A57
