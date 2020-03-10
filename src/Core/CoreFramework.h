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

class XE_API CoreFramework : public XE::IFramework
{
	OBJECT( CoreFramework, IFramework )

private:
	struct Private;

public:
	CoreFramework();

	~CoreFramework();

public:
	int Exec( std::function<void()> val = nullptr );

public:
	ITimerServicePtr GetTimerService() const override;

	IEventServicePtr GetEventService() const override;

	IInputServicePtr GetInputService() const override;

	IAudioServicePtr GetAudioService() const override;

	IWorldServicePtr GetWorldService() const override;

	IThreadServicePtr GetThreadService() const override;

	IAssetsServicePtr GetAssetsService() const override;

	ILoggerServicePtr GetLoggerService() const override;

	IRenderServicePtr GetRenderService() const override;

	IPhysicsServicePtr GetPhysicsService() const override;

	IProfilerServicePtr GetProfilerService() const override;

	ILocalizationServicePtr GetLocalizationService() const override;

	IServicePtr GetService( const IMetaClassPtr & val ) const override;

	bool RegisterService( const IMetaClassPtr & val ) override;

	void UnregisterService( const IMetaClassPtr & val ) override;

public:
	void Exit() override;

	bool IsExit() const override;

	Language GetSystemLanguage() const override;
	
	std::filesystem::path GetModulePath() const override;

	std::filesystem::path GetAssetsPath() const override;

	std::filesystem::path GetUserDataPath() const override;

	std::filesystem::path GetApplicationPath() const override;

protected:
	virtual void Prepare();

	virtual void Startup();

	virtual void Update();

	virtual void Clearup();

protected:
	virtual void LoadModules();

	virtual void LoadServices();

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

#endif // __COREFRAMEWORK_H__3160BD89_FCC4_4C30_B3D4_D540CB0A51E0
